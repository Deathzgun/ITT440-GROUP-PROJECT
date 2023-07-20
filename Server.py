#server

import socket
import datetime

def handle_client(client_socket):
    # Receive data from the client
    data = client_socket.recv(1024).decode('utf-8')

    # Manipulate incoming text with server's current date and time
    current_time = datetime.datetime.now().strftime("%d %B %Y, %H:%M")
    combined_text = f"{data} received at {current_time}"

    # Send the modified text back to the client
    client_socket.send(combined_text.encode('utf-8'))

    # Close the connection
    client_socket.close()

def start_server():
    # Create a socket object
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    # Bind the socket to a specific IP address and port
    server_address = ('', 8484)
    server_socket.bind(server_address)

    # Listen for incoming connections
    server_socket.listen(5)
    print('Server listening on port 8484...')

    while True:
        # Accept a client connection
        client_socket, client_address = server_socket.accept()
        print(f'Accepted connection from {client_address[0]}:{client_address[1]}')

        # Handle the client in a separate thread
        handle_client(client_socket)

start_server()
