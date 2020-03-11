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
    console.log('Load homepage')
    res.status(200)
    res.sendFile('html/index.html', {root: __dirname})
})

app.post("/", (req, res) => {
    console.log('Test connection')
    res.status(200)
    res.send(`I got you, ${req.body.content}`);
});

app.get('/state', (req,res) => {
    let name = req.query.name
    let index = names.indexOf(name)

    if(index == -1) {
        console.log('Lamp not found')
        res.status(403)
        res.send('Can\'t find anything yo')
    } else {
        console.log(`Get state of ${names[index]}`)
        res.send(lamps[index].state.toString())
    }
    res.send()
})

app.get('/all', (req,res) => {
    console.log('Get all lamps')
    res.status(200)
    res.send(JSON.stringify(lamps))
})

app.get('/names', (req,res) => {
    console.log('Get names')
    res.status(200)
    res.send(JSON.stringify(names))
})

app.post('/state', (req, res) => {
    let name = req.body.name
    let state = parseInt(req.body.state)
    let index = names.indexOf(name)
    console.log(`Set state of ${name} to ${state}`)

    if(index>-1) {
        console.log('Successful')
        lamps[index].state = state
        res.status(200)
        res.send('Successful')
    } else {
        console.log('Lamp not found')
        res.status(404)
        res.send('Failed')
    }
})

app.listen(port, () => console.log(`NUS DSC 2020 app listening on port ${port}!`))