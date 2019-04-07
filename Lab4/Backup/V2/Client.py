import socket
import re
import random
import time
from func import *

# ! Add error Handling

chunks = []
parChunks = []
dic = {

}

def getCompileModel(tag):
    return re.compile("<{}>(\d+)</{}>".format(tag, tag), re.IGNORECASE)


def encapsulateData(Mat):
    totalString = '<Matrix>'
    for row in Mat:
        rowstring = '<Row>'
        for number in row:
            rowstring += "<Number>"+str(number)+"</Number>"
        rowstring += "</Row> \n"
        totalString += rowstring
    return totalString+"</Matrix>"


def getRandomMatrix(size):
    mat = []
    for i in range(size):
        row = []
        for j in range(size):
            row.append(random.randint(1, 1000))
        mat.append(row)
    return mat


def encapsulateParityMatrix(parMat):
    requiredString = "<Matrix>"
    for row in parMat:
        requiredString += "<Row>"
        for digit in row:
            requiredString += "<Parity>{}</Parity>".format(digit)
        requiredString += "</Row> \n"
    return requiredString+"</Matrix>"


arrSize = getCompileModel('Size')
parity = getCompileModel('Parity')
rowPattern = r"<Row>(.*)</Row>"
numModel = getCompileModel('Number')
totSize = getCompileModel('totSize')
block = getCompileModel('b')
Parity = getCompileModel(tag='Parity')
iNode = getCompileModel(tag="i")
jNode = getCompileModel(tag="j")

size=50
Mat = getRandomMatrix(size=size)
requiredString = encapsulateData(Mat)
totalChunks = len(requiredString)/1000

parityMatrix = getParityMatrix(mat=Mat)
parityString = encapsulateParityMatrix(parMat=parityMatrix)

if len(requiredString) % 1000 != 0:
    residualChunk = 1
else:
    residualChunk = 0

for chunkNumber in range(totalChunks):
    chunks.append("<b>{}</b>".format(chunkNumber) +
                  requiredString[chunkNumber*1000:(chunkNumber+1)*1000])
chunks.append("<b>{}</b>".format(totalChunks) +
              requiredString[totalChunks*1000:])
chunks.insert(0, "<totSize>{}</totSize>".format(totalChunks+1))
for chunkNumber in range(totalChunks):
    parChunks.append("<b>{}</b>".format(chunkNumber) +
                     parityString[chunkNumber*1000:(chunkNumber+1)*1000])
parChunks.append("<b>{}</b>".format(totalChunks) +
                 parityString[totalChunks*1000:])

s = socket.socket()
ports = 12345
portc = 32451
s.connect(('127.0.0.1', ports))
s.send(chunks[0])
# print(s.recv(1024))
for i in range(totalChunks+2):
    s.send(str(chunks[i]))
    s.recv(1024)
s.send(str(chunks[-1]))
s.recv(1024)
for i in range(totalChunks+1):
    s.send(str(parChunks[i]))
    s.recv(1024)
s.send(str(parChunks[-1]))
s.send("Ack")
reTranmitString=s.recv(1024)
allIs = iNode.findall(reTranmitString)
allJs = jNode.findall(reTranmitString)
reTransmitString ='<re>'
for i in range(len(allIs)):
    reTranmitString+="<correct><i>{}</i><j>{}</j><value>{}</value>".format(allIs[i],allJs[i],Mat[i][i])
s.send(reTranmitString+"</re>")
s.close()
