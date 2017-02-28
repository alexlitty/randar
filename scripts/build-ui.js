var async  = require('async');
var exec   = require('child_process').exec;
var fs     = require('fs');
var glob   = require('glob');
var less   = require('less');
var mkdirp = require('mkdirp');
var path   = require('path');

function publish(filename, contents, done) {
    filename = path.normalize(
        path.join(__dirname, '..', 'bin', 'ui', filename)
    );

    mkdirp(path.dirname(filename));
    fs.writeFile(filename, contents, done);
}

var tasks = [
    {
        description : 'javascript',
        files       : 'ui/**/*.js',

        run: function(filenames, done) {
            publish(
                'ui.js',
                filenames.map(function(filename) {
                    return fs.readFileSync(filename);
                }).join(''),
                done
            );
        }
    },

    {
        description : 'styles',
        files       : 'ui/**/*.less',

        run: function(filenames, done) {
            async.parallel(
                filenames.map(function(filename) {
                    return function(rendered) {
                        less.render(
                            fs.readFileSync(filename).toString(),
                            {
                                filename : filename,
                                compress : true
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

function build() {
    async.parallel(
        tasks.map(function(task) {
            return function(done) {
                glob(task.files, { }, function(err, filenames) {
                    (err && done(err)) || task.run(filenames, done);
                });
            }
        }),

        function(err) {
            if (err) {
                console.error(err);
            }
        }
    );
}

build();
