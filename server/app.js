const express = require('express')
const cors = require('cors')
const LedRoutes = require('./routes/ledRoutes')
const app = express();
const port = 3001
app.use('/led',LedRoutes)
app.listen(port,()=>{
    console.log(`Servidor rodando na porta: ${port}`)
})