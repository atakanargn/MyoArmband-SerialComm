import sys
sys.path.append('/home/pi/MYO/lib/')

# BLUETOOTH'TAN GELEN VERILER IÇIN GEREKEN KÜTÜPHANE
# "lib" dosyasından gelir ve hareketleri yorumlar
from device_listener import DeviceListener
from pose_type import PoseType
from time import sleep

# RS232 Serihaberleşme yapısı
class RS232Listener(DeviceListener):
	def __init__(self):
		from serial import Serial

		self.sonHareket = ""
		self.ardu = Serial()
		self.ardu.baudrate = 9600
		self.baglan()

	def on_pose(self, pose):
		pose_type = PoseType(pose)
		print("# HAREKET : "+pose_type.name+"\n#")

		# EL HAREKETLERI BU KISIMDA TANIMLANIR
		# VE UART SERI HABERLEŞME PROTOKOLÜ ILE
		# MOTORLARIN ÇALIŞMASI SAĞLANIR.
		if(pose_type.name == "REST" and self.sonHareket != pose_type.name):
			self.sonHareket = pose_type.name
			print("# EL ACIK")
			self.ardu.write("{}".format(2))
		elif(pose_type.name == "FIST" and self.sonHareket != pose_type.name):
			self.sonHareket = pose_type.name
			print("# EL KAPALI")
			self.ardu.write("{}".format(5))
		elif(pose_type.name == "WAVE_IN" and self.sonHareket != pose_type.name):
			self.sonHareket = pose_type.name
			print("# 3 PARMAK TUTMA")
			self.ardu.write("{}".format(3))
		elif(pose_type.name == "WAVE_OUT" and self.sonHareket != pose_type.name):
			self.sonHareket = pose_type.name
			print("# ISARET ETME")
			self.ardu.write("{}".format(4))

		if(pose_type.name == "UNKNOWN"):
			self.sonHareket = pose_type.name
			return -1

	# SERI HABERLEŞME YAPILACAK CIHAZI OTOMATIK BULDURMA
	# VE BAĞLANTI YAPMA
	def baglan(self):
		try: self.ardu.close()
		except: pass
		sleep(0.5)
		import serial.tools.list_ports
		comlist = serial.tools.list_ports.comports()
		for element in comlist:
			if("/dev/ttyUSB" in element.device): self.ardu.port = element.device
		try: self.ardu.open()
		except: pass