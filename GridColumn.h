#include "Block.h"
#include "BlockGrid.h"
#ifndef GRIDCOLUMN_H
#define GRIDCOLUMN_H
constexpr int TOTALCOLSIZE = 9; // there are total of 9 cols in a puzzle

class GridColumn
{
	std::vector<int> m_gridColumn;
public:
	GridColumn(const BlockGrid& grid, int colIndex);	//default constructor
	void printGridRow();							//print whole row-experimental
	bool gridColumnCheck(int value);						//check if value is present in whole row
	~GridColumn();
};

#endif // !GRIDCOLUMN_H
