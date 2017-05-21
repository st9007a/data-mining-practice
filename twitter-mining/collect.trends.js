const fs = require('fs')
const twit = require('twit')

const t = new twit(require('./config.json'))

const getTrends = () => t.get('trends/place', {id: 1}, (err, chunk, res) => {
  if (err) throw err
  const now = new Date()
  const data = {date: now, chunk: chunk}
  console.log('Get trends at ' + now)
  fs.appendFileSync('trends.txt', JSON.stringify(data) + '\n')
})

getTrends()
setInterval(() => getTrends(), 1000 * 60 * 10)
