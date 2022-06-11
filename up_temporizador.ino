#define increment 4
#define decrement 5
#define reset 6

int cont = 0;
unsigned long time = 0;
unsigned long currentTime = 0;
unsigned long previousTime = 0;

bool valueBI = 0; 
bool valueBD = 0; 
bool valueR = 0; 
bool previousStateBI = 0; 
bool previousStateBD = 0; 
bool previousStateR = 0; 
  
void setup()
{
  DDRB = 255; //11111111
  DDRD = 128; //10000000
}

void loop()
{
  operation();
  blinking();
}

void operation(){
  dRead();
  PORTB = cont;
  if(valueBI == 1 && previousStateBI == 0){
    PORTD = 128;
    cont++;
  }
  previousStateBI = valueBI;
  if(valueBD == 1 && previousStateBD == 0){
    PORTD = 128;
    cont--;
  }
  previousStateBD = valueBD;
  if(valueR == 1 && previousStateR == 0){
    PORTD = 128;
    cont = 0;
  }
  previousStateR = valueR;
  if(cont == 10){
    cont = 0;
  }
}
  

void blinking(){
  ms();
  if(cont >= 7 && time <= 500){
    PORTD = 128;
  }
  else if(time > 500 && time <= 1000){
    PORTD = 0;
  }
  else{
    previousTime = currentTime;   
  }
}

void ms(){
  currentTime = millis();
  time = currentTime - previousTime;
}

void dRead(){
  valueBI = digitalRead(increment);
  valueBD = digitalRead(decrement);
  valueR = digitalRead(reset);
}