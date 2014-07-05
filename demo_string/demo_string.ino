/*
  demo_string.ino
  display a string

  loovee
  2014-7-5

  for more information, please refer to
  https://github.com/Litchee/Square8
  
  About the pin connect, refer to http://arduino.cc/en/Tutorial/RowColumnScanning
  
*/

#include <LED_Matrix.h>
#include <LED_Matrix_dfs.h>
#include <MsTimer2.h>

void setup()
{
    matrix.begin(DIR_NORMAL);
}

void loop()
{
    matrix.dispString(STR_ONCE, 800, "8Square-Once");
    matrix.clear();
    delay(1000);
    
    matrix.dispString(STR_LOOP, 800, "8Square-Loop");
}
