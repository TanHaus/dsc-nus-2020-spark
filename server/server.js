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
    res.send(`I got you, ${req.body.content}`);
});

app.get('/state', (req,res) => {
    let name = req.query.name
    let index = names.indexOf(name)

    if(index == -1) {
        // do something
        res.send('Can\'t find anything yo')
    } else {
        // do something
        console.log(lamps[index])
        res.send(lamps[index].state.toString())
    }
    res.send()
})

app.get('/all', (req,res) => {
    res.send(JSON.stringify(lamps))
})

app.post('/state', (req, res) => {
    let name = req.body.name
    let state = parseInt(req.body.state)
    let index = names.indexOf(name)

    lamps[index].state = state
})

app.listen(port, () => console.log(`Example app listening on port ${port}!`))