# Association Rules

## Description

Use multi algorithm to find associztion rules (apriori, dhp,...)
But performance is too bad.

## Require

* node.js v7.4.0
* npm v4.0.5

## Execute

* It will read a file named 'input.txt' and output to a file named 'output.txt'
* use `npm i` to install dependencies
* `node app.js -s [min_sup] -c [min_conf]` to run association rules algorithm 
* 0 < min_sup , min_conf < 1

## Ouput

output-hw.txt is the result of input.txt with min_sup = 0.01 and min_conf = 0.5

## Caveat !!!

Nodejs is very slow when reading file. It cost about 6 hours to execute the whole algorithm with the input file at moodle.
