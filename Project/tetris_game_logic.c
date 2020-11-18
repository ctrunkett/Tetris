// Copyright (c) 2015-19, Joe Krachey
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

#include "main.h"


static	Shape blocktype; 
	
typedef struct block { 
	uint8_t xPos;
	uint8_t yPos;
  uint16_t Color;
} Block;


extern volatile int x_pos;
extern volatile int y_pos;
extern volatile uint8_t random;

// GAME BOARD IS 10 BY 20 BUT ALLOW SOME HEAD ROOM FOR BLOCKS TO SPAWN
// AND FALL NATURALLY INTO PLAY
Block board[25][10];
const uint8_t* num_bitmaps[10] = {zero_bitmaps, one_bitmaps, two_bitmaps, three_bitmaps,
																four_bitmaps,five_bitmaps,six_bitmaps,seven_bitmaps,eight_bitmaps, nine_bitmaps};
volatile uint16_t linesCleared = 0;
static uint16_t highscore_eeprom_address[3] = {0xAA00,0xAA10,0xAA20};

/*******************************************************************************
* Function Name: draw_block
********************************************************************************
* Summary: Sets blocks of the game board array to either black or a color 
* associated with a block type, based on the active high reset
* Returns:
*  Nothing
*******************************************************************************/
void draw_block(uint8_t *currBlockY, uint8_t *currBlockX, Shape *BlockType, bool RESET) {
	
	int8_t x_start, y_start;

	if (*BlockType == SQUARE) {
		if (RESET) {
		  board[*currBlockY][*currBlockX].Color = LCD_COLOR_BLACK;
      board[*currBlockY-1][*currBlockX].Color = LCD_COLOR_BLACK;
      board[*currBlockY][*currBlockX+1].Color = LCD_COLOR_BLACK;
      board[*currBlockY-1][*currBlockX+1].Color = LCD_COLOR_BLACK;
			
		}
		else { // (RESETorDRAW == DRAW)
      board[*currBlockY][*currBlockX].Color = LCD_COLOR_YELLOW;
      board[*currBlockY-1][*currBlockX].Color = LCD_COLOR_YELLOW;
      board[*currBlockY][*currBlockX+1].Color = LCD_COLOR_YELLOW;
      board[*currBlockY-1][*currBlockX+1].Color = LCD_COLOR_YELLOW;
    }
  }
	else if (*BlockType == LONGBOI) {// if (*BlockType == rand) { while (1);}
		if (RESET) {
		  board[*currBlockY][*currBlockX].Color = LCD_COLOR_BLACK;
			//lcd_draw_image(x,y, image, LCDBLACK);
      board[*currBlockY-1][*currBlockX].Color = LCD_COLOR_BLACK;
      board[*currBlockY-2][*currBlockX].Color = LCD_COLOR_BLACK;
      board[*currBlockY-3][*currBlockX].Color = LCD_COLOR_BLACK;
		}
		else { // (RESETorDRAW == DRAW)
      board[*currBlockY][*currBlockX].Color = LCD_COLOR_CYAN;
      board[*currBlockY-1][*currBlockX].Color = LCD_COLOR_CYAN;
      board[*currBlockY-2][*currBlockX].Color = LCD_COLOR_CYAN;
      board[*currBlockY-3][*currBlockX].Color = LCD_COLOR_CYAN;
    }
  }
		else if (*BlockType == LONGBOI180) {
		if (RESET) {
		  board[*currBlockY][*currBlockX].Color = LCD_COLOR_BLACK;
      board[*currBlockY][*currBlockX+1].Color = LCD_COLOR_BLACK;
      board[*currBlockY][*currBlockX+2].Color = LCD_COLOR_BLACK;
      board[*currBlockY][*currBlockX+3].Color = LCD_COLOR_BLACK;
		}
		else { // (RESETorDRAW == DRAW)
      board[*currBlockY][*currBlockX].Color = LCD_COLOR_CYAN;
      board[*currBlockY][*currBlockX+1].Color = LCD_COLOR_CYAN;
      board[*currBlockY][*currBlockX+2].Color = LCD_COLOR_CYAN;
      board[*currBlockY][*currBlockX+3].Color = LCD_COLOR_CYAN;
    }
  }
	else if (*BlockType == SBLOCK) {
		if (RESET) {
		  board[*currBlockY][*currBlockX].Color = LCD_COLOR_BLACK;
      board[*currBlockY][*currBlockX+1].Color = LCD_COLOR_BLACK;
      board[*currBlockY-1][*currBlockX+1].Color = LCD_COLOR_BLACK;
      board[*currBlockY-1][*currBlockX+2].Color = LCD_COLOR_BLACK;
		}
		else { // (RESETorDRAW == DRAW)
      board[*currBlockY][*currBlockX].Color = LCD_COLOR_ORANGE;
      board[*currBlockY][*currBlockX+1].Color = LCD_COLOR_ORANGE;
      board[*currBlockY-1][*currBlockX+1].Color = LCD_COLOR_ORANGE;
      board[*currBlockY-1][*currBlockX+2].Color = LCD_COLOR_ORANGE;
    }
  }
	else if (*BlockType == SBLOCK180) {
		if (RESET) {
		  board[*currBlockY][*currBlockX].Color = LCD_COLOR_BLACK;
      board[*currBlockY-1][*currBlockX].Color = LCD_COLOR_BLACK;
      board[*currBlockY-1][*currBlockX-1].Color = LCD_COLOR_BLACK;
      board[*currBlockY-2][*currBlockX-1].Color = LCD_COLOR_BLACK;
		}
		else { // (RESETorDRAW == DRAW)
      board[*currBlockY][*currBlockX].Color = LCD_COLOR_ORANGE;
      board[*currBlockY-1][*currBlockX].Color = LCD_COLOR_ORANGE;
      board[*currBlockY-1][*currBlockX-1].Color = LCD_COLOR_ORANGE;
      board[*currBlockY-2][*currBlockX-1].Color = LCD_COLOR_ORANGE;
    }
  }
	else if (*BlockType == ZBLOCK) {
		if (RESET) {
		  board[*currBlockY][*currBlockX].Color = LCD_COLOR_BLACK;
      board[*currBlockY][*currBlockX-1].Color = LCD_COLOR_BLACK;
      board[*currBlockY-1][*currBlockX-1].Color = LCD_COLOR_BLACK;
      board[*currBlockY-1][*currBlockX-2].Color = LCD_COLOR_BLACK;
		}
		else { // (RESETorDRAW == DRAW)
      board[*currBlockY][*currBlockX].Color = LCD_COLOR_RED;
      board[*currBlockY][*currBlockX-1].Color = LCD_COLOR_RED;
      board[*currBlockY-1][*currBlockX-1].Color = LCD_COLOR_RED;
      board[*currBlockY-1][*currBlockX-2].Color = LCD_COLOR_RED;
    }
  }
	else if (*BlockType == ZBLOCK180) {
		if (RESET) {
		  board[*currBlockY][*currBlockX].Color = LCD_COLOR_BLACK;
      board[*currBlockY-1][*currBlockX].Color = LCD_COLOR_BLACK;
      board[*currBlockY-1][*currBlockX+1].Color = LCD_COLOR_BLACK;
      board[*currBlockY-2][*currBlockX+1].Color = LCD_COLOR_BLACK;
		}
		else { // (RESETorDRAW == DRAW)
      board[*currBlockY][*currBlockX].Color = LCD_COLOR_RED;
      board[*currBlockY-1][*currBlockX].Color = LCD_COLOR_RED;
      board[*currBlockY-1][*currBlockX+1].Color = LCD_COLOR_RED;
      board[*currBlockY-2][*currBlockX+1].Color = LCD_COLOR_RED;
    }
  }
	
//	if (!RESET) {
//		//update_board();
//	}
}

