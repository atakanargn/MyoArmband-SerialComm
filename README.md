# MYO ARMBAND PROJE KURULUM VE AYARLARI
## NEDIR BU?
* ITech robotik ve otomasyon şirketinde, Biyonik el projesi üstünde çalışırken Arduino ve Rasberry pi ile haberleşme yapmamız gerekti başta STM ile haberleşme yapıyorduk ancak STM üstünde çalışacak vaktimiz ve yazılımcımız olmadığı için -vakit olsa öğrenmeye çalışırdım- Arduino kullandık.
* MYO-Armbanddan gelen veri Rasberry'e takılan Bluetooth dongle ile haberleşir ardından gelen veriler yorumlandıktan sonra Arduino ile motor hareketlerine döndürülür, kurulan mekanik sistem ise motorlarla çalışır ve el hareketlerine dönüşür.

## SIFIR KURULUM
## SERIAL BAĞLANTISINDA TIMEOUT EKLEMEYI UNUTMA!
* Raspbian-2018 versiyonu sd-karta atılır.

* Sistem güncel olmalıdır.

* Çalışmadan önce Kütüphane kurulumları yapılmalı 
        " pip install -r reqs.txt "
        " pip3 install -r reqs.txt "

* Band verileri okuma ve Arduino ile seri haberleşme kısmı Python 2.7.15 ile çalışır.
   --> Çalıştırmadan önce band'un bluetooth'unun takılı olduğundan emin olun.
   --> Test için aşağıdaki komutu çalıştırıp, okunan hareketlerin ekrana basılmış halini görebilirsiniz.
        " sudo python main.py 0 "
   --> Seri haberleşme modunda çalıştırmak için;
        " sudo python main.py 1 "

* Ekran yazılımı Python 3.5.3 ile çalışır, çalışması için hwclock kurulu olmalıdır.
    --> /dev/ttyAMA0 için UART konfigürasyonları yapılmalı.
        LINK : https://blog.samm.com/raspberry-pi-uart/
    --> Donanımsal saat yani RTC ayarları da yapılıp, hwclock yazılımı ile konfigürasyon yapılmalı.
        LINK : https://learn.adafruit.com/adding-a-real-time-clock-to-raspberry-pi/set-rtc-time
