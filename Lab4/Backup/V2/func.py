import re
import random

def getCompileModel(tag):
    return re.compile("<{}>(\d+)</{}>".format(tag, tag), re.IGNORECASE)


def getParity(number):
    if bin(number).count('1') == 1:
        return 1
    else:
        return 0

def getParityMatrix(mat):
    parMat = []
    for row in mat:
        tempRow = []
        for number in row:
            tempRow.append(getParity(int(number)))
        parMat.append(tempRow)
    return parMat


    def getParityMatrix(mat):
        parMat = []
    for row in mat:
        tempRow = []
        for number in row:
            tempRow.append(getParity(int(number)))
        parMat.append(tempRow)
    return parMat

def getRandomMatrix(size):
    mat = []
    for i in range(size):
        row = []
        for j in range(size):
            row.append(random.randint(1, 1000))
        mat.append(row)
    return mat

def common_elements(list1, list2):
    commonElements=[]
    for i in range(len(list1)):
        commonElements.append(list(element for element in list1[i] if element in list2[i]))
    return commonElements

arrSize = getCompileModel('Size')
parity = getCompileModel('Parity')
rowPattern = r"<Row>(.*)</Row>"
numModel = getCompileModel('Number')
totSize = getCompileModel('totSize')
block = getCompileModel('b')
valueModel = getCompileModel("value")



