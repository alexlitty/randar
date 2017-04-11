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
    const headers = glob.sync(path.join(engineIncludeDir, '**', '*.hpp'));
    const sources = glob.sync(path.join(engineSrcDir, '**', '*.cpp'));

    publish('binding.gyp', JSON.stringify({
        targets: [{
            target_name : 'engine',
            sources     : sources.map((filename) => {
                return filename.replace(
                    engineDir,
                    path.join('..', 'engine')
                )
            }),

            cflags: [
                // Disable warnings.
                '-w',

                // Multithread make.
                '-j 2'
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
