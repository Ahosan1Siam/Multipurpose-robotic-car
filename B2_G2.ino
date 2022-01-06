#include <LiquidCrystal.h>
#include <Keypad.h>
#include <TinyGPS.h>
#include <Wire.h>
#include <Servo.h>
Servo myservo;
TinyGPS gps;  //Creates a new instance of the TinyGPS object

#include "DHT.h"
#define DHTPIN 23
float comparetempareture = 25.00, comparehumidity =65.80;
const int rs = 12, en = 13, d4 = 8, d5 = 9, d6 = 10, d7 = 11;
const byte ROWS = 4; //four rows
const byte COLS = 3; //four col
boolean start1,start2,start3,start4,start5,start6= false;
int flag =0;
const int n=1;
bool newData = false;
bool newData_servo= false;
int GasSensor = 28;
int PirSensor = 33;
int Led = 29;
int Led_pir= 34;
int pos = 0;
int Buzzer = 30;
char customKey,mode;
char hexaKeys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[ROWS] = {2, 3, 4, 5}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {6, 7, 14}; //connect to the column pinouts of the keypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int LeftMotorForward = 15;
int LeftMotorReverse = 16;
int RightMotorForward = 17;
int RightMotorReverse = 18;

int LeftMotorForward_2 = 19;
int LeftMotorReverse_2 = 31;
int RightMotorForward_2 = 32;
int RightMotorReverse_2 = 22;

int FanMotorForward = 24;
int FanMotorReverse = 25;

int FanMotorForward_2 =26;
int FanMotorReverse_2 = 27;

#define DHTTYPE DHT22       // DHT22 sensor is used
DHT dht(DHTPIN, DHTTYPE);   // Initialize DHT library

char temperature[] = "Temp = 00.0 C";
char humidity[]    = "RH   = 00.0 %";