/*******************************************************************************
* Function Name: update_board
********************************************************************************
* Summary: iterates through the game board array and fills the board appropriately
*						using lcd_draw_image
* Returns:
*  Nothing
*******************************************************************************/
void update_board(void){
	uint8_t i, j;
	uint16_t x_start, y_start;
	for (i = 0; i < 25; i++){
		for (j = 0; j < 10; j++) {
			x_start = 45 + (((j+1)*SQUARE_WIDTH) - SQUARE_WIDTH/2);
			y_start = ((i+1)*SQUARE_WIDTH) - SQUARE_WIDTH/2;
			lcd_draw_image(x_start, SQUARE_WIDTH, y_start, SQUARE_WIDTH, square_bitmaps, board[i+4][j].Color, LCD_COLOR_BLACK);
		}
	}
}

///*******************************************************************************
//* Function Name: update_board_block
//********************************************************************************
//* Summary:
//* Returns:
//*  Nothing
//*******************************************************************************/
//void update_board_block(int8_t y_begin, int8_t y_end,  int8_t x_begin, int8_t x_end, uint16_t drawColor, uint16_t eraseColor){
//	uint8_t i, j;
//	uint16_t x_start, y_start;
//	
//	// control bounds
//	if (y_begin < 0) {y_begin = 0;}
//	if (y_end > BOARD_HEIGHT-1) {y_end = BOARD_HEIGHT-1;}
//	if (x_begin < 0) {x_begin = 0;}
//	if (x_end > BOARD_WIDTH-1) {x_end = BOARD_WIDTH-1;}
//	
//	for (i = y_begin; i <= y_end; i++){
//		for (j = x_begin; j <= x_end; j++) {
//			if (board[i+4][j].Color == eraseColor) {		
//				x_start = 45 + (((j+1)*SQUARE_WIDTH) - SQUARE_WIDTH/2);
//				y_start = ((i+1)*SQUARE_WIDTH) - SQUARE_WIDTH/2;
//				lcd_draw_image(x_start, SQUARE_WIDTH, y_start, SQUARE_WIDTH, square_bitmaps, drawColor, LCD_COLOR_BLACK);
//			}
//		}
//	}
//}

/*******************************************************************************
* Function wait_ms
********************************************************************************
* Summary: a wait function used for delays
* Returns:
*  Nothing
*******************************************************************************/

extern volatile uint32_t wait; // can also be used to spawn random block
void wait_ms(int32_t milliseconds) {
  wait = 0;
  while (wait < milliseconds) {
    // TIMER4 ISR INCREMENTS WAIT ONCE EVERY MILLISECOND
  }
  return;
}

/*******************************************************************************
* Function Name: init_game
********************************************************************************
* Summary: initializes background of board and clears board array
* Returns:
*  Nothing
*******************************************************************************/
void init_game(uint8_t *currBlockY, uint8_t *currBlockX) {
	
  uint8_t i;
  uint8_t j;
	uint16_t x_start, y_start;
	lcd_clear_screen(LCD_COLOR_RED);
	lcd_draw_image(X_LEFT_SIDE, side_bricksWidthPixels, Y_SIDE_UPPER, side_bricksHeightPixels, side_bricksBitmaps, LCD_COLOR_BLACK, LCD_COLOR_RED);
	lcd_draw_image(X_LEFT_SIDE, side_bricksWidthPixels, Y_SIDE_LOWER, side_bricksHeightPixels, side_bricksBitmaps, LCD_COLOR_BLACK, LCD_COLOR_RED);
	lcd_draw_image(X_RIGHT_SIDE, side_bricksWidthPixels, Y_SIDE_UPPER, side_bricksHeightPixels, side_bricksBitmaps, LCD_COLOR_BLACK, LCD_COLOR_RED);
	lcd_draw_image(X_RIGHT_SIDE, side_bricksWidthPixels, Y_SIDE_LOWER, side_bricksHeightPixels, side_bricksBitmaps, LCD_COLOR_BLACK, LCD_COLOR_RED);

	//initializes black board
  for (i = 0; i < BOARD_HEIGHT+5; i++) {
    for (j = 0; j < BOARD_WIDTH; j++) {
      board[i][j].Color = LCD_COLOR_BLACK;
			x_start = 45 + (((j+1)*SQUARE_WIDTH) - SQUARE_WIDTH/2);
			y_start = ((i+1)*SQUARE_WIDTH) - SQUARE_WIDTH/2;
			lcd_draw_image(x_start, SQUARE_WIDTH, y_start, SQUARE_WIDTH, square_bitmaps, board[i+4][j].Color, LCD_COLOR_BLACK);		
			//update_board();
    }
  }
		linesCleared = 0;
		spawn_block(currBlockY, currBlockX);
}
/*******************************************************************************
* Function Name: spawn_block
********************************************************************************
* Summary: Generates a random block above the board at array location (4,4)
* Returns:
*  Nothing
*******************************************************************************/

