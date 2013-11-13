
// X-axis
int x_pin = 3;
int x = 0;
float x_cm = 28.0; // in cm
int x_max = 116;
float x_scale = 1; // V/cm

// Y Axis
int y_pin = 6;
float y_cm = 18.0; // in cm
int y_max = 152;
int y = 0;
float y_scale = 1; // V/cm

// Pen Pin
int pen_pin = 2;


void setup() {                
  pinMode(x_pin, OUTPUT);     
  pinMode(y_pin, OUTPUT);
  pinMode(pen_pin, OUTPUT);
  
  penDown();
  
  Serial.begin(9600);
  Serial.flush();
}

void penUp() {
  digitalWrite(pen_pin, LOW);
}

void penDown() {
   digitalWrite(pen_pin, HIGH);
}

void setX(int value) {
  analogWrite(x_pin, value); 
  x = value;
  delay(50);
}

void setY(int value) {
  analogWrite(y_pin, value); 
  y = value;
  delay(50);
}


void setXcm(float cm) {
  if (cm > x_cm || cm < 0)
    return;

  setX(int(x_max/x_cm * cm));
}

void setYcm(float cm) {
  if (cm > y_cm || cm < 0)
    return;

  setY(int(y_max/y_cm * cm));
}

union u_tag {
  byte b[4]; 
  double fval;
}; 


float read_float() {
  u_tag ser_float;
  
  for(int i=0;i<4;i++) {
      ser_float.b[i] = Serial.read();
      delay(10); 
  }
    
  return ser_float.fval;
}

void writeFloat(float f) {
    Serial.write(lowByte(long(f)));    // Serial.println(x1);
    Serial.write(highByte(long(f)));    // Serial.println(x1);
//    Serial.flush();
//Serial.println("yeah");
         delay(10); 
    //    Serial.print(highByte(f), BYTE);    // Serial.println(x1); 
}

void loop() {

  if (Serial.available() >= 16) {
    float x1=0, y1=0, x2=0, y2=0;
    // read X1
    x1 = read_float();
    writeFloat(x1);
    
    y1 = read_float();
    writeFloat(y1);
        
    x2 = read_float();
    writeFloat(x2);
    
    y2 = read_float();
    writeFloat(y2);

    penDown();
    
    //Serial.println("--START--");    
    setXcm(x1);
    setYcm(y1);
    
    delay(300);

    //Serial.println("--END--");    
    //Serial.println(x2);
    //Serial.println(y2);    
    setXcm(x2);
    setYcm(y2);
    
    delay(300);
    
    penUp();
    
  } 

}

