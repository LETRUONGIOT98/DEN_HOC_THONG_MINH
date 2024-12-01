// Khai báo chân kết nối
const int trigPin = 7; // Chân Trig kết nối với chân 2 của Arduino
const int echoPin = 8; // Chân Echo kết nối với chân 3 của Arduino
#define led 3
#define cambien A0
int gioihan = 30;
int dosang = 450; 
#define coi 4
int i =0;
long times;
void setup() {
  // Khởi tạo Serial để xuất kết quả
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  pinMode(coi, OUTPUT);
  digitalWrite(coi, LOW);
  pinMode(cambien, INPUT);
  // Khởi tạo chân Trig là đầu ra
  pinMode(trigPin, OUTPUT);
  // Khởi tạo chân Echo là đầu vào
  pinMode(echoPin, INPUT);
}

void loop() {
  // Biến để lưu thời gian
  long duration;
  // Biến để lưu khoảng cách
  float khoangcach;

  // Làm sạch chân Trig
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Gửi xung siêu âm
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Đọc thời gian xung Echo quay lại
  duration = pulseIn(echoPin, HIGH);

  // Tính khoảng cách (cm)
  khoangcach = (duration * 0.034) / 2;
  
  // Xuất kết quả lên Serial Monitor
  Serial.print("Khoang cach: ");
  Serial.print(khoangcach);
  Serial.println(" cm");
  
  // Delay một chút trước khi vòng lặp tiếp theo
  if(khoangcach > 5 && khoangcach < 100){
    times = millis();
    int val = analogRead(cambien);
    val = map(val,0,1023,1023,0);
    if(val > dosang + 50 && i > 0){
      i = i - 1;
      //delay(1);
    }
    if(val < dosang - 50 && i < 255){
      i = i + 1;
      //delay(1);
    }
    Serial.print("PWM: ");
    Serial.print(i);
    Serial.print("  DO SANG HIEN TAI: ");
    Serial.print(val);
    Serial.print("  DO SANG SET: ");
    Serial.println(dosang);
    analogWrite(led, i);
    if(khoangcach < gioihan){
      digitalWrite(coi, HIGH);
    }
    else digitalWrite(coi, LOW);
  }
  else {
    if(millis() - times >= 5000){
      i = 0;
    analogWrite(led, i);}
    digitalWrite(coi, LOW);}
    
}
