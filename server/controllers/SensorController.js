
module.exports= class ProductsController{
    static async init(req,res){
        res.send({message: 'funcionando'})
    }
    static async sensorAtivado(req,res){
        res.json({})
    }
}