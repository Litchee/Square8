/*
  LED_Matrix.cpp
  2013 Copyright (c) Seeed Technology Inc.  All right reserved.

  Author:Loovee
  2013-10-21
 
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include <Arduino.h>
#include <Streaming.h>
#include <MsTimer2.h>

#include "LED_Matrix.h"
#include "font.h"

/*

1   r5      5
2   r7      6
3   c2      7
4   c3      8
5   r8      9
6   c5      11
7   r6      12
8   r3      13
9   r1      A1
10  c4      A2
11  c6      A3
12  r4      A4
13  c1      A5
14  r2      2
15  c7      3
16  c8      4

*/

// 2-dimensional array of row pin numbers:
const int row[8] = {
A1, 2, 13, A4, 5, 12, 6, 9};

// 2-dimensional array of column pin numbers:
const int col[8] = {
A5, 7, 8, A2, 11, A3, 3, 4};


#define __BIT(n)    (0x01<<n)


#if _USE_TIMER_
void timerIsr()
{
    matrix.timer_();
}
#endif

// if no use timer, this function should be used in main() per 1ms
void LED_Matrix::timer_()
{
    for(int i=0; i<8; i++)
    {
        digitalWrite(row[i], LOW);
    }
    
    matrix.set_n(~matrix.disp_dta[7-matrix.ctrl_bit]);
    matrix.set_p(BIT(matrix.ctrl_bit++));
    matrix.ctrl_bit = matrix.ctrl_bit>7 ? 0 : matrix.ctrl_bit;
}

void LED_Matrix::begin()
{
    ctrl_bit = 0;
    cmd_get  = 0;
    dirDisp  = DIR_NORMAL;

    clear();
    
    io_init();
    
#if _USE_TIMER_
    MsTimer2::set(1, timerIsr); // 500ms period
    MsTimer2::start();
#endif  
}

void LED_Matrix::setDispDta(uchar *dta)
{

    if(NULL == dta)return;
    
    for(int i=0; i<8; i++)
    {
        disp_dta[i] = dta[i];
    }
}

void LED_Matrix::io_init()
{
    for(int i=0; i<8; i++)
    {
        pinMode(row[i], OUTPUT);
        pinMode(col[i], OUTPUT);
    }
}

void LED_Matrix::set_n(uchar dta)
{
    for(int i=0; i<8; i++)
    {
        if(dta & __BIT(i))
        {
            digitalWrite(col[i], HIGH);
        }
        else
        {
            digitalWrite(col[i], LOW);
        }
    }
    
}

void LED_Matrix::set_p(uchar dta)
{

    for(int i=0; i<8; i++)
    {
        if(dta & __BIT(i))
        {
            digitalWrite(row[i], HIGH);
        }
        else
        {
            digitalWrite(row[i], LOW);
        }
    }
}

void LED_Matrix::getMatrix(uchar *matrix, char asc)
{
    if(NULL == matrix)return;
    
    for(int i=0; i<7; i++)
    {
        int tmp = (asc-32)*7+i;
        matrix[i] = pgm_read_byte(&Font5x7[tmp]); 
        matrix[i] = matrix[i] << 1;
    }
    
    matrix[7] = 0x00;
}

void LED_Matrix::putIntMatrix(unsigned int *matrix)
{
    unsigned char mat[8];
    for(int i=0; i<8; i++)
    {
        mat[i] = matrix[i]>>8;
    }
    
    
    memset(disp_dta, 0x00, 8);
    //setDispDta(mat);  


    MsTimer2::stop();
    for(int i=0; i<8; i++)
    {
        for(int j=0; j<8; j++)
        {
            if(mat[j] & BIT(i))
            {
                disp_dta[7-i] += BIT(j);
            }
        }
    }
    
    //for(int i=0; i<8; i++)disp_dta[i] = mat[i];
    MsTimer2::start();
        

}

void LED_Matrix::dispChar(char c)
{
    if(DIR_NORMAL != dirDisp && DIR_DOWN != dirDisp)return ;
    getMatrix(disp_dta, c);
    setDispDta(disp_dta);
    if(DIR_DOWN != dirDisp)return ;
    matrixRev();
}

