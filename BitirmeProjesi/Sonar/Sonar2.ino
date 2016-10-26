#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

#include <Servo.h> //Servo kütüphanesini taslağımıza dahil ediyoruz.
Servo myservo; //Servo motoru kontrol etmek için "myservo" adında bir obje yaratıyoruz.
int poz = 0; //Poziyon bilgisini saklamak için "poz" adında bir değişken tanımlıyoruz.
int i=0;
int dist,inv=0;
boolean stan=0;
int pos = 0;
#include <Ultrasonic.h>
Ultrasonic ultrasonic(2,6);


Adafruit_PCD8544 display = Adafruit_PCD8544(8, 9, 10, 12, 11);


extern uint8_t TinyFont[]; //5110 kütüphanesindeki TintFont (Minik Font)u kullanmamız için onu tanıtıyoruz.
extern uint8_t snr[]; //Açılıştaki Sonar resmini tanıtıyoruz.

void setup() {
  Serial.begin(9600);
  display.begin();
  display.setContrast(60);

pinMode(1,OUTPUT);
  pinMode(13, OUTPUT); // set a pin for buzzer output
  pinMode(5, OUTPUT); //Arduino Pro Mini'de 3.3v ya da 5v güç çıkışı bulunmadığı ...
                      //için standart giriş çıkış pinlerini bu amaçla kullanıyoruz.
                      //Burada 5 numaralı pini çıkış olarak ayarlıyoruz. Bu pin 5110 LCD'ye...
                      //güç vermek için kullanılacak.
  pinMode(7, OUTPUT); //5110 LCD'nin arkaplan ışığını yakmak için güç aldığımız dijital pin. Çıkış olarak ayarlıyoruz.
  pinMode(2, OUTPUT); // Ultrasonik ses dalgasını gönderme komutunu bu pinle yapacağız.
  pinMode(6, INPUT); // Geri gelen ses dalgalarını bu pinden algılayacağız.
  pinMode(4, OUTPUT); //Ultrasonik sensörün Vcc pinini Arduino'nun 4. pinine bağladık.
  digitalWrite(4, HIGH); //Ultrasonik sensöre güç veriyoruz.
  digitalWrite(5,HIGH);//5110'a güç veriyoruz.
  digitalWrite(7,HIGH);//5110 arkaplan ışığına güç veriyoruz.
  myservo.attach(3);  //Servo motorumuzun 3. pine bağlı olduğunu bildiriyoruz.
   myservo.attach(3); 
  // AÇIL
  buzz(13, 2500, 500); 

  delay(3000); //3 saniye bekledikten sonra
 display.clearDisplay();
}

void loop() {
distance(); 

for(i=5;i<=165;i=i+2){
       myservo.write(i);              // tell servo to go to position in variable 'pos'
    delay(15);
    display.clearDisplay();   
  display.drawLine(i-2,0,42,47,WHITE); 
  display.drawLine(i,0,42,47,BLACK);
  grid();
  distance(); 
  
  display.display();   
  delay(50); 
}
for(i=165;i>=15;i=i-2){
   myservo.write(i);              // tell servo to go to position in variable 'pos'
    delay(15);
      display.clearDisplay();
  display.drawLine(i,0,42,47,BLACK);
  grid();
  distance(); 
  display.display();   
  delay(50);
  
}
distance(); 
}

void distance(){
  grid();
  display.setCursor(66,33);
  dist=ultrasonic.Ranging(CM);
  display.println(dist);
  
  if (dist<=10){
  display.setCursor(54,41);
  display.println("ALERT"); 
   buzz(13, 2500, 500); 
   renk();
  }
   Serial.print(i);
  Serial.print(",");
  Serial.print(dist);
  Serial.print("."); 
}

void grid(){
  //function body
  display.drawLine(0,0,42,47,BLACK);
  display.drawLine (84,0,42,47,BLACK);
  display.drawCircle(42,47,5,BLACK);
  display.drawCircle(42,47,15,BLACK);
  display.drawCircle(42,47,25,BLACK);
  display.drawCircle(42,47,35,BLACK);
  display.drawCircle(42,47,45,BLACK); 
  display.drawCircle(42,47,55,BLACK);
  display.fillTriangle(0,1,41,47,0,47,WHITE);
  display.fillTriangle(84,1,43,47,84,47,WHITE);
  display.drawLine(0,7,0,47,BLACK);
  display.drawLine(42,0,42,47,BLACK);
  display.drawLine(0,47,3,47,BLACK);
  display.drawLine(0,42,1,42,BLACK);
  display.drawLine(0,37,3,37,BLACK);
  display.drawLine(0,32,1,32,BLACK);
  display.drawLine(0,27,3,27,BLACK);
  display.drawLine(0,22,1,22,BLACK);
  display.drawLine(0,17,3,17,BLACK);
  display.drawLine(0,12,1,12,BLACK);
  display.drawLine(0,7,3,7,BLACK);
  display.fillCircle(42,(48-dist/8),2,BLACK);
}
void buzz(int targetPin, long frequency, long length) {
  long delayValue = 1000000/frequency/2; // calculate the delay value between transitions
  //// 1 second's worth of microseconds, divided by the frequency, then split in half since
  //// there are two phases to each cycle
  long numCycles = frequency * length/ 1000; // calculate the number of cycles for proper timing
  //// multiply frequency, which is really cycles per second, by the number of seconds to 
  //// get the total number of cycles to produce
 for (long i=0; i < numCycles; i++){ // for the calculated length of time...
    digitalWrite(targetPin,HIGH); // write the buzzer pin high to push out the diaphram
    delayMicroseconds(delayValue); // wait for the calculated delay value
    digitalWrite(targetPin,LOW); // write the buzzer pin low to pull back the diaphram
    delayMicroseconds(delayValue); // wait againf or the calculated delay value
  }
}
void renk(){
  
for(int fadeValue = 255 ; fadeValue >= 0; fadeValue -=35) { 
    analogWrite(1, fadeValue);            
    delay(30);                            
  }
  
  }
