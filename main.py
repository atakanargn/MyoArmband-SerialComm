import sys
# Bluetooth kütüphaneleri konumu
sys.path.append('/home/pi/MYO/lib/')
# system() komutu, işletim sistemi üzerinde komut çalıştırmak için kullanılır.
from os import system
# Armband için Bluetooth kütüphanesi
from myo import Myo
# HAREKET LISTENERLARI
from listeners import *
# TITRESIM TIPLERI
from vibration_type import VibrationType
# SLEEP() FONKSIYONU
from time import sleep

def main():
    print("### ITECH BIYONIK-EL YAZILIMI ###\n#")
    print('# Myo yazilimi baslatiliyor')
    # HAREKET TANIMLAMA LISTENERI
    if(sys.argv[1] == "0"):
        listener = PrintPoseListener()
    elif(sys.argv[1] == "1"):
        listener = RS232Listener()
    # MYO NESNESI
    myo = Myo()

    try:
        # MYO BAGLANTI
        myo.connect()
        # LISTENER EKLEME
        myo.add_listener(listener)
        # BASLANGICTA 5 KISA TITRESIM
        for i in range(0,5): myo.vibrate(VibrationType.SHORT)

        # PROGRAM BU DONGU ICINDE CALISIR
        while True:
            # myo.run() KOMUTU : HAREKETLERI ALGILAR
            mPose = myo.run()
            # myo.run() KOMUTUNDAN "-1" DEGERI DONER ISE
            # YANI HAREKET DEGERI "UNKNOWN" ISE
            if(mPose == -1):
                # GUVENLI CIKIS
                myo.safely_disconnect()
                # TEKRAR BAGLANTI
                myo.connect()
                # TEKRAR LISTENER EKLE
                myo.add_listener(listener)
                # TEKRAR 5 TITRESIM
                for i in range(0,5): myo.vibrate(VibrationType.SHORT)
    # KLAVYEDEN DURDURMA
    except KeyboardInterrupt:
        break
    except ValueError:
        break
    finally:
        # GUVENLI CIKIS
        myo.safely_disconnect()
        print('# Cikis yapildi.\n#')
        print("### ITECH BIYONIK-EL YAZILIMI ###")

# PROGRAM BU BÖLÜMDE ÇALIŞIR
if __name__ == '__main__':
    main()
