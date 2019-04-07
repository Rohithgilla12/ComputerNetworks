import socket               # Import socket module
import random
import pickle
import time

def makeString(numArray):
    ret=""
    for number in numArray:
        ret+=str(number)+","
    return ret+'\n'

def getMyrandom(number):
	randomNums=[]
	for i in range(number):
		row=[]
		for j in range(number):
			row.append([0,1][random.randint(0,1)])
		randomNums.append(row)
	return randomNums
	
s = socket.socket()         # Create a socket object
# host = socket.gethostname() # Get local machine name/for this example
ports = 12345             #server port
portc = 32451 	   #client's own port for incoming connections (if any)
# s.bind((host, portc))
s.connect(('127.0.0.1', ports))

ranArr=getMyrandom(4)
#numString = makeString(ranArr)
for i in range(len(ranArr)):
	if(ranArr[i].count(1)%2 !=0):
		ranArr[i].append(1)
	else:
		ranArr[i].append(0)
if(ranArr[2][1] == 0):
	ranArr[2][1]=1
else:
	ranArr[2][1]=0

lastRow=[]
for i in range(len(ranArr)-1):
	temp=[row[0] for row in ranArr]
	if(temp.count(1)%2 !=0):
		lastRow.append(1)
	else:
		lastRow.append(0)
lastRow.append(0)
ranArr.append(lastRow)
data= pickle.dumps(ranArr)
s.send(data)
message= s.recv(1024)
print(message)
s.send("It was nice talking to you ")
try:
	time.sleep(1)
	message= s.recv(1024)	
	print(message)
except socket.error:
	pass
s.close()                # Close the socket when done
