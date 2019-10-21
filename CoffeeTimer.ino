#include <TM1637Display.h>

#define CLK 2
#define DIO 3
#define BUTTON 4

TM1637Display display(CLK, DIO);
long startTime = millis();
bool isReset = true; //tracks whether or not it's waiting for reset button to be pushed

bool blinkState = false; //false = off, true = on, used when an element is blinking
int blinktime = 1000; //number of ms between blinks

uint8_t data[] = {SEG_G, SEG_G, SEG_G, SEG_G};

void setup() {
  //Setup button, pulled down
  pinMode(BUTTON, INPUT);
  digitalWrite(BUTTON, HIGH); //set pullup
  
  // Zero out display with dashes until button is pushed
  display.setBrightness(0x0f);
 
  display.setSegments(data);  
}

void loop() {
  //Calculate times, and "blink status"
  long elapsedTime = millis() - startTime;
  long elapsedSeconds = floor(elapsedTime / 1000);
  long minutes = (elapsedSeconds / 60) % 60;
  long hours = floor(elapsedSeconds/ 3600);

  //blink status: divide passed time by blink time, see if it is even or odd
  //even: on
  //odd: off
  if (int(floor(elapsedTime / blinktime)) % 2 == 0)
  {
    blinkState = true;
  }
  else
  {
    blinkState = false;
  }
  
  //check to see if reset happened
  if (isReset)
  {
    //Check for button push, else blink every half second 
    if (digitalRead(BUTTON) == LOW) //button pushed
    {
      isReset = false;
      startTime = millis(); //reset timer
    }
  }


  else if ((elapsedSeconds/60) >= 6000) //overtime
  {
    //Check for reset
    if (digitalRead(BUTTON) == LOW) //button pushed
    {
      startTime = millis(); //reset timer
    }
    
    //write 99:99 and blink
    if (blinkState)
    {
      display.showNumberDecEx(9999, 0xff);
    }
    else
    {
      display.clear();
    }
  }
  
  else //normal operation
  {
    //check for reset
    if (digitalRead(BUTTON) == LOW) //button pushed
    {
      startTime = millis(); //reset timer
    }

    else
    {
    //Display the number, and have the colon on if blinkstate is true

    //Hours are in data 0 and 1
    data[0] = display.encodeDigit((hours/10) % 10);
    data[1] = display.encodeDigit(hours % 10);
       
    
    //Minutes are in data 2 and 3
    data[2] = display.encodeDigit((minutes/10)%10);
    data[3] = display.encodeDigit(minutes % 10);

    
    if (blinkState)
    {
      data[1] = data[1] + 0x80;
    }

    display.setSegments(data); //write
    }
  }

}
