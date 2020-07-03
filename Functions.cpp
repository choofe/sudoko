#include "functions.h"
#include "Algorithm.h"
#include "Header.h"
bool g_finishedChecking{ false };
std::ostream& operator<<(std::ostream& out, const block_t& blockt)   //overloading << operator to print out a block of 1~9
{
	for (std::size_t i{ 0 }; i < blockt.size(); ++i)
	{
		for (std::size_t j{ 0 }; j < blockt.at(i).size(); ++j)
		{
			out << blockt.at(i).at(j) << " ";
		}
		out << '\n';
	}
	out << '\n';
	return out;
}

//fill random cells of 'grid' with random value 1~9 and checks if it is acceptable in terms of sudoko 
//to form an initial puzzle. there is a magic number on line 32 >> determines how many 
//initial cells to be filled initially
void fillRandom(BlockGrid& grid, int initiallyFilledCellNumber = 25)
{
	static std::mt19937 rand{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };
	static std::uniform_int_distribution digit{ 1,9 };//uniform distribution bet
	static std::uniform_int_distribution cell{ 0,80 };//uniform distribution bet
	// magic number! i < VVVV determines how many initial cells would be pre-filled in puzzle
	for (int i{ 1 }; i <= initiallyFilledCellNumber; ++i)
	{
		int randValue{ digit(rand) };			//random value to inset on grid
		int randCell{ cell(rand) };				//random firstBlock from 0~80 representing cells
		int gridRowNumber{ randCell / 27 };		// block row firstBlock in block grid vector
		int gridColumnNumber{ (randCell % 9) / 3 };	//block column firstBlock in block grid vector
		int cellRow{ (randCell / 9) % 3 };		//cell row in block vector
		int cellColumn{ (randCell % 9) % 3 };		//cell column in block vector
		int totalRowIndex{ randCell / 9 };		//index of row in block grid
		int totalColumnIndex{ randCell % 9 };		//index of column in block grid

		//check if there is already a number and the rules are not broken if
		//fill the cell with randValue
		if (grid.getBlock(gridRowNumber, gridColumnNumber).memberAccess(cellRow, cellColumn) == 0 &&
			grid.getBlock(gridRowNumber, gridColumnNumber).blockCheck(randValue) &&
			GridRow(grid, totalRowIndex).gridRowCheck(randValue) &&
			GridColumn(grid, totalColumnIndex).gridColumnCheck(randValue))
		{
			grid.getBlock(gridRowNumber, gridColumnNumber).memberSet({ cellRow,cellColumn }, randValue); //fill cell with randValue
		}
		else //put counter one back because this failed iteration should not be count!
		{
			--i;
		}

	}
}

//fill a vector of class Position with each of 81 cell data 
//in the grid.
position_t initaialPositions(const BlockGrid& grid)
{
	const grid_t& gridVector{ grid.getGrid() };
	position_t initial;

	initial.reserve(81);//increase vector to 82 to reduce resizings

	for (std::size_t i{ 0 }; i < 81; ++i) //fill initial values with 0 as empty cells
		initial.push_back({ Position(i, 0) });

	for (auto& i : initial)
	{
		///////////////////////////////////////////////////////////
		// fetch the value on grid in "i"th firstBlock . 
		//"i" have been already converted to grid row and cell and cell row and 
		//column and stored in i th member of vector initial
		//////////////////////////////////////////////////////////
		int value{ gridVector.at(i.getGridRowNumber()).at(i.getGridColumnNumber()).getBlock().at(i.getCellRow()).at(i.getCellColumn()) };
		if (value != 0)// if there is an initial number in cell
		{
			i.setValue(value);//store the value
			i.setIsInitialNumber(true);//mark the firstBlock as initial.
			i.m_availableChecks.push_back(value);//as it is a initial cell there is only one available check!
			i.m_availableCheckIndicator.push_back(false);
		}
		else
		{// fill the Position::m_availableChecks with possible candidate
			for (int checks{ 1 }; checks <= 9; ++checks)
				if (areRulesMet(grid, initial, i.getIndex(), checks))
				{
					i.m_availableChecks.push_back(checks);
					i.m_availableCheckIndicator.push_back(false);
				}
		}
	}
	return initial;
}