void spawn_block(uint8_t *currBlockY, uint8_t *currBlockX) {
	random = (random % DISTINCT_NUM_BLOCKS) + 1; // plus 1 for our enumerbalee
	blocktype = (Shape)random;
	*currBlockX = 4;
	*currBlockY = 4;
	draw_block(currBlockY, currBlockX, &blocktype, false);
	fall_block(currBlockY, currBlockX, &blocktype);
}

/*******************************************************************************
* Function Name: check_block_surroundings
********************************************************************************
* Summary: Based on current location, and desired direction, determines
*						determines if an individual square of a block can move. 
*						Helper method to check_surroundings
* Returns:
*  true if block can move in desired direction
*******************************************************************************/
bool checkBlockSurrounding(uint8_t currBlockY, uint8_t currBlockX, int8_t DIRECTION) {
  if (DIRECTION == MOVE_LEFT) { // LEFT
    if ( currBlockX > 0) {
      if (board[currBlockY][currBlockX - 1].Color == LCD_COLOR_BLACK) {
        return true;
      } else {
        return false;
      }
    } else {
      // BLOCK IS ON EDGE (like a clare)
      return false;

    }
  } else if (DIRECTION == MOVE_RIGHT) { // RIGHT
    if (currBlockX < BOARD_WIDTH - 1) {
      if (board[currBlockY][currBlockX + 1].Color == LCD_COLOR_BLACK) {
        return true;
      } else {
        return false;
      }
    } else {
      // BLOCK IS ON EDGE (like a clare)
      return false;

    }
  } else if (DIRECTION == MOVE_DOWN) { // DOWN
    if ( currBlockY < BOARD_HEIGHT + 4 ) {
      if (board[currBlockY + 1][currBlockX].Color == LCD_COLOR_BLACK) {
        return true;
      } else {
        return false;
      }
    } else {
      // BLOCK IS ON EDGE (like a clare)
      return false;

    }

  }

  return false; 
}

