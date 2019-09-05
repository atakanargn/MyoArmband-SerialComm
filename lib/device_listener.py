from utilities import *

class DeviceListener(object):
	def handle_data(self, data):
		if data.cls != 4 and data.command != 5:
			# BAGLANTI KESILDIGINDE CALISAN KISIM
			print("# BAGLANTI KESILDI")
			return

		connection, attribute, data_type = unpack('BHB', data.payload[:4])
		payload = data.payload[5:]

		if attribute == 0x23:
			data_type, value, address, _, _, _ = unpack('6B', payload)
			if data_type == 3:
				# GECERLI HAREKET GELDIGINDE CALISAN KISIM
				self.on_pose(value)

	def on_pose(self, pose):
		pass
