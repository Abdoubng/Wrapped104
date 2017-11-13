#!/usr/bin/python
import sys
import time
import iec60870
import threading
import traceback
import signal

def signal_handler(signal, frame):
	global running
	running =0
	print('You pressed Ctrl+C!')
	#sys.exit(0)
signal.signal(signal.SIGINT, signal_handler)

running = 1
class Slave():
	def __init__(self):
		self._slave=iec60870.T104Slave_create(None, 0)
		#connectionparam=iec60870.Slave_getConnectionParameters(self._slave)
		slave = self._slave
		#iec60870.intero(slave)
		iec60870.clock(slave)
		iec60870.Slave_start(self._slave)
		time.sleep(1)
	def start(self):
		global running
		while running:
            		#connectionparam=iec60870.Slave_getConnectionParameters(self._slave)
			
	        	#iec60870.Slave_setInterrogationHandler(self._slave,iec60870.interrogationHandler, None)
			
	        	#aAsdu = iec60870.ASDU_create(connectionparam, iec60870.M_ME_NB_1, False, iec60870.PERIODIC, 0, 1, False, False)
		#connectionparam=iec60870.Slave_getConnectionParameters(self._slave)

        	#io = iec60870.InformationObject(iec60870.MeasuredValueScaled_create(None, 110, 2, iec60870.IEC60870_QUALITY_GOOD))
        	#iec60870.ASDU_addInformationObject(aAsdu, io)
        	#iec60870.Slave_enqueueASDU(self._slave, aAsdu)
                	time.sleep(0.5)

		
	def stop(self):
		print 2	

def main():
	slave=Slave()
	slave.start()
if __name__== "__main__":
    main()

	



