bin=gcc
train?=training.txt
test?=test.txt

all:
	$(bin) desicion-tree.c -o do

run:	./do
	./do --train $(train) --test $(test)

./do:
	$(bin) desicion-tree.c -o do
