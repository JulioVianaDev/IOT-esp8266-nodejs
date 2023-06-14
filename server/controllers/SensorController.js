const Sensor = require('../models/sensor')
module.exports= class ProductsController{
    static async init(req,res){
        res.send({message: 'funcionando'})
    }
    static async sensorAtivado(req,res){
        const {nome,distancia} = req.body
        const sensor = new Sensor({
           nome,
           distancia
        })
        try {
          await sensor.save()
          res.status(201).json({message: "Sensor enviado com sucesso",sensor: sensor})
        } catch (error) {
          res.status(500).json({message: "Ocorreu um erro ao cadastrar o dado do sensor, tente novamente mais tarde"})
        }
    } 
}