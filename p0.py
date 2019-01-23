##
 # @fileoverview Project 0 <Celluar Automata> for PHYS498
 # @author Yukun Jin <yjin44@illinois.edu>
 #
import matplotlib.pyplot as plt
import numpy as np
import gzip
import sys
id = 0
compressed_size = []
sweeps = np.zeros(10000)
sweeps = np.arange(0,10000,1)
while(id<10000):
    file = open('state_file/'+str(id),'r')
    state = file.readlines()
    a = []
    for line in state:
        site = line.split()
        a.append(site)
    mat = np.zeros((100,100))
    for i in range(len(a)):
        for j in range(len(a[i])):
            mat[i][j] = int(a[i][j])
    plt.show(plt.matshow(mat))
    id+=499

i=0
while(i<10000):
    file_2 = open('state_file/'+str(i),'r')
    data = file_2.read()
    compressed_size.append(sys.getsizeof(gzip.compress(bytes(data,'utf-8'))))
    i+=1
compressed_size_np = np.array(compressed_size)
plt.plot(sweeps,compressed_size_np)
plt.xlabel('sweeps')
plt.ylabel('Number of compressed bits')
plt.show()
