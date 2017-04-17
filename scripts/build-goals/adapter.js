const async  = require('async');
const fs     = require('fs');
const glob   = require('glob');
const less   = require('less');
const mkdirp = require('mkdirp');
const os     = require('os');
const path   = require('path');
const spawn  = require('child_process').spawn;

const rootDir          = path.normalize(path.join(__dirname, '..', '..'));
const adapterDir       = path.join(rootDir, 'modules', 'adapter');
const engineDir        = path.join(rootDir, 'modules', 'engine');
const engineIncludeDir = path.join(engineDir, 'include', 'randar');
const engineSrcDir     = path.join(engineDir, 'src');

function publish(filename, contents, sensitive, done) {
    const filepath = path.normalize(path.join(adapterDir, filename));

    function write() {
        mkdirp(path.dirname(filepath));
        fs.writeFile(filepath, contents, (err) => {
            if (!err) {
                console.log('Published', filepath);
            }
            done(err);
        });
    }

    /**
     * If this file is sensitive to updates, only publish it when its
     * contents have changed.
     *
     * For example, node-gyp will perform an unconditional full compilation
     * if the binding file has changed, regardless if a partial compilation
     * is logically possible.
     */
    if (sensitive) {
        fs.readFile(filepath, (err, data) => {
            if (data && data.toString() == contents) {
                done();
            } else {
                write();
            }
        });
    }

    else {
        write();
    }
}

function run(command, args, successMessage, done) {
    const program = spawn(command, args, {
        cwd   : adapterDir,
        stdio : 'inherit'
    });

    program.on('close', (err) => {
        if (!err) {
            console.log(successMessage);
        }
        done(err);
    });
}

