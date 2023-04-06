const ServiceInterfaces         = require('./interface');
const config                    = require('../config');
const { default: TwitchApi }    = require('node-twitch');
const axios                     = require('axios');

const client = new TwitchApi({
    client_id: config.TWITCH_CLIENT_ID,
    client_secret: config.TWITCH_SECRET,
    scopes: ['user_read'],
    redirect_uri: config.TWITCH_REDIRECT_URI
});

async function refreshToken(client, code) {
    try {
        const params = new URLSearchParams();
        const config = {
            headers: {
                'Content-type': 'application/x-www-form-urlencoded'
            }
        }
        params.append('grant_type', 'refresh_token');
        params.append('client_id', client.client_id);
        params.append('client_secret', client.client_secret);
        params.append('refresh_token', code);
        const request = await axios.post(`https://id.twitch.tv/oauth2/token`,params, config);
        return (request.data.access_token);
    } catch (error) {
        console.log(error);
        return (error);
    }
}


const TwitchService = new ServiceInterfaces.Service("Twitch", "");

class followWidget extends ServiceInterfaces.Widget {
    async callThisWidget(client, param, code) {
        try {
            if (!code || code === undefined || code === null) {
                return (`<div class="mt-5"> Please login to twitch on your profile to access to this widget ^^ </div>`);
            }
            const access_token = await refreshToken(client, code);
            client.access_token = access_token;
            const user = await client.getUsers(param);
            if (!user.data[0]) {
                return (`<div class="mt-3"> User not found </div>`);
            }
            const follows = await client.getFollows({to_id: user.data[0].id})
            return(`<div class="mt-3"> Current followers:</div> <div class="mt-2"> ${follows.total} </div>`);
        } catch (error) {
            console.log(error);
            return (`<div class="mt-3"> An error occured </div>`);
        }
    }
}

class clipsWidgets extends ServiceInterfaces.Widget {
    async callThisWidget(client, param, code) {
        try {
            if (!code || code === undefined || code === null) {
                return (`<div class="mt-5"> Please login to twitch on your profile to access to this widget ^^ </div>`);
            }
            const access_token = await refreshToken(client, code);
            client.access_token = access_token;
            const user = await client.getUsers(param);
            if (!user.data[0]) {
                return (`<div class="mt-3"> User not found </div>`);
            }            
            const clips = await client.getClips({broadcaster_id: user.data[0].id });
            let response = "<div class='mt-3'>"
            for (const clip of clips.data) {
                response += `<div class='m-6 box'>`
                response += `<div class='mt-1'> Clip title: </div>`
                response += `<div class='mt-1'> ${clip.title} </div>`
                response += `<div class='mt-1'> Clip views: </div>`
                response += `<div class='mt-1'> ${clip.view_count} </div>`
                response += `<div class='mt-1'> <form action="${clip.url}" method="get" target="_blank"> <button class="button is-info" type="submit"> Watch it </button> </form> </div>`
                response += "</div>"
            }
            response += "</div>"
            return response;
        } catch (error) {
            return (`<div class="mt-3"> An error occured </div>`);
        }
    }
}


const followW = new followWidget("Follows", "The chosen user's follows number", "account", "STRING");
const clipsW = new clipsWidgets("Clips", "The chosen user's best clips", "account", "STRING");


TwitchService.addWidget(followW);
TwitchService.addWidget(clipsW);
TwitchService.setClient(client);

module.exports = TwitchService;