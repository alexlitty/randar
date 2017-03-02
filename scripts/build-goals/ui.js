(function() {
    var async  = require('async');
    var browserify = require('browserify');
    var exec   = require('child_process').exec;
    var fs     = require('fs');
    var glob   = require('glob');
    var less   = require('less');
    var mkdirp = require('mkdirp');
    var path   = require('path');

    function publish(filename, contents, done) {
        var niceFilename = path.join('bin', 'ui', filename);

        filename = path.normalize(
            path.join(__dirname, '..', '..', niceFilename)
        );

        mkdirp(path.dirname(filename));
        fs.writeFile(filename, contents, function(err) {
            if (!err) {
                console.log('Published', niceFilename);
            }

            done(err);
        });
    }

    var tasks = [
        {
            description : 'html',
            files       : 'ui/**/*.html',

            run: function(filenames, done) {
                publish(
                    'ui.html',
                    fs.readFileSync('ui/html/ui.html'),
                    done
                );
            }
        },

        {
            description : 'javascript',
            files       : 'ui/**/*.js',

            run: function(filenames, done) {
                browserify(
                    filenames.sort(function(a, b) {
                        var aBoot = a.indexOf('boot.js') > -1;
                        var bBoot = b.indexOf('boot.js') > -1;

                        if (aBoot && !bBoot) {
                            return -1;
                        } else if (!aBoot && bBoot) {
                            return 1;
                        } else {
                            return 0;
                        }
                    })
                ).bundle(function(err, output) {
                    (err && done(err)) || publish('ui.js', output, done);
                });
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

    function build(options, done) {
        async.parallel(
            tasks.map(function(task) {
                return function(done) {
                    glob(task.files, { }, function(err, filenames) {
                        (err && done(err)) || task.run(filenames, done);
                    });
                }
            }),

            done
        );
    }

    module.exports = {
        build: build
    };
})();
