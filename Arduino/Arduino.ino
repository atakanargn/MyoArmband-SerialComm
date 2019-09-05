#include <Servo.h>
Servo servo;
int SERVO_PWM = 13;
int sonaci = 0;

int motorbas1Pin = 2;
int motorbas2Pin = 4;
int BP_PWM = 3;
#define BP_OKU A7

int motori1Pin = 7;
int motori2Pin = 6;
int IP_PWM = 5;
#define IP_OKU A6

int motoro1Pin = 8;
int motoro2Pin = 9;
int OP_PWM = 10;
#define OP_OKU A5

int motors1Pin = 11;
int motors2Pin = 12;
int SP_PWM = 14;
#define SP_OKU A4

bool ipBreak = false;
bool opBreak = false;
bool spBreak = false;

void setup() {
  pinMode(motorbas1Pin, OUTPUT);
  pinMode(motorbas2Pin, OUTPUT);

  pinMode(motori1Pin, OUTPUT);
  pinMode(motori2Pin, OUTPUT);

  pinMode(motoro1Pin, OUTPUT);
  pinMode(motoro2Pin, OUTPUT);

  pinMode(motors1Pin, OUTPUT);
  pinMode(motors2Pin, OUTPUT);

  pinMode(BP_PWM, OUTPUT);// BP PWM PİNİ
  pinMode(IP_PWM, OUTPUT);//İP PWM PİNİ
  pinMode(OP_PWM, OUTPUT);// OP PWM PİNİ
  pinMode(SP_PWM, OUTPUT); //NP PWM PİNİ
  pinMode(SERVO_PWM, OUTPUT);

  analogWrite(BP_PWM, 200);
  digitalWrite(IP_PWM, HIGH);
  digitalWrite(OP_PWM, HIGH);
  digitalWrite(SP_PWM, HIGH);

  servo.attach(SERVO_PWM);

  SWrite(50);

  Serial.begin(9600);
  Serial.setTimeout(0);
}
int sonuc;

int bpokunan1 = 0;
int bpokunan2;
int bpfeedback;

int ipokunan1 = 0;
int ipokunan2;
int ipfeedback;

int opokunan1 = 0;
int opokunan2;
int opfeedback;

int spokunan1 = 0;
int spokunan2;
int spfeedback;

