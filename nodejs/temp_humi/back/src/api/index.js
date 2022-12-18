const Router = require('koa-router');
const tracker = require('./tracker')

const api = new Router();


api.use('/tracker',tracker.routes());
// api.use('/showtrackerresult',tracker.routes());
// api.get('/movie', (ctx, next) => {
//     ctx.body = 'GET ' + ctx.request.path;
// });

module.exports = api;