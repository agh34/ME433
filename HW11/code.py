import board
import time
import digitalio
import analogio

from ulab import numpy as np # to get access to ulab numpy functions
# Declare an array with some made up data like
a = np.array([1,3,5,2,4,8,10])
# Test some stats functions, like
# print(np.min(a))
# print(np.max(a))
# print(np.median(a))

arr = np.linspace(0, 50, 1024)

sin1 = np.sin(2*np.pi*arr)
sin2 = np.sin(10*np.pi*arr)
sin3 = np.sin(50*np.pi*arr)


sinsum = sin1 + sin2 + sin3
#print
Y = np.fft.fft(sinsum)

for j in range(len(Y[0])):
    print(f"({abs(Y[0][j])})")
    time.sleep(0.05)
