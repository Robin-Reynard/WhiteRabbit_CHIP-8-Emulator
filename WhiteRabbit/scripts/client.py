import time
import numpy as np
from PIL import Image
import base64
from io import BytesIO
from PyQt5.QtWidgets import QApplication
from PyQt5.QtNetwork import QTcpSocket

class DemoClient():
    CHIP8_IMAGE_FORMAT = (32, 64)
    
    def __init__(self, ip, port):
        self.socket = QTcpSocket()
        try:
            self.connect_to_server(ip, port)
            # Run demo commands
            self.run_publish_text_command()
            screen_capture = self.run_get_screen_capture_command(show_image=False)
            self.run_publish_image_command(screen_capture)
            self.run_publish_command_press()
            self.run_get_chip8_info_command()
            self.run_publish_command_release()
        finally:
            # Always properly close port
            self.close_port()

    ########################### SERVER REQUEST EXAMPLES ###########################
    
    def run_publish_text_command(self):
        request = '{"request": "PUBLISH_TEXT","text": "Hello there!"}'
        message = "PUBLISH_TEXT request sent! Awaiting confirmation :3"
        self.send_request(request, message)
    
    def run_publish_command_press(self):
        request = '{"request": "PUBLISH_COMMAND","command_key": "A","command_action": "PRESS"}'
        message = "PUBLISH_COMMAND PRESSED request sent! The rabbit vanished!"
        self.send_request(request, message)
        time.sleep(2.5)
    
    def run_publish_command_release(self):
        request = '{"request": "PUBLISH_COMMAND","command_key": "A","command_action": "RELEASE"}'
        message = "PUBLISH_COMMAND RELEASE request sent! The rabbit came back!"
        self.send_request(request, message)
    
    def run_get_chip8_info_command(self):
        request = '{"request": "GET_CHIP8_INFO"}'
        message = "GET_CHIP8_INFO request sent!"
        self.send_request(request, message)
    
    def run_get_screen_capture_command(self, show_image=False):
        request = '{"request": "GET_SCREEN_CAPTURE"}'
        message = "GET_SCREEN_CAPTURE request sent! Waiting for server response to display image"
        image = self.send_get_image_request(request, message)
        if show_image:
            image.show()
        return image
    
    def run_publish_image_command(self, screen_capture):
        # Convert Image object to a base64 string for data transfer
        buffer = BytesIO()
        screen_capture.save(buffer, format="JPEG")
        img_str = base64.b64encode(buffer.getvalue()).decode()

        request = '{"request": "PUBLISH_IMAGE","image": " ' + img_str + '"}'
        message = "PUBLISH_IMAGE request sent! Have a look-see in WhiteRabbit"
        self.send_request(request, message)
    
    ########################### SERVER COMMUNICATION METHODS ###########################
    def connect_to_server(self, ip, port):
        # Reach out to server for connection
        self.socket.connectToHost(ip, port)
        # Wait up to 5 seconds for server to establish connection
        self.wait_for_server_connection(5000)

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

    def send_request(self, request, message):
        # Send data to server
        self.socket.write(request.encode())
        self.socket.flush()
        print(message)

        # Display server answer when available
        self.wait_for_server_response(1000)
        response = self.socket.readAll().data().decode()
        print("  [Server responded]", response)
    
    def send_get_image_request(self, request, message):
        # Send data to server
        self.socket.write(request.encode())
        self.socket.flush()
        print(message)

        # Get the image from the server in the form of QByteArray when available
        self.wait_for_server_response(1000)
        response = self.socket.readAll()
        # Convert QByteArray to matrix
        pixels = np.frombuffer(response, dtype=np.uint8).reshape(self.CHIP8_IMAGE_FORMAT)
        # Increase the contrast between black/white
        pixels *= 255
        # Create image object 
        image = Image.fromarray(pixels)
        # Imcrease image size
        image = image.resize((640,320))

        return image

    def close_port(self):
        self.socket.disconnectFromHost()


app = QApplication([])
client = DemoClient('127.0.0.1', 3000)