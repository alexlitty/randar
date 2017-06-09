require('../init');
const less = require('less');

function publish(filename, contents, done) {
    const filepath = path.join(RANDAR_PATH.UI, 'browser-client', 'build', filename);

    mkdirp(path.dirname(filepath));
    fs.writeFile(filepath, contents, function(err) {
        if (!err) {
            console.log('Published', filepath);
        }

        done(err);
    });
}

var tasks = [
    {
        description : 'html',
        files       : 'modules/ui/browser-client/html/**/*.html',

        run: function(filenames, done) {
            filenames.forEach(filename => {
                publish(
                    path.basename(filename),
                    fs.readFileSync(filename),
                    function() { }
                );
            });

            done();
        }
    },

    {
        description : 'less',
        files       : 'modules/ui/browser-client/less/**/*.less',

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
                    if (err) {
                        done(err);
                    } else {
                        publish(
                            'ui.css',
                            outputs.join(''),
                            done
                        );
                    }
                }
            );
        }
    }
];

function build(options, done) {
    async.parallel(
        tasks.map(function(task) {
            let search = path.join(RANDAR_PATH.ROOT, task.files);

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
