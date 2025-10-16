import serial
import matplotlib.pyplot as plt
import matplotlib.colors as colors
import json


arduinoComPort = "COM5"
baudRate = 9600
serialPort = serial.Serial(arduinoComPort, baudRate, timeout=1)

data = [] # Array to store one data point at a time
all_data = [[],[],[],[],[]] # Array to store all data points

# Loop forever
while True:
  
  lineOfData = serialPort.readline().decode().strip()

  if len(lineOfData) > 0:
    
    if(lineOfData=="ldjflksdjfkjsdflksdf"):
      break
  
    data = lineOfData.split(" ")
    
    print(data)
    
    for index, element in data:
      all_data[index].append(element)

# Save data to JSON file
with open("file.json", "w") as f:
  json.dump(all_data, f)  