import mido
import serial
import json

port = mido.open_output('Midi Through:Midi Through Port-0 14:0')
ser = serial.Serial('/dev/ttyUSB0', 921600)

def is_json(myjson):
  try:
    json_object = json.loads(myjson)
  except ValueError as e:
    return False
  return True

def play(note):
    try:
        msg = mido.Message.from_bytes(note)
        port.send(msg)
    except:
        print("Bad MIDI message: " + str(note) )

while True:
    line = ser.readline()
    if is_json(line):
        midi = json.loads(line)
        arr = midi["midi"]
        for cnt in range(0, len(arr) - 3, 3):
            if arr[cnt]:
                note = [arr[cnt], arr[cnt+1], arr[cnt+2]]
                play(note)
                print(note)
