/*
  szmf heart

  loovee
  2014-3-20
  
  update - 2014-7-5 - add dispString function
  update - 2014-7-7 - add wdt

  for more information, please refer to
  https://github.com/Litchee/Square8
  
  About the pin connect, refer to http://arduino.cc/en/Tutorial/RowColumnScanning
  
  button connect to A0
  
*/

#include <LED_Matrix.h>
#include <LED_Matrix_dfs.h>
#include <MsTimer2.h>
#include <avr/wdt.h>


#define wdt_init(X)     wdt_enable(X)
#define feed()          wdt_reset()


const int pinBtn = A0;

int speed = 0;

// 0 for normal
// 1 for 45 angle
int heartType = 0;

int delay_time1 = 200;
int delay_time2 = 1000;

// matrix of big heart
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

// matrix of small heart
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

unsigned char big_heart_45[8] = 
{
0b00000000,
0b00011110,
0b00011110,
0b01111110,
0b01111110,
0b01111110,
0b01111110,
0b00000000,
};

unsigned char small_heart_45[8] = 
{
0b00000000,
0b00000000,
0b00011000,
0b00111000,
0b00111000,
0b00000000,
0b00000000,
0b00000000,

};

void speedCnt()
{
    speed++;
    if(speed>4)speed=0;
    
    delay_time2 = (5-speed)*200;
}

void typeCnt()
{
    heartType = 1-heartType;
    
    if(heartType == 1)                  // 45 angle
    {
        matrix.dispMatrix(big_heart_45);
    }
    else
    {
        matrix.dispMatrix(big_heart);
    }
}


// matrix of empty

unsigned char full[8] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
unsigned char empty[8] = {0, 0, 0, 0, 0, 0, 0, 0};

int state = 1;

/*
 * delay ms until the button is pressed
 */
void checkBtnAndDelay(int ms)
{
    feed();
    for(int i=0; i<ms; i++)
    {
        delay(1);

        if(!digitalRead(pinBtn))
        {
            delay(10);
            
            long timer_t = millis();
            if(!digitalRead(pinBtn))
            {
                
                if(0 == heartType)
                {
                    matrix.dispMatrix(big_heart);
                }
                else
                {
                    matrix.dispMatrix(big_heart_45);
                }
                
                
                int flg_setype = 0;
                while(!digitalRead(pinBtn))
                {
                    if((millis()-timer_t)>1000)         // more than 1s
                    {
                        typeCnt();
                        timer_t = millis();
                        
                        flg_setype = 1;

                    }
                }
            
                if(flg_setype)return;
                speedCnt();

            }

            return;
        }
    }
}
long tiemr_tmp = 1;


void setup()
{
    matrix.begin(DIR_NORMAL);
    Serial.begin(115200);
    pinMode(pinBtn, INPUT);
    digitalWrite(pinBtn, HIGH);
    Serial.println("8 square firmware v2.0");
    Serial.println("by loovee, Jul 5, 2014");
    Serial.println("github.com/loovee/square8");
    
    matrix.dispString(STR_ONCE, 800, "8Square");
    delay(1000);
    
    wdt_init(WDTO_2S);                      // initialize watch dot, 2s
    feed();

}


void loop()
{

    if(0 == heartType)
    {
        matrix.dispMatrix(big_heart);
    }
    else
    {
        matrix.dispMatrix(big_heart_45);
    }
    
    checkBtnAndDelay(150);
    
    if(0 == heartType)   
    {
        matrix.dispMatrix(small_heart);
    }
    else
    {
        matrix.dispMatrix(small_heart_45);
    }
    
    checkBtnAndDelay(50);
    matrix.dispMatrix(empty);
    checkBtnAndDelay(delay_time2);
            
    if(0 == heartType)   
    {
        matrix.dispMatrix(small_heart);
    }
    else
    {
        matrix.dispMatrix(small_heart_45);
    }
    checkBtnAndDelay(80);
}
