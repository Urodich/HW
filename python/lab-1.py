import collections
from queue import Queue
import queue
from PIL import Image
import numpy
import vector

loop=False
angle=0
max_angle=0

q=Queue()


pix = numpy.asarray(Image.open('./картинки/1.bmp').convert('L'))


line_vec = vector.obj(0,0)

A=[[vector.obj(0,0) for i in range(30)]for i in range(30)]


def Step(vect, tail):
    i=tail[0][0]
    j=tail[0][1]
    if i<0 or j<0 or i>29 or j>29: return
    if pix[i][j]!=0: return
    pix[i][j]=-1
    q.put([vect,tail])
    tail.pop(0)
    Step( vector.obj(-1, -1),tail+[i-1, j-1])
    Step( vector.obj(-1, 0),tail+[i-1, j])
    Step( vector.obj(-1, +1),tail+[i-1, j+1])
    Step( vector.obj(0, -1),tail+[i, j-1])
    Step( vector.obj(0, +1),tail+[i, j+1])
    Step( vector.obj(+1, -1),tail+[i+1, j-1])
    Step( vector.obj(+1, 0),tail+[i+1, j])
    Step( vector.obj(+1, +1),tail+[i+1, j+1])

    return

def wind(vect, track):
    cur_vec = vector.obj(0,0)
    for i in track:
        cur_vec+=vect
    A[track[0][0]][track[0][1]]=vector.normalize
    return



for i in range(30):
    for j in range(30):
        if pix[i][j]==0:
            Step(i,j)

for i in q:
    wind(i[0],i[1])

