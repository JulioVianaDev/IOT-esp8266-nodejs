const express = require('express');
const cors = require('cors');
const app = express();
const port = 3000;
const LedRouter = require('./routes/ledRoutes')
const SensorRouter = require('./routes/sensorRoutes')
require('dotenv').config()
app.use(cors());
app.use(express.json())
app.use("/led",LedRouter);
app.use("/sensor",SensorRouter);


app.get('/api', (req, res) => {
  const response = { message: 'success', led: true };
  res.json(response);
});

app.listen(port, () => {
  console.log(`Server is running on http://localhost:${port}`);
});

require("./database/connection")