/*******************************************************************************
* Function Name: check_surroundings
********************************************************************************
* Summary: Based on current location, desired direction, and blocktype, determines if 
*						a block can move
* Returns:
*  true if block can move in desired direction
*******************************************************************************/
bool check_surroundings(uint8_t currBlockY, uint8_t currBlockX, int8_t DIRECTION, Shape blockType) {
  // DEPENDING ON BLOCKTYPE IT WILL CHECK CERTAIN POSITIONS
  if (DIRECTION == MOVE_LEFT) { // LEFT

    if ( blockType == SQUARE && currBlockX > 0) {
      return checkBlockSurrounding(currBlockY, currBlockX, MOVE_LEFT) &&
        checkBlockSurrounding(currBlockY - 1, currBlockX, MOVE_LEFT);
    }
	
	else if (  blockType == LONGBOI && currBlockX > 0) {
      return checkBlockSurrounding(currBlockY, currBlockX, MOVE_LEFT) &&
        checkBlockSurrounding(currBlockY - 1, currBlockX, MOVE_LEFT) &&
        checkBlockSurrounding(currBlockY - 2, currBlockX, MOVE_LEFT) &&
        checkBlockSurrounding(currBlockY - 3, currBlockX, MOVE_LEFT);
			
    } else if (  blockType == LONGBOI180 && currBlockX > 0) {
      return checkBlockSurrounding(currBlockY, currBlockX, MOVE_LEFT);

    } else if (  blockType == SBLOCK && currBlockX > 0) {
      return checkBlockSurrounding(currBlockY, currBlockX, MOVE_LEFT) &&
        checkBlockSurrounding(currBlockY - 1, currBlockX + 1, MOVE_LEFT);

    } else if (  blockType == SBLOCK180 && currBlockX > 0) {
      return checkBlockSurrounding(currBlockY, currBlockX, MOVE_LEFT) &&
        checkBlockSurrounding(currBlockY - 1, currBlockX - 1, MOVE_LEFT) &&
        checkBlockSurrounding(currBlockY - 2, currBlockX - 1, MOVE_LEFT);

    } else if (  blockType == ZBLOCK && currBlockX < 2) { // HOT BLOCK IS OFFSET
      return checkBlockSurrounding(currBlockY - 1, currBlockX - 2, MOVE_LEFT) &&
        checkBlockSurrounding(currBlockY, currBlockX - 1, MOVE_LEFT);

    } else if (  blockType == ZBLOCK180 && currBlockX > 0) {
      return checkBlockSurrounding(currBlockY, currBlockX, MOVE_LEFT) &&
        checkBlockSurrounding(currBlockY - 1, currBlockX, MOVE_LEFT) &&
        checkBlockSurrounding(currBlockY - 2, currBlockX + 1, MOVE_LEFT);

    }

  } else if (DIRECTION == MOVE_RIGHT) { // RIGHT
    if (  blockType == SQUARE && currBlockX < BOARD_WIDTH - 2) { // HOT BLOCK IS OFFSET
      return checkBlockSurrounding(currBlockY, currBlockX + 1, MOVE_RIGHT) &&
        checkBlockSurrounding(currBlockY - 1, currBlockX + 1, DIRECTION);
			
    } else if (  blockType == LONGBOI && currBlockX < BOARD_WIDTH - 1) {
      return checkBlockSurrounding(currBlockY, currBlockX, MOVE_RIGHT) &&
        checkBlockSurrounding(currBlockY - 1, currBlockX, MOVE_RIGHT) &&
        checkBlockSurrounding(currBlockY - 2, currBlockX, MOVE_RIGHT) &&
        checkBlockSurrounding(currBlockY - 3, currBlockX, MOVE_RIGHT);
			
    } else if (  blockType == LONGBOI180 && currBlockX < BOARD_WIDTH - 4) { // HOT BLOCK IS OFFSET
      return checkBlockSurrounding(currBlockY, currBlockX + 3, MOVE_RIGHT);

    } else if (  blockType == SBLOCK && currBlockX < BOARD_WIDTH - 3) { // HOT BLOCK IS OFFSET
      return checkBlockSurrounding(currBlockY, currBlockX + 1, MOVE_RIGHT) &&
        checkBlockSurrounding(currBlockY - 1, currBlockX + 2, MOVE_RIGHT);

    } else if (  blockType == SBLOCK180 && currBlockX < BOARD_WIDTH - 1) {
      return checkBlockSurrounding(currBlockY, currBlockX, MOVE_RIGHT) &&
        checkBlockSurrounding(currBlockY - 1, currBlockX, MOVE_RIGHT) &&
        checkBlockSurrounding(currBlockY - 2, currBlockX - 1, MOVE_RIGHT);

    } else if (  blockType == ZBLOCK && currBlockX < BOARD_WIDTH - 1) {
      return checkBlockSurrounding(currBlockY, currBlockX, MOVE_RIGHT) &&
        checkBlockSurrounding(currBlockY - 1, currBlockX - 1, MOVE_RIGHT);

    } else if (  blockType == ZBLOCK180 && currBlockX < BOARD_WIDTH - 2) { // HOT BLOCK IS OFFSET
      return checkBlockSurrounding(currBlockY, currBlockX, MOVE_RIGHT) &&
        checkBlockSurrounding(currBlockY - 1, currBlockX + 1, MOVE_RIGHT) &&
        checkBlockSurrounding(currBlockY - 2, currBlockX + 1, MOVE_RIGHT);

    }
  } else if (DIRECTION == MOVE_DOWN) { // DOWN
    if (  blockType == SQUARE && currBlockY < BOARD_HEIGHT + 4) {
      return checkBlockSurrounding(currBlockY, currBlockX, MOVE_DOWN) &&
        checkBlockSurrounding(currBlockY, currBlockX + 1, MOVE_DOWN);
			
    } else if (  blockType == LONGBOI && currBlockY < BOARD_HEIGHT + 4) {
      return checkBlockSurrounding(currBlockY, currBlockX, MOVE_DOWN);

    } else if (  blockType == LONGBOI180 && currBlockY < BOARD_HEIGHT + 4) {
      return checkBlockSurrounding(currBlockY, currBlockX, MOVE_DOWN) &&
				checkBlockSurrounding(currBlockY, currBlockX + 1, MOVE_DOWN) &&
				checkBlockSurrounding(currBlockY, currBlockX + 2, MOVE_DOWN)  &&
				checkBlockSurrounding(currBlockY, currBlockX + 3, MOVE_DOWN);
			
			
    } else if (  blockType == SBLOCK && currBlockY < BOARD_HEIGHT + 4) {
      return checkBlockSurrounding(currBlockY, currBlockX, MOVE_DOWN) &&
				checkBlockSurrounding(currBlockY, currBlockX + 1, MOVE_DOWN) &&
				checkBlockSurrounding(currBlockY - 1, currBlockX + 2, MOVE_DOWN);
			
    } else if (  blockType == SBLOCK180 && currBlockY < BOARD_HEIGHT + 4) {
      return checkBlockSurrounding(currBlockY, currBlockX, MOVE_DOWN) &&
				checkBlockSurrounding(currBlockY - 1, currBlockX - 1, MOVE_DOWN);
			
    } else if (  blockType == ZBLOCK && currBlockY < BOARD_HEIGHT + 4) {
      return checkBlockSurrounding(currBlockY, currBlockX, MOVE_DOWN) &&
				checkBlockSurrounding(currBlockY, currBlockX - 1, MOVE_DOWN) &&
				checkBlockSurrounding(currBlockY - 1, currBlockX - 2, MOVE_DOWN);
			
    } else if (  blockType == ZBLOCK180 && currBlockY < BOARD_HEIGHT + 4) {
      return checkBlockSurrounding(currBlockY, currBlockX, MOVE_DOWN) &&
				checkBlockSurrounding(currBlockY - 1, currBlockX + 1, MOVE_DOWN);
    }
	}
	
	else if (DIRECTION == MOVE_NULL) { // ROTATION
		if (  blockType == SQUARE && currBlockY < BOARD_HEIGHT + 4 ) {
			return 
				board[currBlockY][currBlockX].Color == LCD_COLOR_BLACK &&
				board[currBlockY-1][currBlockX].Color == LCD_COLOR_BLACK &&
				board[currBlockY][currBlockX+1].Color == LCD_COLOR_BLACK &&
				board[currBlockY-1][currBlockX+1].Color == LCD_COLOR_BLACK;
			
    } else if (  blockType == LONGBOI && currBlockY < BOARD_HEIGHT + 4) {
      return 
				board[currBlockY][currBlockX].Color == LCD_COLOR_BLACK &&
				board[currBlockY-1][currBlockX].Color == LCD_COLOR_BLACK &&
				board[currBlockY-2][currBlockX].Color == LCD_COLOR_BLACK &&
				board[currBlockY-3][currBlockX].Color == LCD_COLOR_BLACK;

    } else if (  blockType == LONGBOI180 && currBlockY < BOARD_HEIGHT + 4) {
      return 
				board[currBlockY][currBlockX].Color == LCD_COLOR_BLACK &&
				board[currBlockY][currBlockX+1].Color == LCD_COLOR_BLACK &&
				board[currBlockY][currBlockX+2].Color == LCD_COLOR_BLACK &&
				board[currBlockY][currBlockX+3].Color == LCD_COLOR_BLACK;
			
    } else if (  blockType == SBLOCK && currBlockY < BOARD_HEIGHT + 4) {
      return 
				board[currBlockY][currBlockX].Color == LCD_COLOR_BLACK &&
				board[currBlockY][currBlockX+1].Color == LCD_COLOR_BLACK &&
				board[currBlockY-1][currBlockX+1].Color == LCD_COLOR_BLACK &&
				board[currBlockY-1][currBlockX+2].Color == LCD_COLOR_BLACK;
			
    } else if (  blockType == SBLOCK180 && currBlockY < BOARD_HEIGHT + 4) {
      return 
				board[currBlockY][currBlockX].Color == LCD_COLOR_BLACK &&
				board[currBlockY-1][currBlockX].Color == LCD_COLOR_BLACK &&
				board[currBlockY-1][currBlockX-1].Color == LCD_COLOR_BLACK &&
				board[currBlockY-2][currBlockX-1].Color == LCD_COLOR_BLACK;
			
    } else if (  blockType == ZBLOCK && currBlockY < BOARD_HEIGHT + 4) {
      return 
				board[currBlockY][currBlockX].Color == LCD_COLOR_BLACK &&
				board[currBlockY][currBlockX-1].Color == LCD_COLOR_BLACK &&
				board[currBlockY-1][currBlockX-1].Color == LCD_COLOR_BLACK &&
				board[currBlockY-1][currBlockX-2].Color == LCD_COLOR_BLACK;
			
    } else if (  blockType == ZBLOCK180 && currBlockY < BOARD_HEIGHT + 4) {
      return 
				board[currBlockY][currBlockX].Color == LCD_COLOR_BLACK &&
				board[currBlockY-1][currBlockX].Color == LCD_COLOR_BLACK &&
				board[currBlockY-1][currBlockX+1].Color == LCD_COLOR_BLACK &&
				board[currBlockY-2][currBlockX+1].Color == LCD_COLOR_BLACK;
    }
	  
	}
		
  return false;
}

