const leagueService  = require('./league');
const weatherService = require('./openweather')
const TimeService    = require('./timezone');
const cryptoService  = require('./crypto');
const twitchService  = require('./twitch');

module.exports = [
    leagueService,
    weatherService,
    TimeService,
    cryptoService,
    twitchService
]