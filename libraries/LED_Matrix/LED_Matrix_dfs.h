/*
  Xadow_LED_dfs.h
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

#ifndef __LED_MATRIX_DFS_H__
#define __LED_MATRIX_DFS_H__


#define uchar unsigned char

#define BIT(X)  (0x01<<X)



#define HIGH_P_ALL()    PORTB |= (BIT(0)|BIT(1)|BIT(2)|BIT(3)|BIT(4));\
                        PORTD |= (BIT(5)|BIT(6))
                    
#define LOW_P_ALL()     PORTB &= ~(BIT(0)|BIT(1)|BIT(2)|BIT(3)|BIT(4));\
                        PORTD &= ~(BIT(5)|BIT(6))

#define HIGH_N_ALL()    PORTC |= (BIT(0)|BIT(1)|BIT(2)|BIT(3));\
                        PORTD |= BIT(4)
                    
#define LOW_N_ALL()     PORTC &= ~(BIT(0)|BIT(1)|BIT(2)|BIT(3));\
                        PORTD &= ~BIT(4)
                        


// cmd
#define CMD_SETMODE     0x01
#define CMD_SLEEP       0x02
#define CMD_DISPMATRIX  0x03
#define CMD_DISPCHAR    0x04
#define CMD_DISPSTR     0x05
#define CMD_DISPOINT    0x06

// DIRECTION
#define DIR_NORMAL      0x00
#define DIR_LEFT        0x03
#define DIR_RIGHT       0x01
#define DIR_DOWN        0x02

// string cycle mode
#define STR_ONCE        0x01
#define STR_LOOP        0x02

#endif

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/