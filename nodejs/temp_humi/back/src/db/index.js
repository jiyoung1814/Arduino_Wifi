const mongoose = require('mongoose');

// const {
//     MONGO_URI: mongoURI
// } = process.env;

mongoURI = 'mongodb://localhost:27017/temp';

module.exports = (function() {
    mongoose.Promise = global.Promise;

    return{
        connect() {
            return mongoose.connect(mongoURI, {
                useNewUrlParser: true,
                useUnifiedTopology: true
            }).then(
                () => {
                    console.log('Successfully connected to mongodb');
                }
            ).catch(e => {
                console.error(e);
            });
        }
    };
})();