char Time[]     = "TIME:  :  :  ";
char Calendar[] = "DATE:  /  /20  ";
byte i, second, minute, hour, date, month, year;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(RightMotorForward, OUTPUT);  
  pinMode(RightMotorReverse, OUTPUT);  
  pinMode(LeftMotorForward, OUTPUT);  
  pinMode(LeftMotorReverse, OUTPUT);
  
  pinMode(RightMotorForward_2, OUTPUT);  
  pinMode(RightMotorReverse_2, OUTPUT);  
  pinMode(LeftMotorForward_2, OUTPUT);  
  pinMode(LeftMotorReverse_2, OUTPUT);

  pinMode(FanMotorForward, OUTPUT);  
  pinMode(FanMotorReverse, OUTPUT);  
  pinMode(FanMotorForward_2, OUTPUT);  
  pinMode(FanMotorReverse_2, OUTPUT);

  pinMode(GasSensor,INPUT);
  pinMode(Led,OUTPUT);

  pinMode(Buzzer,OUTPUT);

  pinMode(PirSensor,INPUT);
  pinMode(Led_pir,OUTPUT);

  pinMode(52, INPUT_PULLUP);                      
  pinMode(53, INPUT_PULLUP); 

  myservo.attach(35);

  dht.begin();
  Wire.begin();
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.clear();
  lcd.print("Initializing..");
  delay(300);
  lcd.clear();
  lcd.setCursor(5,0);
  delay(500);
  lcd.print("Hello");
  delay(300);
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("Welcome to the");
  lcd.setCursor(5,1);
  lcd.print("System");
  delay(300);
  lcd.clear();
  for(int i=0;i<n;i++){
  Menu_Display();
}
}
void loop() {
  
  if(flag==0){
    Menu_Operate();
    }
    if(start1==true)
    { carmode();
      }
    else if(start2==true)
    {
      temp_hummode();
     }
    else if(start3==true)
    {
      gasmode();
     }
    else if(start4==true)
    {
      gpsmode();
     }
    else if(start5==true)
     {
      clockmode();
      }
    else if(start6==true)
    {
      securitymode();
      }
}
void Menu_Display()
{
  lcd.setCursor(4,0);
  lcd.print("Press 9 for");
  lcd.setCursor(5,1);
  lcd.print("car mode");
  Serial.println("Press 9 for car mode");
  delay(300);
  lcd.clear();

  lcd.setCursor(4,0);
  lcd.print("Press * for");
  lcd.setCursor(2,1);
  lcd.print("Temp_hum mode");
  Serial.println("Press * for Temp_hum mode");
  delay(300);
  lcd.clear();

  lcd.setCursor(4,0);
  lcd.print("Press 0 for");
  lcd.setCursor(5,1);
  lcd.print("Gas mode");
  Serial.println("Press 0 for gas mode");
  delay(300);
  lcd.clear();

  lcd.setCursor(4,0);
  lcd.print("Press # for");
  lcd.setCursor(5,1);
  lcd.print("Gps mode");
  Serial.println("Press # for gps mode");
  delay(300);
  lcd.clear();

  lcd.setCursor(4,0);
  lcd.print("Press 7 for");
  lcd.setCursor(5,1);
  lcd.print("Clock mode");
  Serial.println("Press 7 for Clock mode");
  delay(300);
  lcd.clear();

  lcd.setCursor(4,0);
  lcd.print("Press 3 for");
  lcd.setCursor(2,1);
  lcd.print("Security mode");
  Serial.println("Press 3 for Security mode");
  delay(300);
  lcd.clear();
}
void Menu_Operate()
{
  customKey = customKeypad.getKey();
  Serial.println(customKey);
  switch(customKey)
  {
    case '9':
    lcd.clear();
    lcd.setCursor(4,0);
    lcd.print("Car mode");
    lcd.setCursor(5,1);
    lcd.print("activated");
    Serial.println("car mode activated");
    delay(300);
    lcd.clear();
    start1=true;
    break;
    
    case '*':
    lcd.clear();
    lcd.setCursor(1,0);
    lcd.print("Temp_hum mode");
    lcd.setCursor(5,1);
    lcd.print("activated");
    Serial.println("Temp_hum mode activated");
    delay(300);
    lcd.clear();
    start2=true;
    break;

    case '0':
    lcd.clear();
    lcd.setCursor(4,0);
    lcd.print("Gas mode");
    lcd.setCursor(5,1);
    lcd.print("activated");
    Serial.println("Gas mode activated");
    delay(300);
    lcd.clear();
    start3=true;
    break;

    case '#':
    lcd.clear();
    lcd.setCursor(4,0);
    lcd.print("GPS mode");
    lcd.setCursor(5,1);
    lcd.print("activated");
    Serial.println("Gps mode activated");
    delay(300);
    lcd.clear();
    start4=true;
    newData=false;
    break;

    case '7':
    lcd.clear();
    lcd.setCursor(4,0);
    lcd.print("Clock mode");
    lcd.setCursor(5,1);
    lcd.print("activated");
    Serial.println("Clock mode activated");
    delay(300);
    lcd.clear();
    start5=true;
    break;

    case '3':
    lcd.clear();
    lcd.setCursor(1,0);
    lcd.print("Security mode");
    lcd.setCursor(5,1);
    lcd.print("activated");
    Serial.println("Security mode activated");
    delay(300);
    lcd.clear();
    start6=true;
    newData_servo= false;
    break;
   } 
}
void carmode()
{   
    lcd.setCursor(0,0);
    lcd.print("Press 1 to start");
    Serial.println("press 1 to start");
    delay(300); 
    flag=1;
    while(flag==1){
    customKey = customKeypad.getKey();
    Serial.println(customKey);
      if(customKey=='1')
      { 
        lcd.clear();
        while(flag==1){
        lcd.setCursor(0,0);
        lcd.print("Car started");
        lcd.setCursor(0,1);
        lcd.print("press 2 to stop");
        customKey = customKeypad.getKey();
        Serial.println(customKey);
        switch(customKey)
        { case '4':
          //Left Turn
          digitalWrite(RightMotorForward, HIGH); 
          digitalWrite(RightMotorReverse, LOW);
          digitalWrite(LeftMotorForward, LOW);
          digitalWrite(LeftMotorReverse, LOW);
           
          digitalWrite(RightMotorForward_2, LOW); 
          digitalWrite(LeftMotorForward_2, LOW);
          digitalWrite(RightMotorReverse_2, HIGH); 
          digitalWrite(LeftMotorReverse_2, HIGH);

          break;

          case '6':
          //Right Turn
          digitalWrite(LeftMotorForward, HIGH); 
          digitalWrite(LeftMotorReverse, LOW);  
          digitalWrite(RightMotorForward, LOW);
          digitalWrite(RightMotorReverse, LOW);

          digitalWrite(RightMotorForward_2, LOW); 
          digitalWrite(LeftMotorForward_2, LOW);
          digitalWrite(RightMotorReverse_2, HIGH); 
          digitalWrite(LeftMotorReverse_2, HIGH);

          break;

          case '5':
          // Forward
          digitalWrite(RightMotorForward, HIGH); 
          digitalWrite(LeftMotorForward, HIGH);
          digitalWrite(RightMotorReverse, LOW); 
          digitalWrite(LeftMotorReverse, LOW);

          digitalWrite(RightMotorForward_2, LOW); 
          digitalWrite(LeftMotorForward_2, LOW);
          digitalWrite(RightMotorReverse_2, HIGH); 
          digitalWrite(LeftMotorReverse_2, HIGH);
          break;

          case '8':
          //Reverse
          digitalWrite(RightMotorReverse, HIGH); 
          digitalWrite(LeftMotorReverse, HIGH);   
          digitalWrite(RightMotorForward, LOW);
          digitalWrite(LeftMotorForward, LOW);

          digitalWrite(RightMotorReverse_2, LOW); 
          digitalWrite(LeftMotorReverse_2, LOW);   
          digitalWrite(RightMotorForward_2, HIGH);
          digitalWrite(LeftMotorForward_2, HIGH);

          break;
          case '2':
          lcd.clear();
          digitalWrite(RightMotorReverse, LOW); 
          digitalWrite(LeftMotorReverse, LOW);   
          digitalWrite(RightMotorForward, LOW);
          digitalWrite(LeftMotorForward, LOW);

          digitalWrite(RightMotorReverse_2, LOW); 
          digitalWrite(LeftMotorReverse_2, LOW);   
          digitalWrite(RightMotorForward_2, LOW);
          digitalWrite(LeftMotorForward_2, LOW);
          flag=0;
          start1=false;
          for(int i=0;i<n;i++){
          Menu_Display();
          }
          break;
          }
        }
       }
    }
}
void temp_hummode()
{
    lcd.setCursor(0,0);
    lcd.print("Press 1 to start");
    Serial.println("press 1 to start");
    lcd.setCursor(0,1);
    lcd.print("press 2 to stop");
    Serial.println("press 2 to stop");
    delay(300);
    flag=1;
    while(flag==1){
    customKey = customKeypad.getKey();
    Serial.println(customKey);
      if(customKey=='1')
      { 
        lcd.clear();
        while(flag==1){
        lcd.setCursor(0,0);
         
        // Read humidity
        int RH = dht.readHumidity() * 10;
        //Read temperature in degree Celsius
        int Temp = dht.readTemperature() * 10;
  
        // Check if any reads failed and exit early (to try again)
        if (isnan(RH) || isnan(Temp)) {
          lcd.clear();
          lcd.setCursor(5, 0);
          lcd.print("Error");
          return;
  }
 
        if(Temp < 0){
           temperature[6] = '-';
           Temp = abs(Temp);
  }
        else
           {temperature[6]   = ' ';}
        temperature[7]   = (Temp / 100) % 10  + 48;
        temperature[8]   = (Temp / 10)  % 10  + 48;
        temperature[10]  =  Temp % 10 + 48;
        temperature[11]  = 223;        // Degree symbol ( °)
  
        if(RH >= 1000){
         humidity[6]    = '1';}
        else{
          humidity[6]      = ' ';}
        humidity[7]      = (RH / 100) % 10 + 48;
        humidity[8]      = (RH / 10) % 10 + 48;
        humidity[10]     =  RH % 10 + 48;
  
        lcd.setCursor(0, 0);
        lcd.print(temperature);
        lcd.setCursor(0, 1);
        lcd.print(humidity);

        float tempc = dht.readTemperature();
        float rhc = dht.readHumidity();


        if (tempc >comparetempareture ) {
             digitalWrite(FanMotorForward, HIGH);
             digitalWrite(FanMotorReverse, LOW);
          }
        if (tempc < comparetempareture) {
            digitalWrite(FanMotorForward, LOW);
            digitalWrite(FanMotorReverse, HIGH);
          }
        if (rhc >comparehumidity ) {
            digitalWrite(FanMotorForward_2, HIGH);
            digitalWrite(FanMotorReverse_2, LOW);
          }
        if (rhc < comparehumidity) {
            digitalWrite(FanMotorForward_2, LOW);
            digitalWrite(FanMotorReverse_2, LOW);
          }
        customKey = customKeypad.getKey();
        Serial.println(customKey);
        switch(customKey)
        { case '2':
          lcd.clear();
          digitalWrite(FanMotorForward, LOW);
          digitalWrite(FanMotorReverse, LOW);
          digitalWrite(FanMotorForward_2, LOW);
          digitalWrite(FanMotorReverse_2, LOW);
          flag=0;
          start2=false;
          for(int i=0;i<n;i++){
          Menu_Display();
          }
          break;
          }
        }
       }
    }
}
void gasmode()
{
    lcd.setCursor(0,0);
    lcd.print("Press 1 to start");
    delay(300);
    flag=1;
    while(flag==1){
    customKey = customKeypad.getKey();
    Serial.println(customKey);
      if(customKey=='1')
      { 
        lcd.clear();
        while(flag==1){
        lcd.setCursor(0,0);
        lcd.print("Sensor started");
        lcd.setCursor(0,1);
        lcd.print("press 2 to stop");
        if(digitalRead(GasSensor)==HIGH)
        {
            digitalWrite(Led,HIGH);
            tone(Buzzer,1000);
            delay(1000);
            noTone(Buzzer);
        }  
       else
        {
            digitalWrite(Led,LOW);
        }
        customKey = customKeypad.getKey();
        Serial.println(customKey);
        switch(customKey)
        { case '2':
          lcd.clear();
          flag=0;
          start3=false;
          for(int i=0;i<n;i++){
          Menu_Display();
          }
          break;
          }
        }
       }
    }
}
void gpsmode()
{   
    lcd.setCursor(0,0);
    lcd.print("Press 1 to start");
    Serial.println("press 1 to start");
    lcd.setCursor(0,1);
    lcd.print("press 2 to stop");
    Serial.println("press 2 to stop");
    delay(300);
    flag=1;
    while(flag==1){
    customKey = customKeypad.getKey();
    Serial.println(customKey);
      if(customKey=='1')
      { 
        lcd.clear();
        while(flag==1){
        lcd.setCursor(0,0);
        unsigned long chars;
        unsigned short sentences, failed;

  // For one second we parse GPS data and report some key values
      if(newData==false){
      for (unsigned long start = millis(); millis() - start < 1000;)
        {
         while (Serial.available())
       {
         char c = Serial.read();
         gps.encode(c); 
      }
     }
        float flat, flon;
        unsigned long age;
        gps.f_get_position(&flat, &flon, &age);   
        Serial.print("Latitude = ");
        Serial.print(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6);
        Serial.print(" Longitude = ");
        Serial.print(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6);
        lcd.setCursor(0, 0);
        lcd.print("Latitude=");
        lcd.setCursor(10, 0);
        lcd.print(flat);
        lcd.setCursor(0, 1);
        lcd.print("Longitude=");
        lcd.setCursor(11, 1);
        lcd.print(flon);
        
        Serial.println(failed);
        newData =true;
     }         
        customKey = customKeypad.getKey();
        Serial.println(customKey);
        switch(customKey)
        { case '2':
          lcd.clear();
          flag=0;
          start4=false;
          newData=false;
          for(int i=0;i<n;i++){
          Menu_Display();
          }
          break;
          }
        }
       }
    }
}
void blink_parameter(){
  byte j = 0;
  while(j < 10 && digitalRead(52) && digitalRead(53)){
    j++;
    delay(25);
  }
}
byte edit(byte x, byte y, byte parameter){
  char text[3];
  while(!digitalRead(52));                        // Wait until button (pin #52) released
  while(true){
    while(!digitalRead(53)){                      // If button (pin #53) is pressed
      parameter++;
      if(i == 0 && parameter > 23)               // If hours > 23 ==> hours = 0
        parameter = 0;
      if(i == 1 && parameter > 59)               // If minutes > 59 ==> minutes = 0
        parameter = 0;
      if(i == 2 && parameter > 31)               // If date > 31 ==> date = 1
        parameter = 1;
      if(i == 3 && parameter > 12)               // If month > 12 ==> month = 1
        parameter = 1;
      if(i == 4 && parameter > 99)               // If year > 99 ==> year = 0
        parameter = 0;
      sprintf(text,"%02u", parameter);
      lcd.setCursor(x, y);
      lcd.print(text);
      delay(50);                                // Wait 200ms
    }
    lcd.setCursor(x, y);
    lcd.print("  ");                             // Display two spaces
    blink_parameter();
    sprintf(text,"%02u", parameter);
    lcd.setCursor(x, y);
    lcd.print(text);
    blink_parameter();
    if(!digitalRead(52)){                         // If button (pin #52) is pressed
      i++;                                       // Increament 'i' for the next parameter
      return parameter;                          // Return parameter value and exit
    }
  }
}
void DS3231_display(){
  // Convert BCD to decimal
    second = (second >> 4) * 10 + (second & 0x0F);
    minute = (minute >> 4) * 10 + (minute & 0x0F);
    hour   = (hour >> 4)   * 10 + (hour & 0x0F);
    date   = (date >> 4)   * 10 + (date & 0x0F);
    month  = (month >> 4)  * 10 + (month & 0x0F);
    year   = (year >> 4)   * 10 + (year & 0x0F);
    // End conversion
    Time[12]     = second % 10 + 48;
    Time[11]     = second / 10 + 48;
    Time[9]      = minute % 10 + 48;
    Time[8]      = minute / 10 + 48;
    Time[6]      = hour   % 10 + 48;
    Time[5]      = hour   / 10 + 48;
    Calendar[14] = year   % 10 + 48;
    Calendar[13] = year   / 10 + 48;
    Calendar[9]  = month  % 10 + 48;
    Calendar[8]  = month  / 10 + 48;
    Calendar[6]  = date   % 10 + 48;
    Calendar[5]  = date   / 10 + 48;
    lcd.setCursor(0, 0);
    lcd.print(Time);                               // Display time
    lcd.setCursor(0, 1);
    lcd.print(Calendar);                           // Display calendar
}
void clockmode()
{
    lcd.setCursor(0,0);
    lcd.print("Press 1 to start");
    Serial.println("press 1 to start");
    lcd.setCursor(0,1);
    lcd.print("press 2 to stop");
    Serial.println("press 2 to stop");
    delay(300);
    flag=1;
    lcd.clear();
    while(flag==1){
    customKey = customKeypad.getKey();
    Serial.println(customKey);
    if(customKey=='1')
      { 
        while(flag==1){
        //lcd.clear();
        if(!digitalRead(52)){                           // If button (pin #52) is pressed
        i = 0;
        hour   = edit(5, 0, hour);
        minute = edit(8, 0, minute);
        date   = edit(5, 1, date);
        month  = edit(8, 1, month);
        year   = edit(13, 1, year);
      // Convert decimal to BCD
        minute = ((minute / 10) << 4) + (minute % 10);
        hour = ((hour / 10) << 4) + (hour % 10);
        date = ((date / 10) << 4) + (date % 10);
        month = ((month / 10) << 4) + (month % 10);
        year = ((year / 10) << 4) + (year % 10);
      // End conversion
      // Write data to DS3231 RTC
        Wire.beginTransmission(0x68);               // Start I2C protocol with DS3231 address
        Wire.write(0);                              // Send register address
        Wire.write(0);                              // Reset sesonds and start oscillator
        Wire.write(minute);                         // Write minute
        Wire.write(hour);                           // Write hour
        Wire.write(1);                              // Write day (not used)
        Wire.write(date);                           // Write date
        Wire.write(month);                          // Write month
        Wire.write(year);                           // Write year
        Wire.endTransmission();                     // Stop transmission and release the I2C bus
        delay(75);                                 // Wait 75ms
      }
         Wire.beginTransmission(0x68);                 // Start I2C protocol with DS3231 address
         Wire.write(0);                                // Send register address
         Wire.endTransmission(false);                  // I2C restart
         Wire.requestFrom(0x68, 7);                    // Request 7 bytes from DS3231 and release I2C bus at end of reading
         second = Wire.read();                         // Read seconds from register 0
          minute = Wire.read();                         // Read minuts from register 1
         hour   = Wire.read();                         // Read hour from register 2
          Wire.read();                                  // Read day from register 3 (not used)
          date   = Wire.read();                         // Read date from register 4
           month  = Wire.read();                         // Read month from register 5
           year   = Wire.read();                         // Read year from register 6
          DS3231_display();                             // Diaplay time & calendar
          delay(50);
          customKey = customKeypad.getKey();
          Serial.println(customKey);
          if(customKey=='2')
          {
            flag=0;
            start5=false;
            lcd.clear();
            for(int i=0;i<n;i++){
            Menu_Display();
          }
       }
          else
       {
          continue;
        }
       }
     }
    }  
  }
void securitymode()
{
    lcd.setCursor(0,0);
    lcd.print("Press 1 to start");
    //lcd.setCursor(0,1);
    //lcd.print("press 2 to stop");
    delay(300);
    flag=1;
    while(flag==1){
    customKey = customKeypad.getKey();
    Serial.println(customKey);
      if(customKey=='1')
      { 
        lcd.clear();
        while(flag==1){
        lcd.setCursor(0,0);
        lcd.print("Sensor started");
        lcd.setCursor(0,1);
        lcd.print("press 2 to stop");
        if(digitalRead(PirSensor)==HIGH)
        {
            digitalWrite(Led_pir,HIGH);
            if(newData_servo==false){
           
                  myservo.write(180);              
                  delay(20);
                  newData_servo==true;
               }
           
            }  
        else
        {
            digitalWrite(Led_pir,LOW);
        }
        customKey = customKeypad.getKey();
        Serial.println(customKey);
        switch(customKey)
        { case '2':
          lcd.clear();
          digitalWrite(Led_pir,LOW);
          myservo.write(90);              
          delay(20);
          //newData_servo==false;
          flag=0;
          start6=false;
          for(int i=0;i<n;i++){
          Menu_Display();
          }
          break;
          }
        }
       }
    }
} 
