import random
import re
import socket
import sys
import time

from func import *

# ! Add error Handling
retChunks = []
dic = {}
ParDic = {}
retMatrix = []
size=50
try:
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM, 0)
except socket.error,e:
    print "Error creating socket: %s" % e
    sys.exit(1)

port = 12345
s.bind(('0.0.0.0', port))
s.listen(5)
while True:
    reI = []
    reJ = []
    retChunks = []
    parChunks = []
    dic = {}
    retMatrix = []
    parMatrix = []
    retParityMatrix = []
    c, addr = s.accept()
    print('Got connection from', addr)    
    RetSize = c.recv(1024)
    getIterSize = int(totSize.findall(RetSize)[0])    
    c.send('Thank you for connecting')
    # // TODO: Add the if else conditions for checking Number and Row 
    for i in range(getIterSize):
        chuck = c.recv(1024)
        if(("totSize" in chuck) or ("Row" in chuck) or ("Number" in chuck)):
            retChunks.append(chuck)
            c.send("Ack")
    retChunks.append(c.recv(1024))
    c.send("Ack")
    #// TODO: Add the if else conditions for checking Parity and Row
    for i in range(getIterSize):
        chuck = c.recv(1024)
        parChunks.append(chuck)
        c.send("Ack")
    parChunks.append(c.recv(1024))
    for i in range(len(retChunks)):
        key = int(block.findall(retChunks[i])[0])
        value = retChunks[i][block.search(retChunks[i]).span()[-1]:]
        dic.update({key: value})
    retreivedString = ''
    for chunk in dic.values():
        retreivedString += chunk
    retRows = re.findall(rowPattern, retreivedString)
    for row in retRows:
        tempRow = []
        for number in numModel.findall(row):
            tempRow.append(int(number))
        retMatrix.append(tempRow)
    for i in range(len(parChunks)):
        key = int(block.findall(parChunks[i])[0])
        value = parChunks[i][block.search(parChunks[i]).span()[-1]:]
        ParDic.update({key: value})
    retreivedParityString = ''
    for chunk in ParDic.values():
        retreivedParityString += chunk
    retPRows = re.findall(rowPattern, retreivedParityString)
    for row in retPRows:
        tempRow = []
        for number in parity.findall(row):
            tempRow.append(int(number))
        retParityMatrix.append(tempRow)    
    # // TODO: Make parity bit change randomly
    numChanges = random.randint(1,10)
    for i in range(numChanges):
        iRow = random.randint(0,size)
        jCol = random.randint(0,size)
        n = retMatrix[iRow][jCol]
        binNum = bin(n)
        li = list(binNum)
        try:
            randomBit = random.randint(1,len(li)-2)
            if li[randomBit] == "0":
                li[randomBit]="1"
            else:
                li[randomBit]= "0"
        except:
            pass
        retMatrix[iRow][jCol] = int(''.join(li),2)
    serComputedParMat = getParityMatrix(retMatrix)
    if(serComputedParMat == retParityMatrix):
        print("No error")
    else:
        for i in range(len(serComputedParMat)):
            for j in range(len(retParityMatrix)):
                if(serComputedParMat[i][j] != retParityMatrix[i][j]):
                    reI.append(i)
                    reJ.append(j)        
        retransBitsString = '<Retransmit>'
        for i in range(len(reJ)):
            retransBitsString += "<i>{}</i><j>{}</j>".format(reI[i], reJ[i])
        retransBitsString += '</Retransmit>'
        c.send(str(retransBitsString))
        temp= c.recv(1024)
        if "value" in temp:
            reValue = temp
        else:
            reValue = c.recv(1024)                
        values = valueModel.findall(reValue)
        print(values)
        for i in range(len(reI)):
        	retMatrix[reI[i]][reJ[i]] = values[i]
        print("Values has been retransmitted successfully")
    clientGenRandomMat = getRandomMatrix(size)
    print(common_elements(retMatrix,clientGenRandomMat))
    c.close()
