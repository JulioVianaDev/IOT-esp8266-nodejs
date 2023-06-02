const mongoose = require('mongoose');

const sensorSchema = new mongoose.Schema({
  nome: String,
  distancia: Number,
  createdAt: { type: Date, default: Date.now }
});

const Sensor = mongoose.model('Sensor', sensorSchema);

module.exports = Sensor;