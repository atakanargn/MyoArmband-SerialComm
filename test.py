from sys import argv
from serial import Serial
from time import sleep
from os import system

def oku():
    print(test.readline())

test = Serial("/dev/tty"+str(argv[1]),9600)
while 1:
    try:
        print("1) EL KAPAMA\t2) EL ACMA\n3) 3 PARMAK TUTMA\t\
4) ISARET ETME\n5) BAGLANTI KESME\t6) BAGLANTI YAPMA\n>> ")
        gelen = raw_input("VERI : ")
        if(gelen=="1"):
            test.write(str(5).encode("utf8")))
        elif(gelen=="2"):
            test.write(str(2).encode("utf8")))
        elif(gelen=="3"):
            test.write(str(3).encode("utf8")))
        elif(gelen=="4"):
            test.write(str(4).encode("utf8")))
        elif(gelen=="5"):
            test.close()
        elif(gelen=="6"):
            test.open()
        sleep(0.5)