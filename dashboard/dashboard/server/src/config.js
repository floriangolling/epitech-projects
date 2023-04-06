require('dotenv').config();

module.exports = {
    PORT: parseInt(process.env.PORT) || 8080,
    HOST: process.env.HOST || '127.0.0.1',
    DB_USER: process.env.POSTGRES_USER || 'postgres',
    DB_PASSWORD: process.env.POSTGRES_PASSWORD || 'postgres',
    DB_PORT: process.env.POSTGRES_PORT || 5432,
    DB_NAME: process.env.POSTGRES_SCHEMA || 'postgres',
    DB_HOST: process.env.POSTGRES_HOST || 'localhost',
    LEAGUE_API_KEY: process.env.LEAGUE_API_KEY || "api_key_lol",
    JWT_SECRET: process.env.JWT || "secret",
    JWT_EMAIL_SECRET: process.env.JWT_EMAIL_SECRET || "secret",
    WEATHER_API_KEY: process.env.WEATHER_API_KEY || "weather_api",
    TWITCH_CLIENT_ID: process.env.TWITCH_CLIENT_ID || "client_d",
    TWITCH_SECRET: process.env.TWITCH_SECRET || "secret",
    PROTOCOL: process.env.PROTOCOL || 'http://',
    TWITCH_REDIRECT_URI: process.env.TWITCH_REDIRECT_URI || `${this.PROTOCOL}${this.HOST}:${this.PORT}}/callback/twitch`
};