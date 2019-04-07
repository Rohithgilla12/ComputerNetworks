import socket               # Import socket module
import random
import pickle
 
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM, 0)         # Create a socket object
port = 12345                # Reserve a port for your service.
s.bind(('0.0.0.0', port))        # Bind to the port

def checkParity(binArr):
	counter2=False
	rowBit=-1
	colBit=-1
	for i in range(len(binArr)-1):
		temp=[row[i] for row in binArr]		
		if(temp[:-1].count(1)%2 != 0):
			if(temp[-1] == 1):
				counter2=True
			else:
				print(i)
				counter2=False
				colBit = i
				break
	counter=False
	for i in range(len(binArr)-1):
		if(binArr[i][:-1].count(1)%2 !=0):
			if(binArr[i][-1] == 1):
				counter=True
			else:
				print(i)
				counter = False
				rowBit = i
				break
		else:	
			if(binArr[i][-1] ==0):
				counter = True
			else:
				counter= False
				rowBit = i
	print("RowBit",rowBit,"ColBit",colBit)
	if (colBit!= -1 and rowBit!=-1):
		return False
	else:
		return True
s.listen(5)                 # Now wait for client connection.
while True:
   c, addr = s.accept()     # Establish connection with client.
   print 'Got connection from', addr
   c.sendall('Thank you for connecting')
   numString = c.recv(1024)
   numArr = pickle.loads(numString)
   if(checkParity(numArr)):
		print("No Error Detected")
   else:
		print("Eror detected is")
   print("Before Processing",numArr)
   
   c.close()                # Close the connection




# import socket               # Import socket module
# import random
# import pickle
 
# s = socket.socket(socket.AF_INET, socket.SOCK_STREAM, 0)         # Create a socket object
# # host = socket.gethostbyname(socket.gethostname()) # Get local machine name
# port = 12345                # Reserve a port for your service.
# s.bind(('0.0.0.0', port))        # Bind to the port

# def checkParity(binArr):
# 	counter=False
# 	for i in range(len(binArr)-1):
# 		if(binArr[i][:-1].count(1)%2 !=0):
# 			if(binArr[i][-1] == 1):
# 				counter=True
# 			else:
# 				return False
# 		else:
# 			if(binArr[i][-1] ==0):
# 				counter = True
# 			else:
# 				return False
# 	return counter


# s.listen(5)                 # Now wait for client connection.
# while True:
#    c, addr = s.accept()     # Establish connection with client.
#    print('Got connection from', addr)
#    c.sendall('Thank you for connecting')
#    numString = c.recv(1024)
#    numArr = pickle.loads(numString)
#    if(checkParity(numArr)):
    	   
# 		print("No Error Detected")
#    else:
# 		print("Eror detected is")
#    print(("Before Processing",numArr))
   
#    c.close()                # Close the connection




