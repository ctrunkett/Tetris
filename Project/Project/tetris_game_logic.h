// Copyright (c) 2015-17, Joe Krachey
// All rights reserved.
//
// Redistribution and use in source or binary form, with or without modification, 
// are permitted provided that the following conditions are met:
//
// 1. Redistributions in source form must reproduce the above copyright 
//    notice, this list of conditions and the following disclaimer in 
//    the documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR 
// PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR 
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; 
// OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, 
// EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#ifndef __TETRIS_GAME_LOGIC_H__
#define __TETRIS_GAME_LOGIC_H__

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include "main.h"
#include "images.h"

#define SCREEN_X            240
#define SCREEN_Y            320

#define SQUARE_SIZE         15
#define TETRIS_UPPER_BOUND	SCREEN_Y - (20*SQUARE_SIZE) //TOP IS 0
#define TETRIS_LEFT_BOUND		45
#define TETRIS_RIGHT_BOUND	(SCREEN_X - 45);

#define BOARD_HEIGHT	20
#define BOARD_WIDTH		10

const int8_t DISTINCT_NUM_BLOCKS = 4;

/*************************************************************************************
** FUNCTION DEFINITIONS
**************************************************************************************/
//void drawBlock(int8_t *currBlockY, int8_t *currBlockX, bool RESETorDRAW, BlockType *blockType);
void wait_ms(int32_t milliseconds);
void mainMenuAnimation(void);
void initGame(void);
//void spawnBlock(int8_t *currBlockY, int8_t *currBlockX, BlockType *blockType);
//void rotateBlock(int8_t *currBlockY, int8_t *currBlockX, BlockType *blockType);
//void moveBlock(int8_t *currBlockY, int8_t *currBlockX, int8_t DIRECTION, BlockType *blockType);
//bool checkSurroundings(int8_t *currBlockY, int8_t *currBlockX, int8_t DIRECTION, BlockType *blockType);
//void fallBlock(int8_t *currBlockY, int8_t *currBlockX, int8_t DIRECTION, BlockType *blockType);
void detectLine(void);
bool detectLoss(void);
void gameOver(void);


#endif