//checks the rules of sudoko 
//checks if 'checkingNum' in cell with 'positionIndex' in 'grid' is a correct answer
//returns true id it is and false if it isn't
bool areRulesMet(const BlockGrid& grid, position_t& position, int posIndex, int checkingNumber)
{
	if (checkingNumber == 0) return false;
	Position& currentPosition{ position.at(posIndex) };
	return (
		checkingNumber <= 9
		&& grid.getBlock(currentPosition.getGridRowNumber(), currentPosition.getGridColumnNumber()).blockCheck(checkingNumber)
		&& GridRow(grid, currentPosition.getTotalRowIndex()).gridRowCheck(checkingNumber)
		&& GridColumn(grid, currentPosition.getTotalColumnIndex()).gridColumnCheck(checkingNumber)
		);
}

bool isSolvable(BlockGrid & grid, position_t & position, int& positionIndex, int& check)
{
	for (auto& i : position)
	{//If there is only one cell that have no possible candidate so the puzzle is unsolvable 
		if (i.getAvailableChecks().size() == 0) return false;
	}
	while (positionIndex <= 80)
	{
		isCorrect(grid, position, positionIndex, check);
		if ((positionIndex < 0 || positionIndex == CHECKISOVER))
		{
			positionIndex = CHECKISOVER;
			break;
		}
		//std::cout << positionIndex << " " << check << '\n';
	}
	bool allDone{ true };
	for (auto i : position) //check if all cells are filled!
		if (i.getValue() == 0) allDone = false;
	return (allDone) ? true : false;
}

