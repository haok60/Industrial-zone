int measurePin = A0;
int ledPower = 2;
static float Voc = 0.6;

int samplingTime = 280;
int deltaTime = 40;
int sleepTime = 9680;
 
float voMeasured = 0.0;
float calcVoltage = 0.0;
float dustDensity = 0.0;
float Vo;
float dV;
void setup(){
  Serial.begin(9600);
  pinMode(ledPower,OUTPUT);
  pinMode(A0,INPUT);
  //analogReference(DEFAULT);
  digitalWrite(ledPower,HIGH);
}
 
void loop(){
  digitalWrite(ledPower,LOW); // Bật IR LED
  delayMicroseconds(samplingTime);  //Delay 0.28ms
  voMeasured = analogRead(A0); // Đọc giá trị ADC V0
  //Serial.println(voMeasured);
  
  delayMicroseconds(deltaTime); //Delay 0.02ms
  digitalWrite(ledPower,HIGH); // Tắt LED
  delayMicroseconds(sleepTime); //Delay 9.68ms
  Vo = (5*voMeasured)/1024;
  dV = Vo - Voc;
  if(dV < 0 )
  {
    dV = 0;
    Voc = Vo;
  }
  // Tính điện áp từ giá trị ADC
  //calcVoltage = (voMeasured*5)/1024; //Điệp áp Vcc của cảm biến (5.0 hoặc 3.3)
  // Linear Equation http://www.howmuchsnow.com/arduino/airquality/
  // Chris Nafis (c) 2012
  //dustDensity = calcVoltage*0.2-0.08; 
 dustDensity = dV*0.2;
 
  Serial.print("Raw Signal Value (0-1023): ");
  Serial.print(voMeasured);
  Serial.print(" - Voltage: ");
//  Serial.print(calcVoltage);
//  Serial.print(" - Dust Density: ");
  Serial.print(Vo);
  Serial.print(" - Dust Density: ");
  Serial.println(dustDensity);
  delay(1000);
}