void loop() {
  sonuc = Serial.read();
  ipokunan1 = analogRead(IP_OKU);
  opokunan1 = analogRead(OP_OKU);
  spokunan1 = analogRead(SP_OKU);
  delay(50);
  ipokunan2 = analogRead(IP_OKU);
  opokunan2 = analogRead(OP_OKU);
  spokunan2 = analogRead(SP_OKU);
  // EL KAPATMA
  if (sonuc == 50) {
    while (1) {
      bpokunan1 = analogRead(BP_OKU);
      ipokunan1 = analogRead(IP_OKU);
      opokunan1 = analogRead(OP_OKU);
      spokunan1 = analogRead(SP_OKU);

      while (bpokunan1 > 250) {
        digitalWrite(motorbas2Pin, HIGH);
        digitalWrite(motorbas1Pin, LOW);

        bpokunan1 = analogRead(BP_OKU);
        delay(50);
        bpokunan2 = analogRead(BP_OKU);
        bpfeedback = abs(bpokunan1 - bpokunan2);
      }

      digitalWrite(motorbas1Pin, LOW);
      digitalWrite(motorbas2Pin, LOW);
      if (ipBreak == false || opBreak == false || spBreak == false) {
        if (ipokunan1 > 250 && ipBreak == false) {
          digitalWrite(motori2Pin, HIGH);
          digitalWrite(motori1Pin, LOW);
        }
        if (ipokunan1 <= 250) {
          digitalWrite(motori2Pin, LOW);
          digitalWrite(motori1Pin, LOW);
          ipBreak = true;
        }
        if (opokunan1 > 200 && opBreak == false) {
          digitalWrite(motoro2Pin, HIGH);
          digitalWrite(motoro1Pin, LOW);
        }
        if (opokunan1 <= 200) {
          digitalWrite(motoro2Pin, LOW);
          digitalWrite(motoro1Pin, LOW);
          opBreak = true;
        }
        if (spokunan1 > 250 && spBreak == false) {
          digitalWrite(motors2Pin, HIGH);
          digitalWrite(motors1Pin, LOW);
        }
        if (spokunan1 <= 250) {
          digitalWrite(motors2Pin, LOW);
          digitalWrite(motors1Pin, LOW);
          spBreak = true;
        }
        ipokunan1 = analogRead(IP_OKU);
        opokunan1 = analogRead(OP_OKU);
        spokunan1 = analogRead(SP_OKU);
        delay(50);
        ipokunan2 = analogRead(IP_OKU);
        opokunan2 = analogRead(OP_OKU);
        spokunan2 = analogRead(SP_OKU);

        ipfeedback = abs(ipokunan1 - ipokunan2);
        opfeedback = abs(opokunan1 - opokunan2);
        spfeedback = abs(spokunan1 - spokunan2);
      }else{
        digitalWrite(motori1Pin, LOW);
        digitalWrite(motori2Pin, LOW);
        digitalWrite(motoro1Pin, LOW);
        digitalWrite(motoro2Pin, LOW);
        digitalWrite(motors1Pin, LOW);
        digitalWrite(motors2Pin, LOW);
        SWrite(50);
        break;
      }
    }
  }
  // 3 PARMAK TUTMA
  if (sonuc == 51) {

    while (1) {
      bpokunan1 = analogRead(BP_OKU);
      ipokunan1 = analogRead(IP_OKU);
      opokunan1 = analogRead(OP_OKU);
      spokunan1 = analogRead(SP_OKU);
      SWrite(130);
      if (ipokunan1 < 700 || opokunan1 < 600) {

        digitalWrite(motori1Pin, HIGH);
        digitalWrite(motori2Pin, LOW);

        digitalWrite(motoro1Pin, HIGH);
        digitalWrite(motoro2Pin, LOW);

        ipokunan1 = analogRead(IP_OKU);
        opokunan1 = analogRead(OP_OKU);
        delay(50);
        ipokunan2 = analogRead(IP_OKU);
        opokunan2 = analogRead(OP_OKU);

        ipfeedback = abs(ipokunan1 - ipokunan2);
        opfeedback = abs(opokunan1 - opokunan2);
      }else{
        digitalWrite(motori1Pin, LOW);
        digitalWrite(motori2Pin, LOW);
        digitalWrite(motoro1Pin, LOW);
        digitalWrite(motoro2Pin, LOW);
        digitalWrite(motors1Pin, LOW);
        digitalWrite(motors2Pin, LOW);

        while (bpokunan1 < 500) {
          digitalWrite(motorbas1Pin, HIGH);
          digitalWrite(motorbas2Pin, LOW);

          bpokunan1 = analogRead(BP_OKU);
          delay(25);
          bpokunan2 = analogRead(BP_OKU);
          bpfeedback = abs(bpokunan1 - bpokunan2);
        }
        digitalWrite(motorbas1Pin, LOW);
        digitalWrite(motorbas2Pin, LOW);
        break;
      }
    }
  }
  // IŞARET ETME
  if (sonuc == 52) {
    ipokunan1 = analogRead(IP_OKU);
    if (ipokunan1 < 300) {
      ipBreak = true;
    }
    bpokunan1 = analogRead(BP_OKU);
    opokunan1 = analogRead(OP_OKU);
    spokunan1 = analogRead(SP_OKU);
    while (bpokunan1 > 250) {
      digitalWrite(motorbas2Pin, HIGH);
      digitalWrite(motorbas1Pin, LOW);
      bpokunan1 = analogRead(BP_OKU);
      delay(50);
      bpokunan2 = analogRead(BP_OKU);
      bpfeedback = abs(bpokunan1 - bpokunan2);
    }

    digitalWrite(motorbas1Pin, LOW);
    digitalWrite(motorbas2Pin, LOW);
    SWrite(50);
    while (1) {
      if (ipBreak == false || opBreak == false || spBreak == false) {
        if (ipokunan1 > 250 && ipBreak == false) {
          digitalWrite(motori2Pin, HIGH);
          digitalWrite(motori1Pin, LOW);
        }
        if (ipokunan1 <= 300) {
          digitalWrite(motori2Pin, LOW);
          digitalWrite(motori1Pin, LOW);
          ipBreak = true;
        }
        if (opokunan1 < 800 && opBreak == false) {
          digitalWrite(motoro1Pin, HIGH);
          digitalWrite(motoro2Pin, LOW);
        }
        if (opokunan1 > 750) {
          digitalWrite(motoro1Pin, LOW);
          digitalWrite(motoro2Pin, LOW);
          opBreak = true;
        }
        if (spokunan1 < 800 && spBreak == false) {
          digitalWrite(motors1Pin, HIGH);
          digitalWrite(motors2Pin, LOW);
        }
        if (spokunan1 > 750) {
          digitalWrite(motors1Pin, LOW);
          digitalWrite(motors2Pin, LOW);
          spBreak = true;
        }
        ipokunan1 = analogRead(IP_OKU);
        opokunan1 = analogRead(OP_OKU);
        spokunan1 = analogRead(SP_OKU);
      }else{
        digitalWrite(motori1Pin, LOW);
        digitalWrite(motori2Pin, LOW);
        digitalWrite(motoro1Pin, LOW);
        digitalWrite(motoro2Pin, LOW);
        digitalWrite(motors1Pin, LOW);
        digitalWrite(motors2Pin, LOW);
        break;
      }
    }
  }
  // EL KAPATMA
  if (sonuc == 53) {
    while (1) {
      bpokunan1 = analogRead(BP_OKU);
      ipokunan1 = analogRead(IP_OKU);
      opokunan1 = analogRead(OP_OKU);
      spokunan1 = analogRead(SP_OKU);
      SWrite(130);
      if (ipokunan1 < 750 || opokunan1 < 750 ||  spokunan1 < 750) {

        digitalWrite(motori1Pin, HIGH);
        digitalWrite(motori2Pin, LOW);

        digitalWrite(motoro1Pin, HIGH);
        digitalWrite(motoro2Pin, LOW);

        digitalWrite(motors1Pin, HIGH );
        digitalWrite(motors2Pin, LOW);

        ipokunan1 = analogRead(IP_OKU);
        opokunan1 = analogRead(OP_OKU);
        spokunan1 = analogRead(SP_OKU);
        delay(50);
        ipokunan2 = analogRead(IP_OKU);
        opokunan2 = analogRead(OP_OKU);
        spokunan2 = analogRead(SP_OKU);

        ipfeedback = abs(ipokunan1 - ipokunan2);
        opfeedback = abs(opokunan1 - opokunan2);
        spfeedback = abs(spokunan1 - spokunan2);
      }else {
        digitalWrite(motori1Pin, LOW);
        digitalWrite(motori2Pin, LOW);
        digitalWrite(motoro1Pin, LOW);
        digitalWrite(motoro2Pin, LOW);
        digitalWrite(motors1Pin, LOW);
        digitalWrite(motors2Pin, LOW);

        while (bpokunan1 < 600) {
          digitalWrite(motorbas1Pin, HIGH);
          digitalWrite(motorbas2Pin, LOW);

          bpokunan1 = analogRead(BP_OKU);
          delay(25);
          bpokunan2 = analogRead(BP_OKU);
          bpfeedback = abs(bpokunan1 - bpokunan2);
        }
        digitalWrite(motorbas1Pin, LOW);
        digitalWrite(motorbas2Pin, LOW);
        break;
      }
    }
  }

  ipBreak = false; opBreak = false; spBreak = false;
}

// SERVO HAREKETI (0 - 220 ARASI)
void SWrite(int angle)
{
  if (angle >= sonaci)
  {
    for (int i = sonaci; i <= angle; i++)
    {
      servo.write(i);
      delay(20);
    }
    sonaci = angle;
  }
  else if (angle < sonaci)
  {
    for (int i = sonaci; i >= angle; i--)
    {
      servo.write(i);
      delay(20);
    }
    sonaci = angle;
  }
}