void allIndicatorFalse(position_t& firstBlock)
{
	for (auto& i : firstBlock)
	{
		for (std::size_t j{ 0 }; j < i.getAvailableCheckIndicator().size();++j)
		{
			i.getAvailableCheckIndicator()[j] = false;
		}
	}
}
bool isFirstCell(position_t& positions, int  iterator)
{
	return (iterator == 0);
}
bool isLastCell(position_t& positions, std::size_t iterator)
{
	return (iterator >= positions.size() - 1);
}
int debug{ 0 };
void firstBlockOrder(BlockGrid& grid, position_t& firstBlock)
{
	
	for (auto& k : firstBlock)
	{
		int value{ grid.getGrid().at(k.getGridRowNumber()).at(k.getGridColumnNumber()).getBlock().at(k.getCellRow()).at(k.getCellColumn()) };
		if (value != 0)// if there is an initial number in cell
		{
			k.setValue(value);//store the value
		}
	}

	std::vector<Position>::iterator it{ firstBlock.begin() };
	while (it != firstBlock.end())
	{

		if (!it->getIsInitial())
		{
			bool onePossibleRight{ false };
			for (auto& j : it->getAvailableChecks())
			{
				if ((j >= it->getAvailableChecks().at(it->getCheckIndex())))
				{
					//std::cout << it->getValue() << '\n';
					if (it->getValue() == 0
						&& grid.getBlock(0,0).blockCheck(j)
						&& GridRow(grid, it->getTotalRowIndex()).gridRowCheck(j)
						&& GridColumn(grid, it->getTotalColumnIndex()).gridColumnCheck(j)
						)
					{
						grid.getBlock(it->getGridRowNumber(), it->getGridColumnNumber()).memberSet({ it->getCellRow(),it->getCellColumn() }, j);
						it->setValue(j);
						onePossibleRight = true;
						
						break;
					}
					else
					{
						it->goToNextCheck();
					}
				}
			}
			if (!onePossibleRight)
			{
				it->setValue(0);
				grid.getBlock(it->getGridRowNumber(), it->getGridColumnNumber()).memberSet({ it->getCellRow(),it->getCellColumn() }, 0);
				--it;
				while (it->getIsInitial() || !(static_cast<std::size_t>(it->getCheckIndex()) < it->getAvailableChecks().size() - 1))
				{
					if (!it->getIsInitial())
					{
						grid.getBlock(it->getGridRowNumber(), it->getGridColumnNumber()).memberSet({ it->getCellRow(),it->getCellColumn() }, 0);
						it->setValue(0);
						it->goToFirstCheck();
					}
					--it;
					it->goToNextCheck();
				}
			}
			else
			{
				++it;

			}
		}
		else
		{
		++it;
		}
	}
	//for (auto i : firstBlock)		std::cout << i.getValue() << '\n';
}
void nextBlock(BlockGrid& grid, position_t& firstBlock)
{
	if (g_finishedChecking)
		return;
	allIndicatorFalse(firstBlock);//all indicators to false
	int it{static_cast<int>( firstBlock.size() - 1) }; //set iterator to last cell
	int tempIt{ 0 };
	while (true)
	{
		if (it < 0 )
		{
			firstBlock[it + tempIt].makeThisAvailablecheck(true);
			std::cout << "seems all checks are done\n";
			g_finishedChecking = true;
			return;
		}
		Position& i{ firstBlock[it] };
		
		if (i.getIsInitial())////if cell is initial
		{
			++tempIt;
			--it;
			if (it < 0)
			{
				g_finishedChecking = true;
				return;
			}
			continue;
		}////if cell is initial
		//////////////
		if (i.isThereMoreNumber())// more numbers available in this current cell---problematic
		{
			int availabelCounter{ 0 };
			int check{ i.getAvailableChecks()[i.getCheckIndex()] };
			while (!areRulesMet(grid, firstBlock, it, check)) 
			{
				++availabelCounter;
				if (i.getCheckIndex() + availabelCounter == i.getAvailableChecks().size())
				{
					grid.getBlock(0, 0).memberSet({ i.getCellRow(),i.getCellColumn() }, 0);
					i.setValue(0);
					i.goToFirstCheck();
					++tempIt;
					--it;
					break;
				}
				check = i.getAvailableChecks()[i.getCheckIndex() + availabelCounter];

			}//while
			
			if (areRulesMet(grid, firstBlock, it, check))
			{
				i.setValue(check);
				grid.getBlock(0, 0).memberSet({ firstBlock[it].getCellRow(),firstBlock[it].getCellColumn() }, check);
				i.setCheckIndex(i.getCheckIndex() + availabelCounter);
				i.makeThisAvailablecheck(true);
				break;
			}
			else //there are more numbers to check but current check failed
			{
				
				continue;
				
			}
		}//end of if there are more numbers
		//////////////////////////
		else//if there is no more available check
		{
			if(isFirstCell(firstBlock,it) ) // if current cell has no more checks and is first 
			{
				std::cout << "seems all checks are done\n";
				break;
			}
			else //if current cell has no more checks and is not first 
			{

				grid.getBlock(0, 0).memberSet({ i.getCellRow(),i.getCellColumn() }, 0);
				i.setValue(0);
				i.goToFirstCheck();
				++tempIt;
				--it;
				while (firstBlock[it].getIsInitial() && !isFirstCell(firstBlock, it))
				{
					if (!firstBlock[it].getIsInitial())
					{
						grid.getBlock(0, 0).memberSet({ firstBlock[it].getCellRow(),firstBlock[it].getCellColumn() }, 0);
						firstBlock[it].goToFirstCheck();
					}
					--it;
				}
				//firstBlock[it].goToNextCheck();/////--->>> this is the problem ***********
				continue;
			}//end of if current cell has no more checks  is not first or last
		}
	}

	bool flagRaised{ false };
	for (auto& i : firstBlock)
	{
		if (i.flagState())
		{
			i.setValue(i.getAvailableChecks()[i.getCheckIndex()]);
			flagRaised = true;
		}
		else if (flagRaised)
		{
			if (!i.getIsInitial())
				i.setValue(0);
		}
	}
	Block block(firstBlock);
	grid.getBlock(0, 0) = block;

}
void nextBlockComplete(BlockGrid& grid, position_t& firstBlock)
{
	
	nextBlock(grid, firstBlock);
	if (g_finishedChecking)
		return;
	//std::vector<Position>::iterator it{ firstBlock.begin() };
	int it{ 0 };
	for (it; static_cast<std::size_t>(it) < firstBlock.size()-1; ++it)// find the last filled cell by nextBlock()
	{
		if (firstBlock[it].flagState())
		{
			break;
		}
	}//for
	if (it >= 9) return;
	if (it == 0 && !firstBlock[it].isThereMoreNumber())
	{
		std::cout << "finished permutation\n";
		return;
	}
	
	++it;//first empty cell!  otherwise 
	
	if (it == 8 && firstBlock[it].getValue() != 0)
	{
		return;
	}
	//std::cout << grid;

		++debug;
	while (true)//main filling loop
	{
		if (debug == 19540)
		{
			std::cout << "";
		}
		//std::cout << grid;
		Position& i{ firstBlock[it] };

		if (i.getIsInitial())//if cell is initial!
		{
			++it;
			continue;
		}//if
		//////////////
		int availabelCounter{ 0 };
		int check{ i.getAvailableChecks()[i.getCheckIndex()] };
		while (!areRulesMet(grid, firstBlock, it, check))
		{
			++availabelCounter;
			if (i.getCheckIndex() + availabelCounter == i.getAvailableChecks().size())
			{
				grid.getBlock(0, 0).memberSet({ i.getCellRow(),i.getCellColumn() }, 0);
				i.setValue(0);
				i.goToFirstCheck();
				--it;
				check = 0;
				break;
			}
			check = i.getAvailableChecks()[i.getCheckIndex() + availabelCounter];
		}//while
		if (areRulesMet(grid, firstBlock, it, check))//////////
		{
			i.setValue(check);
			grid.getBlock(0, 0).memberSet({ firstBlock[it].getCellRow(),firstBlock[it].getCellColumn() }, check);
			
			i.setCheckIndex(i.getCheckIndex() + availabelCounter);
			++it;
			if (it > 8) break;
			continue;
		}
		else
		{
			while (!firstBlock[it].isThereMoreNumber() || firstBlock[it].getIsInitial())
			{
				if (!firstBlock[it].getIsInitial())
				{
					grid.getBlock(0, 0).memberSet({ firstBlock[it].getCellRow(),firstBlock[it].getCellColumn() }, 0);
					firstBlock[it].setValue(0);
					firstBlock[it].setCheckIndex(0);
				}
				--it;
				if (it < 0) break;
			}
			if (it < 0) break;
			if (firstBlock[it].isThereMoreNumber())
			{
				firstBlock[it].setCheckIndex(firstBlock[it].getCheckIndex() + 1);////is problem?
				continue;
			}

		}

		
	}

}


