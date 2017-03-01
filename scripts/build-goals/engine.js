(function() {
    var child_process = require('child_process');

    function build(options, done) {
        if (process.platform === 'linux') {
            var args = ['linux64', '-j', '3'];
            if (options.full) {
                args.push('-B');
            }
            
            var make = child_process.spawn('make', args);
            make.stdout.on('data', function(data) {
                console.log(data.toString());
            });

            make.stderr.on('data', function(data) {
                console.log(data.toString());
            });

            make.on('error', function(error) {
                done(error);
            });

            make.on('close', function(code) {
                done();
            });
        }

        else {
            done('Engine must be built manually on ' + process.platform);
        }
    }

    module.exports = {
        build: build
    };
})();
