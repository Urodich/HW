from PIL import Image
import numpy
import vector

loop=False
angle=0
max_angle=0

pix = numpy.asarray(Image.open('./картинки/1.bmp').convert('L'))

cur_vec = vector.obj(0,0)
line_vec = vector.obj(0,0)
def Step(i,j, vect):
    if i<0 or j<0 or i>29 or j>29: return
    if pix[i][j]!=0: return
    pix[i][j]=-1

    Step(i-1, j-1, vector.obj(-1, -1))
    Step(i-1, j, vector.obj(-1, -1))
    Step(i-1, j+1, vector.obj(-1, -1))
    Step(i, j-1, vector.obj(-1, -1))
    Step(i, j+1, vector.obj(-1, -1))
    Step(i+1, j-1, vector.obj(-1, -1))
    Step(i+1, j, vector.obj(-1, -1))
    Step(i+1, j+1, vector.obj(-1, -1))

    return

for i in range(30):
    for j in range(30):
        if pix[i][j]==0:
            Step(i,j)



