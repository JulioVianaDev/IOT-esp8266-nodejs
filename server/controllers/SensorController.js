
module.exports= class ProductsController{
    static async init(req,res){
        res.send({message: 'funcionando'})
    }
    static async sensorAtivado(req,res){
        const {nome} = req.body
        console.log(nome)
        res.json({nome})
    } 
}