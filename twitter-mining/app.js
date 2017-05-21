const fs = require('fs')
const twit = require('twit')

const t = new twit(require('./config.json'))

const getTrends = () => t.get('trends/place', {id: 1}, (err, data, res) => {
  if (err) throw err
  console.log('Get trends at ' + new Date())
  fs.appendFileSync('trends.txt', JSON.stringify(data) + '\n')
})

getTrends()
setInterval(() => getTrends(), 1000 * 60 * 10)
