#ifndef GAME_INSTANCE_TWOZERO
#define GAME_INSTANCE_TWOZERO

#include <iostream>
#include <cstdint>

static uint64_t hiBoardMask = 0xf0f0f0f0f0f0f0f0;
static uint64_t loBoardMask = 0x0f0f0f0f0f0f0f0f;

/* Move values in row to group them together
 */
void swipeRow(uint8_t* row);

/* Add adjacent values in row
 */
void addRow(uint8_t* row);

/* Move sequence on single row of game board
 */
void moveRow(uint8_t* row);

/* Reverse value of nibles in uint16_t
 */
void reverseRow(uint16_t* row);

/* Construct table of all possible moves 
 * performed on board row and their succesive score
 */
void buildMoveTable(uint16_t* table);

/* Convert uint64_t to array of nibles 
   arr pointer needs to point to uint8_t * 16 block
   (uint8_t is used because it is smalles variable type)
 */
void boardStateToArray(uint64_t board, uint8_t* arr);

/* Convert and print board state from uint64_t
 */
void printBoard(uint64_t board);

/* Next board state read from table
 */
uint64_t nextBoardTable(uint64_t board, uint16_t* table, int direction);

/* Board state after move
   DONT USE IT IT IS NOT FINISHED
   USE nextBoardTable FOR NOW
 */
//uint64_t nextBoard(uint64_t board, int direction);

#endif //GAME_INSTANCE_TWOZERO