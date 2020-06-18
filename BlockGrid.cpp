#include "BlockGrid.h"


// default constructor
BlockGrid::BlockGrid()
{
	
	m_grid.resize(GRIDROWSIZE);
	for (std::size_t i{ 0 }; i < GRIDROWSIZE; ++i)
		m_grid.at(i).resize(GRIDCOLUMNSIZE);
	for (std::size_t i{ 0 }; i < GRIDROWSIZE; ++i)
		for (std::size_t j{ 0 }; j < GRIDCOLUMNSIZE; ++j)
		{
			//creating a temporary block with use of default constructor of block class 
			//which makes random block
			Block temp;
			m_grid.at(i).at(j) = temp;
		}
			
}
BlockGrid::BlockGrid(const grid_t& blockGrid) //copy constructor
{
	m_grid = blockGrid;
}
// too lazy to think of a more intuitive way to call this constructor!
// so just throw a parameter to do so!!! 
// and this one create a 3x3 grid of int'0' filled blocks
//no matter zero is true or false
BlockGrid::BlockGrid(bool zero)
{
	m_grid.resize(GRIDROWSIZE);
	for (std::size_t i{ 0 }; i < GRIDROWSIZE; ++i)
		m_grid.at(i).resize(GRIDCOLUMNSIZE);
	
	for (std::size_t i{ 0 }; i < GRIDROWSIZE; ++i)
		for (std::size_t j{ 0 }; j < GRIDCOLUMNSIZE; ++j)
		{
			Block temp(true);
			m_grid.at(i).at(j) = temp;
		}

}
void BlockGrid::resetToZero()
{
	BlockGrid temp{ true };
	m_grid = temp.m_grid;
}

void BlockGrid::resetToInitial(position_t& positions)
{
	for (auto i:positions)
	{
		if (!(i.getIsInitial()))
		{
			
			m_grid.at(i.getGridRowNumber()).at(i.getGridColumnNumber()).memberSet({ i.getCellRow(),i.getCellColumn() }, 0);
		}
	}
		
}
		

const Block& BlockGrid::operator[](const Pair& x) const
{
	return m_grid[x.getRow()][x.getColumn()];
}
Block& BlockGrid::operator[](const Pair& x)
{
	return m_grid[x.getRow()][x.getColumn()];
}
//returns block in [x,y] of m_grid used when need a unknown object
const Block& BlockGrid::getBlock(int x, int y) const
{
	return m_grid.at(x).at(y);
}

// overloaded get block returning known object
Block& BlockGrid::getBlock(int x, int y) 
{
	return m_grid.at(x).at(y);
}

//returns whole grid
const grid_t& BlockGrid::getGrid() const 
{
	return m_grid;
}


std::ostream& operator<<(std::ostream& out, BlockGrid& blockGrid)
{
	out << blockGrid.m_grid;
	return out;
}

std::ostream& operator<<(std::ostream& out, grid_t& grid)
{

	for (std::size_t i{ 0 }; i < grid.size(); ++i)
	{
		out << "-------+------+-------" << '\n';
		for (int k{ 0 }; k < grid.at(0).at(0).getRowSize(); ++k)
		{
			out << '|';
			for (std::size_t j{ 0 }; j < grid.at(i).size(); ++j)
			{
				for (std::size_t l{ 0 }; l < grid.at(i).at(j).getBlock().at(0).size(); ++l)
				{
					block_t t{ grid.at(i).at(j).getBlock() };
					out << t.at(k).at(l) << ' ';
				}
				out << '|';
			}
			out << '\n';
		}

	}
	out << "-------+------+-------" << '\n';
	return out;


}