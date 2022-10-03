from copy import copy
import os
from queue import Queue
import queue
from typing import List, Tuple
from PIL import Image, ImageChops
import numpy as np


#параметры программы
                            #best
TAIL=4                      #4          влияет на скорость изменения вектора
ANGLE=0.9  #cos of angle   #0.9         отделяет угол от прямой
COUNT = 16  #pictures       #16
RESOLUTION=30               #30

#функция находит углы
def transform(image, vector):
    q=[]
    Path=[]

    #предобработка изображения на всякий случай
    pixx = np.asarray(image)
    pix=pixx.copy()
    for i in range(RESOLUTION):
        for j in range(RESOLUTION):
            if pix[i][j]<200:
                pix[i][j]=0
    
    A=[[np.array([0,0,0]) for i in range(RESOLUTION)]for i in range(RESOLUTION)]

    #проходит по закрашенным точкам и добавляет их в очередь
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

    #проходит по очереди и сопоставляет каждой точке вектор 
    def wind(vect, track):
        cur_vec = np.array([0,0,0])
        for i in track:
            cur_vec=cur_vec+(A[i[0]][i[1]])
        cur_vec=cur_vec+vect

        if np.linalg.norm(cur_vec)!=0:
            cur_vec=cur_vec/np.linalg.norm(cur_vec)
        A[track[-1][0]][track[-1][1]]=cur_vec
    #изменяет цвет точек в зависимости от изменения вектора по пути обхода
        value=np.dot(A[track[-1][0]][track[-1][1]], A[track[0][0]][track[0][1]])
        if(value>ANGLE): value = 1
        else: value=0

        pix[track[-1][0]][track[-1][1]]+=150
        pix[track[0][0]][track[0][1]]=value*150

        if((A[track[0][0]][track[0][1]]==(np.array([0,0,0]))).all()): 
            pix[track[0][0]][track[0][1]]=155
        return

    #поиск начальной точки
    def start():
        for i in range(RESOLUTION):
            for j in range(RESOLUTION):
                if pix[i][j]==0:
                    start=[i,j]
                    q.append([np.array([0, 0,0]), [[i,j]]])
                    return
    #просмотр векторной формы
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
#повторный проход для повернутого изображения
def double_check(image):
    image_copy=copy(image)
    image_copy=image_copy.rotate(180)

    image1=(transform(image, False))
    image2=(transform(image_copy, False).rotate(180))

    im3 = ImageChops.multiply(image1, image2)
   
    return im3

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
#коллажик
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
#коллажик 
def create_collage(listofimages : List[str], isSave=False, n_cols : int = 0, n_rows: int = 0, 
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
    if (isSave):
        if os.path.exists(destination_file):
            os.remove(destination_file)
        new_im.save(destination_file)
#расширение найденных точек 
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
 
def angle_count(pict):
    
    def Clean(i,j):
            pict[i][j]=150
            for x in range(i-1,i+2):
                for y in range(j-1,j+2):
                    if(x>=0 and y>=0 and x<RESOLUTION and y<RESOLUTION and pict[x][y]==0): Clean(x,y)
    angls=0
    for i in range(RESOLUTION):
        for j in range(RESOLUTION):
            if(pict[i][j]==0):
                angls+=1
                Clean(i,j)
    return angls

def loop_check(image):
    pict = np.asarray(image).copy()
    def Clean(x,y):
            pict[x][y]=150
            if(x+1<RESOLUTION and pict[x+1][y]==255): Clean(x+1,y)
            if(x>0 and pict[x-1][y]==255): Clean(x-1,y)
            if(y+1<RESOLUTION and pict[x][y+1]==255): Clean(x,y+1)
            if(y>0 and pict[x][y-1]==255): Clean(x,y-1)

    def Start():
        for x in range(RESOLUTION):
            for y in range(RESOLUTION):
                if(pict[x][y]==255):
                    Clean(x,y)
                    return
    
    Start()

    #Image.fromarray(pict).show()
    for i in range(RESOLUTION):
        for j in range(RESOLUTION):
            if (pict[i][j]==255):return True
    return False

def Conclusion(loop, angles):
    if(loop==False):
        if(angles==0): print("прямая")
        else: print("ломанная")
    else:
        if(angles==0):print("круг")
        elif(angles<3): print("овал")
        elif(angles==3): print("треугольник")
        elif(angles==4): print("квадрат")
        else: print("круг")
            
#tests
def test_part1():
    images=[]
    vectors=[]
    for i in range(COUNT):
        image = Image.open('./картинки/'+str(i+1)+'.bmp').convert('L')
        images.append(transform(image, False))
        vectors.append(transform(image, True))
    create_collage(vectors)
    create_collage(images)

def test_part2(save):
    images=[]
    for i in range(COUNT):
        image = Image.open('./картинки/'+str(i+1)+'.bmp').convert('L')
        images.append(Image.fromarray(Union(double_check(image))))
    create_collage(images, save)
    return images

def test_part3(images):
    for image in images:
        ang = angle_count(np.asarray(image).copy())
        loop=loop_check(image)
        Conclusion(loop, ang)

#test_part1()
# test_part2(False)
#test_part3(test_part2(False))

print()
for i in range(COUNT):
        image = Image.open('./lab1/картинки/'+str(i+1)+'.bmp').convert('L')
        mod_pict=Union(double_check(image))
        Conclusion(loop_check(image),angle_count(mod_pict))
        