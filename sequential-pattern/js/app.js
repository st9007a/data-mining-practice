const fs = require('fs')
const reader = require('readline-promise')

let sup = process.argv[process.argv.indexOf('-s') + 1]

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

reader.createInterface({
  terminal: false,
  input: fs.createReadStream('input.txt')
})
.each(line => {
  console.log(JSON.stringify(parseLine(line)))
})
.then(count => {
  sup *= count.lines
})
.catch(err => console.log(err))
