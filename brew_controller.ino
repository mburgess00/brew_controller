
#define sclk 13
#define mosi 11
#define cs   10
#define dc   8
#define rst  0  // you can also connect this to the Arduino reset

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <SPI.h>

#if defined(__SAM3X8E__)
    #undef __FlashStringHelper::F(string_literal)
    #define F(string_literal) string_literal
#endif

// Color definitions
#define BLACK    0x0000
#define BLUE     0x001F
#define RED      0xF800
#define GREEN    0x07E0
#define CYAN     0x07FF
#define MAGENTA  0xF81F
#define YELLOW   0xFFE0 
#define WHITE    0xFFFF

Adafruit_ST7735 tft = Adafruit_ST7735(cs, dc, mosi, sclk, rst);

float p = 3.1415926;

int currentCol = 0;
int currentRow = 0;
int prevCol = 0;
int prevRow = 0;

int setHLT = 160;
int setRIMS = 160;
int setBK = 100;

int currHLT = 161;
int currRIMS = 162;

boolean paused = true;
int mode = 0;
int prevmode = 0;
 
#define Neutral 0
#define Press 1
#define Up 2
#define Down 3
#define Right 4
#define Left 5
 
// Check the joystick position
int CheckJoystick()
{
  int joystickState = analogRead(3);
  
  if (joystickState < 50) return Left;
  if (joystickState < 150) return Down;
  if (joystickState < 250) return Press;
  if (joystickState < 500) return Right;
  if (joystickState < 650) return Up;
  return Neutral;
}

//Draw dot when element is on
void elementOn(int element)
{
  switch (element)
  {
    case 0:
      tft.fillCircle(25, 8, 5, RED);
      break;
    case 1:
      tft.fillCircle(75, 8, 5, RED);
      break;
    case 2:
      tft.fillCircle(125, 8, 5, RED);
      break;
  }
}

//Erase dot when element turns off
void elementOff(int element)
{
  switch (element)
  {
    case 0:
      tft.fillCircle(25, 8, 5, BLACK);
      break;
    case 1:
      tft.fillCircle(75, 8, 5, BLACK);
      break;
    case 2:
      tft.fillCircle(125, 8, 5, BLACK);
      break;
  }
}


//Draw an empty arrow in defined position
void clearArrow(int col, int row)
{
  switch (row)
  {
    case 0:
      switch (col)
      {
        case 0:
          tft.fillTriangle(25, 18, 20, 23, 30, 23, BLACK);
          tft.drawTriangle(25, 18, 20, 23, 30, 23, WHITE);
          break;
        case 1:
          tft.fillTriangle(75, 18, 70, 23, 80, 23, BLACK);
          tft.drawTriangle(75, 18, 70, 23, 80, 23, WHITE);
          break;
        case 2:
          tft.fillTriangle(125, 18, 120, 23, 130, 23, BLACK);
          tft.drawTriangle(125, 18, 120, 23, 130, 23, WHITE);
          break;
      }
      break; 
    case 1:
      switch (col)
      {
        case 0:
          tft.fillTriangle(25, 50, 20, 45, 30, 45, BLACK);
          tft.drawTriangle(25, 50, 20, 45, 30, 45, WHITE);
          break;
        case 1:
          tft.fillTriangle(75, 50, 70, 45, 80, 45, BLACK);
          tft.drawTriangle(75, 50, 70, 45, 80, 45, WHITE);
          break;
        case 2:
          tft.fillTriangle(125, 50, 120, 45, 130, 45, BLACK);
          tft.drawTriangle(125, 50, 120, 45, 130, 45, WHITE);
          break;
      }
      break;
    case 2:
      tft.drawRect(8, 78, 74, 18, BLACK);
      break;      
    case 3:
      switch (col)
      {
        case 0:
          tft.drawRect(8, 103, 38, 18, BLACK);
          break;
        case 1:
          tft.drawRect(58, 103, 50, 18, BLACK);
          break;
        case 2:
          tft.drawRect(118, 103, 27, 18, BLACK);
          break;
      }
  }
}

