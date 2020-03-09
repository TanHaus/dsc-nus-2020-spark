const express = require('express')
const app = express()
const port = process.env.PORT || 5000

const bodyParser = require("body-parser");
app.use(bodyParser.urlencoded());

app.get('/', (req, res) => res.send('CHROMATICA!'))

app.post("/", (req, res) => {
    res.send(`${req.body.test}`);
});

app.listen(port, () => console.log(`Example app listening on port ${port}!`))