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


pixx = numpy.asarray(Image.open('./картинки/1.bmp').convert('L'))
pix=pixx.copy()

line_vec = vector.obj(x=0,y=0)

A=[[vector.obj(x=0,y=0) for i in range(30)]for i in range(30)]


def Step(vect, tail):
    i=tail[0][0]
    j=tail[0][1]
    if i<0 or j<0 or i>29 or j>29: return
    if pix[i][j]!=0: return
    pix[i][j]=-1
    q.put([vect,tail])
    if tail.__len__==5: tail.pop(0)
    Step( vector.obj(x=-1, y=-1),tail+[i-1, j-1])
    Step( vector.obj(x=-1, y=0),tail+[i-1, j])
    Step( vector.obj(x=-1, y=1),tail+[i-1, j+1])
    Step( vector.obj(x=0, y=-1),tail+[i, j-1])
    Step( vector.obj(x=0, y=1),tail+[i, j+1])
    Step( vector.obj(x=1, y=-1),tail+[i+1, j-1])
    Step( vector.obj(x=1, y=0),tail+[i+1, j])
    Step( vector.obj(x=1, y=1),tail+[i+1, j+1])

    return

def wind(vect, track):
    cur_vec = vector.obj(x=0,y=0)
    for i in track:
        cur_vec+=vect
    A[track[0][0]][track[0][1]]=vector.normalize
    return



for i in range(30):
    for j in range(30):
        if pix[i][j]==0:
            Step(vector.obj(x=0, y=0), [[i,j]])

for i in q:
    wind(i[0],i[1])

