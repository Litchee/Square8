/*
  demo_matrix.ino
  
  display a matrix

  loovee
  2014-7-5
  
  for more information, please refer to
  https://github.com/Litchee/Square8
  
  About the pin connect, refer to http://arduino.cc/en/Tutorial/RowColumnScanning
  
*/

#include <LED_Matrix.h>
#include <LED_Matrix_dfs.h>
#include <MsTimer2.h>

/*
 * matrix of a heart
 */
unsigned char big_heart[8] = {

0b00000000,
0b01100110,
0b11111111,
0b11111111,
0b11111111,
0b01111110,
0b00111100,
0b00011000,
};


void setup()
{
    matrix.begin(DIR_NORMAL);
    matrix.dispMatrix(big_heart);

}


void loop()
{

}
