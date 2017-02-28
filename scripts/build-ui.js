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

    console.log('Publishing:', filename);
    mkdirp(path.dirname(filename));
    fs.writeFile(filename, contents, done);
}

var tasks = [
    {
        run: function(done) {
            glob('ui/**/*.less', { }, function(err, filenames) {
                if (err) {
                    done(err);
                    return;
                }

                var renderings = filenames.map(function(filename) {
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
                });

                async.parallel(renderings, function(err, outputs) {
                    if (err) {
                        done(err);
                    }

                    else {
                        publish("styles.css", outputs.join(''), done);
                    }
                });
            });
        }
    }
];

tasks.forEach(function(task) {
    task.run(function(err) {
        if (err) {
            console.error(err);
        }
    });
});
