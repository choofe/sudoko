#include "GridCol.h"


//creating a whole 9 element of 'colIndex'th col in grid
GridCol::GridCol(const BlockGrid& grid, int colIndex)
{
	int blockGridCol{ colIndex / 3 };
	m_gridCol.reserve(TOTALCOLSIZE); //avoiding resizes
	for (size_t i{ 0 }; i < GRIDCOLSIZE; ++i)
	{
		auto tempCol{ grid.getBlock(i,blockGridCol).getCol(colIndex % 3) };
		for (auto j : tempCol)
			m_gridCol.push_back(j);
	}
}


void GridCol::printGridRow()
{
	for (auto i : m_gridCol)
		std::cout << i << '\n';

}
//return true if val is not present in whole col and false otherwise
bool GridCol::gridColCheck(int val)
{
	for (int i{ 0 }; i < m_gridCol.size(); ++i)
	{
		if (val == m_gridCol.at(i)) return false;
	}
	return true;
}

GridCol::~GridCol()
{
}
