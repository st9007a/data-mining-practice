const reader = require('readline-promise')
const fs = require('fs')


const sup = process.argv[process.argv.indexOf('-s') + 1]
const conf = process.argv[process.argv.indexOf('-c') + 1]

var holder = {}
var hash = []

for (let i = 0; i < 7; i++) hash.push({ count: 0, pairs: [], counts: [] })

const addData = array => {
  for (const el of array) {
    if (holder[el] == undefined) {
      holder[el] = 1
    }
    else {
      holder[el] += 1
    }
  }
}

const forEachTwoPair = (trac, cb) => {
  for (let i = 0; i < trac.length; i++) {
    for (let j = i + 1; j < trac.length; j++) {
      const pair = [trac[i], trac[j]].sort((a, b) => parseInt(a) - parseInt(b))
      cb(pair)
    }
  }
}

const toHash = pair => {
  const index = (parseInt(pair[0]) * 10 + parseInt(pair[1])) % 7
  for (let i = 0; i < hash[index].pairs.length; i++) {
    if (hash[index].pairs[i][0] == pair[0] && hash[index].pairs[i][1] == pair[1]) {
      hash[index].count++
      hash[index].counts[i]++
      return
    }
  }
  hash[index].pairs.push(pair)
  hash[index].counts.push(1)
  hash[index].count++
}

reader.createInterface({
  terminal: false,
  input: fs.createReadStream('input.txt')
})
.each(line => {
  let transcation = line.split(' ').filter(el => el !== '')
  forEachTwoPair(transcation, (pair) => {
    toHash(pair)
  })
})
.then(count => {
  console.log(count)
  console.log(hash)
  /*
  console.log(hash[0].pairs)
  console.log(hash[1].pairs)
  console.log(hash[2].pairs)
  console.log(hash[3].pairs)
  console.log(hash[4].pairs)
  console.log(hash[5].pairs)
  console.log(hash[6].pairs)
  */
})
.catch(err => {
  console.log(err)
})

