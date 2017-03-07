# Association Rules

## Require

* node.js v7.4.0
* npm v4.0.5

## Execute

* use `npm i` to install dependencies
* `node app.js -s [min_sup] -c [min_conf]` to run association rules algorithm 
* 0 < min_sup , min_conf < 1

## Caveat !!!

Nodejs is very slow when reading file. It cost about 6 hours to execute the whole algorithm with the input file at moodle.