/*******************************************************************************
* Function Name: rotate_block
********************************************************************************
* Summary: checks if current block can rotate and, if possible
*					rotates block about the reference square. Square blocks don't rotate
* Returns:
*  Nothing
*******************************************************************************/
void rotate_block(uint8_t *currBlockY, uint8_t *currBlockX, Shape *BlockType) {
	uint8_t original_currX; 
	draw_block(currBlockY, currBlockX, BlockType, true); // clear block from gameboard
	
	original_currX = *currBlockX;
	
	
	// check if new block can fit
  if (*BlockType == LONGBOI) {
		
		if (*currBlockX == BOARD_WIDTH - 1) {
			
			*currBlockX = *currBlockX - 3;
		} else if (*currBlockX == BOARD_WIDTH - 2) {
			*currBlockX = *currBlockX - 2;
		} else if (*currBlockX == BOARD_WIDTH - 3) {
			*currBlockX = *currBlockX - 1;
		}
		if (check_surroundings(*currBlockY, *currBlockX, MOVE_NULL, LONGBOI180)) {
			*BlockType = LONGBOI180;
		}
		else {
		*currBlockX = original_currX;
		}
		
  } else if (*BlockType == LONGBOI180) {
		
		if (check_surroundings(*currBlockY, *currBlockX, MOVE_NULL, LONGBOI)) {
			*BlockType = LONGBOI;
		}
		
	} else if (*BlockType == SBLOCK) {
		
		*currBlockX = *currBlockX + 1;
		
		if (check_surroundings(*currBlockY, *currBlockX, MOVE_NULL, SBLOCK180)) {
			*BlockType = SBLOCK180;
		} else {
			*currBlockX = original_currX;
		}
		
		
	} else if (*BlockType == SBLOCK180) {
		
		if (*currBlockX == BOARD_WIDTH - 1) {
			*currBlockX = *currBlockX - 2;
		}
		else {
			*currBlockX = *currBlockX - 1;
		}
		
		if (check_surroundings(*currBlockY, *currBlockX, MOVE_NULL, SBLOCK)) {
			*BlockType = SBLOCK;
		}
		else {
			*currBlockX = original_currX;
		}
		
	} else if (*BlockType == ZBLOCK) {
		
		
		*currBlockX = *currBlockX - 1;
		
		if (check_surroundings(*currBlockY, *currBlockX, MOVE_NULL, ZBLOCK180)) {
			*BlockType = ZBLOCK180;
		}
		else {
			*currBlockX = original_currX;
		}
		
	} else if (*BlockType == ZBLOCK180) {
		
		if (*currBlockX == 0) {
			*currBlockX = *currBlockX + 2;
		}
		else {
			*currBlockX = *currBlockX + 1;
		}
		
		if (check_surroundings(*currBlockY, *currBlockX, MOVE_NULL, ZBLOCK)) {
			*BlockType = ZBLOCK;
		}
		else {
			*currBlockX = original_currX;
		}
	}
	
	draw_block(currBlockY,currBlockX, BlockType, false);
	
	return;
}
/*******************************************************************************
* Function Name: move_block
********************************************************************************
* Summary: Called if check_surroundings is passed. Moves the block in desired direction
* Returns:
*  Nothing
*******************************************************************************/
void move_block(uint8_t *currBlockY, uint8_t *currBlockX, Direction DIRECTION, Shape *BlockType) {
  draw_block(currBlockY, currBlockX, BlockType, true);
	if (DIRECTION == MOVE_DOWN) {
		*currBlockY += 1;
	}
	else if (DIRECTION == MOVE_LEFT || MOVE_RIGHT) {
	*currBlockX += DIRECTION;
	}
	draw_block(currBlockY, currBlockX, BlockType, false);
	
	return;
}

/*******************************************************************************
* Function Name: fall_block
********************************************************************************
* Summary: used for block to fall downward naturally
* Returns:
*  Nothing
*******************************************************************************/
void fall_block(uint8_t *currBlockY, uint8_t *currBlockX, Shape *BlockType) {
  draw_block(currBlockY, currBlockX, BlockType, true);
	*currBlockY = *currBlockY + 1;
	draw_block(currBlockY, currBlockX, BlockType, false);
  return;
}

/*******************************************************************************
* Function Name: flash_LEDs
********************************************************************************
* Summary: flashes LEDs
* Returns:
*  Nothing
*******************************************************************************/

void flash_LEDs(void) {
	
	toggle_LEDs();
	wait_ms(100);
	toggle_LEDs();
	wait_ms(100);
	toggle_LEDs();
	wait_ms(100);
	toggle_LEDs();
	wait_ms(100);
	toggle_LEDs();
	wait_ms(100);
	toggle_LEDs();
}

