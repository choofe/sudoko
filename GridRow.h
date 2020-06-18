#include "Block.h"
#include "BlockGrid.h"

#ifndef GRIDROW_H
#define GRIDROW_H
constexpr int TOTALROWSIZE = 9; // there are total of 9 rows in a puzzle

class GridRow
{
	std::vector<int> m_gridRow;
public:
	GridRow(const BlockGrid& grid, int rowIndex);	//default constructor
	void printGridRow();							//print whole row-experimental
	bool gridRowCheck(int value);					//check if value is present in whole row
	~GridRow();
};

#endif // !GRIDROW_H

