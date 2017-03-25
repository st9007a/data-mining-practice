#!/usr/bin/env python
from argparse import ArgumentParser

class Cluster:

    def __init__(self, file_name, data_list):
        self.groups = []
        self.data_list = data_list
        self.file_name = file_name

def main():

    parser = ArgumentParser()
    parser.add_argument("--file", "-f", help="input the file name you want to clustering")
    args = parser.parse_args()

    if args.file:
        print args.file

if __name__ == '__main__':
    main()