/*******************************************************************************
* Function Name: fall_delay_ms
********************************************************************************
* Summary: adjusts fall delay time for number of lines cleared. More lines cleared
*					means faster falling
* Returns:
*  delay time
*******************************************************************************/
uint32_t fall_delay_ms(uint16_t numLinesCleared) {

	if (numLinesCleared == 0) {
		return 2000;
	}
	else if (numLinesCleared == 1) {
		return 1800;
	}
	else if (numLinesCleared == 2) {
		return 1600;
	}
	else if (numLinesCleared == 3) {
		return 1400;
	}
	else if (numLinesCleared == 4) {
		return 1200;
	}
	else if (numLinesCleared > 4) {
		return 1000;
	}
	
	return 1000;
}

/*******************************************************************************
* Function Name: detect_line
********************************************************************************
* Summary: Searches board array to determine if a line has been filled.
						Flashes LEDs, clears line, and increments line cont if a line is full
* Returns:
*  Nothing
*******************************************************************************/
void detect_line(void) {
  int8_t i;
  int8_t j;
  int8_t k;

  bool lineFull;

  for (i = 5; i < BOARD_HEIGHT+5; i++) {
    lineFull = true;
    for (j = 0; j < BOARD_WIDTH; j++) {
      if (board[i][j].Color == LCD_COLOR_BLACK) {
        lineFull = false;
        j = BOARD_WIDTH; 
      }
    }
		//TODO invert the cleared line quick to look cool for a hot sec, top row set to all black
		if (lineFull) {
			for (k = i; k>0; k--) {
				for (j = 0; j < BOARD_WIDTH; j++) {
					board[k][j].Color = board[k-1][j].Color;
				}
			}
			for (j = 0; j < BOARD_WIDTH; j++){ // top row is black
			board[0][j].Color = LCD_COLOR_BLACK;
			}
			
      i--; // decrement i so we still check the next line after shifting game board
			linesCleared++;
			flash_LEDs();
		}
  }
	//update_board();
}


/*******************************************************************************
* Function Name: detect_loss
********************************************************************************
* Summary: Searches hidden fourth row of game board (above screen) to determine
*					if the game has been lost
* Returns:
*  true if game lost
*******************************************************************************/

bool detect_loss(void) {
  int8_t j;
  for (j = 0; j < BOARD_WIDTH; j++) {
    if (board[4][j].Color != LCD_COLOR_BLACK) { // check the headroom
      return false;
    }
  }
  return true;
}
/*******************************************************************************
* Function Name: gameOver
********************************************************************************
* Summary: Inverts the game board, called when game ends
* Returns:
*  Nothing
*******************************************************************************/

void gameOver(void) {
	uint8_t i, j;
	uint16_t x_start, y_start;
	for (i = 0; i < 25; i++){
		for (j = 0; j < 10; j++) {
			x_start = 45 + (((j+1)*SQUARE_WIDTH) - SQUARE_WIDTH/2);
			y_start = ((i+1)*SQUARE_WIDTH) - SQUARE_WIDTH/2;
			lcd_draw_image(x_start, SQUARE_WIDTH, y_start, SQUARE_WIDTH, square_bitmaps, LCD_COLOR_BLACK, board[i+4][j].Color);
		}
	}
	wait_ms(150);
	for (i = 0; i < 25; i++){
		for (j = 0; j < 10; j++) {
			x_start = 45 + (((j+1)*SQUARE_WIDTH) - SQUARE_WIDTH/2);
			y_start = ((i+1)*SQUARE_WIDTH) - SQUARE_WIDTH/2;
			lcd_draw_image(x_start, SQUARE_WIDTH, y_start, SQUARE_WIDTH, square_bitmaps, board[i+4][j].Color, LCD_COLOR_BLACK);
		}
	}
	wait_ms(150);
}

/*******************************************************************************
* Function Name: tetris_init
********************************************************************************
* Summary: flashes LEDs and calls hardware init
* Returns:
*  Nothing
*******************************************************************************/
void tetris_init(void){
	initialize_hardware();
//					eeprom_byte_write(EEPROM_I2C_BASE, highscore_eeprom_address[2], 0x00); // bump down other scores
//				eeprom_byte_write(EEPROM_I2C_BASE, highscore_eeprom_address[1], 0x00);
//				
//				// write current score
//				eeprom_byte_write(EEPROM_I2C_BASE, highscore_eeprom_address[0], 0x00);
	flash_LEDs();
}

/*******************************************************************************
* Function Name: display_high_score
********************************************************************************
* Summary: Displays the three high scores to the screen
* Returns:
*  Nothing
*******************************************************************************/

