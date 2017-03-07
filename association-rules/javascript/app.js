const reader = require('readline-promise')
const fs = require('fs')

var sup = parseFloat(process.argv[process.argv.indexOf('-s') + 1])
var conf = parseFloat(process.argv[process.argv.indexOf('-c') + 1])

var candSet = []
var limitedSet = []
var pairSet = []
var hash = []

for (let i = 0; i < 7; i++) {
  hash.push({ count: 0, pairs: [], counts: [] })
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

const matchRecord = (pair, data) => {
  let check = 1
  for (let j = 0; j < pair.length; j++) {
    check |= data.indexOf(pair[j])
  }
  return check
}

const generateNextPair = candidate => {
  if (candidate.length == 0) {
    return new Error('Empty candidate')
  }

  const vote = candidate[0].pairs.length
  let singleSet = []
  let nextPair = []

  //generate single set
  for (const c of candidate) {
    for (const pair of c.pairs) {
      if (singleSet.filter(el => el === pair).length > 0) {
        continue
      }
      singleSet.push(pair)
    }
  }

  //generate pair set from single set and candidate
  for (let i = 0; i < candidate.length; i++) {
    let notSet = singleSet
    for (const p of candidate[i].pairs) {
      notSet = notSet.filter(el => el !== p)
    }
    for (const n of notSet) {
      nextPair.push({ count: 0, pairs: candidate[i].pairs.concat(n).sort((a, b) => parseInt(a) - parseInt(b)) })
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
      for (const citem of c.pairs) {
        check |= np.pairs.indexOf(citem)
      }
      if (check > 0) {
        np.count++
      }
    }
  }
  nextPair = nextPair.filter(el => el.count > vote).map(el => el.pairs)

  //find unuse candidate
  findLimitedCand(candidate, nextPair)

  return nextPair
}

const findLimitedCand = (oldCand, nextPair) => {
  oldCand.forEach(el => { el.vote = 0 })
  for (let i = 0; i < oldCand.length; i++) {
    for (let j = 0; j < nextPair.length; j++) {
      if (matchRecord(oldCand[i].pairs, nextPair[j]) > 0) {
        oldCand[i].vote++
        break
      }
    }
  }
  oldCand = oldCand.filter(el => el.vote == 0).map(el => el.pairs)
  oldCand.forEach(el => limitedSet.push(el))
}

const findAllCand = () => {
  for (let i = 0; i < pairSet.length; i++) {
    for (let j = 0; j < pairSet[i].length; j++) {
      pairSet[i][j] = { count: 0, pairs: pairSet[i][j] }
    }
  }
  return reader.createInterface({
    terminal: false,
    input: fs.createReadStream('input.txt')
  })
  .each(line => {
    const transcation = line.split(" ").filter(el => el !== '')
    for (let i = 0; i < pairSet.length; i++) {
      for (let j = 0; j < pairSet[i].length; j++) {
        if (matchRecord(pairSet[i][j].pairs, transcation) > 1) {
          pairSet[i][j].count++
        }
      }
    }
  })
  .then(count => {
    for (let i = 0; i < pairSet.length; i++) {
      pairSet[i] = pairSet[i].filter(el => el.count > sup)
    }
    candSet = candSet.concat(pairSet)
  })

}

const generateNextCandidate = pairs => {
  pairs = pairs.map(el => { return {count: 0, pairs: el} })
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
  .then(count => pairs.filter(el => el.count >= sup))
}

const generatePairSet = pair => {
  const p = generateNextPair(pair.map(el => { return { count: 0, pairs: el }}))
  if (p.length == 0) {
    return
  }
  pairSet.push(p)
  generatePairSet(p)
}

const findMinConf = () => {
  let singleSet = []
  let voteLimitedSet = limitedSet.map(el => { return { count: 0, pairs: el } })
  const level2LimitedSet = limitedSet.filter(el => el.length == 2)

  // find single set from level 2 limited set
  for (const l of level2LimitedSet) {
    for (const item of l) {
      if (singleSet.filter(el => el.pairs[0] === item).length > 0) {
        continue
      }
      singleSet.push({count: 0, pairs: [item]})
    }
  }
  return reader.createInterface({
    terminal: false,
    input: fs.createReadStream('input.txt')
  })
  .each(line => {
    let transcation = line.split(' ').filter(el => el != '')
    // get count of limitedSet
    for (const v of voteLimitedSet) {
      if (matchRecord(v.pairs, transcation) > 0) {
        v.count++
      }
    }

    // get count of singleSet
    for (const s of singleSet) {
      if (transcation.indexOf(s.pairs[0]) >= 0) {
        s.count++
      }
    }

  })
  .then(count => {
    const rules = []
    candSet = [singleSet].concat(candSet)

    for (let i = voteLimitedSet.length - 1; i >= 0 ; i--) {
      for (let j = voteLimitedSet[i].pairs.length - 2; j >= 0; j--) {
        for (let k = 0; k < candSet[j].length; k++) {
          const isSame = candSet[j][k].pairs.length === voteLimitedSet[i].pairs.length && candSet[j][k].pairs.every(function(el, index) { return el === voteLimitedSet[i].pairs[index]})
          if (isSame) {
            continue
          }
          const cond = voteLimitedSet[i].count / candSet[j][k].count
          if (matchRecord(candSet[j][k].pairs, voteLimitedSet[i].pairs) > 0 && cond >= conf) {
            let rule = {
              cond: cond,
              prefix: candSet[j][k].pairs,
              suffix: voteLimitedSet[i].pairs.filter(el => candSet[j][k].pairs.indexOf(el) < 0)
            }
            fs.appendFileSync('output.txt', `{${rule.prefix.join()}} => {${rule.suffix.join()}} (${rule.cond})\n`)
          }
        }
      }
    }
    return rules
  })
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
  //get two-pair candidate from hash table
  for (let i = 0; i < hash.length; i++) {
    if (hash[i].count < sup) {
      continue
    }
    for (let j = 0; j < hash[i].pairs.length; j++) {
      if (hash[i].counts[j] >= sup) {
        candidate.push({count: hash[i].counts[j], pairs: hash[i].pairs[j]})
      }
    }
  }
  candSet.push(candidate)
  //get three-pair candidate
  let next = null
  nextPairs = generateNextPair(candidate)
  generateNextCandidate(nextPairs).then(cand => {
    if (cand.length > 0) {
      candSet.push(cand)
      generatePairSet(cand.map(el => el.pairs))
      return 1
    }
    return 0
  })
  .then(flag => {
    if (flag === 1) {
      findAllCand()
    }
    findMinConf()
  })
})
.catch(err => {
  console.log(err)
})

