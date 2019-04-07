import socket
import re
import time
import random
from func import *

# ! Add error Handling

retChunks = []
dic = {}
ParDic = {}
retMatrix = []
size=50
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM, 0)
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
    print("Iter Size", getIterSize)
    c.send('Thank you for connecting')
    # TODO: Add the if else conditions for checking Number and Row
    for i in range(getIterSize):
        chuck = c.recv(1024)
        retChunks.append(chuck)
        c.send("Ack")
    retChunks.append(c.recv(1024))
    c.send("Ack")
    # TODO: Add the if else conditions for checking Parity and Row
    for i in range(getIterSize):
        parChunks.append(c.recv(1024))
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
    serComputedParMat = getParityMatrix(retMatrix)
    # TODO: Make parity bit change randomly
    if retParityMatrix[4][5] == 1:
        retParityMatrix[4][5] = 0
    else:
        retParityMatrix[4][5] = 1
    if retParityMatrix[15][5] == 1:
        retParityMatrix[15][5] = 0
    else:
        retParityMatrix[15][5] = 1
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
    print(retParityMatrix, serComputedParMat)
    c.close()
