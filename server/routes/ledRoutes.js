const router = require('express').Router();
const LedController = require('../controllers/LedController');

router.get('/',LedController.init)
router.get('/state-led',LedController.ledState)

module.exports = router