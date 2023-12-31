#!/usr/bin/python
# The LDR detects light constantly, too fast for the RPi to read. We slow
# down process a bit by "charging" a capacitor and reading the resulting value.
# The LDR has less resistance in bright light, and more resistance in dim light.
# Thus: DARK = HIGH value, LIGHT = LOW Value

import RPi.GPIO as GPIO
from time import sleep, strftime, time
import time                    # redundant calls, condense!
import sys
import os
import psutil

GPIO.setmode(GPIO.BOARD)
GPIO.setwarnings(False)
GPIO.setup(12,GPIO.OUT)
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

def get_cpu():                                                                                                                 # new function (be sure to import psutil)
    temp = psutil.sensors_temperatures()['cpu_thermal'][0].current                                                             #
    return temp                                                                                                                #
                                                                                                                               #
cpuTemp = get_cpu()                                                                                                            #
                                                                                                                               # new variable
def write_data():                                                                                                              #
     with open("ldrdata.csv", "a") as log: #be sure to specify path to "ldrdata.csv", i.e. /home/pi/bin/ldrdata.csv            # 
          log.write("{0},{1},LDR: {2},CPU: {3}C\n".format(strftime("%Y-%m-%d"),strftime("%H:%M:%S "), lightVal, cpuTemp))      # added {3} and cpuTemp to output string

def led_func():
    ldr_thresh = 30000 #calibrate this number
    if lightVal >= ldr_thresh:
        GPIO.output(12,GPIO.HIGH) #if value is greater than thresh, it is DARK, set LED to on
    if lightVal <= ldr_thresh:
        GPIO.output(12,GPIO.LOW) #if value is lower than thresh, it is BRIGHT,  set LED to off

# Main loop
while True:
    write_data()
    led_func()
    break