void createBlock(BlockGrid& grid, position_t& firstBlock)
{
	for (auto i : firstBlock)
	{
		for (auto j : i.getAvailableCheckIndicator())
		{
			j = false;
		}
	}
	

	std::size_t it{ firstBlock.size() - 1 };
	while (true)
	{
		Position& i{ firstBlock[it] };
		
		if (i.getIsInitial())
		{
			--it;
			continue;
		}
		if (i.isThereMoreNumber() && !i.getIsInitial())
		{
			std::size_t c{ 1 };
			int check{ i.getAvailableChecks()[i.getCheckIndex() + c] };
			int tempCheckIndex{ i.getCheckIndex() };
			while (!areRulesMet(grid, firstBlock, it, check) && (i.getCheckIndex() + c < i.getAvailableChecks().size()))
			{
				check = i.getAvailableChecks()[i.getCheckIndex() + c];
				++tempCheckIndex;
				++c;
			}//while

			while (i.getCheckIndex() != tempCheckIndex)
			{
				i.goToNextCheck();
			}
			if (static_cast<std::size_t>(i.getCheckIndex()) < i.getAvailableChecks().size())
			{
				if (static_cast<std::size_t>(i.getCheckIndex()) < i.getAvailableChecks().size() - 1)
				{
					int step{ i.getAvailableChecks()[i.getCheckIndex()] };
					firstBlock[it].goToNextCheck();
					firstBlock[it].makeThisAvailablecheck(true);
					firstBlock[it].setValue(step);
					grid.getBlock(0, 0).memberSet({ firstBlock[it].getCellRow(),firstBlock[it].getCellColumn() }, step);
					break;
				}
				else
				{
					grid.getBlock(0, 0).memberSet({ firstBlock[it].getCellRow(),firstBlock[it].getCellColumn() }, 0);
					firstBlock[it].setValue(0);
					i.goToFirstCheck();
					--it;
					firstBlock[it].goToNextCheck();
				}
			}//if
			else
			{
				if (!firstBlock[it].getIsInitial())
				{
					grid.getBlock(0, 0).memberSet({ firstBlock[it].getCellRow(),firstBlock[it].getCellColumn() }, 0);
					firstBlock[it].setValue(0);
					i.goToFirstCheck();
				}
				if (it != 0)
				{
					--it;
					continue;
				}
				else
				{
					break;
				}
			}//else

		}//if
		else
		{
			if (!i.getIsInitial())
			{
				i.setValue(0);
				grid.getBlock(0, 0).memberSet({ i.getCellRow(),i.getCellColumn() }, 0);
				i.goToFirstCheck();
				--it;
			}
			else
			{
				--it;
			}
			//firstBlock[it].goToNextCheck();
			continue;
		}
	}//while




	///////////////////////////
	/*Position& i{ firstBlock[it] };
	if (!(i.isThereMoreNumber()) && !(i.getIsInitial()))
	{
		if (i.isThereMoreNumber())
		{
			i.makeThisAvailablecheck(false);
			int c{ 1 };
			int check{ i.getAvailableChecks()[i.getCheckIndex() + c] };

			while (!(grid.getBlock(0, 0).blockCheck(check)
				|| GridRow(grid, i.getTotalRowIndex()).gridRowCheck(check)
				|| GridColumn(grid, i.getTotalColumnIndex()).gridColumnCheck(check))
				&& (i.getCheckIndex() + c < i.getAvailableChecks().size()))
			{
				++c;
				i.goToNextCheck();
			}
			if (i.getCheckIndex() + c < i.getAvailableChecks().size())
			{
				firstBlock[it].makeThisAvailablecheck(true);
				break;
			}
			else
			{
				i.goToFirstCheck();
				--it;
				continue;
			}
		}
		else
		{
			i.makeThisAvailablecheck(false);
			i.goToFirstCheck();
			--it;
			while (!firstBlock[it].isThereMoreNumber())
			{
				firstBlock[it].goToFirstCheck();
				--it;
			}
			int check{ firstBlock[it].getAvailableChecks()[firstBlock[it].getCheckIndex()] };
			if ((grid.getBlock(0, 0).blockCheck(check)
				&& GridRow(grid, firstBlock[it].getTotalRowIndex()).gridRowCheck(check)
				&& GridColumn(grid, firstBlock[it].getTotalColumnIndex()).gridColumnCheck(check)
				))
			{
				firstBlock[it].makeThisAvailablecheck(false);
				firstBlock[it].goToNextCheck();
				firstBlock[it].makeThisAvailablecheck(true);

				break;
			}
			else
			{

				continue;
			}
		}


	}

}*/
	bool flagRaised{ false };
	for (auto& i : firstBlock)
	{
		if (i.flagState())
		{
			i.setValue(i.getAvailableChecks()[i.getCheckIndex()]);
			flagRaised = true;
		}
		else if (flagRaised)
		{
			if(!i.getIsInitial())
			i.setValue(0);
		}
	}
	Block block(firstBlock);
	grid.getBlock(0, 0) = block;

}
void nextBlockOrder(BlockGrid& grid, position_t& firstBlock)
{
	nextBlock(grid,firstBlock);
	//std::cout << grid;
	if (!firstBlock.at(0).isThereMoreNumber())
	{
		std::cout << "no more order for 1st block!\n";
		return;
	}
	//grid.resetToInitial(firstBlock);
	//for (auto& k : firstBlock) // reset 1st block to initial
	//{
	//	int value{ grid.getGrid().at(k.getGridRowNumber()).at(k.getGridColumnNumber()).getBlock().at(k.getCellRow()).at(k.getCellColumn()) };
	//	if (value != 0)// if there is an initial number in cell
	//	{
	//		k.setValue(value);//store the value
	//	}
	//}

	std::vector<Position>::iterator it{ firstBlock.begin() };
	//while (it != firstBlock.end() && !it->flagState())
	for (it; it < firstBlock.end() ; ++it)
	{
		if (it->flagState())
		{
			it->makeThisAvailablecheck(false);
			break;
		}
	}
	

	++it;
	while (it != firstBlock.end() && it != firstBlock.begin())
	{
		if (it->getIsInitial())
		{
			++it;
		}//if is initial
		else
		{
			int check{ it->getAvailableChecks()[it->getCheckIndex()] };
			while (!areRulesMet(grid, firstBlock, it - firstBlock.begin(), check))
			{
				if (it->isThereMoreNumber())
				{
					it->goToNextCheck();
					check = it->getAvailableChecks()[it->getCheckIndex()];
					
				}//if
				else
				{
					if (it < firstBlock.end() - 1 && it >= firstBlock.begin() + 1)
					{
						it->goToFirstCheck();
						--it;

						continue;
						//if (it->isThereMoreNumber())
						//{
						//	it->goToNextCheck();
						//	check = it->getAvailableChecks()[it->getCheckIndex()];
						//	continue;
						//}
						//else//is not first or last one but no more checks!!!
						//{///////////////\\\\\\\\\//
						//	it->goToFirstCheck();
						//	grid.getBlock(it->getGridRowNumber(), it->getGridColumnNumber()).memberSet({ it->getCellRow(),it->getCellColumn() }, 0);
						//	it->setValue(0);
						//	--it;
						//	if (!it->getIsInitial())
						//	{
						//		it->goToNextCheck();
						//		check = it->getAvailableChecks()[it->getCheckIndex()];
						//		grid.getBlock(it->getGridRowNumber(), it->getGridColumnNumber()).memberSet({ it->getCellRow(),it->getCellColumn() }, check);
						//		it->setValue(check);
						//		continue;
						//	}
						//	else
						//	{
						//		--it;
						//		continue;
						//	}
						//}
					}//if 'it' is in the range
					else
					{
						break;
					}//else if 'it' is NOT in the range
				}//else

			}//while
			if (it < firstBlock.end()  && it >= firstBlock.begin() )
			{
				check = it->getAvailableChecks()[it->getCheckIndex()];
				grid.getBlock(it->getGridRowNumber(), it->getGridColumnNumber()).memberSet({ it->getCellRow(),it->getCellColumn() }, check);
				it->setValue(check);
				if (it == firstBlock.end() || it == firstBlock.begin())
					break;
				else
				{
					++it;
					//it->makeThisAvailablecheck(true);
					continue;
				}
			}//if
			else
			{
				std::cout << "no more checks!!!!\n";
				break;
			}//else

		}//else(is initial)


	}//main while
		
		
		
	//	//////////////////////////////////
	//	if (!it->getIsInitial())
	//	{
	//		bool onePossibleRight{ false };
	//		for (auto& j : it->getAvailableChecks())
	//		{
	//			if (it->isThereMoreNumber()&&(j >= it->getAvailableChecks().at(it->getCheckIndex())))
	//			{
	//				//std::cout << it->getValue() << '\n';
	//				if (it->getValue() == 0
	//					&& grid.getBlock(0, 0).blockCheck(j)
	//					&& GridRow(grid, it->getTotalRowIndex()).gridRowCheck(j)
	//					&& GridColumn(grid, it->getTotalColumnIndex()).gridColumnCheck(j)
	//					)
	//				{
	//					grid.getBlock(it->getGridRowNumber(), it->getGridColumnNumber()).memberSet({ it->getCellRow(),it->getCellColumn() }, j);
	//					it->setValue(j);
	//					onePossibleRight = true;

	//					break;
	//				}
	//				else
	//				{
	//					it->goToNextCheck();
	//				}
	//			}
	//		}
	//		if (!onePossibleRight)
	//		{
	//			it->setValue(0);
	//			grid.getBlock(it->getGridRowNumber(), it->getGridColumnNumber()).memberSet({ it->getCellRow(),it->getCellColumn() }, 0);
	//			--it;
	//			while ((it->getIsInitial() || (it < firstBlock.end() - 1)) || !it->isThereMoreNumber())
	//			{
	//				if (!it->getIsInitial())
	//				{
	//					grid.getBlock(it->getGridRowNumber(), it->getGridColumnNumber()).memberSet({ it->getCellRow(),it->getCellColumn() }, 0);
	//					it->setValue(0);
	//					it->goToFirstCheck();
	//				}
	//				if (it < firstBlock.end() - 1 && (it >= firstBlock.begin()+1) )
	//				{
	//					
	//					--it;
	//					if (it->isThereMoreNumber())
	//						it->goToNextCheck();
	//					
	//					break;
	//				}
	//				else
	//				{
	//					it->goToFirstCheck();
	//					--it;
	//				}
	//			}
	//		}
	//		else
	//		{
	//			++it;

	//		}
	//	}
	//	else
	//	{
	//		++it;
	//	}
	//}
}
