const reader = require('readline-promise')
const Promise = require('promise')
const fs = require('fs')


var sup = parseFloat(process.argv[process.argv.indexOf('-s') + 1])
var conf = parseFloat(process.argv[process.argv.indexOf('-c') + 1])

var holder = {}
var hash = []

for (let i = 0; i < 7; i++) {
  hash.push({ count: 0, pairs: [], counts: [] })
}

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

var p = 0
const forEachTwoPair = (trac, cb) => {
  for (let i = 0; i < trac.length; i++) {
    for (let j = i + 1; j < trac.length; j++) {
      const pair = [trac[i], trac[j]].sort((a, b) => parseInt(a) - parseInt(b))
      cb(pair)
    }
  }
  process.stdout.write((p++).toString() + '\r')
}

const generateNextPair = candidate => {
  if (candidate.length == 0) {
    return new Error('Empty candidate')
  }

  const vote = candidate[0].length

  //generate single set
  let singleSet = []
  for (const pairs of candidate) {
    for (const p of pairs) {
      if (singleSet.filter(el => el === p).length > 0) {
        continue
      }
      singleSet.push(p)
    }
  }
  //generate pair set from single set and candidate
  let nextPair = []
  for (let i = 0; i < candidate.length; i++) {
    let notSet = singleSet
    for (const p of candidate[i]) {
      notSet = notSet.filter(el => el !== p)
    }
    for (const n of notSet) {
      nextPair.push({ count: 0, pairs: candidate[i].concat(n).sort((a, b) => parseInt(a) - parseInt(b)) })
    }
  }

  //trim next pair
  for (let i = 0; i < nextPair.length; i++) {
    for (let j = i + 1; j < nextPair.length; j++) {
      let check = 1
      for (let k = 0; k < nextPair[i].pairs.length; k++) {
        check |= nextPair[j].pairs.indexOf(nextPair[i].pairs[k])
      }
      if (check > 0) {
        nextPair.splice(j, 1)
      }
    }
  }

  //vote
  for (const c of candidate) {
    for (const np of nextPair) {
      let check = 1
      for (const citem of c) {
        check |= np.pairs.indexOf(citem)
      }
      if (check > 0) {
        np.count++
      }
    }
  }
  nextPair = nextPair.filter(el => el.count > vote)

  return nextPair
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
  sup *= count.lines
  let candidate = []
  for (let i = 0; i < hash.length; i++) {
    if (hash[i].count < sup) {
      continue
    }
    for (let j = 0; j < hash[i].pairs.length; j++) {
      if (hash[i].counts[j] >= sup) {
        candidate.push(hash[i].pairs[j])
      }
    }
  }
  console.log(candidate)
  console.log(generateNextPair(candidate))
})
.catch(err => {
  console.log(err)
})

