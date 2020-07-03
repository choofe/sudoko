#include "Block.h"
#include "BlockGrid.h"

#ifndef GRIDCOLUMN_H
#define GRIDCOLUMN_H
constexpr int TOTALCOLUMNSIZE = 9; // there are total of 9 cols in a puzzle

class GridColumn
{
	std::vector<int> m_gridColumn;
public:
	GridColumn(const BlockGrid& grid, int columnIndex);	//default constructor
	void printGridRow();							//print whole row-experimental
	bool gridColumnCheck(int value);						//check if value is present in whole row
};

#endif // !GRIDCOLUMNUMN_H
