const fs = require('fs')
const reader = require('readline-promise')

let sup = parseFloat(process.argv[process.argv.indexOf('-s') + 1])

const sequenceTable = []
const c1 = []

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

const findSubPattern = pattern => {
  if (pattern.length == 0) {
    return
  }
  let isExist = false
  for (const c of c1) {
    if (isSameSet(pattern, c.element)) {
      c.sup++
      isExist = true
      break
    }
  }
  if (!isExist) {
    c1.push({ element: pattern, sup: 1 })
  }
  for (let i = 0; i < pattern.length; i++) {
    findSubPattern(pattern.filter((el, idx) => i !== idx))
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
  for (let i = 0; i < sequenceTable.length; i++) {
    for (const item of sequenceTable[i].seq) {
      findSubPattern(item)
    }
  }
  c1 = c1.filter(el => el.sup >= sup)
})
.catch(err => console.log(err))
