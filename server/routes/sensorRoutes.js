const router = require('express').Router();
const SensorController = require('../controllers/SensorController')

router.get('/',SensorController.init)
router.post('/acesso',SensorController.sensorAtivado)

module.exports = router