void displayHighScore(uint8_t highscore0, uint8_t highscore1, uint8_t highscore2) {
	
	uint8_t thousand;
	uint8_t hundred;
	
	lcd_clear_screen(LCD_COLOR_BLACK);
	lcd_draw_image(SCREEN_CENTER_X, highscoresWidthPixels, SCREEN_CENTER_Y, highscoresHeightPixels, highscoresBitmaps, LCD_COLOR_RED, LCD_COLOR_BLACK);

	//isolate each decimal place and print at offsets from eachother
	
	hundred  = (highscore0/100)%10;
	thousand = (highscore0-hundred*100)/1000;
// DISPLAY FIRST PLACE SCORE
	lcd_draw_image(THOUSANDS, num_widthPixels, FIRST_PLACE_Y, num_heightPixels, num_bitmaps[thousand%10], LCD_COLOR_MAGENTA, LCD_COLOR_BLACK);
	lcd_draw_image(HUNDREDS, num_widthPixels, FIRST_PLACE_Y, num_heightPixels, num_bitmaps[hundred%10], LCD_COLOR_MAGENTA, LCD_COLOR_BLACK);
	lcd_draw_image(TENS, num_widthPixels, FIRST_PLACE_Y, num_heightPixels, num_bitmaps[0], LCD_COLOR_MAGENTA, LCD_COLOR_BLACK);
	lcd_draw_image(ONES, num_widthPixels, FIRST_PLACE_Y, num_heightPixels, num_bitmaps[0], LCD_COLOR_MAGENTA, LCD_COLOR_BLACK);
	
	hundred  = (highscore1/100)%10;
	thousand = (highscore1-hundred*100)/1000;

	lcd_draw_image(THOUSANDS, num_widthPixels, SECOND_PLACE_Y, num_heightPixels, num_bitmaps[thousand%10], LCD_COLOR_MAGENTA, LCD_COLOR_BLACK);
	lcd_draw_image(HUNDREDS, num_widthPixels, SECOND_PLACE_Y, num_heightPixels, num_bitmaps[hundred%10], LCD_COLOR_MAGENTA, LCD_COLOR_BLACK);
	lcd_draw_image(TENS, num_widthPixels, SECOND_PLACE_Y, num_heightPixels, num_bitmaps[0], LCD_COLOR_MAGENTA, LCD_COLOR_BLACK);
	lcd_draw_image(ONES, num_widthPixels, SECOND_PLACE_Y, num_heightPixels, num_bitmaps[0], LCD_COLOR_MAGENTA, LCD_COLOR_BLACK);
	
	hundred  = (highscore2/100)%10;
	thousand = (highscore2-hundred*100)/1000;

	lcd_draw_image(THOUSANDS, num_widthPixels, THIRD_PLACE_Y, num_heightPixels, num_bitmaps[thousand%10], LCD_COLOR_MAGENTA, LCD_COLOR_BLACK);
	lcd_draw_image(HUNDREDS, num_widthPixels, THIRD_PLACE_Y, num_heightPixels, num_bitmaps[hundred%10], LCD_COLOR_MAGENTA, LCD_COLOR_BLACK);
	lcd_draw_image(TENS, num_widthPixels, THIRD_PLACE_Y, num_heightPixels, num_bitmaps[0], LCD_COLOR_MAGENTA, LCD_COLOR_BLACK);
	lcd_draw_image(ONES, num_widthPixels, THIRD_PLACE_Y, num_heightPixels, num_bitmaps[0], LCD_COLOR_MAGENTA, LCD_COLOR_BLACK);
}
/*******************************************************************************
* Function Name: project_main
********************************************************************************
* Summary: implements a version of Tetris called 4-TRIS. Tetris but better: only 4 blocks
*					Game Play:
******************Tap Screen to Start
******************Move Block using joystick, tilting the board, or arrow buttons
******************Rotate by clicking up button or by tapping screen
******************Tap screen at end to play a new round
******************Speeeeeed downward with joystick or down button
******************Each line cleared is worth one hundred points!
* Returns:
*  Nothing
*******************************************************************************/
extern volatile bool ADC_avg_ready;
extern volatile bool AlertADC; 
extern volatile bool timerDone;
extern volatile uint16_t avg_ps2x; // global x avg value
extern volatile uint16_t avg_ps2y;
extern volatile bool buttonPressed;

extern volatile bool leftButtonPressed;
extern volatile bool rightButtonPressed;
extern volatile bool upButtonPressed;
extern volatile bool downButtonPressed;


