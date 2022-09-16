import collections
from email.mime import image
import os
from queue import Queue
import queue
from typing import List, Tuple
from PIL import Image
import numpy as np

TAIL=5                      #4
ANGLE=0.92  #cos of angle   #0.93
COUNT = 16  #pictures       #16
RESOLUTION=30               #30


loop=False
angles=0

def transform(id, vector):
    q=[]
    Path=[]

    pixx = np.asarray(Image.open('./картинки/'+str(id+1)+'.bmp').convert('L'))
    pix=pixx.copy()
    for i in range(RESOLUTION):
        for j in range(RESOLUTION):
            if pix[i][j]<200:
                pix[i][j]=0
    
    A=[[np.array([0,0,0]) for i in range(RESOLUTION)]for i in range(RESOLUTION)]

    def Step(vect, tail):
        i=tail[-1][0]
        j=tail[-1][1]

        if i<0 or j<0 or i>RESOLUTION-1 or j>RESOLUTION-1: return
        if pix[i][j]!=0: return     #условия

        Path.append([vect,tail])
        
        #доп шаги
        pix[i][j]=-1

        if len(tail)==TAIL: tail.pop(0)
    
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

        value=np.dot(A[track[-1][0]][track[-1][1]], A[track[0][0]][track[0][1]])
        if(value>ANGLE): value = 1
        else: value=0

        pix[track[-1][0]][track[-1][1]]+=150
        pix[track[0][0]][track[0][1]]=value*150

        if((A[track[0][0]][track[0][1]]==(np.array([0,0,0]))).all()): 
            pix[track[0][0]][track[0][1]]=155
        return


    def start():
        for i in range(RESOLUTION):
            for j in range(RESOLUTION):
                if pix[i][j]==0:
                    start=[i,j]
                    q.append([np.array([0, 0,0]), [[i,j]]])
                    return

    def view():
        red = [[abs(i[0]*255) for i in j] for j in A]
        green = [[abs(i[1]*255) for i in j] for j in A]
        blue = [[abs(i[2]*255) for i in j] for j in A]
        

        out_data = np.stack((red, green, blue), axis=2).astype('uint8')
        out_img = Image.fromarray(out_data)
        return out_img

    start()
    indx=0

    while indx<len(q):
        i=q[indx]
        Step(i[0],i[1])
        indx+=1

    for i in Path:
        wind(i[0],i[1])
        
    if(vector): return view()
    else: return Image.fromarray(pix)


#коллажик 
def find_multiples(number : int):
    multiples = set()
    for i in range(number - 1, 1, -1):
        mod = number % i
        if mod == 0:
            tup = (i, int(number / i))
            if tup not in multiples and (tup[1], tup[0]) not in multiples:
                multiples.add(tup)
                
    if len(multiples) == 0:
        mod == number % 2
        div = number // 2
        multiples.add((2, div + mod))
        
    return list(multiples)

def get_smallest_multiples(number : int, smallest_first = True) -> Tuple[int, int]:
    multiples = find_multiples(number)
    smallest_sum = number
    index = 0
    for i, m in enumerate(multiples):
        sum = m[0] + m[1]
        if sum < smallest_sum:
            smallest_sum = sum
            index = i
            
    result = list(multiples[i])
    if smallest_first:
        result.sort()
        
    return result[0], result[1]
    
def create_collage(listofimages : List[str], n_cols : int = 0, n_rows: int = 0, 
                   thumbnail_scale : float = 1.0, thumbnail_width : int = 0, thumbnail_height : int = 0):
    
    n_cols = n_cols if n_cols >= 0 else abs(n_cols)
    n_rows = n_rows if n_rows >= 0 else abs(n_rows)
    
    n_cols = 4
    n_rows = 4

    if n_cols == 0 and n_rows != 0:
        n_cols = len(listofimages) // n_rows
        
    if n_rows == 0 and n_cols != 0:
        n_rows = len(listofimages) // n_cols
        
    if n_rows == 0 and n_cols == 0:
        n_cols, n_rows = get_smallest_multiples(len(listofimages))
    
    thumbnail_width = 0 if thumbnail_width == 0 or n_cols == 0 else round(thumbnail_width / n_cols)
    thumbnail_height = 0 if thumbnail_height == 0 or n_rows == 0 else round(thumbnail_height/n_rows)
    
    all_thumbnails : List[Image.Image] = []
    for p in listofimages:
        thumbnail = p#Image.open(p)
        if thumbnail_width * thumbnail_scale < thumbnail.width:
            thumbnail_width = round(thumbnail.width * thumbnail_scale)
        if thumbnail_height * thumbnail_scale < thumbnail.height:
            thumbnail_height = round(thumbnail.height * thumbnail_scale)
        
        thumbnail.thumbnail((thumbnail_width, thumbnail_height))
        all_thumbnails.append(thumbnail)

    new_im = Image.new('RGB', (thumbnail_width * n_cols, thumbnail_height * n_rows), 'white')
    
    i, x, y = 0, 0, 0
    for col in range(n_cols):
        for row in range(n_rows):
            if i > len(all_thumbnails) - 1:
                continue
            
            #print(i, x, y)
            new_im.paste(all_thumbnails[i], (x, y))
            i += 1
            y += thumbnail_height
        x += thumbnail_width
        y = 0

    destination_file = os.path.join(os.path.dirname("./results/"), f"Angle = {ANGLE} Tail = {TAIL}.jpg")
    new_im.show()
    # if os.path.exists(destination_file):
    #     os.remove(destination_file)
    # new_im.save(destination_file)

def test_part1():
    images=[]
    for i in range(COUNT):
        images.append(transform(i, False))

    create_collage(images)

def test_part1_vector():
    vectors=[]
    for i in range(COUNT):
        vectors.append(transform(i, True))
    create_collage(vectors)

def test_part2():
    images=[]
    for i in range(COUNT):
        images.append(Image.fromarray(Union(transform(i,False))))
    create_collage(images)

def Union(image):
    pict=np.asarray(image).copy()
    points = []

    def larger(point):
        i=point[0]
        j=point[1]
        if(i>0 and j>0):pict[i-1][j-1]=0
        if(i>0):pict[i-1][j]=0
        if(i>0 and j<RESOLUTION-1):pict[i-1][j+1]=0
        if(j>0):pict[i][j-1]=0
        if(j<RESOLUTION-1):pict[i][j+1]=0
        if(i<RESOLUTION-1 and j>0):pict[i+1][j-1]=0
        if(i<RESOLUTION-1):pict[i+1][j]=0
        if(i<RESOLUTION-1 and j<RESOLUTION-1):pict[i+1][j+1]=0

    for i in range(RESOLUTION):
        for j in range(RESOLUTION):
            if pict[i][j]==0: points.append([i,j])
    for i in points:
        larger(i)
    return pict

#test_part1()
test_part2()