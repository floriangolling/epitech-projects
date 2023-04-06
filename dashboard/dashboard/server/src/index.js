const express                   = require('express');
const bodyParser                = require('body-parser')
const history                   = require('connect-history-api-fallback');
const config                    = require('./config');
const database                  = require('./database');
const cors                      = require('cors')
const postgres                  = require('./database/database');
const path                      = require('path');
const apiRouter                 = require('./api');
const authentificationRouter    = require('./api/authentification');
const aboutRouter               = require('./api/about')
const app                       = express();
const AuthRouter                = require('./api/OauthRouter');

app.use(cors());
app.use(bodyParser.urlencoded({ extended: false}));
app.use(bodyParser.json())
app.use(aboutRouter);
app.use(authentificationRouter);
app.use(AuthRouter);
app.use('/api', apiRouter);
app.use(history());

database.init(postgres)
.then(() => {
    app.listen(config.PORT, () => {
        console.log(`Example app listening at ${config.HOST}:${config.PORT}`);
    });
}).catch((err) => {
    console.log('\x1b[31m%s\x1b[0m', err);
});

app.use(express.static(path.join(__dirname, '..', '..', 'client', 'dist')));

app.get('*', (req, res) => {
    res.sendFile(path.join(__dirname, '..', '..', 'client', 'dist', 'index.html'));
});