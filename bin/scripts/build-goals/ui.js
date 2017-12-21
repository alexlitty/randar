require('../init');
const less = require('less');

function publish(filename, contents, done) {
    const filepath = path.join(RANDAR_PATH.UI, 'build', filename);

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
        files       : 'modules/ui/html/**/*.html',

        run: function(filenames, done) {
            filenames.forEach(filename => {
                let template = `
                    <html>
                        <head>
                            <link href="ui.css" rel="stylesheet">
                            <script src="../js/boot.js"></script>
                        </head>
                        <body>
                            <main id="randar">
                                {CONTENT}
                            </main>
                        </body>
                    </html>
                `;

                publish(
                    path.basename(filename),
                    template.replace('{CONTENT}', fs.readFileSync(filename)),
                    function() { }
                );
            });

            done();
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
