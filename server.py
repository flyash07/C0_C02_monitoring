import socket

s = socket.socket()    
print ("Socket successfully created")

port = 12370

s.bind(('192.168.173.125', port))  
print ("socket binded to %s" %(port))

s.listen(10)    
print ("socket is listening")     

while True:
    c, addr = s.accept()    
    print ('Got connection from', addr )

    while True:
        data = c.recv(1024).decode()
        print(data)
    c.close();

