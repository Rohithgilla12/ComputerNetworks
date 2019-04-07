import socket               # Import socket module
import random

randomChars="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!#$%&()*+,-./:;?@[]^_`{|}~"
def makeString(numArray):
    ret=""
    for number in numArray:
        ret+=str(number)+","
    return ret+'\n'

def getMyrandom(number):
    randList=[]
    for i in range(number):
        rr= random.randint(1,1000)
        if(rr %2 ==0):
            randList.append(random.randint(0,100))
        else:
            randList.append(randomChars[random.randint(0,len(randomChars)-1)])
    return randList

s = socket.socket()         # Create a socket object
host = socket.gethostname() # Get local machine name/for this example
ports = 12345             #server port
portc = 32451 	   #client's own port for incoming connections (if any)
s.bind((host, portc))
s.connect((host, ports))

ranArr=getMyrandom(25)
numString = makeString(ranArr)
s.send(numString)

message= s.recv(1024)
print(message)
s.send("It was nice talking to you ")
message= s.recv(1024)
print(message)
commonArr=message.split(',')
commonArr.pop()
commNumArry=[]
for i in commonArr:
    commNumArry.append(int(i))
print(commNumArry,ranArr)
s.close                     # Close the socket when done

