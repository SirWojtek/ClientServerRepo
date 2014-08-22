#!/usr/bin/env python

import sys
import os
import socket
import db_connector as con
import thread
import time

TCP_IP = '127.0.0.1'
TCP_PORT = 1234
BUFFER_SIZE = 1024

def dbgprint(output):
	if (len(sys.argv) > 1):
		print output

class TcpServer:

	def __init__(self, port):
		self.s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
		self.s.setblocking(1)
		self.s.bind((TCP_IP, port))
		self.tcp_conn = self.listen(self.s)

	def listen(self, s):
		s.listen(1)
		tcp_conn, addr = s.accept()
		dbgprint("Connection address: " + str(addr))
		return tcp_conn

	def receiveMessage(self, tcp_conn):
		data = tcp_conn.recv(BUFFER_SIZE)
		if data:
			return data
		return ""

db_con = con.db_connector()
db_con.cur.execute("SELECT * FROM users")
users = db_con.dbDictFactory(db_con.cur)
x = TcpServer(TCP_PORT)
while 1:
	data = x.receiveMessage(x.tcp_conn)
	if data == "": 
		x.tcp_conn = x.listen(x.s)
	else:
		dbgprint("Received data: " + str(data))
		x.tcp_conn.send("Received")
x.tcp_conn.close()