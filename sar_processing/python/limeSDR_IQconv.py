import numpy as np
import matplotlib.pyplot as plt


#pulls in a 2D colvec. The 1st channel is  I, the next is Q. So yeah. 

adcRes = 16 #ADC resolution in bits

filename = "60MHzbw_2450fc_term_16bit.txt"
#filename = "60MHzbw_2450fc_toneAt2470_16bit.txt"




iqData = np.loadtxt(filename, dtype=int)

iqData = iqData/(2**adcRes)
print(iqData)
np.savetxt('iqVals--TERM--16Bit.csv', iqData, fmt="%f", delimiter=",")












iqData = iqData.T

I = iqData[0][:]
Q = iqData[1][:]

IQ = I + 1j*Q
fft = np.fft.fft(IQ)
plt.figure(1)
plt.plot(np.abs(np.fft.fftshift(fft)))

plt.figure(3)
plt.plot(10*np.log10(np.abs(np.fft.fftshift(fft))))

plt.figure(4)
plt.plot(np.real(IQ))

