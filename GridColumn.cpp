#include "GridColumn.h"


//creating a whole 9 element of 'columnIndex'th column in grid
GridColumn::GridColumn(const BlockGrid& grid, int colIndex)
{
	int blockGridColumn{ colIndex / 3 };
	m_gridColumn.reserve(TOTALCOLUMNSIZE); //avoiding resizes
	for (std::size_t i{ 0 }; i < GRIDCOLUMNSIZE; ++i)
	{
		auto tempColumn{ grid.getBlock(i,blockGridColumn).getColumn(colIndex % 3) };
		for (auto j : tempColumn)
			m_gridColumn.push_back(j);
	}
}


void GridColumn::printGridRow()
{
	for (auto i : m_gridColumn)
		std::cout << i << '\n';

}
//return true if value is not present in whole column and false otherwise
bool GridColumn::gridColumnCheck(int value)
{
	for (std::size_t i{ 0 }; i < m_gridColumn.size(); ++i)
	{
		if (value == m_gridColumn.at(i)) return false;
	}
	return true;
}

