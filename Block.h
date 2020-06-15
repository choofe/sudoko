#pragma once
#include <iostream>
#include <cmath>
#include <vector>
#include <random>
#include <ctime>
#include "Pair.h"

constexpr int BLOCKROWSIZE = 3;
constexpr int BLOCKCOLSIZE = 3;


#ifndef BOARD_T_H
#define BOARD_T_H
using block_t = std::vector<std::vector<int>>;
#endif // !BOARD_T_H

class Block;

#ifndef BOARDVECT_T_H
#define BOARDVECT_T_H
using grid_t = std::vector<std::vector<Block>>;
#endif // !BOARDVECT_T_H

class Block
{
private:
	block_t m_block;

public:
	Block();							//default constructor
	Block(const block_t& block);		//constructor to initialize from a user provided board_t
	Block(const Block& b);				//copy constructor
	Block(bool zero);					//copy constructor
	bool blockCheck(int val);			//check if val is present in this block
	friend std::ostream& operator<<(std::ostream& out, const Block& b);//printing this block
	void printBlock();//same as above line-experimental purpose
	const int memberAccess(int x, int y)const; //cell value getter 
	void memberSet(const Pair& p, int val);	   //cell value setter
	int getRowSize();//row numbers-experimental (used for avoiding magic numbers)
	int getColSize();//column numbers-experimental (used for avoiding magic numbers)
	block_t& fillShuffle(block_t& b);//shuffling an existing board 
	const block_t& getBlock() const; //returning this block
	void swap(block_t& b, Pair& p1, Pair& p2); //swap 2 cells
	const std::vector<int> getRow(int rowIndex) const ; //return whole row
	const std::vector<int> getCol(int rowIndex) const ; //return whole col
	~Block();
};

