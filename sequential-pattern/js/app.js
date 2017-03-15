const fs = require('fs')
const reader = require('readline-promise')

const sup = process.argv[process.argv.indexOf('-s') + 1]

if (!sup) {
  exit(1)
}
