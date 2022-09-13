import collections
from queue import Queue
import queue
from PIL import Image
import numpy as np


loop=False
angle=0
max_angle=0

q=Queue()

pixx = np.asarray(Image.open('./картинки/1.bmp').convert('L'))
pix=pixx.copy()

line_vec = np.array([0,0])

A=[[np.array([0,0]) for i in range(30)]for i in range(30)]


def Step(vect, tail):
    i=tail[-1][0]
    j=tail[-1][1]

    if i<0 or j<0 or i>29 or j>29: return
    if pix[i][j]!=0: return

    pix[i][j]=-1
    q.put([vect,tail])
    if tail.__len__==5: tail.pop(0)

    tail.append([i-1, j-1])
    Step( np.array([-1, -1]),tail)
    tail.pop()
    tail.append([i-1, j])
    Step( np.array([-1, 0]),tail)
    tail.pop()
    tail.append([i-1, j+1])
    Step( np.array([-1, 1]),tail)
    tail.pop()
    tail.append([i, j-1])
    Step( np.array([0, -1]),tail)
    tail.pop()
    tail.append([i, j+1])
    Step( np.array([0, 1]),tail)
    tail.pop()
    tail.append([i+1, j-1])
    Step( np.array([1, -1]),tail)
    tail.pop()
    tail.append([i+1, j])
    Step( np.array([1, 0]),tail)
    tail.pop()
    tail.append([i+1, j+1])
    Step( np.array([1, 1]),tail)
    tail.pop()

    return

def wind(vect, track):
    cur_vec = np.array([0,0])
    for i in track:
        cur_vec=cur_vec+(A[i[0]][i[1]])
    cur_vec=cur_vec+(vect)
    
    print(np.linalg.norm(cur_vec))
    A[track[-1][0]][track[-1][1]]=cur_vec
    return


for i in range(30):
    for j in range(30):
        if pix[i][j]==0:
            Step(np.array([0, 0]), [[i,j]])
            break

print(q.qsize())

while not q.empty():
    i=q.get()
    wind(i[0],i[1])


for i in A:
    print(i)