import collections
from email.mime import image
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


A=[[np.array([0,0,0]) for i in range(30)]for i in range(30)]

start=[-1,-1]

def Step(vect, tail):
    i=tail[-1][0]
    j=tail[-1][1]

    if i<0 or j<0 or i>29 or j>29: return
    if pix[i][j]!=0: return

    if start==[-1,-1]: start=[i,j]
    elif start==[i,j]: loop=True

    pix[i][j]=-1
    q.put([vect,tail])
    if tail.__len__==5: tail.pop(0)


    tail.append([i-1, j-1])
    Step( np.array([-1, -1,0]),tail)
    tail.pop()
    tail.append([i-1, j])
    Step( np.array([-1, 0,0]),tail)
    tail.pop()
    tail.append([i-1, j+1])
    Step( np.array([-1, 1,0]),tail)
    tail.pop()
    tail.append([i, j-1])
    Step( np.array([0, -1,0]),tail)
    tail.pop()
    tail.append([i, j+1])
    Step( np.array([0, 1,0]),tail)
    tail.pop()
    tail.append([i+1, j-1])
    Step( np.array([1, -1,0]),tail)
    tail.pop()
    tail.append([i+1, j])
    Step( np.array([1, 0,0]),tail)
    tail.pop()
    tail.append([i+1, j+1])
    Step( np.array([1, 1,0]),tail)
    tail.pop()

    return

def wind(vect, track):
    cur_vec = np.array([0,0,0])
    for i in track:
        cur_vec=cur_vec+(A[i[0]][i[1]])
    cur_vec=cur_vec+vect

    
    if np.linalg.norm(cur_vec)!=0:
        cur_vec=cur_vec/np.linalg.norm(cur_vec)
    A[track[-1][0]][track[-1][1]]=cur_vec
    return



for i in range(30):
    for j in range(30):
        if pix[i][j]==0:
            start=[i,j]
            Step(np.array([0, 0,0]), [[i,j]])
            break


while not q.empty():
    i=q.get()
    wind(i[0],i[1])

def view():
    red = [[i[0]*255 for i in j] for j in A]
    green = [[i[1]*255 for i in j] for j in A]
    blue = [[i[2]*255 for i in j] for j in A]
    

    out_data = np.stack((red, green, blue), axis=2).astype('uint8')
    out_img = Image.fromarray(out_data)
    out_img.show()

view()
print("loop",loop)