//Draw a filled arrow in defined position
void setArrow(int col, int row)
{
  switch (row)
  {
    case 0:
      switch (col)
      {
        case 0:
          tft.fillTriangle(25, 18, 20, 23, 30, 23, WHITE);
          break;
        case 1:
          tft.fillTriangle(75, 18, 70, 23, 80, 23, WHITE);
          break;
        case 2:
          tft.fillTriangle(125, 18, 120, 23, 130, 23, WHITE);
          break;
      }
      break; 
    case 1:
      switch (col)
      {
        case 0:
          tft.fillTriangle(25, 50, 20, 45, 30, 45, WHITE);
          break;
        case 1:
          tft.fillTriangle(75, 50, 70, 45, 80, 45, WHITE);
          break;
        case 2:
          tft.fillTriangle(125, 50, 120, 45, 130, 45, WHITE);
          break;
      }
      break;
    case 2:
      tft.drawRect(8, 78, 74, 18, WHITE);
      break;
    case 3:
      switch (col)
      {
        case 0:
          tft.drawRect(8, 103, 38, 18, WHITE);
          break;
        case 1:
          tft.drawRect(58, 103, 50, 18, WHITE);
          break;
        case 2:
          tft.drawRect(118, 103, 27, 18, WHITE);
          break;
      }
  }
}

//Print a temperature value indefined position
void setValue(int col, int row, int value)
{
  switch (row)
  {
    case 0:
      switch (col)
      {
        case 0:
          tft.setCursor(10, 28);
          tft.setTextColor(CYAN, BLACK);
          tft.print(value);
          break;
        case 1:
          tft.setCursor(60, 28);
          tft.setTextColor(CYAN, BLACK);
          tft.print(value);
          break;
        case 2:
          tft.setCursor(110, 28);
          tft.setTextColor(CYAN, BLACK);
          tft.print(value);
          if (value < 100)
          {
            tft.print("% ");
          }
          else
          {
            tft.print("%");
          }
          break;
      }
      break; 
    case 1:
      switch (col)
      {
        case 0:
          tft.setCursor(10, 55);
          tft.setTextColor(YELLOW, BLACK);
          tft.print(value);
          break;
        case 1:
          tft.setCursor(60, 55);
          tft.setTextColor(YELLOW,BLACK);
          tft.print(value);
          break;
      }
      break;
  }
}

//Display paused state
void setPaused(boolean value)
{
  if (value == true)
  {
    tft.setTextColor(RED, BLACK);
    tft.setCursor(10, 80);
    tft.print("PAUSED");
  }
  else
  {
    tft.setCursor(10, 80);
    tft.setTextColor(WHITE, BLACK);
    tft.print("PAUSE ");
  }
}

//Subroutine to enable mode choices at the bottom
void setMode(int modeToSet)
{
  tft.setCursor(10, 105);
  if (modeToSet == 0)
  {
    tft.setTextColor(GREEN, BLACK);
    //turn off RIMS and BK
    elementOff(1);
    elementOff(2);
  }
  else
  {
    tft.setTextColor(WHITE, BLACK);
  }
  tft.print("HLT");
 
  tft.setCursor(60, 105);
  if (modeToSet == 1)
  {
    tft.setTextColor(GREEN, BLACK);
    //turn off BK
    elementOff(2);
  }
  else
  {
    tft.setTextColor(WHITE, BLACK);
  }
  tft.print("RIMS");
  
  tft.setCursor(120, 105);
  if (modeToSet == 2)
  {
    tft.setTextColor(GREEN, BLACK);
    //turn off HLT and RIMS
    elementOff(0);
    elementOff(1);
  }
  else
  {
    tft.setTextColor(WHITE, BLACK);
  }
  tft.print("BK");
  
  tft.setTextColor(WHITE, BLACK);
}




