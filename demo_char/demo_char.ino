/*
  8 square - display char
  
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


char str[] = "8Square";

void loop()
{
    for(int i=0; i<(sizeof(str)-1); i++)
    {
        matrix.dispChar(str[i]);
        delay(500);
    }
    matrix.clear();
    delay(1500);
}
