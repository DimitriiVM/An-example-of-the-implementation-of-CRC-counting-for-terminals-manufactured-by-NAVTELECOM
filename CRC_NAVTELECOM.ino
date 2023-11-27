uint8_t mas[] ={0x40, 0x4e, 0x54, 0x43, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x2a, 0x3f, 0x56};
// 14 и 15 байт  это для контрольной суммы

void setup() {
  Serial.begin(115200);
  Serial.println("Hello, ESP32-C3!");
}

void loop() {
  Serial.println("OLD");
  Serial.println(mas[14], HEX);
  Serial.println(mas[15], HEX);
  Serial.println("NEW");
  mas[14] = CSd(mas);
  Serial.println(mas[14], HEX);
  mas[15] = CSp(mas);
  Serial.println(mas[15], HEX);
  Serial.println();
  for(int i = 0; i< sizeof(mas); i++){
    Serial.print(mas[i],HEX);
  }
  Serial.println();
  delay(3000);
}

uint8_t CSd(uint8_t* masCSd){
  uint8_t unitCSd = 0;
  uint8_t lenstart = 16;
  uint8_t lenfinish = lenstart + masCSd[12];
  for(uint8_t i = lenstart; i < lenfinish; i++){
    unitCSd ^= masCSd[i];
  }
  return unitCSd;
}

uint8_t CSp(uint8_t* masCSp){
  uint8_t unitCSp = 0;
  for(uint8_t i = 0; i < 15; i++){
    unitCSp ^= masCSp[i];
  }
  return unitCSp;
}

/*
Контрольные суммы, использующиеся в заголовке, вычисляются по всей длине данных, указанных
в предыдущем поле, по алгоритму «исключающего или» (XOR) с помощью следующей функции:
unsigned char xor_sum
(
unsigned char *buffer,  (вх) указатель на буфер с данными 
unsigned int length  (вх) количество байт для подсчета 
)
{
unsigned char temp_sum = 0;
while ( length-- > 0 )
{
temp_sum ^= *buffer++;
}
return ( temp_sum );
}
*/
