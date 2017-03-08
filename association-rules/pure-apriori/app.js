const reader = require('readline-promise')
const fs = require('fs')

var sup = parseFloat(process.argv[process.argv.indexOf('-s') + 1])
var conf = parseFloat(process.argv[process.argv.indexOf('-c') + 1])

let c1 = []
let limitedSet = []
let candSet = []

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
    for (const i of c.candidate) {
      if (itemSet.filter(el => el === i).length > 0) {
        continue
      }
      itemSet.push(i)
    }
  }

  for (let i = 0; i < cand.length; i++) {
    let notSet = itemSet
    for (const c of cand[i].candidate) {
      notSet = notSet.filter(el => el !== c)
    }
    for (const n of notSet) {
      nextL.push({ vote: 0, candidate: cand[i].candidate.concat(n).sort((a, b) => parseInt(a) - parseInt(b))})
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
  return nextL
}

const generateC = l => {
  l = l.map(el => { return {count: 0, candidate: el} })
  return reader.createInterface({
    terminal: false,
    input: fs.createReadStream('input.txt')
  })
  .each(line => {
    let tran = parseTransaction(line)
    for (const item of l) {
      if (matchSubSet(item.candidate, tran) > 0) {
        item.count++
      }
    }
  })
  .then(count => {
    const nc = l.filter(el => el.count >= sup)
    candSet.push(nc)
    return nc
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
  oldCand = oldCand.filter(el => el.vote == 0)
  oldCand.forEach(el => limitedSet.push(el))
}

const miningLimitedSet = cand => {
  const nl = generateL(cand)
  if (nl.length == 0) {
    //candSet.forEach(el => console.log(el))
    return null
  }
  return generateC(nl).then(cand => miningLimitedSet(cand))
}

const findAllRules = () => {
  fs.writeFileSync('output.txt', '')
  console.log(candSet[0])
  for (const l of limitedSet) {
    for (let i = l.candidate.length - 2; i >= 0; i--) {
      for (let j = 0; j < candSet[i].length; j++) {
        let condition = l.count / candSet[i][j].count
        if (matchSubSet(candSet[i][j].candidate, l.candidate) > 0 && condition >= conf) {
          let rule = {
            cond: condition,
            prefix: candSet[i][j].candidate,
            suffix: l.candidate.filter(el => candSet[i][j].candidate.indexOf(el) < 0)
          }
          fs.appendFileSync('output.txt', `{${rule.prefix.join()}} => {${rule.suffix.join()}} (${rule.cond})\n`)
        }
      }
    }
  }
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
  candSet.push(c1)
  miningLimitedSet(c1).then(() => {
    findAllRules()
  })
})
.catch(err => console.log(err))


