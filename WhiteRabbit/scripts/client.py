import socket
import sys

# Create a TCP/IP socket
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Connect the socket to the port where the server is listening
server_address = ('192.168.0.143', 43985)
print(sys.stderr, 'connecting to %s port %s' % server_address)
sock.connect(server_address)
data = 'This is the message.  It will be repeated.'
len_data = len(data)

def try_send_data():
    print(sys.stderr, 'sending "%s"' % data)
    sock.sendall(data.encode())
def try_receive_data():
    # Look for the response
    amount_received = 0
    amount_expected = len_data
    
    while amount_received < amount_expected:
        data = sock.recv(len_data)
        amount_received += len_data
        print(sys.stderr, 'received "%s"' % data)

try:
    data = "Hello There"
    try_send_data()
    try_receive_data()

    data = "General Kenobi"
    try_send_data()
    try_receive_data()

    data = ":D"
    try_send_data()
    try_receive_data()

    

finally:
    print(sys.stderr, 'closing socket')
    sock.close()