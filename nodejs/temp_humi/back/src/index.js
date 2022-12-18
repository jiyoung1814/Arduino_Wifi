require('dotenv').config();
// const {
//     PORT: port,
//     MONGO_URI: mongoURI
// } = process.env;

port = 8000;

const Koa = require('koa');
const Router = require('koa-router');
const bodyParser = require('koa-bodyparser');
const fs = require('fs');

const db = require('./db');
const api = require('./api');

db.connect(); //db연결

const app = new Koa();

app.use(bodyParser());
  
const router = new Router();
router.use('/api', api.routes());// api 라우트를 /api 경로 하위 라우트로 설정


router.get('/',(ctx,next) => {
    const rawContent = fs.readFileSync('./view/index.ejs').toString('utf-8');
    ctx.body = rawContent;
    // ctx.body = '<h1>함체 온도 센싱</h1>'
    // ctx.body = port
}) 


app.use(router.routes());
app.use(router.allowedMethods());

app.listen(port, () => {
    console.log(`server is listening to port ${port}`);
});

