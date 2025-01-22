import io
import socket
import sys
import time
import numpy as np
from PIL import Image
import base64
from io import BytesIO
from PyQt5.QtWidgets import QApplication, QMainWindow
from PyQt5.QtCore import QByteArray, QDataStream, QIODevice, QTimer
from PyQt5.QtNetwork import QTcpSocket

class DemoClient():
    CHIP8_IMAGE_FORMAT = (32, 64)
    def __init__(self, ip, port):

        self.socket = QTcpSocket()
        self.connect_to_server(ip, port)
        self.run_publish_text_command()
        screen_capture = self.run_get_screen_capture_command()
        self.run_publish_image_command(screen_capture)
        self.run_publish_command_command()
        self.close_port()


    def connect_to_server(self, ip, port):
        # Reach out to server for connection
        self.socket.connectToHost(ip, port)

        # Wait up to 5 seconds for server to establish connection
        self.wait_for_server_connection(5000)
    
    def run_publish_text_command(self):
        request = '{"request": "PUBLISH_TEXT","text": "Hello there!"}'
        self.socket.write(request.encode())
        self.socket.flush()

        print("PUBLISH_TEXT request sent! Waiting for server response")
        self.wait_for_server_response(1000)

        # Read the response from the server
        response = self.socket.readAll().data().decode()
        print("    Server says", response)
    
    def run_get_screen_capture_command(self):
        request = '{"request": "GET_SCREEN_CAPTURE"}'
        self.socket.write(request.encode())
        self.socket.flush()

        print("GET_SCREEN_CAPTURE request sent! Waiting for server response to display image")
        self.wait_for_server_response(1000)

        # Get the image from the server
        response = self.socket.readAll()
        pixels = np.frombuffer(response, dtype=np.uint8).reshape(self.CHIP8_IMAGE_FORMAT)

        # Display the image
        pixels[pixels == 1] = 255
        image = Image.fromarray(pixels)
        image = image.resize((640,320))
        image.show()

        return image
    
    def run_publish_image_command(self, screen_capture):
        # Convert PIL Image to a base64 string
        buffer = BytesIO()
        screen_capture.save(buffer, format="JPEG")
        img_str = base64.b64encode(buffer.getvalue()).decode()

        request = '{"request": "PUBLISH_IMAGE","image": " ' + img_str + '"}'
        self.socket.write(request.encode())
        self.socket.flush()

        print("PUBLISH_IMAGE request sent! Your image should be displayed in WhiteRabbit!")
        self.wait_for_server_response(1000)

        # Read the response from the server
        response = self.socket.readAll().data().decode()
        print("    Server says", response)
    
    def run_publish_command_command(self):
        request = '{"request": "PUBLISH_COMMAND","command_key": "A","command_action": "PRESS"}'
        self.socket.write(request.encode())
        self.socket.flush()
        print("PUBLISH_COMMAND PRESSED request sent! White Rabbit should be winking")
        self.wait_for_server_response(10000)
        response = self.socket.readAll().data().decode()
        print("    Server says", response)

        request = '{"request": "PUBLISH_COMMAND","command_key": "A","command_action": "RELEASE"}'
        self.socket.write(request.encode())
        self.socket.flush()
        print("PUBLISH_COMMAND RELEASE request sent! White Rabbit should be looking at you")
        self.wait_for_server_response(10000)
        response = self.socket.readAll().data().decode()
        print("    Server says", response)

        
        time.sleep(5)

        print("PUBLISH_COMMAND PRESSED request sent! White Rabbit should be winking")
        self.wait_for_server_response(10000)
        response = self.socket.readAll().data().decode()
        print("    Server says", response)
        print("PUBLISH_COMMAND RELEASE request sent! White Rabbit should be looking at you")
        self.wait_for_server_response(10000)
        response = self.socket.readAll().data().decode()
        print("    Server says", response)

        





    def wait_for_server_connection(self, time_in_ms):
        if not self.socket.waitForConnected(time_in_ms):
            print("Connection failed:", self.socket.errorString())
            exit(1)
        else:
            print("Connected to server.")

    def wait_for_server_response(self, time_in_ms):
        if not self.socket.waitForReadyRead(time_in_ms):
            print("Failed to receive data:", self.socket.errorString())
            exit(1)
    
    def close_port(self):
        self.socket.disconnectFromHost()


app = QApplication([])
client = DemoClient('127.0.0.1', 3000)
#client.start_on_connected()
#app.exec()


'''

# Create a TCP/IP socket
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

#Qt_5_12

# Connect the socket to the port where the server is listening
server_address = ('127.0.0.1', 3000)
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
    data = '{"request": "GET_SCREEN_CAPTURE"}'
    try_send_data()
    received_image = try_receive_image()

    print(received_image)

    pixels = np.frombuffer(received_image, dtype=np.uint8).reshape((32, 64))
    pixels[pixels > 0.5] = 255
    print(pixels)
    #pixels2 = np.where(pixels<1,0,255)
    image = Image.fromarray(pixels)
    image = image.resize((640,320))
    image.show()
    
    data = '{"request": "PUBLISH_COMMAND","command_key": "B","command_action": "PRESS"}'
    try_send_data()
    try_receive_data()


    data = '{"request": "GET_CHIP8_INFO"}'
    try_send_data()
    try_receive_data(1000)

    
    data = '{"request": "PUBLISH_COMMAND","command_key": "A","command_action": "RELEASE"}'
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
    sock.close()'''