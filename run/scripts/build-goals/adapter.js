require('../init');

function publish(filename, contents, sensitive, done) {
    const filepath = path.normalize(path.join(RANDAR_PATH.ADAPTER, filename));

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
        cwd   : RANDAR_PATH.ADAPTER,
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
    const gypFilename    = 'binding.gyp';
    const moduleFilename = 'build/adapter.node';

    let sources = glob.sync(path.join(RANDAR_PATH.ADAPTER_SOURCE, '**', '*.cpp'));
    sources = sources.concat(glob.sync(path.join(RANDAR_PATH.ENGINE_SOURCE, '**', '*.cpp')));

    // Describe the complete compilation of the engine node module.
    const gypBinding = {
        targets: [{
            target_name: 'adapter',

            // Source paths must be relative to binding.gyp.
            sources: sources.map((filename) => {
                let result = filename.replace(
                    RANDAR_PATH.ADAPTER,
                    path.join('..', 'adapter')
                );

                result = result.replace(
                    RANDAR_PATH.ENGINE,
                    path.join('..', 'engine')
                );

                return result;
            }),

            include_dirs: [
                'modules/engine/include',
                'modules/engine/include/bullet3',
                'modules/adapter/include'
            ].map((dir) => path.normalize(path.join(RANDAR_PATH.ROOT, dir))),

            libraries: [
                '-lstdc++',
                '-lX11',
                '-lXxf86vm',
                '-pthread',
                '-lGL',
                '-lGLEW',
                '-lBulletDynamics',
                '-lBulletCollision',
                '-lLinearMath',
                '-lpng'
            ],

            cflags: [
                '-std=c++11'
            ],

            // Enable exceptions.
            'cflags!'    : ['-fno-exceptions'],
            'cflags_cc!' : ['-fno-exceptions']
        }]
    };

    async.series([
        (next) => publish(
            gypFilename, JSON.stringify(gypBinding, null, '    '), true, next
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
            if (fs.existsSync(path.join(RANDAR_PATH.ADAPTER, 'build'))) {
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
            `Published ${path.join(RANDAR_PATH.ADAPTER, moduleFilename)}`,
            next
        )
    ], done);
}

module.exports = {
    build: build
};
