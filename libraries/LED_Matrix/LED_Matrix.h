/*
  LED_Matrix.h
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

#ifndef __LED_MATRIX_H__
#define __LED_MATRIX_H__

#include <string.h>
#include "LED_Matrix_dfs.h"


#define _USE_TIMER_         1           // IF USE TIMER2


class LED_Matrix{

private:

    uchar disp_dta[8];
    int ctrl_bit;
    uchar dirDisp;

private:

    void setDispMatrix(unsigned char *matrix);                       // set disp_dta

    void matrixRev();
    
    void setDispDta(uchar *dta);
    void getMatrix(uchar *matrix, char asc);
    
    void io_init();
    
    void set_n(uchar n, uchar st);
    void set_n(uchar dta);
    void set_p(uchar p, uchar st);
    void set_p(uchar dta);
    
public:
    void timer_();
    
// user interface here
public:

    void begin(uchar dir);
    void setDir(uchar dir){dirDisp = dir;}                          // set display direction
    
    void clear(){memset(disp_dta, 0, 7);}                               // clear display
    void dispMatrix(unsigned char *mat){setDispMatrix(mat);}                    // display a matrix
    
    void disPoint(uchar x, uchar y, uchar state);                       // set a point
    
    void dispChar(char c);                                              // display a char
    void dispString(uchar cycle, int ts, char *str);     // display a string
    
};

extern LED_Matrix matrix;

#endif

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/