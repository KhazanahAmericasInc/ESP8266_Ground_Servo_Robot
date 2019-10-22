import sys, os, json, time, keyboard

import httplib2
http = httplib2.Http()


url_json = 'http://10.8.9.108/Servo'
#url_json = 'http://172.29.32.71/Servo'   
headers={'Content-Type': 'application/json; charset=UTF-8'}

while(1):

    data = {'left': '67', 'right': '71'}

    if keyboard.is_pressed('w'):
        data = {'left': '179', 'right': '0'}

    elif keyboard.is_pressed('s'):
        data = {'left': '0', 'right': '179'}

    if keyboard.is_pressed('a'):
        data = {'left': '40', 'right': '40'}

    if keyboard.is_pressed('d'):
        data = {'left': '90', 'right': '90'}

    response, content = http.request(url_json, 'POST', headers=headers, body=json.dumps(data))
    #print (response)
    #print (content)

