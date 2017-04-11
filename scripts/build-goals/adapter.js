const async  = require('async');
const fs     = require('fs');
const glob   = require('glob');
const less   = require('less');
const mkdirp = require('mkdirp');
const path   = require('path');

const rootDir          = path.normalize(path.join(__dirname, '..', '..'));
const adapterDir       = path.join(rootDir, 'modules', 'adapter');
const engineDir        = path.join(rootDir, 'modules', 'engine');
const engineIncludeDir = path.join(engineDir, 'include', 'randar');
const engineSrcDir     = path.join(engineDir, 'src');

function publish(filename, contents) {
    const filepath = path.normalize(path.join(adapterDir, filename));

    mkdirp(path.dirname(filepath));
    fs.writeFileSync(filepath, contents);

    console.log('Published', filepath);
}

function build(options, done) {
    const swigFilename = 'engine.i';
    const wrapFilename = 'engine_wrap.cxx';
    const gypFilename  = 'binding.gyp';

    const headers = glob.sync(path.join(engineIncludeDir, '**', '*.hpp'));
    const sources = glob.sync(path.join(engineSrcDir, '**', '*.cpp'));

    headerContents = headers.reduce((result, filename) => {
        result[filename] = fs.readFileSync(filename).toString();
        return result;
    }, { });

    // Sort headers by dependencies required.
    var availableHeaders = headers.slice();
    var sortedHeaders    = [];
    while (availableHeaders.length) {
        var key = availableHeaders.findIndex((header) => {
            return availableHeaders.every((otherHeader) => {
                return headerContents[header].indexOf(
                    otherHeader.replace(engineIncludeDir, '')
                ) == -1;
            });
        });

        if (key == -1) {
            key = 0;
        }
        sortedHeaders = sortedHeaders.concat(
            availableHeaders.splice(key, 1)
        );
    }

    // Start the swig file with the main module declaration.
    var swigContents = [
        '%module engine',
        '%{',
    ].concat(sortedHeaders.map((filename) => {
        return '#include "' + filename + '"';
    })).concat([
        '%}'
    ]).concat(sortedHeaders.map((filename) => {
        return '%import "' + filename + '"';
    })).join('\n');

    // Publish the swig file.
    publish(swigFilename, swigContents);

    // Define the final node module being built.
    publish(gypFilename, JSON.stringify({
        targets: [{
            target_name : 'engine',
            sources     : sources.map((filename) => {
                return filename.replace(
                    engineDir,
                    path.join('..', 'engine')
                )
            }).concat([wrapFilename]),

            cflags: [
                // Disable warnings.
                '-w'
            ],

            // Enable exceptions.
            'cflags!'    : ['-fno-exceptions'],
            'cflags_cc!' : ['-fno-exceptions']
        }]
    }, null, '    '));
}

module.exports = {
    build: build
};
