
from scipy.io import savemat
import numpy as np
import sys

if len(sys.argv) < 2:
    print(f"\33[31mScript is used: python {sys.argv[0]} infile.txt\33[0m")
    exit()

end = len(sys.argv[1])
outfile_name = sys.argv[1][0:end-3] + "mat"
infile_name = sys.argv[1]


iqData = np.loadtxt(infile_name, dtype=int, skiprows=1)
IQ = iqData[...,0] + 1j*iqData[...,1]

savemat(outfile_name, {'IQ':IQ})







