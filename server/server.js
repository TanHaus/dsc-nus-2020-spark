const express = require('express')
const app = express()
const port = process.env.PORT || 5000

class Lamp {
    constructor(name) {
        this.state = 0
        this.name = name
    }
    toggleState() {
        if(this.state === 1) this.state = 0
        else this.state = 1
    }
}

let names = ['lamp1', 'lamp2']
let lamps = names.map(name => new Lamp(name))

const bodyParser = require("body-parser");
app.use(bodyParser.urlencoded());

app.get('/', (req, res) => {
    res.sendFile('html/index.html', {root: __dirname})
})

app.post("/", (req, res) => {
    res.send(`I got you, ${req.body}`);
});

app.get('/state', (req,res) => {
    let name = req.body.name
    let index = names.indexOf(name)
    if(index == -1) {
        // do something
    } else {
        // do something
    }
    res.send()
})

app.post('/send', (req, res) => {

})

app.listen(port, () => console.log(`Example app listening on port ${port}!`))