import csv

t = [] # column 0
d = [] #colum 1

with open('sigD.csv') as f:
    # open the csv file
    reader = csv.reader(f)
    for row in reader:
        # read the rows 1 one by one
        t.append(float(row[0])) # leftmost column
        d.append(float(row[1])) # second column

import matplotlib.pyplot as plt
import numpy as np

# plt.plot(t,d,'b-*')
# plt.xlabel('Time [s]')
# plt.ylabel('Signal')
# plt.title('Signal vs Time')
# plt.show()

dt = t[1]-t[0]

Fs = 1/dt #sample rate
Ts = 1.0/Fs
ts = np.arange(0,t[-1],Ts)
y = d
n = len(y)
k = np.arange(n)
T = n/Fs
frq = k/T
frq = frq[range(int((n/2)))]
Y = np.fft.fft(y)/n
Y = Y[range(int(n/2))]

fig, (ax1, ax2) = plt.subplots(2,1)
ax1.plot(t,y,'b')
ax1.set_xlabel('Time')
ax1.set_ylabel('Amplitude')
ax2.loglog(frq,abs(Y),'b')
ax2.set_xlabel('Freq (Hz)')
ax2.set_ylabel('|Y(freq)')
plt.show()