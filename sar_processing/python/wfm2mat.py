
from scipy.io import savemat
import numpy as np
import sys

if len(sys.argv) < 3:
    print(f"\33[31mScript is used: python {sys.argv[0]} infile.txt outfile.mat\33[0m")
    exit()

outfile_name = sys.argv[2]
infile_name = sys.argv[1]



savemat(outfile_name, {'wfm':wfm})

