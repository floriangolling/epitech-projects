const ServiceInterfaces = require('./interface');
const axios             = require('axios');
const CryptoService     = new ServiceInterfaces.Service("Crypto", "");

class CryptoWiget extends ServiceInterfaces.Widget {
    async callThisWidget(client, param) {
        try {
            const request = await axios.get(`https://data.messari.io/api/v1/assets/${param}/metrics/market-data`)
            return (`<div class="mt-2"> Dollar actual price : 
            <div class="mt-2"> ${request.data.data.market_data.price_usd}</div> </div>`);
        } catch (error) {
            return ("<div>symbol not found</div>")
        }
    }
}

const crypto = new CryptoWiget("Crypto's value", "The current USD value of crypto", "symbol", "STRING");

CryptoService.addWidget(crypto);

module.exports = CryptoService;