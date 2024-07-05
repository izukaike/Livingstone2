'''
Author: Izuka Ikedionwu

Description: python side to interface with pi and front this is the middle man

features:
- streamlined wifi

Created: 6/28/24
'''

#dependencies

#wifi
import socket
import numpy
import json
import struct

#global variables
PT1 = 0
PT2 = 1
PT3 = 2
PT4 = 3
PT5 = 4
FS  = 5
TS  = 6
RR  = 7

class System_Health:
    '''
    Shared Data
    '''
    py_stats  = {}
    pi_stats  = {}
    sys_stats = {}

    #        measurement           default status
    py_stats['initial wifi connection'] = 'null'
    py_stats['wifi message sent']       = 'null'
    py_stats['v1 open command']         = 'null'

    #ToDo Fill in the feedback list

    sys_stats.update(py_stats,**pi_stats)

     
    def get_pi_status(self):
        return self.pi_stats
    
    
    def get_py_status(self):
        return self.py_stats
    
    
    def get_sys_status(self):
        return self.sys_stats



class Wifi_Host:
    def __init__(self,host,port):
    
        #pi ip address 
        self.host   = host
        self.port   = port
        self.connection   = ''
        self.addy   = ''

        try:
            with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as server_socket:
                # Bind the socket to the host and port
                server_socket.bind((self.host,self.port))
    
                # Start listening for incoming connections
                server_socket.listen()
                print(f"Server is listening on {self.host}:{self.port}")
                # Accept incoming connections
                self.connection, self.addy = server_socket.accept()

                System_Health.py_stats["initial wifi connection"] = 'good'
    

        except Exception as e:
            print(f"Error: {e} at connect")
            System_Health.py_stats["initial wifi connection"] = 'bad'
    
    def send_command(self,d):
        '''
        telemetry packet:
        [heartbeat][data layer][aborts][status data]
        '''
        #form packet
        sent = self.connection.sendall(d)
        System_Health.py_stats["wifi message sent"] = 'good'
    
        if(sent == 0):
            System_Health.py_stats["wifi message sent"] = 'bad'
            raise RuntimeError("socket connection broken at sent")
        return 0
    def recieve_data(self):
        '''
        telemetry packet:
        [heartbeat][data layer][status data]
        '''
        packet_size = 1024
        self.data = self.connection.recv(packet_size)

        if(self.data == ''):
            System_Health.py_stats["recieve packet"] = 'bad'
            raise RuntimeError("did not recieve packet")
        else:
            System_Health.py_stats["recieve packet"] = 'good'

        return self.data

#processes incoming data and forms outgoing data packets
class Telemetry:
    def __init__(self,wifi):
        # default 
        #32 bits for 32 commands -> bitwise operations for processing 
        self.heartbeat  = -49 #checksum for verification
        self.tail       = -48 #check sum of end of message
        self.data       =  0
        self.status     =  6
        self.data_out   = struct.pack('iiii',0,0,0,0)
        self.wifi       = wifi
        #idk how to set up incoming data packets yet

        #all this class does is set and clear bits for the fized data packets coming in and out
        
        ''' 
        Data out
        byte                     bits
        [heartbeat]||[valve1][valve2][valve3][valve4]
        '''

    #add heartbeat -> header for data

    def send_data(self):
        self.wifi.send_command(self.send_data_out())
        return 0
    
    def get_data(self):
        rx = self.wifi.recieve_data()

        #ToDo: finish this function 
        #what what is my data packet look like and what am I expecting
        return rx

    def open_valve(self, num):
        #set msb
        self.data = self.data | (1 << (num-1))
        System_Health.py_stats["v{num} open command"] = 'good'
        return 0 
    
    
    def close_valve(self, num):
        #clear msb
        self.data = self.data & ~(1 << (num-1)) 
        System_Health.py_stats["v{num} open command"] = 'bad'
        return 0
    def spark_coil(self):
        self.data = self.data & ~(1 << 4) 
        System_Health.py_stats["v{num} open command"] = 'bad' #status gets cleared from pi side
        return 0

    #not used by front-end
    def send_data_out(self):
        self.data_out = struct.pack('iiii',self.heartbeat,self.data,self.status,self.tail)
        return self.data_out

#collects data and visualizes it for System_Health analysis

#todo finish this class
class Metrics:
    def __init__(self):
        print("metrics")







            
