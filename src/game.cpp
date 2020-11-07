#include "game.h"

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> distrib(0, 0xF);

void swipeRow(uint8_t* row)
{
	for (int i = 3; i > 0; i--) {
		int ti = i;
		while (row[i] == 0 && ti >= 0) {
			row[i] = row[ti];
			row[ti--] = 0;
		}
	}
}

void addRow(uint8_t* row)
{
	for (int i = 3; i > 0; i--) {
		if (row[i] == row[i-1] && row[i] != 0 && row[i] != 15) {
			row[i]++;
			row[i-1] = 0;
		}
	}
}

void moveRow(uint8_t* row)
{
	swipeRow(row);
	addRow(row);
	swipeRow(row);
}

void reverseRow(uint16_t* row)
{
	*row = ((*row & 0xFF00) >> 8) | ((*row & 0x00FF) << 8);
	*row = ((*row & 0xF0F0) >> 4) | ((*row & 0x0F0F) << 4);
}

void buildMoveTable(uint16_t* table)
{
	uint8_t d[4];
	uint8_t temp[4];
	for (uint8_t i1 = 0; i1 < 16; i1++) {
		d[0] = i1;
		for (uint8_t i2 = 0; i2 < 16; i2++) {
			d[1] = i2;
			for (uint8_t i3 = 0; i3 < 16; i3++) {
				d[2] = i3;
				for (uint8_t i4 = 0; i4 < 16; i4++) {
					d[3] = i4;
					for (int i = 0; i < 4; i++) 
						temp[i] = d[i];
					moveRow(temp);
					table[((i1 * 16 + i2) * 16 + i3) * 16 + i4] = (temp[3]) + (temp[2] << 4) + (temp[1] << 8) + (temp[0] << 12);
				}
			}
		}
	}
}

void boardStateToArray(uint64_t board, uint8_t* arr)
{
	uint8_t tempArr[16];
	uint64_t boardHi = (board & hiBoardMask) >> 4;
	uint64_t boardLo = (board & loBoardMask);

	std::memcpy(tempArr, &boardHi, sizeof boardHi);
	std::memcpy(tempArr + sizeof uint64_t, &boardLo, sizeof uint64_t);
	
	int arrIndex = 8;
	for (int i = 0; i < 16; i++) {
		arr[i] = tempArr[15 - arrIndex];
		if (i % 2 == 0) arrIndex -= 8; else arrIndex += 9;
	}
}

bool addRandomVal(uint64_t* board) {
	uint8_t arr[16];
	boardStateToArray(*board, arr);
	int ch{};
	for (uint8_t e : arr)
		if (e != 0)
			ch++;
	if (ch == 15)
		return false;
	int r = distrib(gen);
	while (arr[r] != 0)
		r = distrib(gen);
	*board += 1 << (4*(15-r));
	return true;
}

void printBoard(uint64_t board) 
{
	uint8_t arr[16];
	boardStateToArray(board, arr);
	std::cout << "_____________________" << '\n';
	for (int i = 0; i < 4; i++) 
	{
		std::cout << "| ";
		for (int j = 0; j < 4; j++) {
			if (arr[i * 4 + j] < 10)
				std::cout << ' ';
			std::cout << (int)arr[i * 4 + j] << " | ";
		}
			
		std::cout << '\n';
	}
	std::cout << "---------------------" << '\n';
}

uint64_t nextBoardTable(uint64_t board, uint16_t* table, int direction)
{
	uint16_t rows[4];

	if (direction % 2 == 0) {
		uint16_t tempRows[4];
		std::memcpy(tempRows, &board, sizeof uint64_t);
		for (int i = 0; i < 4; i++) {
			rows[i] = ((tempRows[0] << (4 * i)) & 0xF000) + ((tempRows[1] << (4 * i) >> 4) & 0x0F00) 
				+ ((tempRows[2] << (4 * i) >> 8) & 0x00F0) + ((tempRows[3] << (4 * i) >> 12) & 0x000F);
		}
	}
	else
		std::memcpy(rows, &board, sizeof uint64_t);

	if (direction < 2)
		for (int i = 0; i < 4; i++)
			rows[i] = table[rows[i]];
	else
		for (int i = 0; i < 4; i++) {
			reverseRow(&rows[i]);
			rows[i] = table[rows[i]];
			reverseRow(&rows[i]);
		}
	
	uint64_t newBoard;

	if (direction % 2 == 0)
	{
		uint16_t tempRows[4];
		for (int i = 0; i < 4; i++) {
			tempRows[i] = ((rows[0] << (4 * i)) & 0xF000) + ((rows[1] << (4 * i) >> 4) & 0x0F00)
				+ ((rows[2] << (4 * i) >> 8) & 0x00F0) + ((rows[3] << (4 * i) >> 12) & 0x000F);
		}
		std::memcpy(&newBoard, tempRows, sizeof uint64_t);
	}
	else
		std::memcpy(&newBoard, rows, sizeof uint64_t);

	return newBoard;
}

int getMoveDirection()
{
	char inputChar;
	int direction{};
	std::cout << "Where to move?\n";
	std::cin >> inputChar;
	switch (inputChar)
	{
	case 'w':
		direction = 0;
		break;
	case 'd':
		direction = 1;
		break;
	case 's':
		direction = 2;
		break;
	case 'a':
		direction = 3;
	}
	return direction;
}

uint64_t gameClock (uint64_t board, uint16_t* table,int direction)
{
	
	uint64_t newBoard = nextBoardTable(board, table, direction);

	if (board != newBoard) {
		addRandomVal(&newBoard);
	}
	printBoard(newBoard);
	return newBoard;
}
/*
uint64_t nextBoard (uint64_t board, int direction)
{
	return board;
}
*/