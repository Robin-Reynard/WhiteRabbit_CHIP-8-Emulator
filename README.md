# :rabbit: WhiteRabbit, a CHIP8 Emulator for Automation and Agents
## Down the rabbit-hole
As I was sitting near my computer one hot summer day, I was considering in my own mind whether the pleasure of coding another agent to auto-play a Mario minigame would be worth the trouble of determining the pixel-perfect location for the emulator to allow the agent to collect viable screenshots, when suddenly a White Rabbit ran close by me.           

There was nothing so very remarkable in that; nor did I think it so very much out of the way to hear the Rabbit say to itself "Oh dear! Oh dear! I shall be late!"; but when the Rabbit actually took out an emulator that could directly communicate with agents, I started to my feet, for it flashed across my mind that I had never seen an emulator interface directly with Python scripts and thus not require complete control of the screen, keyboard, and mouse, and burning with curiosity, I ran across the field after it, and fortunately was just in time to see it pop down a large rabbit-hole under the hedge.           

📖 Alice in Wonderland Chapter 1, probably, if Lewis Carroll had seen my (really) cool emulator

## So what is WhiteRabbit?
It's a CHIP8 emulator with a TCP/IP Server written in C++ using the Qt framework. It looks like this!       

![WR](https://github.com/user-attachments/assets/82226911-af33-437a-abf5-ecaa56014b94)

## What can it do?
The emulator can ...     
🎮 Run any uploaded CHIP8 game          
⏲️ Adjust the speed of the game execution      
⏯️ Play/pause the game      
↩️ Reset the game     

The server can connect to clients and send ...              
➡️ 📺 On-screen display from the emulator (No need to continuously screenshot your screen to get visual input!)               
➡️ 🎹 Pressed and released keys from the CHIP8 keyboard         
➡️ 🎵 Get sound status       

The server can receive from the connected clients ...     
⬅️ 🎹 CHIP8 keyboard commands (press or release a key) and relays information to the emulator (No need to have the agent take control of the keyboard to play the game!)         
⬅️ 🖼️ Publish images to the emulator GUI          
⬅️ 📜 Publish text to the emulator GUI            

## White Rabbit Chip8 (Chip-8 Program)
Now you might be wondering what that cool-looking rabbit with a watch is at the top left of the program. It's an interactive program I've written in the Chip-8 language where upon pressing the "A" key (either on the displayed keyboard or via request through the server), the rabbit vanishes! Don't worry; releasing the "A" key will bring it back.    
Its purpose? To welcome you 🐰              

## Demo Client (Python Script)
Additionally, I've written a script in Python that demonstrates how to connect to the WhiteRabbit server, as well as send and receive requests.      
The script proceeds in the following manner:       
1️⃣ Connects to the server       
2️⃣ Publishes "Hello There!" to the console (lower right of the program screen)          
3️⃣ Requests a screen capture of the CHIP8 display         
4️⃣ Upscales & blurs the received image and then publishes it to the dedicated image spot at the top right of the program             
5️⃣ Publishes the request to press the "A" key, causing the rabbit to disappear            
6️⃣ Requests the CHIP8 keyboard information; the "A" key is registered as being pressed           
7️⃣ Publishes the request to release the "A" key; the rabbit is back         

Location of the script: WhiteRabbit/scripts subfolder         

key_A Pressed - Rabbit is gone!| key_A Released - Rabbit is back |  Client Demo Final Output
:-------------------------:|:-------------------------:|:-------------------------:
![demo-wr-gone](https://github.com/user-attachments/assets/5de83124-f7ef-463b-a673-b6838007aa42) | ![demo-wr](https://github.com/user-attachments/assets/0e6224cf-d4b3-4922-ac8e-c65f02c05286) |  ![demo-client](https://github.com/user-attachments/assets/4fb57ca4-de24-424b-bbb5-55cab9074f15)


## Server Requests 
Ah! I see you ventured this far into the rabbit hole, perchance you have an agent/automation project in mind? 👀 The following information shall prove useful then.  
### Server Info
**Server IP**: 127.0.0.1               
**Port Number**: 3000                 
**QDataStream Version**: Qt_5_12               

### GET_CHIP8_INFO
**Function**: Gets the state of keyboard keys and if the emulator is beeping             
```
'{"request": "GET_CHIP8_INFO"}'
```
**Output**: JSON string, where if a key is marked as 'true', then it is currently being pressed            
```
Output example:
{
    "is_beeping": false,
    "key_0": false,
    "key_1": false,
    "key_2": false,
    "key_3": false,
    "key_4": false,
    "key_5": false,
    "key_6": false,
    "key_7": false,
    "key_8": false,
    "key_9": false,
    "key_A": true,
    "key_B": false,
    "key_C": false,
    "key_D": false,
    "key_E": false,
    "key_F": false
}
```
### GET_SCREEN_CAPTURE
**Function**: Gets the display information of the CHIP8 emulator             
```
'{"request": "GET_SCREEN_CAPTURE"}'
```
**Output**: A QByteArray of length 2048, where a \x00 indicates a black pixel and \x01 a white one. The output must be reshaped to the CHIP8 screen dimensions of [32x64]                   
```
Output example:
b'\x00\x00\x01\x00\x00\x01\x00\x00\x00\x00\x00\x01\x00\ ... truncated ... \x00\x00\x00\x00\x00\x00\x00\x01\x00'
```

### PUBLISH_TEXT
**Function**: Displays YOUR_TEXT to the WhiteRabbit text console             
**Input**: text (YOUR_TEXT as your desired message)                
```
'{"request": "PUBLISH_TEXT","text": "YOUR_TEXT"}'
```

### PUBLISH_COMMAND
**Function**: The equivalent of pressing/releasing a key on the keyboard             
**Input**: 
* command_key (YOUR_KEY as either a number 0-9 or a letter A-F, depending on the key)
* command_action (either PRESS or RELEASE depending on the desired action)                 
```
'{"request": "PUBLISH_COMMAND","command_key": "YOUR_KEY","command_action": "PRESS|RELEASE"}'
```
### PUBLISH_IMAGE
**Function**: Displays YOUR_IMAGE to the WhiteRabbit client image location             
**Input**: image (YOUR_IMAGE as a base64 encoded string representation of your image)                
```
'{"request": "PUBLISH_IMAGE","image": "YOUR_IMAGE"}'
```

### Server received request
To indicate that the WhiteRabbit server has received the request (in the cases where it doesn't have to send back any data), it will reply with a rabbit smile.
```
:3
```

## Get started
This is the simplest and headache-free method of making sure it runs.
1️⃣ Install Qt
2️⃣ git clone the repository
3️⃣ Open and run the project from Qt

## Special Thanks
Big thanks to the authors and maintainers of the following resources, without whom the project would hav been exponentially harder to finish.
**CHIP8 Documentation**
https://multigesture.net/articles/how-to-write-an-emulator-chip-8-interpreter/    
http://devernay.free.fr/hacks/chip8/C8TECH10.HTM
https://en.wikipedia.org/wiki/CHIP-8
**TCP Server in Qt**
https://doc.qt.io/qt-6/qtnetwork-fortuneserver-example.html    
https://doc.qt.io/qt-6/qtnetwork-fortuneclient-example.html   
