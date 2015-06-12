int piezoOnePin = A0;
int piezoOneVal = 0;

int piezoTwoPin = A1;
int piezoTwoVal = 0;

//int piezoThreePin = A2;
//int piezoThreeVal = 0;

void setup()
{
  Bean.enableWakeOnConnect( true );
}

void loop()
{
  bool connected = Bean.getConnectionState();
  
  if ( connected )
  {
    piezoOneVal = analogRead(piezoOnePin);
    piezoTwoVal = analogRead(piezoTwoPin);
    //piezoThreeVal = analogRead(piexoThreePin);

    Bean.setScratchNumber(1, piezoOneVal);
    Bean.setScratchNumber(2, piezoTwoVal);
    //Bean.setScratchNumber(3, piezoThreeVal);
  
    Bean.sleep(10);
  }
  else
  {
   // Sleep unless woken
   Bean.sleep( 0xFFFFFFFF ); 
  }
  
  
}