void LED_Matrix::dispStringSlide(uchar cycle, int ts, int len_, char *str)
{
    //if(DIR_NORMAL != dirDisp && DIR_DOWN != dirDisp)return ;
    
    cmd_get = 0;
    while(1)
    {

        int len = len_;
        
        if(len > 20)return ;
        
        unsigned char matrix[154];
        unsigned int matrix_i[7];
        
        memset(matrix, 0, 147);
        
        for(int i=0; i<len; i++)
        {
            getMatrix(&matrix[7*(i+1)], str[i]);
        }
        
        len++;
        
        for(int i=0; i<len; i++)
        {
            for(int j=0; j<7; j++)
            {
                matrix_i[j] = matrix[7*i+j];
                matrix_i[j] <<= 8;
                matrix_i[j] += matrix[7*(i+1)+j]<<2;
            }
            
            for(int k=0; k<6; k++)
            {

                putIntMatrix(matrix_i);
                
                if(cmd_get)
                {
                    cmd_get = 0;
                    return ;
                }
                delay(ts/5);
                
                for(int m=0; m<7; m++)
                {
                    matrix_i[m] <<= 1;
                }
            }
        } 
        
        if (STR_ONCE == cycle)
        {
            memset(disp_dta, 0x00, 8);
            return;
        }
    }
}


void LED_Matrix::matrixRev()
{

    for(int i=0; i<4; i++)
    {
        unsigned char tmp = disp_dta[i];
        disp_dta[i] = disp_dta[7-i];
        disp_dta[7-i] = tmp;
    }
}

void LED_Matrix::dispMatrix(uchar *mat)
{
    MsTimer2::stop();
    
    for(int i=0; i<8; i++)disp_dta[i] = 0x00;
    
    memset(disp_dta, 0x00, 8);
    
    if(DIR_DOWN == dirDisp)         // 3
    {
        for(int i=0; i<8; i++)
        {
            disp_dta[i] = mat[i];
        }
        
        matrixRev();
    }
    
    else if(DIR_NORMAL == dirDisp)          // 0
    {
        for(int i=0; i<8; i++)
        {
            disp_dta[i] = mat[i];
        }
    }
    else if(DIR_LEFT == dirDisp)            // 1
    {
        // Serial.println("LEFT");
        for(int i=0; i<8; i++)
        {
            for(int j=0; j<8; j++)
            {
                if(mat[j] & BIT(i))
                {
                    disp_dta[7-i] += BIT(7-j);
                }
            }
        }
        
        //matrixRev();
    }
    else if(DIR_RIGHT == dirDisp)           // 2
    {
        //Serial.println("RIGHT");
        for(int i=0; i<8; i++)
        {
            for(int j=0; j<8; j++)
            {
                if(mat[j] & BIT(i))
                {
                    disp_dta[7-i] += BIT(j);
                }
            }
        }
        
        
    } 
    MsTimer2::start();
}

void LED_Matrix::setPoint(uchar x, uchar y, uchar state)
{

    if(DIR_DOWN == dirDisp)
    {
        disp_dta[7-y] &= ~BIT(x);
        disp_dta[7-y] |= state ? BIT(x) : 0;
    }
    else if(DIR_NORMAL == dirDisp)
    {
        disp_dta[y] &= ~BIT(4-x);
        disp_dta[y] |= state ? BIT(4-x) : 0;
    }
    else if(DIR_RIGHT == dirDisp)
    {
        //disp_dta[x] &= ~BIT(7-y);
        //disp_dta[x] |= state ? BIT(7-y) : 0;
    }
    else if(DIR_LEFT == dirDisp)
    {
        //disp_dta[7-x] &= ~BIT(y);
        //disp_dta[7-x] |= state ? BIT(y) : 0;
    } 
}

LED_Matrix matrix;


/*********************************************************************************************************
  END FILE
*********************************************************************************************************/