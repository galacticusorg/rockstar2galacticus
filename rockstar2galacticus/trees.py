#! /usr/bin/env python

import numpy as np

def count_trees(forest_file):    
    def blocks(ifile,size=65536):
        while True:
            b = ifile.read(size)
            if not b: break
            yield b
    with open(forest_file, "r") as f:
        f.readline()
        ntrees = np.sum(bl.count("\n") for bl in blocks(f))
    return ntrees
