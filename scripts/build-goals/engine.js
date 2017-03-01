(function() {
    function build() {
        if (process.platform === 'linux' || process.platform === 'darwin') {

        }

        else {
            console.log('Engine must be built manually on', process.platform);
        }
    }

    module.exports = {
        build: build
    };
})();
