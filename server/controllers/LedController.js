const cron = require("cron");
let ledState = false;
const toggleLED = () => {
    ledState = !ledState;
    // Code to control the LED goes here
    console.log(`LED state: ${ledState}`);
};
const job = new cron.CronJob('*/1 * * * * *', toggleLED);

job.start();

module.exports= class ProductsController{
    static async init(req,res){
        res.send({message: 'funcionando'})
    }
    static async ledState(req,res){
        res.json({ state: ledState });
        
    }
}