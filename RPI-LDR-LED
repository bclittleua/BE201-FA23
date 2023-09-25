#!/usr/bin/python
import RPi.GPIO as GPIO
from time import sleep, strftime, time
import time
import sys
import os

GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)

#define the pin that goes to the circuit
pin_to_circuit = 17

def rc_time (pin_to_circuit):
    count = 0

    GPIO.setup(pin_to_circuit, GPIO.OUT)
    GPIO.output(pin_to_circuit, GPIO.LOW)
    time.sleep(0.1)
    GPIO.setup(pin_to_circuit, GPIO.IN)
    #Count until the pin goes high
    while (GPIO.input(pin_to_circuit) == GPIO.LOW):
        count += 1
    return count

lightVal = rc_time(pin_to_circuit)

def write_data():
     with open("ldrdata", "a") as log:
          log.write("{0},{1},{2}\n".format(strftime("%Y-%m-%d"),strftime("%H:%M:%S "), lightVal))

    # Main loop
while True:
    write_data()
    break
