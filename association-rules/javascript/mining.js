const reader = require('readline-promise')
const Promise = require('promise')
const fs = require('fs')


var sup = parseFloat(process.argv[process.argv.indexOf('-s') + 1])
var conf = parseFloat(process.argv[process.argv.indexOf('-c') + 1])

var limitedSet = []
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

const generateNextPair = candidate => {
  if (candidate.length == 0) {
    return new Error('Empty candidate')
  }

  const vote = candidate[0].length
  let singleSet = []
  let nextPair = []

  //generate single set
  for (const pairs of candidate) {
    for (const p of pairs) {
      if (singleSet.filter(el => el === p).length > 0) {
        continue
      }
      singleSet.push(p)
    }
  }
  //generate pair set from single set and candidate
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
  nextPair.forEach(el => {el.count = 0})

  //find unuse candidate
  findLimitedCand(candidate, nextPair)

  return nextPair
}

const findLimitedCand = (oldCand, nextPair) => {
  nextPair = nextPair.map(el => el.pairs)
  oldCand = oldCand.map(el => { return {count: 0, pairs: el} })
  for (let i = 0; i < oldCand.length; i++) {
    for (let j = 0; j < nextPair.length; j++) {
      let check = 1
      for (let k = 0; k < oldCand[i].pairs.length; k++) {
        check |= nextPair[j].indexOf(oldCand[i].pairs[k])
      }
      if (check > 0) {
        oldCand[i].count++
      }
    }
  }
  oldCand = oldCand.filter(el => el.count == 0).map(el => el.pairs)
  limitedSet.push(oldCand)
}

const generateNextCandidate = pairs => {
  return reader.createInterface({
    terminal: false,
    input: fs.createReadStream('input.txt')
  })
  .each(line => {
    let transcation = line.split(' ').filter(el => el !== '')
    for (let i = 0; i < pairs.length; i++) {
      let check = 1
      for (let j = 0; j < pairs[i].pairs.length; j++) {
        check |= transcation.indexOf(pairs[i].pairs[j])
      }
      if (check > 0) {
        pairs[i].count++
      }
    }
  })
  .then(count => pairs.filter(el => el.count >= sup).map(el => el.pairs))
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
  let next = null
  console.log(candidate)
  console.log(next = generateNextPair(candidate))
  generateNextCandidate(next).then(cand => console.log(cand))
})
.catch(err => {
  console.log(err)
})
