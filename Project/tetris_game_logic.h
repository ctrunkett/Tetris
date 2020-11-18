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
#include "project_hardware_init.h"

#define SCREEN_X            240
#define SCREEN_Y            320

#define SCREEN_UPPER_Y			35
#define SCREEN_LOWER_Y			285
#define SCREEN_CENTER_X    ((SCREEN_X/2)-1)
#define SCREEN_CENTER_Y    ((SCREEN_Y/2)-1)

#define THOUSANDS					SCREEN_CENTER_X - 33
#define HUNDREDS					SCREEN_CENTER_X - 11
#define TENS							SCREEN_CENTER_X + 11
#define ONES							SCREEN_CENTER_X + 33

#define FIRST_PLACE_Y			SCREEN_CENTER_Y - 39
#define SECOND_PLACE_Y		SCREEN_CENTER_Y + 38
#define THIRD_PLACE_Y			SCREEN_CENTER_Y + 110

#define X_LEFT_SIDE				22
#define X_RIGHT_SIDE			218
#define Y_SIDE_UPPER			80
#define Y_SIDE_LOWER			240

#define SQUARE_SIZE         15
#define TETRIS_UPPER_BOUND	SCREEN_Y - (20*SQUARE_SIZE) //TOP IS 0
#define TETRIS_LEFT_BOUND		45
#define TETRIS_RIGHT_BOUND	(SCREEN_X - 45);

#define BOARD_HEIGHT	20
#define BOARD_WIDTH		10
#define DISTINCT_NUM_BLOCKS 7
typedef enum{
  SQUARE = 1,
  LONGBOI = 2, LONGBOI180 = 3,
  SBLOCK = 4, SBLOCK180 = 5,
  ZBLOCK = 6, ZBLOCK180 = 7,
}Shape;

//typedef enum{
//SQUARE = 0,
//LONGBOI = 1, LONGBOI180 = 4,
//SBLOCK = 2, SBLOCK180 = 5,
//ZBLOCK = 3, ZBLOCK180 = 6,
//}Shape;

typedef enum{
	MOVE_LEFT = -1, MOVE_RIGHT = 1, MOVE_DOWN = 2, MOVE_NULL = 0,
}Direction;

/*************************************************************************************
** FUNCTION DEFINITIONS
**************************************************************************************/
//void drawBlock(int8_t *currBlockY, int8_t *currBlockX, bool RESETorDRAW, BlockType *blockType);
void wait_ms(int32_t milliseconds);
void mainMenuAnimation(void);
void initGame(uint8_t *currBlockY, uint8_t *currBlockX);
//void spawnBlock(int8_t *currBlockY, int8_t *currBlockX, BlockType *blockType);
//void rotateBlock(int8_t *currBlockY, int8_t *currBlockX, BlockType *blockType);
//void moveBlock(int8_t *currBlockY, int8_t *currBlockX, int8_t DIRECTION, BlockType *blockType);
//bool checkSurroundings(int8_t *currBlockY, int8_t *currBlockX, int8_t DIRECTION, BlockType *blockType);
//void fallBlock(int8_t *currBlockY, int8_t *currBlockX, int8_t DIRECTION, BlockType *blockType);
void detect_line(void);
bool detect_loss(void);
void gameOver(void);
void spawn_block(uint8_t *currBlockY, uint8_t *currBlockX);
void fall_block(uint8_t *currBlockY, uint8_t *currBlockX, Shape *BlockType);
void draw_block(uint8_t *currBlockY, uint8_t *currBlockX, Shape *BlockType, bool RESET);
void tetris_init(void);
void update_board(void);
void project_main(void);

#endif

