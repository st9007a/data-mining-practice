const twit = require('twit')
const t = new twit(require('./config.json'))

t.get('search/tweets', { q: 'banana since:2011-07-11', count: 100 }, function(err, data, response) {
  console.log(data);
})
