// const Arduino = require('../../db/modules/Arduino2')
// const Arduino = require('db/modules/Arduino')

// const moment = require('moment')
// const Arduino = require('db/modules/Arduino')
// require('moment-timezone')
// moment.tz.setDefault("Asia/Seoul")
const MongoClient = require('mongodb').MongoClient;
const mongoURI = 'mongodb://localhost:27017';
var data;


exports.root = async ctx => {

    setTimeout(function()){
        
    }

    try{
        MongoClient.connect(mongoURI, function(err, client) {
            if (err) throw err;
            // mydb 라는 데이터 베이스를 사용
            const dbMydb = client.db('temp');
            
            const collection = dbMydb.collection('tracker_tem_hums');
            // console.log(collection)
            // dbMydb.collection('tracker_temp_hums').find().sort({'_id':-1}).limit(1).toArray((err, rslt) =>{
            //     // console.log( '${err}    ${rslt}');
            //     console.log(rslt);
            // })

            // collection.find().toArray((err, items) => {
            //     console.log(items)
            // })
            collection.find().sort({'_id':-1}).limit(1).toArray((err, items) => {
                console.log(items)
                data = items;
            })
          });

          
        
    }catch(e){
        ctx.throw(e,500);
    }

    ctx.body = {data};
}



