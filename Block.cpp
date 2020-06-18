#include "Block.h"

Block::Block(const block_t& block) :m_block{ block } {} //in case user provide a block_t
Block::Block(const Block& copyBlock) {m_block = copyBlock.m_block;}		//copy constructor
// too lazy to think of a more intuitive way to call this constructor!
// so just throw a parameter to do so!!! 
// and this one create a int'0' filled block
// no matter zero is true or false
Block::Block(bool) 
{
	block_t temp{ block_t(BLOCKROWSIZE, std::vector<int>(BLOCKCOLUMNSIZE)) };
	m_block = temp;
}

//returns true if value is not present in this block
//returns false if value is present in this block
bool Block::blockCheck(int value)
{
	for (std::size_t i{ 0 }; i < m_block.size(); ++i)
		for (std::size_t j{ 0 }; j < m_block.at(0).size(); ++j)
		{
			if (value == m_block.at(i).at(j)) return false;
		}
	return true;
}


// create a shuffled block_t which contains digits 1~9 in a random order
Block::Block() //default constructor
{
	block_t temp{ block_t(BLOCKROWSIZE, std::vector<int>(BLOCKCOLUMNSIZE)) };
	m_block = fillShuffle(temp);
}

//shuffling method
block_t& Block::fillShuffle(block_t& blockt)
{
	//fill blockt with sorted number 1 ~ 9
	//////////////////////////////////////////
	int count{ 1 };
	for (std::size_t i{ 0 }; i < blockt.size(); ++i)
		for (std::size_t j{ 0 }; j < blockt.at(0).size(); ++j)
		{
			blockt.at(i).at(j) = count;
			++count;
		}
	///////////////////////////////////////////
	
	//shuffling sort filled blockt 
	///////////////////////////////////////////
	static std::mt19937 rand{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };
	static std::uniform_int_distribution row{ 0,static_cast<int>(blockt.size() - 1) };//uniform distribution between 0 and row size 
	static std::uniform_int_distribution column{ 0,static_cast<int>(blockt.at(0).size() - 1) };//uniform distribution between 0 and column size
	int numberOfShuffling{ 100 }; //number of shuffling-not !

	for (int i{ 0 }; i <= numberOfShuffling; ++i)
	{
		Pair p1(row(rand), column(rand));
		Pair p2(row(rand), column(rand));
		swap(blockt, p1, p2);
	}
	return blockt;
}
//swapping method
void Block::swap(block_t& blockt, Pair& p1, Pair& p2)
{
	if (p1 == p2) return;
	int temp{ 0 };
	temp = blockt.at(p1.getRow()).at(p1.getColumn());
	blockt.at(p1.getRow()).at(p1.getColumn()) = blockt.at(p2.getRow()).at(p2.getColumn());
	blockt.at(p2.getRow()).at(p2.getColumn()) = temp;
}

//returning whole rowIndex row of block
const std::vector<int> Block::getRow(int rowIndex) const
{
	std::vector<int> row;
	for (std::size_t i{ 0 }; i < m_block.size(); ++i)
		row.push_back(m_block.at(rowIndex).at(i));
	return row;
}
//returning whole rowIndex row of block
const std::vector<int> Block::getColumn(int colIndex) const
{
	std::vector<int> row;
	for (std::size_t i{ 0 }; i < m_block.at(colIndex).size(); ++i)
		row.push_back(m_block.at(i).at(colIndex));
	return row;
}

//returning basic data
const block_t& Block::getBlock() const {return m_block;}
int Block::getRowSize() { return m_block.size(); } //rows number
int Block::getColumnSize() { return m_block.at(0).size(); } //cols number
void Block::printBlock() { std::cout << *this; } //print current m_block
const int Block::memberAccess(int x, int y) const { return m_block.at(x).at(y); } //cell value in [x,y]

//setting value in pair with value
void Block::memberSet(const Pair& pair,int value)
{
	m_block.at(pair.getRow()).at(pair.getColumn()) = value;
}

//believe it or not! this overloading was necessary!!
//so I just put it here. No harm!
std::ostream& operator<<(std::ostream& out, std::ostream& in) 
{
	return in;
}

std::ostream& operator<<(std::ostream& out,const Block& block)  
{
	for (unsigned int i{ 0 }; i < block.m_block.size(); ++i)
	{
		for (unsigned int j{ 0 }; j < block.m_block[i].size(); ++j)
			out << block.m_block.at(i).at(j) << " ";
		out << '\n';
	}
	return out;
}
