#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>
#include <random>
#include "Header.h"
#include "Block.h"
#include "BlockGrid.h"
#include "GridRow.h"
#include "GridColumn.h"
#include "Position.h"

#ifndef FUNCTIONS_H
#define FUNCTIONS_H
constexpr int CHECKISOVER = 81; //magic number for end checking whether solvable or not
std::ostream& operator<<(std::ostream& out, const block_t& blockt);
void fillRandom(BlockGrid& grid, int initiallyFilledCellNumber);
position_t initaialPositions(const BlockGrid& grid);
bool areRulesMet(const BlockGrid& grid, position_t& position, int posIndex, int checkingNumber);
bool isSolvable(BlockGrid& grid, position_t& position, int& positionIndex, int& check);
void createBlock(BlockGrid& grid, position_t& firstBlock);
void firstBlockOrder(BlockGrid& grid, position_t& position);
void nextBlockOrder(BlockGrid& grid, position_t& position);
void allIndicatorFalse(position_t& firstBlock);
void nextBlock(BlockGrid& grid, position_t& firstBlock);
bool isLastCell(position_t& positions, int iterator);
bool isFirstCell(position_t& positions, int  iterator);
void nextBlockComplete(BlockGrid& grid, position_t& firstBlock);
#endif // !FUNCTIONS_H

