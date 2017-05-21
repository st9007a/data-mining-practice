const ArgumentParser = require('argparse').ArgumentParser
const fs = require('fs')
const twit = require('twit')

const parser = new ArgumentParser({
  addHelp: true,
  version: '0.0.1',
})
const t = new twit(require('./config.json'))
const twitStream = t.stream('statuses/sample')

parser.addArgument(['-f', '--filter'], {help: 'Get filter tweets'})

const args = parser.parseArgs()

if (!args.filter) {
  twitStream.on('tweet', (tweet) => {
    console.log(tweet)
    fs.appendFileSync('tweets.txt', JSON.stringify(tweet) + '\n', 'utf-8')
  })
}
else {
  const filter = JSON.parse(args.filter)
  console.log('filter: ' + JSON.stringify(filter))
}

