const fs = require('fs')
const twit = require('twit')
const t = new twit(require('./config.json'))
const twitStream = t.stream('statuses/sample')

twitStream.on('tweet', (tweet) => {
  console.log(tweet)
  fs.appendFileSync('tweets.txt', JSON.stringify(tweet) + '\n', 'utf-8')
})

