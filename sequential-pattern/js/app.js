const fs = require('fs')
const reader = require('readline-promise')

let sup = parseFloat(process.argv[process.argv.indexOf('-s') + 1])

let sequenceTable = []
let itemSet = []
let sequenceSet = []

const parseLine = tran => {
  let rawData = tran.split(' ').filter(el => el !== '')
  let data = {
    seq: [],
    sid: rawData.shift(),
  }
  for (let i = 0; i < rawData.length; i++) {
    const tranTime = rawData[i]
    let isExist = false
    for (let j = 0; j < data.seq.length; j++) {
      if (data.seq[j].time === tranTime) {
        data.seq[j].items.push(rawData[++i])
        isExist = true
        break
      }
    }
    if (isExist) {
      continue
    }
    data.seq.push({
      items: [rawData[++i]],
      time: tranTime,
    })
  }
  data.seq = data.seq
    .sort((a, b) => a.time - b.time)
    .map(el => el.items)
  return data
}

const isSubSet = (subSet, superSet) => {
  if (subSet.length > superSet.length) {
    return -1
  }
  let check = 1
  for (const sub of subSet) {
    check |= superSet.indexOf(sub)
  }
  return check
}

const isSameSet = (a, b) => {
  return a.length == b.length && a.every((el, i) => b[i] === el)
}

const isInDB = (subSeq, superSeq) => {
  let k = 0
  for (let i = 0; i < subSeq.length; i++) {
    let isExist = false
    for (let j = k; j < superSeq.length; j++) {
      if (superSeq[j].indexOf(subSeq[i]) >= 0) {
        k++
        isExist = true
        break
      }
    }
    if (!isExist) {
      return false
    }
  }
  return true
}

const isSubSeq = (subSeq, superSeq) => {
  let indexRecord = []
  for (let i = 0; i < subSeq.length; i++) {
    indexRecord.push(superSeq.indexOf(subSeq[i]))
  }
  for (let i = 0; i < indexRecord.length; i++) {
    if (indexRecord[i] < 0 || (indexRecord[i + 1] && indexRecord[i] > indexRecord[i + 1])) {
      return false
    }
  }
  return true
}

const findSubPattern = pattern => {
  if (pattern.length == 0) {
    return
  }
  let isExist = false
  for (const c of itemSet) {
    if (isSameSet(pattern, c.element)) {
      c.sup++
      isExist = true
      break
    }
  }
  if (!isExist) {
    itemSet.push({ element: pattern, sup: 1 })
  }
  for (let i = 0; i < pattern.length; i++) {
    findSubPattern(pattern.filter((el, idx) => i !== idx))
  }
}

//input = [
//  {seq: array, sup: number}
//]
const generateNextLevelSeqSet = candSeqSet => {
  if (candSeqSet.length == 0) {
    return
  }

  console.log(candSeqSet)
  return
  let vote = candSeqSet[0].seq.length
  let singleSet = []
  let nextLevelSeqSet = []

  //generate single set
  for (const cand of candSeqSet) {
    for (const s of cand.seq) {
      if (singleSet.indexOf(s) < 0) {
        singleSet.push(s)
      }
    }
  }

  //generate next level set by single set and cand seq set
  for (let i = 0; i < candSeqSet.length; i++) {
    for (let j = 0; j < singleSet.length; j++) {
      if (candSeqSet[i].seq.indexOf(singleSet[j]) < 0) {
        nextLevelSeqSet.push({seq: candSeqSet[i].seq.concat(singleSet[j]), vote: 0})
      }
    }
  }

  //trim next level set
  for (const next of nextLevelSeqSet) {
    for (const cand of candSeqSet) {
      if (isSubSeq(cand.seq, next.seq)) {
        next.vote++
      }
    }
  }
  nextLevelSeqSet = nextLevelSeqSet
    .filter(el => el.vote > vote)
    .map(el => {
      return { seq: el.seq, sup: 0 }
    })

  //find candidate
  for (const next of nextLevelSeqSet) {
  }
}

reader.createInterface({
  terminal: false,
  input: fs.createReadStream('input.txt')
})
.each(line => {
  sequenceTable.push(parseLine(line))
})
.then(count => {
  sup *= count.lines
  //find item set
  for (let i = 0; i < sequenceTable.length; i++) {
    for (const item of sequenceTable[i].seq) {
      findSubPattern(item)
    }
  }
  sequenceSet.push(itemSet)

  //filter min support and build map
  itemSet = itemSet
    .filter(el => el.sup >= sup)
    .map((el, idx) => {
      Object.assign(el, { map: idx })
      return el
    })

  for (let i = 0; i < sequenceTable.length; i++) {
    sequenceTable[i].seq = sequenceTable[i].seq
      .map(el => {
        let newEl = []
        for (const item of itemSet) {
          if (isSubSet(item.element, el) >= 0) {
            newEl.push(item.map)
          }
        }
        return newEl
      })
      .filter(el => el.length > 0)
  }
  sequenceTable = sequenceTable.filter(el => el.seq.length > 0)
  generateNextLevelSeqSet(itemSet.map(el => {
    return { seq: [el.map], sup: 0 }
  }))
})
.catch(err => console.log(err))
