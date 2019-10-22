#Craig Crundwell
#Oct 20, 2019
#This python program connects to the arduino server hosted by the servo robot
#WASD is used on the keyboard to control the robot movement

#imports
import sys, os, json, time, keyboard
import httplib2
http = httplib2.Http()

#This ip is found by running the arduno code connected to the serial monitor
url_json = 'http://10.8.9.108/Servo'

#header for json formatted data packet   
headers={'Content-Type': 'application/json; charset=UTF-8'}

while(1):

    #sets command to stop
    data = {'left': '67', 'right': '71'}

    #forward
    if keyboard.is_pressed('w'):
        data = {'left': '179', 'right': '0'}

    #backward
    elif keyboard.is_pressed('s'):
        data = {'left': '0', 'right': '179'}

    #left
    if keyboard.is_pressed('a'):
        data = {'left': '40', 'right': '40'}

    #right
    if keyboard.is_pressed('d'):
        data = {'left': '90', 'right': '90'}

    #sends command to server
    response, content = http.request(url_json, 'POST', headers=headers, body=json.dumps(data))


