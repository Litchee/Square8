#include <Streaming.h>

#include <LED_Matrix.h>
#include <LED_Matrix_dfs.h>
#include <TimerOne.h>

unsigned char mat[8] = 
{
0x0,
0x0,
0x0,
0x0,
0x0,
0x0,
0x0,
0x0,
};

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

unsigned char small_heart[8] = {
0b00000000,
0b00000000,
0b00100100,
0b01111110,
0b01111110,
0b00111100,
0b00011000,
0b00000000,
};

unsigned char mat2[8] = 
{
0b00000000,
0b01101100,
0b11111110,
0b11111110,
0b01111100,
0b00111000,
0b00010000,
0b00000000,
};

void setup()
{
    Serial.begin(115200);
    
    matrix.begin();
    
    //matrix.dispStringSlide(2, 1000, 5, "hello");
    
    
    //matrix.dispMatrix(mat);
}

void loop()
{
    
    matrix.dispMatrix(big_heart);
    delay(200);
    
    matrix.dispMatrix(small_heart);
    delay(800);

}