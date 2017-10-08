int buttonSel = 6;
int buttonDown = 7;
int buttonUp = 8;
int ledPinRed = 9;
int ledPinGreen = 10;
int ledPinBlue = 11;
int ledPinWhite = 13;
int RedArraySeq[41] = {255,255,255,255,255,255,255,255,255,223,191,159,127,95,63,31,0,0,0,0,0,0,0,0,0,31,63,95,127,159,191,223,255,255,255,255,255,255,255,255,255};
int GreenArraySeq[41] = {0,31,63,95,127,159,191,223,255,255,255,255,255,255,255,255,255,223,191,159,127,95,63,31,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int BlueArraySeq[41] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,31,63,95,127,159,191,223,255,255,255,255,255,255,255,255,255,223,191,159,127,95,63,31,0};
int RedArray[7] = {1,1,1,0,0,0,1};
int GreenArray[7] = {0,0,1,1,1,0,0};
int BlueArray[7] = {1,0,0,0,1,1,1};
int RedArraySeqW[41] = {0,0,0,0,0,0,0,0,0,31,63,95,127,159,191,223,255};
int GreenArraySeqW[41] = {127,111,95,79,63,47,31,15,0,15,31,47,63,79,95,111,127};
int BlueArraySeqW[41] = {255,223,191,159,127,95,63,31,0,0,0,0,0,0,0,0,0};
int WhiteArraySeqW[41] = {127,143,159,175,191,207,223,239,255,239,223,207,191,175,159,143,127};
int value_fade = 25;
int ColorValue = 0;
int WhiteValue = 8;
int ValueRed = 0;
int ValueGreen = 0;
int ValueBlue = 0;
int ValueRedVol = 255;
int ValueBlueVol = 127;
int ValueGreenVol = 0;
int Vol = 255;
int Vol1 = 255;
int Vol2 = 255;
int ValueRedF = 0;
int ValueBlueF = 0;
int ValueGreenF = 0;
int ValueRedP= 0;
int ValueBlueP = 0;
int ValueGreenP = 0;
int ValueRedW = 0;
int ValueGreenW = 0;
int ValueBlueW = 0;
int ValueWhiteW = 0;
boolean premuto = false;
int funzione1 = 0;
boolean funzione2 = false;
int vecchio_val = 0;
int val = 0;
int i = 1;
int j = 0;
unsigned long int time;
unsigned long int tempo;
unsigned long int lettura_time;
unsigned long int lettura_tempo;
unsigned long int lettura_time_sel;
unsigned long int lettura_time_color;
boolean upRed = true;
boolean upGreen = true;
boolean upBlue = true;

void setup() {
  Serial.begin(9600);
  pinMode(buttonDown,INPUT);
  pinMode(buttonUp,INPUT);
  pinMode(buttonSel,INPUT);
  time = millis();
  tempo = millis();
  lettura_time=millis();
  lettura_tempo=millis();
  lettura_time_color=millis();
  lettura_time_sel=millis();
} 

