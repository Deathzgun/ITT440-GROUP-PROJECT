#client

import socket

# Get server IP address and port number from user input
server_ip = input("Enter server IP address: ")
server_port = int(input("Enter server port number: "))

# Create a socket object
client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Establish a connection to the server
server_address = (server_ip, server_port)
client_socket.connect(server_address)

# Get user input string
user_input = input("Enter your text: ")

# Send the user input string to the server
client_socket.send(user_input.encode('utf-8'))

# Receive the reply from the server
reply = client_socket.recv(1024).decode('utf-8')

# Print the incoming reply string from the server
print("Reply from server:", reply)

# Close the connection
client_socket.close()
