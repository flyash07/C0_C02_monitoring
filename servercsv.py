import socket
import csv

s = socket.socket()    
print("Socket successfully created")

port = 12370

s.bind(('192.168.173.125', port))  
print("Socket binded to %s" % port)

s.listen(10)    
print("Socket is listening")     

# Open the CSV file for writing. Data will be appended if the file already exists.
with open('sensor_data.csv', 'a', newline='') as csvfile:
    datawriter = csv.writer(csvfile)
    while True:
        c, addr = s.accept()    
        print('Got connection from', addr)

        try:
            while True:
                data = c.recv(1024).decode()
                if not data:
                    break
                print(data)

                # Write the received data to the CSV file.
                # Assuming each piece of data is a separate row.
                datawriter.writerow([data])

        finally:
            c.close()

