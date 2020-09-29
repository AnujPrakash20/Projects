#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

#define SERVO_PIN 3
Servo myservo;
 
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.


void setup() {
  Serial.begin(115200);
  SPI.begin();
  mfrc522.PCD_Init();
  Serial.println("Arduino RFID door lock");

  myservo.attach(SERVO_PIN);
  myservo.write( 0 );

pinMode(7,INPUT);
digitalWrite(7,LOW);

}
void push()
{
 
  if(digitalRead(7) == HIGH)
  {
    myservo.write(0);
    delay(15);
  }
}

void loop(){
  //Look for new cards
  if ( !mfrc522.PICC_IsNewCardPresent() ){
    return;
  }
  //Select one of the cards
  if ( !mfrc522.PICC_ReadCardSerial() ) {
    return;
  }
  
  String content= "";
  byte letter;
  for( byte i = 0; i < mfrc522.uid.size; i++ ){
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
     if( i < mfrc522.uid.size-1 ) content+="-";
  }
  content.toUpperCase();
  Serial.println();
  Serial.println("UID tag :'" + content + "'");


  if( content == "E6-15-C1-BB" || "35-17-F2-15" ){
    Serial.println("Authorized access");
    myservo.write( 90 );
 delay(15);
    push();
  }
  else
  {
    Serial.println("Access denied");
  }
  delay(1000);
}
