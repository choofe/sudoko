#include "Position.h"
#include "Header.h"

#ifndef BLOCKGRID_H
#define BLOCKGRID_H

constexpr int GRIDROWSIZE = 3;
constexpr int GRIDCOLUMNSIZE = 3;

class BlockGrid
{
private:
	grid_t m_grid;
public:
	BlockGrid();		//default constructor 
	BlockGrid(const grid_t& b);
	BlockGrid(bool zero);
	void resetToZero();
	void resetToInitial(position_t & positions);
	friend std::ostream& operator<<(std::ostream& out, BlockGrid& b);
	const Block& operator[](const Pair& x) const;
	Block& operator[](const Pair& x);
	const Block& getBlock(int x, int y) const;
	Block& getBlock(int x, int y);
	const grid_t& getGrid() const;
	
};

std::ostream& operator<<(std::ostream& out, grid_t& b);
std::ostream& operator<<(std::ostream& out, BlockGrid& b);
#endif // !BLOCKGRID_H
