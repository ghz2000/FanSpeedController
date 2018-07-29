const int fanPin =  11;
const int button1 = 18;
const int button2 = 19;


int ledState = LOW;             // ledState used to set the LED
long previousMillis = 0;        // will store last time LED was updated
long segPreviousMillis = 0;

long previousMillis7seg = 0;
long interval7seg = 3000;

long pushButton1PreviousMillis = 0;
long pushButton2PreviousMillis = 0;
long pushButtonInterval = 200;

long interval = 1000;           // interval at which to blink (milliseconds)

long segInterval = 1;  //1ms表示して10ms消灯する

void setup() {
  // set the digital pin as output:
  pinMode(fanPin, OUTPUT);
  DDRD = 0xFF;  //DigitalPin 0-7 をすべて出力に
  digitalWrite(button1, HIGH);  //pull UP
  digitalWrite(button2, HIGH);  //pull UP
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  TCCR2B &= B11111000;
  TCCR2B |= B00000001;
}

unsigned long currentMillis;

int i=0;
int j=0;

void loop(){

  currentMillis = millis();
 
  if(digitalRead(button1) == LOW){
    if(currentMillis - pushButton1PreviousMillis > pushButtonInterval){
      i++;
      if(10<i) i=0;
      pushButton1PreviousMillis = currentMillis;
    }  
  }

  if(digitalRead(button2) == LOW){
    if(currentMillis - pushButton1PreviousMillis > pushButtonInterval){
      i--;
      if(i<0) i=10;
      pushButton1PreviousMillis = currentMillis;
    }  
  }
  
  //analogWrite 0-255;
//  analogWrite(11,25*i);
  
  if(j<i){
    digitalWrite(fanPin,HIGH);
  }else{
    digitalWrite(fanPin,LOW);
  }

  j++;
  if(j==10)j=0;  


//7seg display
  show7seg(i);

}

//7Seg用
const int calactor[11]={0x08,0xAF,0x30,0x24,0x86,0x44,0x40,0x2F,0x00,0x04,0x02};

//7Segを点灯させるルーチン
void show7seg(int segment){
  currentMillis = millis();
  
  //0の状態で interval7seg 経過したら7セグを消灯させる
  if(segment == 0){
    if(previousMillis7seg + interval7seg < currentMillis){
      PORTD = 0xFF;
      return;
    }
  }else{
    previousMillis7seg = currentMillis;
  }
  
  if(currentMillis - segPreviousMillis > segInterval){
    segPreviousMillis = currentMillis;

    if(PORTD == 0xFF){ 
      PORTD = calactor[segment];
    }else{
      PORTD = 0xFF;
    }
  }
}
