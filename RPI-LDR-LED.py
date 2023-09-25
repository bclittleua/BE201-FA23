#!/usr/bin/python
import RPi.GPIO as GPIO
from time import sleep, strftime, time
import time
import sys
import os

GPIO.setmode(GPIO.BOARD)
GPIO.setwarnings(False)
GPIO.setup(12,GPIO.OUT)

#define the BOARD pin to read LDR from
pin_to_circuit = 11

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
     with open("ldrdata.csv", "a") as log: #be sure to specify path to "ldrdata.csv", i.e. /home/pi/bin/ldrdata.csv
          log.write("{0},{1},{2}\n".format(strftime("%Y-%m-%d"),strftime("%H:%M:%S "), lightVal))

def led_func():
    ldr_thresh = 200 #calibrate this number
    if lightVal >= ldr_thresh:
        GPIO.output(12,GPIO.HIGH) #if value is greater than thresh, set LED to on
    if lightVal <- ldr_thresh:
        GPIO.output(12,GPIO.LOW) #if value is lower than thresh, set LED to off

    # Main loop
while True:
    write_data()
    led_func()
    time.sleep(1)
    break
