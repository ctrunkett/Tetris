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
/*
typedef enum {
  BLACK, // BLACK HOLDS VALUE 0

  BLUE, // THESE ARE NON-ZERO
  RED,
  GREEN,
  YELLOW,
  PURPLE,
  ORANGE,
} COLOR;
*/
typedef enum{
  SQUARE = 0,
  LONGBOI = 1, LONGBOI180 = 4,
  SBLOCK = 2, SBLOCK180 = 5,
  ZBLOCK = 3, ZBLOCK180 = 6,
}Shape;
Shape BlockType;

typedef struct block { 
	uint8_t xPos;
	uint8_t yPos;
  uint16_t Color;
} Block;

extern volatile int x_pos;
extern volatile int y_pos;

//typedef struct blockType {
//  Block occupied[];
//} blockType;


// GAME BOARD IS 10 BY 20 BUT ALLOW SOME HEAD ROOM FOR BLOCKS TO SPAWN
// AND FALL NATURALLY INTO PLAY
Block board[25][10];

const bool RESET = false; // if RESET is not asserted, function is to draw

void drawBlock(int8_t *currBlockY, int8_t *currBlockX, bool RESETorDRAW) {
  if (BlockType == 0) {
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
	else if (BlockType == LONGBOI) {
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
		else if (BlockType == LONGBOI180) {
		if (RESETorDRAW == RESET) {
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
	else if (BlockType == SBLOCK) {
		if (RESETorDRAW == RESET) {
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
	else if (BlockType == SBLOCK180) {
		if (RESETorDRAW == RESET) {
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
	else if (BlockType == ZBLOCK) {
		if (RESETorDRAW == RESET) {
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
	else if (BlockType == ZBLOCK180) {
		if (RESETorDRAW == RESET) {
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
	/*
  else if (*blockType == LBLOCK0) {
		if (RESETorDRAW == RESET) {
		  board[*currBlockY][*currBlockX].Color = LCD_COLOR_BLACK;
      board[*currBlockY+1][*currBlockX].Color = LCD_COLOR_BLACK;
      board[*currBlockY+2][*currBlockX].Color = LCD_COLOR_BLACK;
      board[*currBlockY+2][*currBlockX+1].Color = LCD_COLOR_BLACK;
		}
		else { // (RESETorDRAW == DRAW)
      board[*currBlockY][*currBlockX].Color = LCD_COLOR_RED;
      board[*currBlockY+1][*currBlockX].Color = LCD_COLOR_RED;
      board[*currBlockY+2][*currBlockX].Color = LCD_COLOR_RED;
      board[*currBlockY+2][*currBlockX+1].Color = LCD_COLOR_RED;
    }
  }
	  else if (*blockType == LBLOCK90) {
		if (RESETorDRAW == RESET) {
		  board[*currBlockY][*currBlockX].Color = LCD_COLOR_BLACK;
      board[*currBlockY+1][*currBlockX].Color = LCD_COLOR_BLACK;
      board[*currBlockY+2][*currBlockX].Color = LCD_COLOR_BLACK;
      board[*currBlockY+2][*currBlockX+1].Color = LCD_COLOR_BLACK;
		}
		else { // (RESETorDRAW == DRAW)
      board[*currBlockY][*currBlockX].Color = LCD_COLOR_RED;
      board[*currBlockY+1][*currBlockX].Color = LCD_COLOR_RED;
      board[*currBlockY+2][*currBlockX].Color = LCD_COLOR_RED;
      board[*currBlockY+2][*currBlockX+1].Color = LCD_COLOR_RED;
    }
  }
	else if (*blockType == LBLOCK180) {
		if (RESETorDRAW == RESET) {
		  board[*currBlockY][*currBlockX].Color = LCD_COLOR_BLACK;
      board[*currBlockY+1][*currBlockX].Color = LCD_COLOR_BLACK;
      board[*currBlockY+2][*currBlockX].Color = LCD_COLOR_BLACK;
      board[*currBlockY+2][*currBlockX+1].Color = LCD_COLOR_BLACK;
		}
		else { // (RESETorDRAW == DRAW)
      board[*currBlockY][*currBlockX].Color = LCD_COLOR_RED;
      board[*currBlockY+1][*currBlockX].Color = LCD_COLOR_RED;
      board[*currBlockY+2][*currBlockX].Color = LCD_COLOR_RED;
      board[*currBlockY+2][*currBlockX+1].Color = LCD_COLOR_RED;
    }
  }	
	else if (*blockType == LBLOCK270) {
		if (RESETorDRAW == RESET) {
		  board[*currBlockY][*currBlockX].Color = LCD_COLOR_BLACK;
      board[*currBlockY+1][*currBlockX].Color = LCD_COLOR_BLACK;
      board[*currBlockY+2][*currBlockX].Color = LCD_COLOR_BLACK;
      board[*currBlockY+2][*currBlockX+1].Color = LCD_COLOR_BLACK;
		}
		else { // (RESETorDRAW == DRAW)
      board[*currBlockY][*currBlockX].Color = LCD_COLOR_RED;
      board[*currBlockY+1][*currBlockX].Color = LCD_COLOR_RED;
      board[*currBlockY+2][*currBlockX].Color = LCD_COLOR_RED;
      board[*currBlockY+2][*currBlockX+1].Color = LCD_COLOR_RED;
    }
  }
  else if (*blockType == JBLOCK0) {
		if (RESETorDRAW == RESET) {
		  board[*currBlockY][*currBlockX].Color = LCD_COLOR_BLACK;
      board[*currBlockY+1][*currBlockX].Color = LCD_COLOR_BLACK;
      board[*currBlockY+2][*currBlockX].Color = LCD_COLOR_BLACK;
      board[*currBlockY+2][*currBlockX+1].Color = LCD_COLOR_BLACK;
		}
		else { // (RESETorDRAW == DRAW)
      board[*currBlockY][*currBlockX].Color = LCD_COLOR_RED;
      board[*currBlockY+1][*currBlockX].Color = LCD_COLOR_RED;
      board[*currBlockY+2][*currBlockX].Color = LCD_COLOR_RED;
      board[*currBlockY+2][*currBlockX+1].Color = LCD_COLOR_RED;
    }
  }
	  else if (*blockType == JBLOCK90) {
		if (RESETorDRAW == RESET) {
		  board[*currBlockY][*currBlockX].Color = LCD_COLOR_BLACK;
      board[*currBlockY+1][*currBlockX].Color = LCD_COLOR_BLACK;
      board[*currBlockY+2][*currBlockX].Color = LCD_COLOR_BLACK;
      board[*currBlockY+2][*currBlockX+1].Color = LCD_COLOR_BLACK;
		}
		else { // (RESETorDRAW == DRAW)
      board[*currBlockY][*currBlockX].Color = LCD_COLOR_RED;
      board[*currBlockY+1][*currBlockX].Color = LCD_COLOR_RED;
      board[*currBlockY+2][*currBlockX].Color = LCD_COLOR_RED;
      board[*currBlockY+2][*currBlockX+1].Color = LCD_COLOR_RED;
    }
  }
	else if (*blockType == JBLOCK180) {
		if (RESETorDRAW == RESET) {
		  board[*currBlockY][*currBlockX].Color = LCD_COLOR_BLACK;
      board[*currBlockY+1][*currBlockX].Color = LCD_COLOR_BLACK;
      board[*currBlockY+2][*currBlockX].Color = LCD_COLOR_BLACK;
      board[*currBlockY+2][*currBlockX+1].Color = LCD_COLOR_BLACK;
		}
		else { // (RESETorDRAW == DRAW)
      board[*currBlockY][*currBlockX].Color = LCD_COLOR_RED;
      board[*currBlockY+1][*currBlockX].Color = LCD_COLOR_RED;
      board[*currBlockY+2][*currBlockX].Color = LCD_COLOR_RED;
      board[*currBlockY+2][*currBlockX+1].Color = LCD_COLOR_RED;
    }
  }	
	else if (*blockType == JBLOCK270) {
		if (RESETorDRAW == RESET) {
		  board[*currBlockY][*currBlockX].Color = LCD_COLOR_BLACK;
      board[*currBlockY+1][*currBlockX].Color = LCD_COLOR_BLACK;
      board[*currBlockY+2][*currBlockX].Color = LCD_COLOR_BLACK;
      board[*currBlockY+2][*currBlockX+1].Color = LCD_COLOR_BLACK;
		}
		else { // (RESETorDRAW == DRAW)
      board[*currBlockY][*currBlockX].Color = LCD_COLOR_RED;
      board[*currBlockY+1][*currBlockX].Color = LCD_COLOR_RED;
      board[*currBlockY+2][*currBlockX].Color = LCD_COLOR_RED;
      board[*currBlockY+2][*currBlockX+1].Color = LCD_COLOR_RED;
    }
  }
	  else if (*blockType == SPLIFF) {
		if (RESETorDRAW == RESET) {
		  board[*currBlockY][*currBlockX].Color = LCD_COLOR_BLACK;
      board[*currBlockY+1][*currBlockX].Color = LCD_COLOR_BLACK;
      board[*currBlockY+2][*currBlockX].Color = LCD_COLOR_BLACK;
      board[*currBlockY+2][*currBlockX+1].Color = LCD_COLOR_BLACK;
		}
		else { // (RESETorDRAW == DRAW)
      board[*currBlockY][*currBlockX].Color = LCD_COLOR_RED;
      board[*currBlockY+1][*currBlockX].Color = LCD_COLOR_RED;
      board[*currBlockY+2][*currBlockX].Color = LCD_COLOR_RED;
      board[*currBlockY+2][*currBlockX+1].Color = LCD_COLOR_RED;
    }
  }
	  else if (*blockType == SPLIFF90) {
		if (RESETorDRAW == RESET) {
		  board[*currBlockY][*currBlockX].Color = LCD_COLOR_BLACK;
      board[*currBlockY+1][*currBlockX].Color = LCD_COLOR_BLACK;
      board[*currBlockY+2][*currBlockX].Color = LCD_COLOR_BLACK;
      board[*currBlockY+2][*currBlockX+1].Color = LCD_COLOR_BLACK;
		}
		else { // (RESETorDRAW == DRAW)
      board[*currBlockY][*currBlockX].Color = LCD_COLOR_RED;
      board[*currBlockY+1][*currBlockX].Color = LCD_COLOR_RED;
      board[*currBlockY+2][*currBlockX].Color = LCD_COLOR_RED;
      board[*currBlockY+2][*currBlockX+1].Color = LCD_COLOR_RED;
    }
  }
	else if (*blockType == SPLIFF180) {
		if (RESETorDRAW == RESET) {
		  board[*currBlockY][*currBlockX].Color = LCD_COLOR_BLACK;
      board[*currBlockY+1][*currBlockX].Color = LCD_COLOR_BLACK;
      board[*currBlockY+2][*currBlockX].Color = LCD_COLOR_BLACK;
      board[*currBlockY+2][*currBlockX+1].Color = LCD_COLOR_BLACK;
		}
		else { // (RESETorDRAW == DRAW)
      board[*currBlockY][*currBlockX].Color = LCD_COLOR_RED;
      board[*currBlockY+1][*currBlockX].Color = LCD_COLOR_RED;
      board[*currBlockY+2][*currBlockX].Color = LCD_COLOR_RED;
      board[*currBlockY+2][*currBlockX+1].Color = LCD_COLOR_RED;
    }
  }	
	else if (*blockType == SPLIFF270) {
		if (RESETorDRAW == RESET) {
		  board[*currBlockY][*currBlockX].Color = LCD_COLOR_BLACK;
      board[*currBlockY+1][*currBlockX].Color = LCD_COLOR_BLACK;
      board[*currBlockY+2][*currBlockX].Color = LCD_COLOR_BLACK;
      board[*currBlockY+2][*currBlockX+1].Color = LCD_COLOR_BLACK;
		}
		else { // (RESETorDRAW == DRAW)
      board[*currBlockY][*currBlockX].Color = LCD_COLOR_RED;
      board[*currBlockY+1][*currBlockX].Color = LCD_COLOR_RED;
      board[*currBlockY+2][*currBlockX].Color = LCD_COLOR_RED;
      board[*currBlockY+2][*currBlockX+1].Color = LCD_COLOR_RED;
    }
  }
	*/

}

extern volatile uint32_t wait; // can also be used to spawn random block
void wait_ms(int32_t milliseconds) {
  wait = 0;
  while (wait < milliseconds) {
    // TIMER4 ISR INCREMENTS WAIT ONCE EVERY MILLISECOND
  }
  return;
}

// METHODS PERTINENT TO GAME LOGIC
void mainMenuAnimation(void) {
	//int CENTER_OF_SCREEN_X, CENTER_OF_SCREEN_Y; 
	int y, x, y_offset, x_offset;
	int i, j;
	
	for (y_offset = TOPOFSCREEN; y_offset > 0; y_offset--) {
		drawimage(CENTER OF X,CENTER OF Y + Y_OFFSET, IMAGE_BITMAP, ERASE); // MOVE ONE OF THEM DEPENDING ON HOW WE WANNA DO IT
		drawimage(CENTER OF X,CENTER OF Y + Y_OFFSET-1, IMAGE_BITMAP, DRAW);
	}
	
	drawimage(CENTER OF X,CENTER OF Y, IMAGE_BITMAP, ERASE);
	
	
	drawimageINVERTCOLORaFEW_timesREALLY_WOW_THEM(CENTER OF X,CENTER OF Y + Y_OFFSET-1, IMAGE_BITMAP, DRAW);
	
	drawimage(CENTER OF X,CENTER OF Y, IMAGE_BITMAP, ERASE);

}

void init_game(void) {
  uint8_t i;
  uint8_t j;
	//initializes black board
  for (i = 0; i < BOARD_HEIGHT; i++) {
    for (j = 0; j < BOARD_WIDTH; j++) {
      board[i][j].Color = LCD_COLOR_BLACK;
			
			board[i][j].xPos = j;
			board[i][j].yPos = i;
    }
		
		spawn_block();
  }
	
}
/* function: spawn block. spawns a random block at the top center of the screen*/
void spawn_block(void) {
	uint8_t rand =  % DISTINCT_NUM_BLOCKS;
				  if (randomNumber == 0) {
				    newBlock = SQUARE;
					  currBlockX = 4;
					  currBlockY = 5;
				  }
				  else if (randomNumber == 1) {
				    newBlock = LONGBOI;
					  currBlockX = 2;
					  currBlockY = 8;
				  }
				  else if (randomNumber == 2) {
				    newBlock = SBLOCK;
					  currBlockX = 8;
					  currBlockY = 10;
				  }
          else if (randomNumber == 3) {
				    newBlock = ZBLOCK;
					  currBlockX = 6;
					  currBlockY = 7;
				  }
		
		
	}
	
	//*currBlockX = CENTER
	//*currBlockY = 
	
}

//void spawnBlock(int8_t *currBlockY, int8_t *currBlockX, BlockType *blockType) {
//  //if (specific block type) {
//	  // modify x and y position
//  //}
		
	drawBlock(currBlockY, currBlockX, DRAW, blockType);
}

void rotateBlock(int8_t *currBlockY, int8_t *currBlockX, BlockType *blockType) {
  if (*blockType == SQUARE) {
    return;
  }
	
}

void moveBlock(int8_t *currBlockY, int8_t *currBlockX, int8_t DIRECTION, BlockType *blockType) {
  drawBlock(currBlockY, currBlockX, RESET, blockType);
	*currBlockX += DIRECTION;
	drawBlock(currBlockY, currBlockX, DRAW, blockType);
	return;
}

bool checkSurroundings(int8_t *currBlockY, int8_t *currBlockX, int8_t DIRECTION, BlockType *blockType) {
  // DEPENDING ON BLOCKTYPE IT WILL CHECK CERTAIN POSITIONS
	if (DIRECTION == -1) { // LEFT
		if (*blockType == SQUARE && *currBlockX > 0) {
			if (board[*currBlockY][*currBlockX-1].Color == LCD_COLOR_BLACK 
        && board[*currBlockY-1][*currBlockX-1].Color == LCD_COLOR_BLACK) {
				  return true;
				}
			else {
			  return false;
			}
	  }
		else if (*blockType == LONGBOI && *currBlockX > 0) {
			if (board[*currBlockY][*currBlockX-1].Color == LCD_COLOR_BLACK 
        && board[*currBlockY-1][*currBlockX-1].Color == LCD_COLOR_BLACK) {
				  return true;
				}
			else {
			  return false;
			}
	  }
	}
	else if (DIRECTION == 1) { // RIGHT
	  if (*blockType == SQUARE && *currBlockX < BOARD_WIDTH-1) {
		  if (board[*currBlockY][*currBlockX+2].Color == LCD_COLOR_BLACK 
        && board[*currBlockY-1][*currBlockX+2].Color == LCD_COLOR_BLACK) {
				  return true;
				}
			else {
			  return false;
			}
	  }
	}
	else if (DIRECTION == 2) { // DOWN
	  if (*blockType == SQUARE && *currBlockY < BOARD_HEIGHT+4) {
		  if (board[*currBlockY+1][*currBlockX].Color == LCD_COLOR_BLACK 
        && board[*currBlockY+1][*currBlockX+1].Color == LCD_COLOR_BLACK) {
				  return true;
				}
			else {
			  return false;
			}
	  }
	}
	return true;
}

// RETURNS TRUE IF BLOCK CANNOT FALL ANYMORE
// IF BLOCK CAN FALL SUCCESSFULLY, RETURN FALSE
void fallBlock(int8_t *currBlockY, int8_t *currBlockX, int8_t DIRECTION, BlockType *blockType) {
  
	drawBlock(currBlockY, currBlockX, RESET, blockType);
	*currBlockY += 1;
	drawBlock(currBlockY, currBlockX, DRAW, blockType);
	
	//return checkSurroundings(currBlockY, currBlockX, DIRECTION, blockType);
  
}

void detectLine(void) {
  int8_t i;
  int8_t j;

  int8_t k;

  bool lineFull;

  for (i = 4; i < BOARD_HEIGHT+4; i++) {
    lineFull = true;
    for (j = 0; j < BOARD_WIDTH; j++) {
      if (board[i][j].Color == LCD_COLOR_BLACK) {
        lineFull = false;
        j = BOARD_WIDTH;
      }
    }

    if (lineFull) {
      // CLEAR LINE BUT MAKE SURE IT DOESN'T CHANGE OUR INDICES

      for (k = i; k < BOARD_HEIGHT - 1; k++) {
        for (j = 0; j < BOARD_WIDTH; j++) {
          board[k][j].Color = board[k + 1][j].Color;
        }
      }

      i--; // decrement i so we still check the next line after shifting game board
    }
  }
}

bool detectLoss(void) {
  int8_t j;
  for (j = 0; j < BOARD_WIDTH; j++) {
    if (board[3][j].Color != LCD_COLOR_BLACK) { // check the headroom
      return false;
    }
  }
  return true;
}

void gameOver(void) {
  
}

//*****************************************************************************
//*****************************************************************************
extern bool alertADC;
extern bool timerDone;
extern bool buttonPressed;
extern uint16_t ps2x;
extern uint16_t ps2y;


int main(void) {
  const int8_t LEFT = -1;
  const int8_t RIGHT = 1;
	const int8_t DOWN = 2;
	
	BlockType blockType;
	int8_t currBlockX;
	int8_t currBlockY;
	
	
	
  bool blockPlaced = false;

  while (420) {

    bool mainMenu = true;
    bool gameActive = true;

    mainMenuAnimation();

    while (mainMenu) {
      // MAIN MENU
      // MAYBE THEY CAN CHOOSE FROM A VARIETY OF SIMPLE GAMES?
      if (buttonPressed) {
        buttonPressed = false;
        mainMenu = false;

      }
    }

    init_game();

    while (gameActive) {
      // MAIN GAME LOOP

      if (buttonPressed) {
        // ROTATE BLOCK
        buttonPressed = false;
        rotateBlock(&currBlockY, &currBlockX, &blockType);
      }

      if (alertADC) {
        // MOVE BLOCKS
        // maybe also allow them to use pushbuttons to move?
        alertADC = false;

        if (ps2x > 420) {
					if ( checkSurroundings(&currBlockY, &currBlockX, RIGHT, &blockType) ) {
            moveBlock(&currBlockY, &currBlockX, RIGHT, &blockType);
					}
        } 
				else if (ps2x < 420) {
          if ( checkSurroundings(&currBlockY, &currBlockX, LEFT, &blockType) ) {
            moveBlock(&currBlockY, &currBlockX, LEFT, &blockType);
					}
        } 
				else if (ps2y < 420) {
					if ( checkSurroundings(&currBlockY, &currBlockX, DOWN, &blockType) ) {
            fallBlock(&currBlockY, &currBlockX, DOWN, &blockType);
					}
					else {
					  blockPlaced = true;
					}
        } 
				else {
          // DO NOTHING
        }

      }

      if (timerDone) {
        // DROP BLOCKS AND DETECT WIN/LOSS
        if ( checkSurroundings(&currBlockY, &currBlockX, DOWN, &blockType) ) {
            fallBlock(&currBlockY, &currBlockX, DOWN, &blockType);
					}
				else {
				  blockPlaced = true;
				}
      }

      if (blockPlaced) {
				blockPlaced = false;
				
        detectLine();
        gameActive = detectLoss(); // set gameActive = false
				
				  if (gameActive) {
				  BlockType newBlock; 
				  int8_t randomNumber = wait%DISTINCT_NUM_BLOCKS;
				  if (randomNumber == 0) {
				    newBlock = SQUARE;
					  currBlockX = 4;
					  currBlockY = 5;
				  }
				  else if (randomNumber == 1) {
				    newBlock = LONGBOI;
					  currBlockX = 2;
					  currBlockY = 8;
				  }
				  else if (randomNumber == 2) {
				    newBlock = SBLOCK;
					  currBlockX = 8;
					  currBlockY = 10;
				  }
          else if (randomNumber == 3) {
				    newBlock = ZBLOCK;
					  currBlockX = 6;
					  currBlockY = 7;
				  }
					
					blockType = newBlock;
				  spawnBlock(&currBlockY, &currBlockX, &blockType);
          
        }
		  }

    }

    wait_ms(1000);
    gameOver();

    while (!mainMenu) {
      // END GAME LOOP
      if (buttonPressed) {
        buttonPressed = false;
        mainMenu = true;
        gameActive = true;
      }

    }

  }
}