void project_main(void) {
	
	uint8_t highscore0, highscore1, highscore2;
	uint8_t temp_highscore_swap;
	
	uint16_t x_touch,y_touch;
  uint8_t touch_event;
	uint8_t joystick_x, joystick_y;
	int16_t accel_x, accel_y;
	int8_t conv_count = -1; // start at -1 for first runthrough ADC
	uint8_t currBlockX, currBlockY;
  bool blockPlaced = false;
	tetris_init();
  while (420) {
		
    bool mainMenu = true;
    bool gameActive = true;
	//initialize welcome screen
    lcd_draw_image(SCREEN_CENTER_X, welcomebricksWidthPixels, SCREEN_UPPER_Y, welcomebricksHeightPixels, welcomebricksBitmaps, LCD_COLOR_RED, LCD_COLOR_BLACK);
		lcd_draw_image(SCREEN_CENTER_X, welcomebricksWidthPixels, SCREEN_LOWER_Y, welcomebricksHeightPixels, welcomebricksBitmaps, LCD_COLOR_RED, LCD_COLOR_BLACK);
		lcd_draw_image(SCREEN_CENTER_X, welcomeWidthPixels, SCREEN_CENTER_Y, welcomeHeightPixels, welcomeBitmaps, LCD_COLOR_YELLOW, LCD_COLOR_RED);
		
    while (mainMenu) {
      // MAIN MENU
      if (ft6x06_read_td_status() > 0) {
        mainMenu = false;
      }
    }

    init_game(&currBlockY, &currBlockX);
		
		update_board();

    while (gameActive) {
      // MAIN GAME LOOP
			
			accel_x = accel_read_x();
			accel_y = accel_read_y();
			touch_event = ft6x06_read_td_status();
			
				//checks if tilt
			if (accel_x > 6000){ // move LEFT
				if (check_surroundings(currBlockY, currBlockX, MOVE_LEFT, blocktype)) {
						move_block(&currBlockY, &currBlockX, MOVE_LEFT, &blocktype);
					}
			} else if (accel_x < -6000){ // move RIGHT
				if (check_surroundings(currBlockY, currBlockX, MOVE_RIGHT, blocktype)) {
						move_block(&currBlockY, &currBlockX, MOVE_RIGHT, &blocktype);
					}
			} else if (accel_y < -10000){ // ROTATE
				rotate_block(&currBlockY, &currBlockX, &blocktype);
			} //Rotate if screen tapped
			else if (ft6x06_read_td_status()>0){
//				x_touch = ft6x06_read_x();
//				if (x_touch < 45) { // move LEFT
//					if (check_surroundings(currBlockY, currBlockX, MOVE_LEFT, blocktype)) {
//						move_block(&currBlockY, &currBlockX, MOVE_LEFT, &blocktype);
//					}
//				} else if (x_touch > 195){ // move RIGHT
//					if (check_surroundings(currBlockY, currBlockX, MOVE_RIGHT, blocktype)) {
//						move_block(&currBlockY, &currBlockX, MOVE_RIGHT, &blocktype);
//					}
				//} else {
					rotate_block(&currBlockY, &currBlockX, &blocktype);
				//}
			}
			//rotate if button pressed
			if (buttonPressed) {
        // ROTATE BLOCK
        buttonPressed = false;
        rotate_block(&currBlockY, &currBlockX, &blocktype);
				//update_board();
      }
			//rotate on UP
			if (upButtonPressed ) {
				upButtonPressed = false;
        rotate_block(&currBlockY, &currBlockX, &blocktype);
			} // speed down on DOWN
			if (downButtonPressed && check_surroundings(currBlockY, currBlockX, MOVE_DOWN, blocktype)) {
				downButtonPressed = false;
				move_block(&currBlockY, &currBlockX, MOVE_DOWN, &blocktype);
			}//move left on LEFT
			if (leftButtonPressed && check_surroundings(currBlockY, currBlockX, MOVE_LEFT, blocktype)) {
				leftButtonPressed = false;
				move_block(&currBlockY, &currBlockX, MOVE_LEFT, &blocktype);
			}//move right on RIGHT
			if (rightButtonPressed && check_surroundings(currBlockY, currBlockX, MOVE_RIGHT, blocktype)) {
				rightButtonPressed = false;
				move_block(&currBlockY, &currBlockX, MOVE_RIGHT, &blocktype);
			}
		
			
			
//			if (AlertADC) {
			// this literally breaks our adc what does this thing even DO here???
//				//wait_ms(500);
//				AlertADC = false;

////				conv_count = (conv_count+1)%16; // 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 
//// 
////				if (conv_count == 15) {
////          // if we have done 16 conversion, allow ADC interrupts, otherwise disable 
////					ADC0->IM |= ADC_IM_MASK1; 
////					// should immediately jumpt to interrupt
////					// raw interrupt is still active

////				}
////				else {
////					// if it is not the 16th sample
////					ADC0->IM &= ~ADC_IM_MASK1; // block RIS from reaching NVIC
////					ADC0->ISC |= ADC_ISC_IN1;  // clear RIS register
////				}
// 
//			}

			if (ADC_avg_ready){
	//checks if joystick movement
      //if (ADC_avg_ready) {
        ADC_avg_ready = false;	
						
				
				if (avg_ps2x > 3475) { // If the x reading is greater than 2.8 V move LEFT
					if (check_surroundings(currBlockY, currBlockX, MOVE_LEFT, blocktype)) {
						move_block(&currBlockY, &currBlockX, MOVE_LEFT, &blocktype);
					}
				} else if (avg_ps2x < 744) { //If the x reading is less than .6 V move RIGHT
					if (check_surroundings(currBlockY, currBlockX, MOVE_RIGHT, blocktype)) {
						move_block(&currBlockY, &currBlockX, MOVE_RIGHT, &blocktype);
					} 
				}
				
				else if (avg_ps2y < 744) { //If the y reading is less than .6 V move DOWN
					if (check_surroundings(currBlockY, currBlockX, MOVE_DOWN, blocktype)) {
						move_block(&currBlockY, &currBlockX, MOVE_DOWN, &blocktype);
					}
				}
				
				//wait_ms(200); // slight delay after moving a block
			//}
			
				
			//update_board();
        

      //wait_ms(fall_delay_ms(linesCleared)); // wait to fall;
			

			
		//update_board();
			

		
  }
		//fall naturally if timeout
		if (timerDone) {
			if (check_surroundings(currBlockY, currBlockX, MOVE_DOWN, blocktype)){
			  fall_block(&currBlockY, &currBlockX, &blocktype);
			  //wait_ms(500);
			} else {
				//wait_ms(wait%DISTINCT_NUM_BLOCKS + 1);
				
				blockPlaced = true;
			}
			
	// if game is still active, generate a new block to fall
      if (blockPlaced) {
				blockPlaced = false;				
        detect_line();
        gameActive = detect_loss(); // set gameActive = false
				if (gameActive) {
				spawn_block(&currBlockY, &currBlockX);
			}
    }
	}
			
	update_board();
		
}
		//saves scores
			DisableInterrupts();
			eeprom_byte_read(EEPROM_I2C_BASE, highscore_eeprom_address[0], &highscore0);

			eeprom_byte_read(EEPROM_I2C_BASE, highscore_eeprom_address[1], &highscore1);

			eeprom_byte_read(EEPROM_I2C_BASE, highscore_eeprom_address[2], &highscore2);

			if (linesCleared > 99) { // then get a life
				linesCleared = 99;
			}
		
			if ( linesCleared*100 >= highscore0) {
				eeprom_byte_write(EEPROM_I2C_BASE, highscore_eeprom_address[2], highscore1); // bump down other scores
				eeprom_byte_write(EEPROM_I2C_BASE, highscore_eeprom_address[1], highscore0);
				
				// write current score
				eeprom_byte_write(EEPROM_I2C_BASE, highscore_eeprom_address[0], linesCleared*100);
				
				highscore0 = linesCleared*100;
				
			}
			else if ( linesCleared*100 >= highscore1) {
				eeprom_byte_write(EEPROM_I2C_BASE, highscore_eeprom_address[2], highscore1); // bump down other score
				
				eeprom_byte_write(EEPROM_I2C_BASE, highscore_eeprom_address[1], linesCleared*100);
				highscore1 = linesCleared*100;
			}
			else if ( linesCleared*100 >= highscore2) {
				eeprom_byte_write(EEPROM_I2C_BASE, highscore_eeprom_address[2], linesCleared*100);
				highscore2 = linesCleared*100;
			}
			EnableInterrupts();
		
//		while (!gameActive){
//			// END GAME LOOP
//			// board flashes forever. TODO LEDs flash. score displays		
//			gameOver();
//			
//			if (buttonPressed) {
//				buttonPressed = false;
//				gameActive = true;
//				//init_game(&currBlockY, &currBlockX);
//			}
//		}
			
			//flashes screen
			gameOver();
			gameOver();
			gameOver();
		if (!gameActive){
		displayHighScore(highscore0, highscore1, highscore2);
		}
		while (!mainMenu) {
		
			if (buttonPressed) {
				buttonPressed = false;
				mainMenu = true;
				//init_game(&currBlockY, &currBlockX);
			}
			if (ft6x06_read_td_status() > 0) {
        mainMenu = true;
      }
		
		}
		
	}
	
	return;
}
