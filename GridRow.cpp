#include "GridRow.h"
#include "BlockGrid.h"


//creating a whole 9 element of 'rowIndex'th row in grid
GridRow::GridRow(const BlockGrid& grid, int rowIndex)
{
	int blockGridRow{ rowIndex / 3 };
	m_gridRow.reserve(TOTALROWSIZE); //avoiding resizes
	for (std::size_t i{ 0 }; i < GRIDROWSIZE; ++i)
	{
		auto tempRow{ grid.getBlock(blockGridRow,i).getRow(rowIndex % 3) };
		for (auto j : tempRow)
			m_gridRow.push_back(j);
	}
}

void GridRow::printGridRow()
{
	for (auto i : m_gridRow)
		std::cout << i << " ";
}

//return true if value is not present in whole row and false otherwise
bool GridRow::gridRowCheck(int value)
{
	for (std::size_t i{ 0 }; i < m_gridRow.size(); ++i)
	{
		if (value == m_gridRow.at(i)) return false;
	}
	return true;
}

