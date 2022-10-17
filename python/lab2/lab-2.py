import os
import struct
from unicodedata import name
from nltk.stem import SnowballStemmer

PS=SnowballStemmer(language="russian")
tokens=[]
Stops=set()
symbols=['.', ',', '!', '?', '`', ' - ', ':', ';', '"', '','1','2','3,','4','5','6','7','8','9','0']

def Start():
    with open("./lab2/stop-ru.txt","r",encoding="utf8") as f:
        for i in f:
            Stops.add(i[0:-1])

    texts=[]
    for filename in os.scandir("./lab2/тексты"):
        if filename.is_file():
            with open(filename.path,"r",encoding="utf8") as f:
                texts.append(f.read().lower().split())

    #remove stop-words
    for i in texts:
        for word in i:
            for sym in symbols:
                word.replace(sym,"")
            if word in Stops:
                i.remove(word)
    for text in texts:
        for i in range(len(text)):
            text[i]=PS.stem(text[i])

    

    for i in range(len(texts)):
        tokens.append(dict())
        for word in texts[i]:
            if word in tokens[i]:
                tokens[i][word]+=1
            else:
                tokens[i][word]=1

def Search():
    search=input("input the phrase: ").lower().split()

    for word in search:
            if word in Stops:
                search.remove(word)
            for sym in symbols:
                word.replace(sym,"")
    for i in range(len(search)):
        search[i]=PS.stem(search[i])
    print(search)
    rate=[0]*len(tokens)

    for i in range(len(tokens)):
        for word in search:
            if word in tokens[i]:
                rate[i]+=tokens[i][word]
    return rate

Results=[]

def Result(rate):
    i=0
    for filename in os.scandir("./lab2/тексты"):
        Results.append([filename.name, rate[i]])
        i+=1
    Results.sort(key= lambda x:x[1], reverse=True)
    for i in Results:
        print(i[0], "  совпадений: ",i[1])

Start()
Result(Search())