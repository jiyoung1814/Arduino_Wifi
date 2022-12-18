const Router = require('koa-router');
const trackerCtrl = require('./tracker.ctrl');
const trackerData = require('./tracker.data')
const tracker = new Router();

tracker.post('/',trackerCtrl.root);
tracker.get('/data',trackerData.root);

// tracker.get('/result', trackerCtrl.result);
// tracker.get('/getTempHumi',trackerCtrl.getTempHumi);

module.exports = tracker;