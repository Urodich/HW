import os
Stops=set()
with open("./lab2/stop-ru.txt","r",encoding="utf8") as f:
    for i in f:
        Stops.append(i[0:-1])

texts=[]
for filename in os.scandir("./lab2/тексты"):
    if filename.is_file():
        with open(filename.path,"r",encoding="utf8") as f:
            texts.append(f.read().split())
#remove stop-words
for i in texts:
    for word in i:
        if word in Stops:
            i.remove(word)