void setup(void) {
  Serial.begin(9600);
  Serial.print("hello!");

  tft.initR(INITR_BLACKTAB);   // initialize a ST7735S chip, black tab

  Serial.println("init");
  
  tft.setRotation(3);
  tft.setTextColor(BLUE, BLACK);
  tft.setTextSize(2);

  uint16_t time = millis();
  tft.fillScreen(ST7735_BLACK);
  
  clearArrow(0,0);
  clearArrow(1,0);
  clearArrow(2,0);
  

  clearArrow(0,1);
  clearArrow(1,1);
  clearArrow(2,1);
    
  setValue(0, 0, setHLT);
  setValue(1, 0, setRIMS);
  setValue(2, 0, setBK);
  
  setValue(0, 1, currHLT);
  setValue(1, 1, currRIMS);
    
  setPaused(paused);

  setMode(mode);
  
  setArrow(0, 0);

}


//Subroutine to handle Joystick
void handleJoyStick(int stickData)
{
  switch (stickData)
  {
    case Left:
      if (prevCol != 0)
      {
        currentCol = prevCol - 1;
      }
      break;
    case Right:
      if (prevCol != 2)
      {
        currentCol = prevCol + 1;
      }
      break;
    case Up:
      if (prevRow != 0)
      {
        currentRow = prevRow - 1;
      }
      break;
    case Down:
      if (prevRow != 3)
      {
        currentRow = prevRow + 1;
      }
      break;
    case Press:
      switch (currentRow)
      {
        case 0:
          switch (currentCol)
          {
            case 0:
              if (setHLT < 200)
              {
                setHLT += 1;
                setValue(0, 0, setHLT);
              }
              break;
            case 1:
              if (setRIMS < 200)
              {
                setRIMS += 1;
                setValue(1, 0, setRIMS);
              }
              break;
            case 2:
              if (setBK < 100)
              {
                setBK += 1;
                setValue(2, 0, setBK);
              }
              break;
          }
          break;
        case 1:
          switch (currentCol)
          {
            case 0:
              if (setHLT > 100)
              {
                setHLT -= 1;
                setValue(0, 0, setHLT);
              }
              break;
            case 1:
              if (setRIMS > 100)
              {
                setRIMS -= 1;
                setValue(1, 0, setRIMS);
              }
              break;
            case 2:
              if (setBK > 0)
              {
                setBK -= 1;
                setValue(2, 0, setBK);
              }
              break;
          }
          break;
        case 2:
          paused = !paused;
          setPaused(paused);
          break;
        case 3:
          switch (currentCol)
          {
            case 0:
              mode = 0;
              setMode(mode);
              break;
            case 1:
              mode = 1;
              setMode(mode);
              break;
            case 2:
              mode = 2;
              setMode(mode);
              break;
          }
          break;
      }
      
      break;
  }
}

void loop() {
  int joy = CheckJoystick();
  handleJoyStick(joy);
  if (prevRow != currentRow || prevCol != currentCol)
  {
    clearArrow(prevCol, prevRow);
    setArrow(currentCol, currentRow);
    prevRow = currentRow;
    prevCol = currentCol;
  }
  
  //read in temps here and set value on screen if changed
  
  //actual element control goes here
  switch (mode)
  {
    case 0:
      //firing the HLT only
      if ((!paused) && (currHLT < setHLT))
      {
        elementOn(0);
      }
      else
      {
        elementOff(0);
      }
      break;
    case 1:
      //firing HLT and RIMS
      if ((!paused) && (currRIMS < setRIMS))
      {
        //ensure HLT off
        elementOff(0);
        //now turn on RIMS
        elementOn(1);
      }
      else
      {
        //turn off RIMS
        elementOff(1);
        //fire HLT?
        if ((!paused) && (currHLT < setHLT))
        {
          elementOn(0);
        }
        else
        {
          elementOff(0);
        }
      }
      break;
    case 2:
      //firing BK only
      break;
  }
  
  //turn off elements regardless of mode

  delay(100);
}