function build(options, done) {
    var swigContents = '';
    function addSwigLines(lines) {
        swigContents += lines.map(line => line + ';\n').join('');
    }

    const swigFilename   = 'adapter.i';
    const wrapFilename   = 'adapter.cxx';
    const gypFilename    = 'binding.gyp';
    const moduleFilename = 'build/adapter.node';

    const headers = glob.sync(path.join(engineIncludeDir, '**', '*.hpp'));
    const sources = glob.sync(path.join(engineSrcDir, '**', '*.cpp'));

    headerContents = headers.reduce((result, filename) => {
        result[filename] = fs.readFileSync(filename).toString();
        return result;
    }, { });

    // Sort headers by dependencies required. If we provide these headers to
    // swig unsorted it will still create the c++ wrapper, but it can't confirm
    // all dependencies have been met -- so we'll see a bunch of scary warnings.
    var availableHeaders = headers.slice();
    var circularHeaders  = [];
    var sortedHeaders    = [];
    while (availableHeaders.length) {
        var key = availableHeaders.findIndex((header) => {
            return availableHeaders.every((otherHeader) => {
                return headerContents[header].indexOf(
                    otherHeader.replace(engineIncludeDir, '')
                ) == -1;
            });
        });

        // If we can't find a header without satisfied dependencies, we've
        // encountered a circular dependency. Swig 
        if (key == -1) {
            key = 0;
            circularHeaders.push(availableHeaders[key]);
        }
        sortedHeaders = sortedHeaders.concat(
            availableHeaders.splice(key, 1)
        );
    }

    if (circularHeaders.length) {
        console.warn('! Detected circular dependencies in');
        circularHeaders.forEach((header) => console.warn('! -', header));
        console.warn('! Build will continue but may fail');
    }

    // Start our swig file with a declaration of the system architecture. This
    // is used to provide the correct typemaps for fixed width integer types,
    // like uint32_t.
    //
    // Swig defaults to 32-bit mappings. If this is a 64-bit system, we must
    // define SWIGWORDSIZE64 to request the 64-bit mappings.
    if (os.arch() == 'x64') {
        addSwigLines(['#define SWIGWORDSIZE64 true']);
    }

    // %naturalvar requests a more intuitive interface with class members.
    addSwigLines(['%naturalvar']);

    // Ignore operators that don't translate well to node code. These operators
    // could be explicitly renamed if we end up needing them.
    addSwigLines([
        '=',
        '+=',
        '-=',
        '*=',
        '/=',
        '%=',
        '+',
        '-',
        '*',
        '/',
        '%',
        '!',
        '==',
        '!=',
        '<',
        '<=',
        '>',
        '>=',
        '<<',
        '>>',
        ' bool',
        ' uint8_t',
        ' uint32_t',
        ' float',
        ' std::string',
        ' std::mutex&',
        ' GLuint',
        ' GLuint*',
        ' GLuint&',
        ' Model&',
        ' btVector3',
        ' btQuaternion',
        ' btTransform'
    ].map(x => `%ignore operator${x}`));

    // Include common typemappings.
    addSwigLines([
        'complex.i',
        'carrays.i',
        'stdint.i',

        'typemaps/implicit.swg',

        'javascript/v8/typemaps.i',
        'javascript/v8/std_common.i',
        'javascript/v8/std_string.i',
        'javascript/v8/std_except.i',
        'javascript/v8/std_complex.i',

        'javascript/v8/std_pair.i',
        'javascript/v8/std_deque.i',
        './std_map.i',
        './std_vector.i',

        'javascripttypemaps.swg',
        'javascriptcode.swg',
        'javascriptcomplex.swg',
        'javascriptfragments.swg',
        'javascripthelpers.swg',
        'javascriptinit.swg',
        'javascriptkw.swg',
        'javascriptprimtypes.swg',
        'javascriptruntime.swg',
        'javascriptstrings.swg',

        'arrays_javascript.i'
    ].map(x => `%include "${x}"`));

    // Define our wrapping module.
    const includes = sortedHeaders.map(filename => `#include "${filename}"`);
    addSwigLines(
        ['%module adapter', '%{'].concat(includes).concat(['%}'])
        .concat(includes.map(line => line.replace('#', '%')))
    );

    // Describe the complete compilation of the engine node module.
    const gypBinding = {
        targets: [{
            target_name: 'adapter',

            sources: sources.map((filename) => {
                return filename.replace(
                    engineDir,
                    path.join('..', 'engine')
                )
            }).concat([wrapFilename]),

            include_dirs: [
                'modules/engine/include',
                'modules/engine/include/bullet3'
            ].map((dir) => path.normalize(path.join(rootDir, dir))),

            libraries: [
                '-lX11',
                '-lXxf86vm',
                '-pthread',
                '-lXi',
                '-lXrandr',
                '-lGL',
                '-lGLEW',
                '-lBulletDynamics',
                '-lBulletCollision',
                '-lLinearMath',
                '-lpng'
            ],

            // Disable warnings.
            cflags: ['-w'],

            // Enable exceptions.
            'cflags!'    : ['-fno-exceptions'],
            'cflags_cc!' : ['-fno-exceptions']
        }]
    };

    async.series([
        (next) => publish(swigFilename, swigContents, false, next),
        (next) => publish(
            gypFilename, JSON.stringify(gypBinding, null, '    '), true, next
        ),

        // Creates a C++ file that wraps our engine within V8-friendly code.
        (next) => run(
            'swig',
            [
                '-c++',
                '-javascript',
                '-node',
                '-o', wrapFilename,
                swigFilename
            ],
            `Published ${path.join(adapterDir, wrapFilename)}`,
            next
        ),

        // Initiate a rebuild if desired.
        (next) => {
            if (!options.rebuild) {
                next();
            } else {
                run('node-gyp', ['clean'], 'Full rebuild initiated', next)
            }
        },

        // Configure compilation if required.
        (next) => {
            if (fs.existsSync(path.join(adapterDir, 'build'))) {
                next();
            } else {
                run('node-gyp', ['configure'], 'Ready to compile adapter', next);
            }
        },

        // Creates an importable node module for our engine.
        (next) => run(
            'node-gyp',
            [
                'build',
                '-j', '4'
            ],
            `Published ${path.join(adapterDir, moduleFilename)}`,
            next
        )
    ], done);
}

module.exports = {
    build: build
};