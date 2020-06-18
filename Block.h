#include <iostream>
#include <cmath>
#include <vector>
#include <random>
#include <ctime>
#include "Pair.h"

#ifndef BLOCK_H
#define BLOCK_H
constexpr int BLOCKROWSIZE = 3;
constexpr int BLOCKCOLUMNSIZE = 3;



using block_t = std::vector<std::vector<int>>;
class Block;

using grid_t = std::vector<std::vector<Block>>;

class Block
{
private:
	block_t m_block;

public:
	Block();							//default constructor
	Block(const block_t& block);		//constructor to initialize from a user provided board_t
	Block(const Block& block);				//copy constructor
	Block(bool zero);					//copy constructor
	bool blockCheck(int value);			//check if value is present in this block
	friend std::ostream& operator<<(std::ostream& out, const Block& block);//printing this block
	void printBlock();//same as above line-experimental purpose
	const int memberAccess(int x, int y)const; //cell value getter 
	void memberSet(const Pair& pair, int value);	   //cell value setter
	int getRowSize();//row numbers-experimental (used for avoiding magic numbers)
	int getColumnSize();//column numbers-experimental (used for avoiding magic numbers)
	block_t& fillShuffle(block_t& block);//shuffling an existing board 
	const block_t& getBlock() const; //returning this block
	void swap(block_t& block, Pair& pair1, Pair& pair2); //swap 2 cells
	const std::vector<int> getRow(int rowIndex) const; //return whole row
	const std::vector<int> getColumn(int rowIndex) const; //return whole col
	
};


#endif // !BLOCK_H
