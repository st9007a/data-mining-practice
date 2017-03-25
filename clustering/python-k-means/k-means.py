#!/usr/bin/env python

import math, sys
from argparse import ArgumentParser

class Cluster:

    def __init__(self, data_list):
        self.center = []
        self.data_list = data_list

    def cluster(self, num):
        for i in range(num):
            self.data_list[i]['group'] = i + 1
            self.center.append(self.data_list[i])
        # print self.data_list[0]
        self.find_center()

    def find_center(self):
        for coordinate in self.data_list:
            distance = ()
            center = None
            for g in self.center:
                new_distance = math.sqrt(math.pow(g['x'] - coordinate['x'], 2) + math.pow(g['y'] - coordinate['y'], 2))
                if  new_distance < distance:
                    distance = new_distance
                    center = g['group']
            coordinate['group'] = center
        print self.data_list

def main():

    input_file = None
    parser = ArgumentParser()

    parser.add_argument('--file', '-f', help = 'input the file name you want to clustering')
    args = parser.parse_args()

    if args.file is None:
        print 'Not input file.'
        sys.exit(0)

    try:
        input_file = open(args.file, 'r')
    except(OSError, IOError) as e:
        print 'File not found.'

    raw_data_list = [elem.rstrip('\r\n') for elem in input_file.readlines()]
    input_file.close()

    data_list = []
    for coordinate in raw_data_list:
        x = coordinate.split(' ')[0]
        y = coordinate.split(' ')[1]
        data_list.append({ 'x': float(x), 'y': float(y) , 'group': 0 })

    cluster = Cluster(data_list)
    cluster.cluster(5)


if __name__ == '__main__':
    main()
