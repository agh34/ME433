import csv

t = [] # column 0
d = []

with open('sigD.csv') as f:
    # open the csv file
    reader = csv.reader(f)
    for row in reader:
        # read the rows 1 one by one
        t.append(float(row[0])) # leftmost column
        d.append(float(row[1])) # leftmost column

import matplotlib.pyplot as plt
import numpy as np

f = []
A = 0.9
B = 0.1
for dp in d:
    if len(f) == 0:
        f.append(0)
    else:
        f.append(f[-1]*A+dp*B)

dt = t[1] - t[0]

Fs = 1/dt #sample rate
Ts = 1.0/Fs
ts = np.arange(0,t[-1],Ts)
y1 = d
y2 = f
n = len(y1)
k = np.arange(n)
T = n/Fs
frq = k/T
frq = frq[range(int((n/2)))]
Y1 = np.fft.fft(y1)/n
Y1 = Y1[range(int(n/2))]
Y2 = np.fft.fft(y2)/n
Y2 = Y2[range(int(n/2))]

fig, (ax1, ax2) = plt.subplots(2,1)
ax1.plot(t,y1,'b',t,y2,'r')
ax1.set_xlabel('Time')
ax1.set_ylabel('Amplitude')
ax2.loglog(frq,abs(Y1),'b',frq,abs(Y2),'r')
ax2.set_xlabel('Freq (Hz)')
ax2.set_ylabel('|Y(freq)')
ax1.set_title('A = '+str(A)+', y = '+str(B))
plt.show()