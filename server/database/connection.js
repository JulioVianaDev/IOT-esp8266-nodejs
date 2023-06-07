const mongoose = require("mongoose")

const MONGO_URI = process.env.MONGO_URI;

const connect = ()=>{
  mongoose.connect(MONGO_URI)
  const connection = mongoose.connection;
  
  connection.on("error",()=>{
    console.log("Erro ao conectar com o mongoDB")
  })
  
  connection.on("open",()=>{
    console.log("Conectado com o mongoDB")
  })
}
connect()