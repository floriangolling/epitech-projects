/*
    If you dont use the server on docker, please remove this comments and have the .env in the root of the server.
*/

//import dotenv from 'dotenv'
//dotenv.config();

export default {
    PORT: parseInt(process.env.APP_PORT, 10) as number || 8080, 
    HOST: process.env.APP_HOST as string || 'http://localhost',
    APP_DOMAIN_NAME: process.env.APP_DOMAIN_NAME || 'com.area.app',

    DB_USER: process.env.POSTGRES_USER || '',
    DB_PASSWORD: process.env.POSTGRES_PASSWORD || '',
    DB_PORT: parseInt(process.env.POSTGRES_PORT, 10) as number|| 5432,
    DB_NAME: process.env.POSTGRES_SCHEMA || '',
    DB_HOST: process.env.POSTGRES_HOST || '',
    ERASE_DB: process.env.ERASE_DB || "false",

    JWT_SECRET: process.env.JWT_SECRET || 'secret',

    TWITCH_CLIENT_ID: process.env.TWITCH_CLIENT_ID || 'token',
    TWITCH_CLIENT_SECRET: process.env.TWITCH_CLIENT_SECRET || 'token',
    TWITCH_REDIRECT_URI: process.env.TWITCH_REDIRECT_URI || 'redirect_uri',

    TWITTER_REDIRECT_URI: process.env.TWITTER_REDIRECT_URI || '',
    TWITTER_CLIENT_ID: process.env.TWITTER_CLIENT_ID || '',
    TWITTER_CLIENT_SECRET: process.env.TWITTER_CLIENT_SECRET || '',

    GITHUB_REDIRECT_URI: process.env.GITHUB_REDIRECT_URI || '',
    GITHUB_CLIENT_ID: process.env.GITHUB_CLIENT_ID || '',
    GITHUB_CLIENT_SECRET: process.env.GITHUB_CLIENT_SECRET || '',
    GITHUB_STATE: process.env.GITHUB_STATE || '',

    REDDIT_REDIRECT_URI: process.env.REDDIT_REDIRECT_URI || '',
    REDDIT_CLIENT_SECRET: process.env.REDDIT_CLIENT_SECRET || '',
    REDDIT_STATE: process.env.REDDIT_STATE || '',
    REDDIT_CLIENT_ID: process.env.REDDIT_CLIENT_ID || '',

    TRELLO_TOKEN: process.env.TRELLO_TOKEN || 'tokenTrello',
    TRELLO_SECRET: process.env.TRELLO_SECRET || 'secretTrello',
    TRELLO_REQUEST_URL: process.env.TRELLO_REQUEST_URL || '',
    TRELLO_ACCESS_URL: process.env.TRELLO_ACCESS_URL || '',
    TRELLO_AUTHORIZE_URL: process.env.TRELLO_AUTHORIZE_URL || '',
    TRELLO_SCOPE: process.env.TRELLO_SCOPE || '',
    TRELLO_EXPIRATION: process.env.TRELLO_EXPIRATION || '',
    TRELLO_APPNAME: process.env.TRELLO_APPNAME || '',
    TRELLO_LOGINCALLBACK: process.env.TRELLO_LOGINCALLBACK || '',

    TWITTER_API_KEY: process.env.TWITTER_API_KEY || '',
    TWITTER_API_KEY_SECRET: process.env.TWITTER_API_KEY_SECRET || ''
};