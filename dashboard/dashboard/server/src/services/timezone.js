const ServiceInterfaces = require('./interface');
const axios             = require('axios');
const TimeService       = new ServiceInterfaces.Service("Time", "");

class TimeWidget extends ServiceInterfaces.Widget {
    async callThisWidget(client, param) {
        try {
            const request = await axios.get('https://www.timeapi.io/api/TimeZone/ip?ipAddress=' + param)
            const newData = new Date(request.data.currentLocalTime);
            const FormatedDate = "" + newData.getDate() + '/' + newData.getMonth() + '/' + newData.getFullYear() + ' ' + newData.getHours() + ':' + newData.getMinutes() + ':' + newData.getSeconds()
            return (`<div class="mt-2"> ${FormatedDate} </div`);
        } catch (error) {
            return ("<div>IP not found</div>")
        }
    }
}

const timeWidget = new TimeWidget("Ip's current time", "The current time of an ipv4 location", "IPv4", "STRING");

TimeService.addWidget(timeWidget);

module.exports = TimeService;