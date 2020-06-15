#pragma once
#include "Block.h"
#include "BlockGrid.h"
constexpr int TOTALROWSIZE = 9; // there are total of 9 rows in a puzzle

class GridRow
{
	std::vector<int> m_gridRow;
public:
	GridRow(const BlockGrid& grid, int rowIndex);	//default constructor
	void printGridRow();							//print whole row-experimental
	bool gridRowCheck(int val);						//check if val is present in whole row
	~GridRow();
};

