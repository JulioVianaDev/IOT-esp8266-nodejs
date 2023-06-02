const mongoose = require("mongoose")

const dbUser = process.env.DB_USER;
const dbPassword = process.env.DB_PASS;

const connect = ()=>{
  mongoose.connect(`mongodb+srv://${dbUser}:${dbPassword}@iot-professor.wistnqo.mongodb.net/?retryWrites=true&w=majority`)
  const connection = mongoose.connection;
  
  connection.on("error",()=>{
    console.log("Erro ao conectar com o mongoDB")
  })
  
  connection.on("open",()=>{
    console.log("Conectado com o mongoDB")
  })
}
connect()