void loop() {
  time = millis();
  if ((funzione1==1) && (funzione2==false)) {
    if(time>lettura_time+150) {
      if (digitalRead(buttonUp)==HIGH) {
        ColorValue=ColorValue+1;
        if (ColorValue>40) {
          ColorValue=40;
        }
      }
      if (digitalRead(buttonDown)==HIGH) {
        ColorValue=ColorValue-1;
        if (ColorValue<0) {
          ColorValue=0;
        }
      }
      ValueRedVol=RedArraySeq[ColorValue];
      ValueGreenVol=GreenArraySeq[ColorValue];
      ValueBlueVol=BlueArraySeq[ColorValue];
      lettura_time=millis();
    }
    analogWrite(ledPinRed,ValueRedVol);
    analogWrite(ledPinGreen,ValueGreenVol);
    analogWrite(ledPinBlue,ValueBlueVol);
    analogWrite(ledPinWhite,0);
  }
  
  if ((funzione1==1) && (funzione2==true)) {
    if(time>lettura_time+25) {
      if (digitalRead(buttonUp)==HIGH) {
        Vol=Vol+1;
        if (Vol>255) {
          Vol=255;
        }
      }
      if (digitalRead(buttonDown)==HIGH) {
        Vol=Vol-1;
        if (Vol<0) {
          Vol=0;
        }
      }
      ValueRedVol=RedArraySeq[ColorValue]*Vol/256;
      ValueGreenVol=GreenArraySeq[ColorValue]*Vol/256;
      ValueBlueVol=BlueArraySeq[ColorValue]*Vol/256;
      lettura_time=millis();
    }
    analogWrite(ledPinRed,ValueRedVol);
    analogWrite(ledPinGreen,ValueGreenVol);
    analogWrite(ledPinBlue,ValueBlueVol);
    analogWrite(ledPinWhite,0);
  }
  
  if ((funzione1==0) && (funzione2==false)) {
    if (time>lettura_time_color+value_fade) {
      if (j == 255) {
        i = i + 1;
        if (i == 7) {
          i = 1;
        }
      }
      ValueRedP = RedArray[i-1];
      ValueRedF = RedArray[i];
      ValueGreenP = GreenArray[i-1];
      ValueGreenF = GreenArray[i];
      ValueBlueP = BlueArray[i-1];
      ValueBlueF = BlueArray[i];
      j = j + 1;
      if (j == 256) {
        j = 0;
      }
      if(time>lettura_time+150) {
          if (digitalRead(buttonUp)==HIGH) {
            value_fade=value_fade+1;
            if (value_fade>50) {
              value_fade=50;
            }
          }
          if (digitalRead(buttonDown)==HIGH) {
            value_fade=value_fade-1;
            if (value_fade<1) {
              value_fade=1;
            }
          }
          lettura_time=millis();
        }
        if (ValueRedP==1 && ValueRedF==0) {
          ValueRed = 255-int(ValueRedP*j);
        }
        else if (ValueRedP==1 && ValueRedF==1) {
          ValueRed = 255;
        }
        else {
          ValueRed = int(ValueRedF*j);
        }
        if (ValueGreenP==1 && ValueGreenF==0) {
          ValueGreen = 255-int(ValueGreenP*j);
        }
        else if (ValueGreenP==1 && ValueGreenF==1) {
          ValueGreen = 255;
        }
        else {
          ValueGreen = int(ValueGreenF*j);
        }
        if (ValueBlueP==1 && ValueBlueF==0) {
          ValueBlue = 255-int(ValueBlueP*j);
        }
        else if (ValueBlueP==1 && ValueBlueF==1) {
          ValueBlue = 255;
        }
        else {
          ValueBlue = int(ValueBlueF*j);
        }
        analogWrite(ledPinRed,ValueRed);
        analogWrite(ledPinGreen,ValueGreen);
        analogWrite(ledPinBlue,ValueBlue);
        analogWrite(ledPinWhite,0);
        lettura_time_color = millis();
      }
  }
  if ((funzione1==0) && (funzione2==true)) {
    if (time>lettura_time_color+value_fade) {
      if (j == 255) {
        i = i + 1;
        if (i == 7) {
          i = 1;
        }
      }
      ValueRedP = RedArray[i-1];
      ValueRedF = RedArray[i];
      ValueGreenP = GreenArray[i-1];
      ValueGreenF = GreenArray[i];
      ValueBlueP = BlueArray[i-1];
      ValueBlueF = BlueArray[i];
      j = j + 1;
      if (j == 256) {
        j = 0;
      }
        if (ValueRedP==1 && ValueRedF==0) {
          ValueRed = 255-int(ValueRedP*j);
        }
        else if (ValueRedP==1 && ValueRedF==1) {
          ValueRed = 255;
        }
        else {
          ValueRed = int(ValueRedF*j);
        }
        if (ValueGreenP==1 && ValueGreenF==0) {
          ValueGreen = 255-int(ValueGreenP*j);
        }
        else if (ValueGreenP==1 && ValueGreenF==1) {
          ValueGreen = 255;
        }
        else {
          ValueGreen = int(ValueGreenF*j);
        }
        if (ValueBlueP==1 && ValueBlueF==0) {
          ValueBlue = 255-int(ValueBlueP*j);
        }
        else if (ValueBlueP==1 && ValueBlueF==1) {
          ValueBlue = 255;
        }
        else {
          ValueBlue = int(ValueBlueF*j);
        }
        if(time>lettura_time+25) {
          if (digitalRead(buttonUp)==HIGH) {
            Vol1=Vol1+1;
            if (Vol1>255) {
              Vol1=255;
          }
        }
        if (digitalRead(buttonDown)==HIGH) {
          Vol1=Vol1-1;
          if (Vol1<0) {
            Vol1=0;
          }
        }
        lettura_time_color = millis();
      }
      ValueRedVol=ValueRed*Vol1/256;
      ValueGreenVol=ValueGreen*Vol1/256;
      ValueBlueVol=ValueBlue*Vol1/256;
      analogWrite(ledPinRed,ValueRedVol);
      analogWrite(ledPinGreen,ValueGreenVol);
      analogWrite(ledPinBlue,ValueBlueVol);
      analogWrite(ledPinWhite,0);
    }
  }
  
  if ((funzione1==2) && (funzione2==false)) {
    if(time>lettura_time+150) {
      if (digitalRead(buttonUp)==HIGH) {
        WhiteValue=WhiteValue+1;
        if (WhiteValue>16) {
          WhiteValue=16;
        }
      }
      if (digitalRead(buttonDown)==HIGH) {
        WhiteValue=WhiteValue-1;
        if (WhiteValue<0) {
          WhiteValue=0;
        }
      }
      ValueRedW=RedArraySeqW[WhiteValue];
      ValueGreenW=GreenArraySeqW[WhiteValue];
      ValueBlueW=BlueArraySeqW[WhiteValue];
      ValueWhiteW=WhiteArraySeqW[WhiteValue];
      lettura_time=millis();
    }
    analogWrite(ledPinRed,ValueRedW);
    analogWrite(ledPinGreen,ValueGreenW);
    analogWrite(ledPinBlue,ValueBlueW);
    analogWrite(ledPinWhite,ValueWhiteW);
 }
  
  if ((funzione1==2) && (funzione2==true)) {
    if(time>lettura_time+25) {
      if (digitalRead(buttonUp)==HIGH) {
        Vol2=Vol2+1;
        if (Vol2>255) {
          Vol2=255;
        }
      }
      if (digitalRead(buttonDown)==HIGH) {
        Vol2=Vol2-1;
        if (Vol2<0) {
          Vol2=0;
        }
      }
      ValueRedW=RedArraySeqW[WhiteValue]*Vol2/256;
      ValueGreenW=GreenArraySeqW[WhiteValue]*Vol2/256;
      ValueBlueW=BlueArraySeqW[WhiteValue]*Vol2/256;
      ValueWhiteW=WhiteArraySeqW[WhiteValue]*Vol2/256;
      lettura_time=millis();
    }
    analogWrite(ledPinRed,ValueRedW);
    analogWrite(ledPinGreen,ValueGreenW);
    analogWrite(ledPinBlue,ValueBlueW);
    analogWrite(ledPinWhite,ValueWhiteW);
  }

  
  val=digitalRead(buttonSel); //Legge la condizione del pulsante
  if (val==HIGH) {  //Se è premuto
    if (premuto==false) { //Se in precedenza non lo era
      lettura_tempo=millis(); //Assegna il tempo iniziale
      tempo=0; //Azzera il tempo
    }
    premuto=true; //Pone vera la variabile premuto
    tempo=millis()-lettura_tempo; //Calcola per quanto tempo è rimasto premuto il pulsante
  } else { //Se viene rilasciato
    premuto=false; //Pone falsa la variabile premuto
  }
  if ((premuto==false) && (tempo>1000)) { //Se il pulsante è stato rilasciato ed è stato premuto per più di 1 sec
    if (funzione2==true) { //Se la funzionee è vera la pone come falsa
      funzione2=false;
    } else {
      funzione2=true; // Altrimenti la pone come vera
    }
    tempo=0; //Azzera il tempo
  }
  if ((premuto==false) && (tempo>100) && (tempo<1000)) { //Se il pulsante è stato rilasciato ed è stato premuto per più di 100 millisecondi ma meno di un secondo
    funzione1=funzione1+1; //Incrementa il valore della funzione1
    if (funzione1==3) { //Se il valore arriva a tre lo ripone azero
      funzione1=0;
    }
    tempo=0; //Azzera il tempo
  }
    Serial.print(funzione1);
    Serial.print(funzione2);
    Serial.print(ColorValue);
    Serial.print(Vol2);
    Serial.println(WhiteValue);
  }
