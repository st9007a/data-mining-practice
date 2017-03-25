#!/usr/bin/env python
import sys
from argparse import ArgumentParser

class Cluster:

    def __init__(self, file_name, data_list):
        self.groups = []
        self.data_list = data_list
        self.file_name = file_name

def main():

    input_file = None
    parser = ArgumentParser()

    parser.add_argument('--file', '-f', help='input the file name you want to clustering')
    args = parser.parse_args()

    if args.file is None:
        print 'Not input file.'
        sys.exit(0)

    try:
        input_file = open(args.file, 'r')
    except(OSError, IOError) as e:
        print 'File not found.'

    raw_data_list = [elem.rstrip('\r\n') for elem in input_file.readlines()]

    data_list = []
    for coordinate in raw_data_list:
        x = coordinate.split(' ')[0]
        y = coordinate.split(' ')[1]
        data_list.append({ 'x': x, 'y': y })

    print data_list

    input_file.close()

if __name__ == '__main__':
    main()
