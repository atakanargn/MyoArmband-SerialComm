# Terminalden işlem yapmak için gereken kütüphane
import subprocess

# Sıcaklığı çekmek için gereken kütüphaneler
from glob import glob
from os import chdir, system
from serial import Serial
from time import sleep

# Raspberry Pi pinler üzerindeki
# UART (Rx-Tx) haberleşme pinleri
# otomatik olarak "/dev/ttyAMA0" konumuna bağlanır.
# Ekranda bu porta bağlı ve 9600 baud ile haberleşiyor.
ser = Serial("/dev/ttyAMA0",9600)

# DS18B20 SICAKLIK SENSÖRÜ KONUMU
w1_file = glob("/sys/bus/w1/devices/" + "28*")[0]+"/w1_slave"

# DS18B20 SICAKLIK SENSÖRÜ DEĞERİ
def sicaklikAl():
    f = open(w1_file,"r")
    ilkSicaklik = f.readlines()[1][-6:][:-1]
    f.close()
    sicaklik = ilkSicaklik[0:2] 
    return int(sicaklik)

# Ekrana veri gönderme işlemlerini kısaltmak
def ekranaGonder(ser, veri):
    # Girilen veriyi byte türüne çevirdik
    veri = veri.encode("utf8")
    # Ekran için satır atlama komutu denebilir
    TERMINATOR = bytearray([0xFF, 0xFF, 0xFF])
    # Ekrana veriyi gönder
    ser.write(veri)
    # Yeni komutlar için satır atla
    ser.write(TERMINATOR)

# Terminalde programı bölmeden komut çalıştırıp
# çıktıları okumaya yarayan metod
def islem(cmd):
    p = subprocess.Popen(cmd, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
    while(True):
        # None değeri dönene kadar işlemin çalıştığını anlarız
        retcode = p.poll()
        line = p.stdout.readline()
        yield line
        if retcode is not None:
            break

while 1:
    try:
        # RTC modülünden veriyi oku
        # Gelen değerleri
        # Gün, Ay, Yıl, Saat, Dakika değişkenlerine ata
        for line in islem(["date", "+\"%D %H%M\""]):
            gelenDeger   = line.decode("utf8").strip()
            print(gelenDeger,sicaklikAl())
            sic = sicaklikAl()
            tarih        = gelenDeger[:9]
            ay,gun,yil   = tarih.split("/")
            yil = "20"+yil

            if(len(gun)!=2):
                gun = "0" + gun
            if(len(ay)!=2):
                ay = "0" + ay

            saat, dakika = gelenDeger[-5:][0:2], gelenDeger[-5:][2:4]
            if(len(saat)!=2):
                saat = "0" + saat
            if(len(dakika)!=2):
                dakika = "0" + dakika
            break

        # DEBUG İÇİN "sarj, nabiz"
        # verilerine rastgele değer verdik
        sarj =85
        nabiz=66

        # Saat
        ekranaGonder(ser, 'page0.saat.val={}'.format(saat))
        # Dakika
        ekranaGonder(ser, 'page0.dakika.val={}'.format(dakika))
        # Gun
        ekranaGonder(ser, 'page0.gun.val={}'.format(gun))
        # Ay
        ekranaGonder(ser, 'page0.ay.val={}'.format(ay))
        # Yil
        ekranaGonder(ser, 'page0.yil.val={}'.format(yil))
        #sarj
        ekranaGonder(ser, 'page0.sarj.val={}'.format(sarj))
        ekranaGonder(ser, 'page0.sarj_gos.val={}'.format(sarj))

        # Pil sıcaklığı
        ekranaGonder(ser, 'page0.pil_sic.val={}'.format(sicaklikAl()))
        ekranaGonder(ser, 'page0.sic_gos.val={}'.format(sicaklikAl()*2))

        # Nabız
        ekranaGonder(ser, 'page0.nabiz.val={}'.format(nabiz))
        # 2 saniye bekle
        sleep(2)
    # Klavyeden CTRL+C gelirse, seri haberleşmeyi kapat
    except KeyboardInterrupt as e:
        ser.close()