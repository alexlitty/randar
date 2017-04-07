const async  = require('async');
const fs     = require('fs');
const glob   = require('glob');
const less   = require('less');
const mkdirp = require('mkdirp');
const path   = require('path');

function publish(filename, contents, done) {
    filepath = path.normalize(
        path.join(__dirname, '..', '..', 'modules', 'ui', 'build', filename)
    );

    mkdirp(path.dirname(filepath));
    fs.writeFile(filepath, contents, function(err) {
        if (!err) {
            console.log('Published', filename);
        }

        done(err);
    });
}

var tasks = [
    {
        description : 'html',
        files       : 'modules/ui/html/**/*.html',

        run: function(filenames, done) {
            filenames.forEach(filename => {
                publish(
                    path.basename(filename),
                    fs.readFileSync(filename),
                    done
                );
            });
        }
    },

    {
        description : 'less',
        files       : 'modules/ui/less/**/*.less',

        run: function(filenames, done) {
            async.parallel(
                filenames.map(function(filename) {
                    return function(rendered) {
                        less.render(
                            fs.readFileSync(filename).toString(),
                            {
                                filename   : filename,
                                compress   : true,
                                strictMath : true
                            },
                            function (err, output) {
                                rendered(err, output && output.css);
                            }
                        );
                    }
                }),

                function(err, outputs) {
                    (err && done(err)) || publish(
                        'ui.css',
                        outputs.join(''),
                        done
                    );
                }
            );
        }
    }
];

function build(options, done) {
    async.parallel(
        tasks.map(function(task) {
            let search = path.join(__dirname, '..', '..', task.files);

            return function(done) {
                glob(search, { }, function(err, filenames) {
                    if (err) {
                        done(err);
                    } else {
                        task.run(filenames, done);
                    }
                });
            }
        }),

        done
    );
}

module.exports = {
    build: build
};
