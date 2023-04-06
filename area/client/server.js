const express = require('express');
const path = require('path');
const app = express();
const fs = require('fs');

const PATH = '/apk/client.apk';

app.use(express.static(path.join(__dirname, 'dist')))

app.get('/client.apk', (req, res) => {
    try {
        if (fs.existsSync(PATH)) {
            res.status(200).download(PATH);
        }
    } catch (error) {
        res.status(404).send({
            message: 'File not found, its maybe still building, have a look later !'
        })
    }
})

app.get('*', (req, res) => {
    res.sendFile(path.join(__dirname, 'dist', 'index.html'));
}) 

app.listen(parseInt(process.env.FRONT_PORT, 10) || 8081, () => {
    console.log(`server rendering front launched on http://localhost:${parseInt(process.env.FRONT_PORT, 10) || 8081}`);
})

