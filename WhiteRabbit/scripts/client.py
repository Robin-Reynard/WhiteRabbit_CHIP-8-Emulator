import socket
import sys
import numpy as np
from PIL import Image
import base64
from io import BytesIO


# Create a TCP/IP socket
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Connect the socket to the port where the server is listening
server_address = ('192.168.0.143', 45867)
print(sys.stderr, 'connecting to %s port %s' % server_address)
sock.connect(server_address)
data = 'This is the message.  It will be repeated.'
len_data = len(data)

def try_send_data():
    print(sys.stderr, 'sending "%s"' % data)
    sock.sendall(data.encode())
def try_receive_data(amount_expected=len_data):
    # Look for the response
    amount_received = 0
    
    while amount_received < amount_expected:
        data = sock.recv(len_data)
        amount_received += len_data
        print(sys.stderr, 'received "%s"' % data)

def try_receive_image():
    # Look for the response
    amount_received = 0
    image_data = bytearray(b'')
    
    while amount_received < 2048:
        data = sock.recv(len_data)
        amount_received += len_data
        image_data.extend(data)
    return image_data

try:
    data = '{"request": "GET_IMAGE"}'
    try_send_data()
    received_image = try_receive_image()

    print(received_image)

    pixels = np.frombuffer(received_image, dtype=np.uint8).reshape((32, 64))
    pixels[pixels > 0.5] = 255
    print(pixels)
    #pixels2 = np.where(pixels<1,0,255)
    image = Image.fromarray(pixels)
    image = image.resize((640,320))
    #image.show()

    data = '{"request": "GET_CHIP8_INFO"}'
    try_send_data()
    try_receive_data()

    data = '{"request": "PUBLISH_COMMAND", "command_keystroke": "A", "command_duration":"5"}'
    try_send_data()
    try_receive_data()

    data = '{"request": "PUBLISH_TEXT","text": "Hello there!"}'
    try_send_data()
    try_receive_data()

    buff = BytesIO()
    image.save(buff, format="JPEG")
    img_str = base64.b64encode(buff.getvalue()).decode()
    print(img_str)
    data = '{"request": "PUBLISH_IMAGE","image": " ' + img_str + '"}'
    try_send_data()
    try_receive_data()
    

finally:
    print(sys.stderr, 'closing socket')
    sock.close()