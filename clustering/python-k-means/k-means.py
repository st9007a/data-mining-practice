#!/usr/bin/env python

import math, sys
from argparse import ArgumentParser

class Cluster:

    def __init__(self, data_list):
        self.center = []
        self.data_list = data_list

    def cluster(self, num):
        for i in range(num):
            self.data_list[i]['group'] = i
            self.center.append(self.data_list[i])
        self.find_nearest_center()
        while self.calc_new_center() == False:
            self.find_nearest_center()
        print self.data_list


    def find_nearest_center(self):
        for coordinate in self.data_list:
            distance = ()
            center = None
            for g in self.center:
                new_distance = math.sqrt(math.pow(g['x'] - coordinate['x'], 2) + math.pow(g['y'] - coordinate['y'], 2))
                if  new_distance < distance:
                    distance = new_distance
                    center = g['group']
            coordinate['group'] = center

    def calc_new_center(self):
        record = []
        new_center = []
        for i in range(len(self.center)):
            record.append({'count': 0, 'xsum': 0, 'ysum': 0})
        for coordinate in self.data_list:
            record[coordinate['group']]['xsum'] += coordinate['x']
            record[coordinate['group']]['ysum'] += coordinate['y']
            record[coordinate['group']]['count'] += 1

        idx = 0
        for sum in record:
            new_center.append({'x': sum['xsum'] / float(sum['count']), 'y': sum['ysum'] / float(sum['count']), 'group': idx})
            idx += 1
        is_continue = self.shift(new_center)
        self.center = new_center
        return is_continue

    def shift(self, new_center):
        for i in range(len(self.center)):
            if math.sqrt(math.pow(self.center[i]['x'] - new_center[i]['x'], 2) + math.pow(self.center[i]['y'] - new_center[i]['y'], 2)) > 0.001:
                return False
        return True



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
