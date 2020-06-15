#pragma once
#include "Block.h"
#include "BlockGrid.h"
constexpr int TOTALCOLSIZE = 9; // there are total of 9 cols in a puzzle

class GridCol
{
	std::vector<int> m_gridCol;						
public:
	GridCol(const BlockGrid& grid, int colIndex);	//default constructor
	void printGridRow();							//print whole row-experimental
	bool gridColCheck(int val);						//check if val is present in whole row
	~GridCol();
};
