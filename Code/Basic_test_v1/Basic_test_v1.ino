/*
  This code validates that everything is working fine.
*/

//within Setup we have code that runs once
void setup()
{
  //Nothing to do here in this case
}

//Code inside Loop will be executed until the power is off or reset button is pressed
void loop()
{
  tone(14, 1000); //set tone on pin 14 to 1,000 hertz
  delay(500);     //wait for 500ms (or 1/2 second)
  noTone(14);     //turn off the tone on pin 14
  delay(500);     //wait for another 500ms and then go back to the beginning of the loop
}
