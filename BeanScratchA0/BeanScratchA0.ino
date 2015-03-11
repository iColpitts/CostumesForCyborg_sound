int piezoOnePin = A0; 
int piezoOneVal = 0;

int piezoTwoPin = A1;
int piezoTwoVal = 0;

int piezoThreePin = A2;
int piezoThreeVal = 0;

void setup()
{
  
}

void loop()
{
  piezoOneVal = analogRead(piezoOnePin);
  piezoTwoVal = analogRead(piezoTwoPin);
  piezoThreeVal = analogRead(piexoThreePin);

  Bean.setScratchNumber(1, piezoOneVal);
  Bean.setScratchNumber(2, piezoTwoVal);
  Bean.setScratchNumber(3, piezoThreeVal);
  
  Bean.sleep(10);
}
