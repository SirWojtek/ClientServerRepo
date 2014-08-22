#!/usr/bin/env python

import sqlite3

DB_NAME = "game_db"

class db_connector:

	def __init__(self):
		self.conn = self.connect()
		self.cur = self.setCursor(self.conn)

	def connect(self):
		return sqlite3.connect(DB_NAME)

	def setCursor(self, conn):
		return conn.cursor()

	def dbDictRowParser(self, cur, row):
		d = {}
		for idx, col in enumerate(cur.description):
			d[col[0]] = row[idx]
		return d

	def dbDictFactory(self, cur):
		out_object = []
		db_object = cur.fetchone()
		while db_object is not None:
			out_object.append(self.dbDictRowParser(cur, db_object))
			db_object = cur.fetchone()
		return out_object