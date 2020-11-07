#include <iostream>
#include <cstdint>
#include "game.h"

int main()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, 3);

    uint16_t* table;
    table = (uint16_t*) malloc(65536 * 2);
    if (table == NULL) exit(1);
    std::cout << "memory allocated" << '\n';

    buildMoveTable(table);
    std::cout << "created table" << '\n';

    uint64_t board{};
    addRandomVal(&board);
    addRandomVal(&board);
    printBoard(board);
    for (int i = 0; i<10; i++)
    {
        board = gameClock(board,table, distrib(gen));
    }

    free(table);
    std::cout << "free memory" << '\n';

    return 0;
}