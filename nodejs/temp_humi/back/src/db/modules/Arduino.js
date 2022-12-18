const mongoose = require('mongoose');
const { Schema } = mongoose;

const arduinoEntrySchema = new Schema({
    datetime:Date,
    temp: Number,
    humi:Number,
}, {collation:'tracker_temp_humi'});



arduinoEntrySchema.statics.insertData = async function ({datetime, temp, humi}){
    const data = new this({datetime, temp, humi})
    return data.save()
}


module.exports = mongoose.model('tracker_tem_hum', arduinoEntrySchema);

