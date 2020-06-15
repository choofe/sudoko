#include "BlockGrid.h"


// default constructor
BlockGrid::BlockGrid()
{
	m_grid.resize(GRIDROWSIZE);
	for (size_t i{ 0 }; i < GRIDROWSIZE; ++i)
		m_grid.at(i).resize(GRIDCOLSIZE);
	for (size_t i{ 0 }; i < GRIDROWSIZE; ++i)
		for (size_t j{ 0 }; j < GRIDCOLSIZE; ++j)
		{
			//creating a temporary block with use of default costructor of block class 
			//which makes random block
			Block temp;
			m_grid.at(i).at(j) = temp;
		}
			
}
BlockGrid::BlockGrid(const grid_t& b) //copy constructor
{
	m_grid = b;
}
// too lazy to think of a more intuitive way to call this constructor!
// so just throw a parameter to do so!!! 
// and this one create a 3x3 grid of int'0' filled blocks
//no matter zero is true or false
BlockGrid::BlockGrid(bool zero)
{
	m_grid.resize(GRIDROWSIZE);
	for (size_t i{ 0 }; i < GRIDROWSIZE; ++i)
		m_grid.at(i).resize(GRIDCOLSIZE);
	
	for (size_t i{ 0 }; i < GRIDROWSIZE; ++i)
		for (size_t j{ 0 }; j < GRIDCOLSIZE; ++j)
		{
			Block temp(true);
			m_grid.at(i).at(j) = temp;
		}

}
//returns block in [x,y] of m_grid used when need a unknown object
const Block& BlockGrid::getBlock(int x, int y) const
{
	return m_grid.at(x).at(y);
}

// overloaded getblock returning known object
Block& BlockGrid::getBlock(int x, int y) 
{
	return m_grid.at(x).at(y);
}

//returns whole grid
const grid_t& BlockGrid::getGrid() const 
{
	return m_grid;
}

BlockGrid::~BlockGrid()
{
}

std::ostream& operator<<(std::ostream& out, BlockGrid& b)
{
	out << b.m_grid;
	return out;
}

std::ostream& operator<<(std::ostream& out, grid_t& b)
{

	for (size_t i{ 0 }; i < b.size(); ++i)
	{
		out << "-------+------+-------" << '\n';
		for (size_t k{ 0 }; k < b.at(0).at(0).getRowSize(); ++k)
		{
			out << "|";
			for (size_t j{ 0 }; j < b.at(i).size(); ++j)
			{
				for (size_t l{ 0 }; l < b.at(i).at(j).getBlock().at(0).size(); ++l)
				{
					block_t t{ b.at(i).at(j).getBlock() };
					out << t.at(k).at(l) << " ";
				}
				out << "|";
			}
			out << '\n';
		}

	}
	out << "-------+------+-------" << '\n';
	return out;


}