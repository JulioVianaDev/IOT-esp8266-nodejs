const router = require('express').Router();
const LedController = require('../controllers/LedController');
router.get('/',LedController.init)

module.exports = router