#!/usr/bin/python
import sys
import time
from iec60870 import *
import threading
import traceback
import signal
import time

def signal_handler(signal, frame):
	print " \nInterrupted\n"
	sys.exit(0)
signal.signal(signal.SIGINT, signal_handler)



class meSlave():
    def __init__(self, arg):
        serverz.initial(arg, 100, 102)
        serverz.setHandlers(arg)
        serverz.Start(arg)

		
try:
    Sserverz=serverz()
    Sslave=meSlave(Sserverz)
    while True:
        time.sleep(2)
except :
    pass
#Sslave.Server_initial(100, 102)
#Sslave.setHandlers()
#Sslave.Start()
