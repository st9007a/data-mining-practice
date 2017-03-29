#!/usr/bin/env python

import math, sys
from argparse import ArgumentParser

global dataset
dataset = []

def region_query(point, eps):
    global dataset
    return [elem for elem in dataset if math.sqrt(math.pow(point['x'] - elem['x'], 2) + math.pow(point['y'] - elem['y'], 2)) < eps]

def expand_cluster(point, neighbor_pts, c, eps, min_pts):
    point['cluster'] = c
    for elem in neighbor_pts:
        if elem['visited'] == False:
            elem['visited'] = True
            new_neighbor_pts = region_query(elem, eps)
            if len(new_neighbor_pts) >= min_pts:
                neighbor_pts = neighbor_pts + new_neighbor_pts
        if elem['cluster'] == None:
            elem['cluster'] = c

def dbscan(eps, min_pts):
    c = 0
    global dataset
    for point in dataset:
        if point['visited'] == True:
            continue
        point['visited'] == True
        neighbor_pts = region_query(point, eps)
        if len(neighbor_pts) < min_pts:
            point['noise'] = True
        else:
            c += 1
            expand_cluster(point, neighbor_pts, c, eps, min_pts)

def main():

    input_file = None
    eps = 40
    min_pts = 5
    parser = ArgumentParser()

    parser.add_argument('--file', '-f', help = 'Input the file name you want to clustering')
    parser.add_argument('--eps', '-e', help = 'default 40')
    parser.add_argument('--minpts', '-m', help = 'default 5')
    args = parser.parse_args()

    if args.file is None:
        print 'Not input file.'
        sys.exit(0)
    if args.eps is not None:
        eps = float(args.eps)
    if args.minpts is not None:
        min_pts = int(args.minpts)

    try:
        input_file = open(args.file, 'r')
    except(OSError, IOError) as e:
        print 'File not found.'

    raw_data_list = [elem.rstrip('\r\n') for elem in input_file.readlines()]
    input_file.close()

    global dataset
    for coordinate in raw_data_list:
        x = coordinate.split(' ')[0]
        y = coordinate.split(' ')[1]
        dataset.append({ 'x': float(x), 'y': float(y), 'visited': False, 'cluster': None, 'noise': False })
    dbscan(eps, min_pts)

    with open(args.file + '-output.txt', 'w+') as output_file:
        for data in dataset:
            output_file.write(str(data['x']) + ' ' + str(data['y']) + ' ' + str(data['cluster']) + '\n')

if __name__ == '__main__':
    main()
