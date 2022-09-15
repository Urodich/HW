import collections
from email.mime import image
from queue import Queue
import queue
from PIL import Image
import numpy as np

loop=False
angle=0
max_angle=0

q=[]
Path=[]

pixx = np.asarray(Image.open('./картинки/1.bmp').convert('L'))
pix=pixx.copy()
for i in range(30):
    for j in range(30):
        if pix[i][j]<200:
            pix[i][j]=0

A=[[np.array([0,0,0]) for i in range(30)]for i in range(30)]


def Step(vect, tail):
    i=tail[-1][0]
    j=tail[-1][1]

    if i<0 or j<0 or i>29 or j>29: return
    if pix[i][j]!=0: return     #условия

    Path.append([vect,tail])

    # cur_vec = np.array([0,0,0])     #векторы
    # for elem in tail:
    #     cur_vec=cur_vec+A[elem[0]][elem[1]]
    # cur_vec=cur_vec+vect

    # if np.linalg.norm(cur_vec)!=0:
    #     cur_vec=cur_vec/np.linalg.norm(cur_vec)
    # A[tail[-1][0]][tail[-1][1]]=cur_vec
    
    #доп шаги
    pix[i][j]=-1

    if len(tail)==5: tail.pop(0)
 
    q.append( [np.array([-1, -1,0]), tail+[[i-1,j-1]]])
    q.append( [np.array([-1, 0,0]), tail+[[i-1, j]]])
    q.append( [np.array([-1, 1,0]), tail+[[i-1, j+1]]])
    q.append( [np.array([0, -1,0]), tail+[[i, j-1]]])
    q.append([ np.array([0, 1,0]), tail+[[i, j+1]]])
    q.append([ np.array([1, -1,0]), tail+[[i+1, j-1]]])
    q.append( [np.array([1, 0,0]), tail+[[i+1, j]]])
    q.append( [np.array([1, 1,0]), tail+[[i+1, j+1]]])


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


def start():
    for i in range(30):
        for j in range(30):
            if pix[i][j]==0:
                start=[i,j]
                q.append([np.array([0, 0,0]), [[i,j]]])
                return

start()

indx=0
while indx<len(q):
    i=q[indx]
    Step(i[0],i[1])
    indx+=1
print("steps = ", indx)
print("points = ", len(Path))

for i in Path:
    wind(i[0],i[1])

def view():
    red = [[abs(i[0]*255) for i in j] for j in A]
    green = [[abs(i[1]*255) for i in j] for j in A]
    blue = [[abs(i[2]*255) for i in j] for j in A]
    

    out_data = np.stack((red, green, blue), axis=2).astype('uint8')
    out_img = Image.fromarray(out_data)
    out_img.show()


#Image.fromarray(pix).show()
view()
#print("loop",loop)