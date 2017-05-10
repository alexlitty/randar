require('../init');
const progress = require('progress');

function download(remoteFilename, localFilename, cb) {
    const remoteUrl   = url.parse(remoteFilename);
    const downloader  = remoteUrl.protocol === 'https:' ? https.get : http.get;
    const localStream = fs.createWriteStream(localFilename);

    const request = downloader(remoteUrl, (response) => {
        if (response.statusCode !== 200) {
            cb(new Error(`${remoteUrl.href}: HTTP ${response.statusCode}`));
            return;
        }

        response.pipe(localStream);

        let barFormat  = ':rate/bps - :percent - :etas remaining';
        let barOptions = {
            complete   : '=',
            incomplete : ' ',
            width      : 32,
            total      : Infinity
        };

        if (response.headers['content-length']) {
            barFormat = '[:bar] ' + barFormat;
            barOptions.total = parseInt(response.headers['content-length']);
        }

        const bar = new progress(barFormat, barOptions);
        bar.interrupt(`Fetching ${remoteFilename} into ${localFilename}`);

        response.on('data', (data) => bar.tick(data.length));
        response.on('end',  () => {
            cb();
        });
    });

    request.on('error', (error) => { 
        cb(error);
    });
}

module.exports = download;
