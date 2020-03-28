int numbers [10][7] = {  
  //C, D, E, G, F, A, B
  { 0, 0, 0, 1, 0, 0, 0 }, // 0
  { 0, 1, 1, 1, 1, 1, 0 }, // 1
  { 1, 0, 0, 0, 1, 0, 0 }, // 2
  { 0, 0, 1, 0, 1, 0, 0 }, // 3
  { 0, 1, 1, 0, 0, 1, 0 }, // 4
  { 0, 0, 1, 0, 0, 0, 1 }, // 5
  { 0, 0, 0, 0, 0, 0, 1 }, // 6
  { 0, 1, 1, 1, 1, 0, 0 }, // 7
  { 0, 0, 0, 0, 0, 0, 0 }, // 8
  { 0, 1, 1, 0, 0, 0, 0 }, // 9
};

int pin_offset = 2  ;
int cmd, value = 0;
String s_read = "";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(2, OUTPUT); // C
  pinMode(3, OUTPUT); // D
  pinMode(4, OUTPUT); // E
  pinMode(5, OUTPUT); // G
  pinMode(6, OUTPUT); // F
  pinMode(7, OUTPUT); // A
  pinMode(8, OUTPUT); // B
  off_all();
}

void write_all_numbers(){
  for( int i = 0; i < 10; i++){
    write_number(i);
    delay(500);
  }
}

void off_all(){
  for( int x = 0; x <= 7; x++){
    digitalWrite(x+pin_offset, HIGH);
  }
}

void write_number(int number){
  for( int x = 0; x <= 7; x++){
    digitalWrite(x+pin_offset, numbers[number][x]);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available() > 0){
    s_read = Serial.readString();
    Serial.print("String length: ");
    Serial.print(s_read.length());
    if(s_read.length() == 3){
      cmd = s_read[0] - 48;
      
      value = s_read[1] - 48;

      Serial.print(" CMD: ");
      Serial.print(cmd);
      Serial.print(" Value: ");
      Serial.print(value);

      if(cmd == 2){        
        if(value >= 0 && 9 >= value){
          write_number(value);
        }
      }else if(cmd == 1){
        digitalWrite(value, HIGH);
      }else if(cmd == 0){
        digitalWrite(value, LOW);
      }
    }
    Serial.println();
  }
}
