import socket               # Import socket module
import random

def common_elements(list1, list2):
    return [element for element in list1 if element in list2]
    
def getMyNumberList(numString):
    numArray=[]
    numSArray=numString.split(',')
    numSArray.pop()
    for i in numSArray:
        try:
            numArray.append(int(i))
        except ValueError:
            pass
    return numArray

def getMyrandom(number):
    randList=[]
    for i in range(number):
        randList.append(random.randint(0,100))
    return randList

def makeString(numArray):
    ret=""
    for number in numArray:
        ret+=str(number)+","
    return ret
    
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM, 0)         # Create a socket object
host = socket.gethostbyname(socket.gethostname()) # Get local machine name
port = 12345                # Reserve a port for your service.
s.bind((host, port))        # Bind to the port

print 'host ip', host
s.listen(5)                 # Now wait for client connection.
while True:
   c, addr = s.accept()     # Establish connection with client.
   print 'Got connection from', addr
   c.sendall('Thank you for connecting')
   numString = c.recv(1024)
   numClientString,greeting=numString.splitlines()[0],numString.splitlines()[-1]
   numArrayClient = getMyNumberList(numClientString)
   numArrayServer = getMyrandom(25)
   print("Before Processing",numClientString)
   print("Array from Client:",numArrayClient,"Server Array",numArrayServer)
   common= common_elements(numArrayClient,numArrayServer)
   common.sort()
   comStr=makeString(common)
   c.sendall(comStr)   
   c.close()                # Close the connection
