#include <iostream>
#include <vector>	//for vector
#include <fstream>	//for file output
#include <random>	//for RNG
#include "Header.h" //for class and using declaration
#include "functions.h"	//non member functions
#include "Block.h"		
#include "BlockGrid.h"
#include "GridRow.h"
#include "GridColumn.h"
#include "Position.h"

extern int g_counting;//global variable for g_counting checking times. no other use. could be ignored!
extern bool g_finishedChecking;

void checkAvailable(BlockGrid& grid, position_t& position)
{
	
	for (auto& i : position)
	{

		for (auto& j : i.getAvailableChecks())
		{
			std::cout << j<<'\n';
			if (i.getValue() == j)
				std::cout << i.getIndex() << " has it\n" ;
		}

	}
}
int main()
{
	//////////////////////////////////////////////
	////this is a confirmed solvable  puzzle	//    
	////it is caught from wikipedia on sudoko	// 
	////the answer is also there				//
	//Block a{ {{5,3,0},{6,0,0},{0,9,8}} };     //   
	//Block b{ {{0,7,0},{1,9,5},{0,0,0}} };		//
	//Block c{ {{0,0,0},{0,0,0},{0,6,0}} };		//
	//Block d{ {{8,0,0},{4,0,0},{7,0,0}} };		//
	//Block e{ {{0,6,0},{8,0,3},{0,2,0}} };		//
	//Block f{ {{0,0,3},{0,0,1},{0,0,6}} };		//
	//Block g{ {{0,6,0},{0,0,0},{0,0,0}} };		//
	//Block h{ {{0,0,0},{4,1,9},{0,8,0}} };		//
	//Block i{ {{2,8,0},{0,0,5},{0,7,9}} };		//
	//											//
	////creating grid of blocks					//
	//grid_t gr{ {{a,b,c},{d,e,f},{g,h,i}} };	//
	//BlockGrid test{ gr };						//
	////to use this table uncomment out this	//
	////block and comment out the following two //
	////two lines below							//
	//////////////////////////////////////////////

	////////////////////////////////////////////
	//this is a confirmed solvable  puzzle	//    
	//it is caught from						// 
	//https://theconversation.com/good-at-sudoku-heres-some-youll-never-complete-5234 
	//the answer is also there				//
	Block a{ {{0,0,0},{1,0,0},{0,0,0}} };     //   
	Block b{ {{7,0,0},{0,0,0},{4,3,0}} };		//
	Block c{ {{0,0,0},{0,0,0},{2,0,0}} };		//
	Block d{ {{0,0,0},{0,0,0},{0,0,0}} };		//
	Block e{ {{0,0,0},{5,0,9},{0,0,0}} };		//
	Block f{ {{0,0,6},{0,0,0},{4,1,8}} };		//
	Block g{ {{0,0,0},{0,0,2},{0,4,0}} };		//
	Block h{ {{0,8,1},{0,0,0},{0,0,0}} };		//
	Block i{ {{0,0,0},{0,5,0},{3,0,0}} };		//
												//
	//creating grid of blocks					//
	grid_t gr{ {{a,b,c},{d,e,f},{g,h,i}} };	//
	BlockGrid test{ gr };						//
	//to use this table uncomment out this	//
	//block and comment out the following two //
	//two lines below							//
	////////////////////////////////////////////
	
	//////////////////////////////////////////////
	////this is a confirmed solvable  puzzle	//    
	////it is caught from						// 
	////https://theconversation.com/good-at-sudoku-heres-some-youll-never-complete-5234 
	////the answer is also there				//
	//Block a{ {{0,0,0},{0,0,0},{0,0,0}} };     //   
	//Block b{ {{0,0,0},{0,0,0},{0,0,0}} };		//
	//Block c{ {{0,0,0},{0,0,0},{0,0,0}} };		//
	//Block d{ {{0,0,0},{0,0,0},{0,0,0}} };		//
	//Block e{ {{0,0,0},{0,0,0},{0,0,0}} };		//
	//Block f{ {{0,0,0},{0,0,0},{0,0,0}} };		//
	//Block g{ {{0,0,0},{0,0,0},{0,0,0}} };		//
	//Block h{ {{0,0,0},{0,0,0},{0,0,0}} };		//
	//Block i{ {{0,0,0},{0,0,0},{0,0,0}} };		//
	//											//
	////creating grid of blocks					//
	//grid_t gr{ {{a,b,c},{d,e,f},{g,h,i}} };	//
	//BlockGrid test{ gr };						//
	////to use this table uncomment out this	//
	////block and comment out the following two //
	////two lines below							//
	//////////////////////////////////////////////
	//BlockGrid test(true);//create zero filled grid -- no matter true or false it just called that constructor
	//fillRandom(test,29); // this can be used to create random initial puzzle
	std::cout << test;
	position_t positions{ initaialPositions(test) }; //initializing every cell data withe the initial puzzle
	position_t blockZero{};
	blockZero.reserve(9);
	for (int i{ 0 }; i < 21; i += 9)
	{
		blockZero.push_back(positions.at(i));
		blockZero.push_back(positions.at(i + 1));
		blockZero.push_back(positions.at(i + 2));
	}
	

	
	std::vector<Position>::iterator it{ blockZero.begin() };

	firstBlockOrder(test, blockZero);
	std::cout << test;
	int counting{ 1 };
	for (int i{ 1 }; i < 500000; ++i)
	{
		if (i == 322558)
		{
			std::cout << "";
		}
		nextBlockComplete(test, blockZero);
		//nextBlockComplete(test, blockZero);
		++counting;
		if (counting % 1 == 0)
			std::cout << test.getBlock(0, 0) << "-----\n" << i << '\n';
		if (g_finishedChecking)
			break;

	}

	int positionIndex{ 0 };//starting the checks from the first cell
	// finding first non initial empty cell on grid
	int firstEmpty{ 0 };
	while (positions.at(firstEmpty).getIsInitial() == true) ++firstEmpty;
	positionIndex = firstEmpty;
	int check{ positions.at(firstEmpty).getAvailableChecks().at(0) }; //starting check number it will change through the process
	int solutionCount{ 0 };
	int puzzleCount{ 0 };
	if (isSolvable(test, positions, positionIndex, check)) //calling checking loop!
		std::cout << test << '\n' << g_counting << '\n';
	else
	{
		std::cout << "Not OK\n" << g_counting << '\n' << test;
	}
	checkAvailable(test, positions);
	while (puzzleCount <= 0)
	{
		g_counting = 0;
		while (check <= 9)
		{
			if (solutionCount > 1) break;
			if (isSolvable(test, positions, positionIndex, check)) //calling checking loop!
			{
				++solutionCount;
				std::cout << test;
				check = positions.at(firstEmpty).getValue() + 1;
				test.resetToInitial(positions);
				positions = initaialPositions(test);
				positionIndex = firstEmpty;
			}
			else
			{
				test.resetToInitial(positions);
				positions = initaialPositions(test);
				positionIndex = firstEmpty;
				++check;
			}
		}
		if (solutionCount == 1)
		{
			int writeToFile{ 0 };

			std::cin >> writeToFile;
			if (writeToFile)
			{
				std::cout << "There is a unique solution\n";
				std::ofstream outfile{ "puzzle.txt",std::ios::app };
				outfile << test;
				outfile.close();
				++puzzleCount;
			}

		}

		else
		{
			if (solutionCount >= 1)
				std::cout << "There are more that one solution";
			else
				std::cout << "No solution found\n";
		}

		test.resetToZero();
		fillRandom(test, 29);
		firstEmpty = 0;
		while (positions.at(firstEmpty).getIsInitial() == true) ++firstEmpty;
		positionIndex = firstEmpty;
		positions = initaialPositions(test);
		solutionCount = 0;
		check = 1;


	}


	return 0;
}