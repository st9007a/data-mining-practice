const reader = require('readline-promise')
const fs = require('fs')

var sup = parseFloat(process.argv[process.argv.indexOf('-s') + 1])
var conf = parseFloat(process.argv[process.argv.indexOf('-c') + 1])

let c1 = []

const generateL = cand => {
  
}

const generateC = l => {
  
}

const findLimitedSet = (oldL, nextCand) => {

}

reader.createInterface({
  terminal: false,
  input: fs.createReadStream('input.txt')
})
.each(line => {
  let tran = line.split(' ').filter(el => el !== '')
  for (const p of tran) {
    let isExist = false
    for (let i = 0; i < c1.length; i++) {
      if (c1[i].candidate === p) {
        c1[i].count++
        isExist = true
        break
      }
    }
    if (!isExist) {
      c1.push({count: 0, candidate: p})
    }
  }
})
.then(count => {
  sup *= count.lines
  c1 = c1.filter(el => el.count >= sup)
  console.log(c1)
})
.catch(err => console.log(err))


