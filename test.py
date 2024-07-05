'''
Author: Izuka Ikedionwu

Description: My test interface -> this is what I advika would interface with

Created: 6/26/24
'''

# My Import
from pycode import Wifi_Host, Metrics, Telemetry, System_Health
from pycode import PT1,PT2,PT3,PT4,PT5,FS,TS,RR
import time

print(FS)
wifi = Wifi_Host("192.168.1.215",4)
sys  = System_Health()
tel  = Telemetry(wifi)

#comm = wifi.recieve_data()
#print(comm)
tel.get_data()
time.sleep(1)
tel.open_valve(1)
time.sleep(1)
tel.close_valve(1)
#:wq
tel.send_data()
print(sys.get_py_status())
time.sleep(1)


