const Arduino = require('../../db/modules/Arduino')
// const Arduino = require('db/modules/Arduino')

// const moment = require('moment')
// const Arduino = require('db/modules/Arduino')
// require('moment-timezone')
// moment.tz.setDefault("Asia/Seoul")


exports.root = async ctx => {
    const{datetime, temp, humi} = ctx.request.body
    console.log(`datetime:${datetime}, temp:${temp}, humi:${humi}`);

    let post = null
    try{
        post = await Arduino.insertData({datetime,temp,humi})
        
    }catch(e){
        ctx.throw(e,500)
    }
    ctx.body = {result:1}
}

// exports.result = async ctx => {
//     const lastest = await Arduino.find().sort({'datetime': -1}).limit(1);  //최신 날짜 가지고 오기
//     ctx.body = "ok";
// }
