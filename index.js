const FFMS2 = require('./build/Release/nodeffms2.node')

module.exports = {
    FFMS2,
    open: (file) => {
        const self = new FFMS2(file);
        self.open(file);
    }
}