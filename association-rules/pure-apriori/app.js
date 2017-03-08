const reader = require('readline-promise')
const fs = require('fs')

var sup = parseFloat(process.argv[process.argv.indexOf('-s') + 1])
var conf = parseFloat(process.argv[process.argv.indexOf('-c') + 1])

let c1 = []
let limitedSet = []

const matchSubSet = (subSet, superSet) => {
  let check = 1
  for (const sub of subSet) {
    check |= superSet.indexOf(sub)
  }
  return check
}

const parseTransaction = data => {
  return data.split(' ').filter(el => el !== '')
}

const generateL = cand => {
  let nextL = []
  let itemSet = []
  let vote = cand[0].candidate.length

  for (const c of cand) {
    if (itemSet.indexOf(c) < 0) {
      itemSet.push(c.candidate)
    }
  }

  for (let i = 0; i < cand.length; i++) {
    let notSet = itemSet
    for (const c of cand[i].candidate) {
      notSet = notSet.filter(el => el !== c)
    }
    for (const n of notSet) {
      nextL.push({ vote: 0, candidate: cand[i].candidate.concat(n)})
    }
  }

  for (let i = 0; i < nextL.length; i++) {
    for (let j = i + 1; j < nextL.length; j++) {
      if (matchSubSet(nextL[i].candidate, nextL[j].candidate) > 0) {
        nextL.splice(j, 1)
      }
    }
  }

  for (const c of cand) {
    for (const ln of nextL) {
      if (matchSubSet(c.candidate, ln.candidate) > 0) {
        ln.vote++
      }
    }
  }

  nextL = nextL.filter(el => el .vote > vote).map(el => el.candidate)
  findLimitedSet(cand, nextL)
}

const generateC = l => {
  return reader.createInterface({
    terminal: false,
    input: fs.createReadStream('input.txt')
  })
  .each(line => {
    let tran = parseTransaction(line)
  })
}

const findLimitedSet = (oldCand, nextL) => {
  oldCand = oldCand.map(el => {
    Object.assign(el, {vote: 0})
    return el
  })
  for (const c of oldCand) {
    for (const nl of nextL) {
      if (matchSubSet(c.candidate, nl) > 0) {
        c.vote++
        break
      }
    }
  }
  oldCand = oldCand.filter(el => el.vote == 0).map(el => { return {count: el.count, candidate: el.candidate} })
  oldCand.forEach(el => limitedSet.push(el))
}

reader.createInterface({
  terminal: false,
  input: fs.createReadStream('input.txt')
})
.each(line => {
  let tran = parseTransaction(line)
  for (const p of tran) {
    let isExist = false
    for (let i = 0; i < c1.length; i++) {
      if (c1[i].candidate[0] === p) {
        c1[i].count++
        isExist = true
        break
      }
    }
    if (!isExist) {
      c1.push({count: 0, candidate: [p]})
    }
  }
})
.then(count => {
  sup *= count.lines
  c1 = c1.filter(el => el.count >= sup)
  limited.push(c1)
  generateL(c1)
})
.catch(err => console.log(err))


