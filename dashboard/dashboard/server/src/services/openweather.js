const ServiceInterfaces = require('./interface');
const config            = require('../config');
const weather           = require('openweather-apis');

const weatherService     = new ServiceInterfaces.Service("Weather", "");

class WWidget extends ServiceInterfaces.Widget {
    async callThisWidget(client, param) {
        try {
            client.setCity(param);
            const wth = await new Promise((resolve, reject) => {
                client.getSmartJSON((err, smart) => {
                    if (err) {
                        reject(err);
                    } else {
                        resolve(smart);
                    }
                })
            })
            let response = "<div class='mt-2'>City's informations:"
            for (const param in wth) {
                if (param !== 'weathercode')
                response += `<div class="mt-2"> ${param} : ${wth[param]} </div>`
            }
            response += "</div>"
            return (response)
        } catch (error) {
            return ("<div>city not found</div>")
        }
    }
}

const weatherWidget = new WWidget("City's weather", "The current weather of a city", "city", "STRING");

weatherService.addWidget(weatherWidget);

weather.setLang('en');
weather.setAPPID(config.WEATHER_API_KEY);
weatherService.setClient(weather);

module.exports = weatherService;