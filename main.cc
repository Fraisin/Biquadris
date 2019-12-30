#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <vector>
#include <memory>
#include "board.h"
#include "block.h"
#include "textdisplay.h"
#include "graphics.h"
#include "commandinterpreter.h"
#include "AbsLevel.h"
#include "LevelZero.h"
#include "LevelOne.h"
#include "LevelTwo.h"
#include "LevelThree.h"
#include "LevelFour.h"
#include "blind.h"
#include "force.h"
#include "heavy.h"
#include <termios.h>
#include <unistd.h>
#include <stdio.h>

using namespace std;

int main (int argc, char *argv[]) {

	//initialize seed at the beginning of our program
	srand(2);

	//Game Variables
	CommandInterpreter CI;
	size_t player1 = 1, player2 = 2;
	size_t width = 11;
	size_t height = 18;
	size_t startingLevel = 0;
	size_t board1counter = 1, board2counter = 1;
	size_t hiscore = 0;
	int counter = -1;
	string p1LevelZero = "sequence1.txt";
	string p2LevelZero = "sequence2.txt";
	bool keystrokes = false; //keystrokes only input

	//Variables Used for Graphics Display
	size_t spacebetween = 8;
	size_t bordersize = 5;
	size_t tileWidth = 22; //this represents the size of one tile
	size_t displayWidth = (width * 2) + spacebetween + (bordersize * 2);
	size_t displayHeight = height + (bordersize * 3);
	bool graphicsOn = true;

	//Parsing Command-Line Arguments
        for (int i = 1; i < argc; i++) {
                string cmd = argv[i];
                if (cmd == "-text") {
			//Set graphicsOn to false 
		       	graphicsOn = false;
		} else if (cmd == "-keystrokes") {
			//Set keystrokes to true
			keystrokes = true;
                } else {
			if (cmd != "-seed" && cmd != "-scriptfile1" &&
			    cmd != "-scriptfile2" && cmd != "-startlevel") {
				//Return that there is no matching argument
				cerr << "Error: Unknown Argument: " << cmd << endl;
				return 1;
			}
			//Retrieve the second parameter for the argument
                        string param = argv[i+1];
                        if (cmd == "-seed") {
				//Make sure parameter can be used as a seed
                                try {
					srand(stoi(param));
				}
				catch(...) {
					cerr << "Error: Parameter cannot be converted into a seed." << endl;
					return 1;
				}
                        }
                        if (cmd == "-scriptfile1") {
				//Test if file exists
				ifstream testfile(param);
				if (!testfile.good()) {
					cerr << "Error: File doesn't exist or cannot be opened." << endl;
					return 1;
				}

				//If it works, set it 
                                p1LevelZero = param;
                        }
                        if (cmd == "-scriptfile2") {
				//Test if file exists
                                ifstream testfile(param);
                                if (!testfile.good()) {
                                        cerr << "Error: File doesn't exist or cannot be opened." << endl;
                                        return 1;
                                }
				
				//If it works, set it
                                p2LevelZero = param;
                        }
                        if (cmd == "-startlevel") {
				//Make sure the parameter can be read as a integer
				try {
                                	startingLevel = stoi(param);
				}
				catch(...) {
                                        cerr << "Error: Parameter cannot be converted into a integer." << endl;
                                        return 1;
                                }

				//Make sure it is within bounds
				if (startingLevel > 4) {
					startingLevel = 4;
					cout << "Setting level to 4 - the maximum." << endl;
				} 
				if (startingLevel < 0) {
					startingLevel = 0;
					cout << "Setting level to 0 - the minimum." << endl;
				}
                        }
                        i++;
                }
        }
	
	//Game Board Setup
	
	//Initialize Variables
	Board* theBoard1 = new Board(width, height, startingLevel, player1);
	Board* theBoard2 = new Board(width, height, startingLevel, player2);
	shared_ptr<AbsBoard> absBoard1(theBoard1);
	shared_ptr<AbsBoard> absBoard2(theBoard2);
	TextDisplay td{width, height, theBoard1, theBoard2};
	GraphicsDisplay* gd = nullptr;
	theBoard1->setObserver(&td);
	theBoard2->setObserver(&td);
	int board1CurLevel = startingLevel;
        int board1NextLevel = startingLevel;
        int board2CurLevel  = startingLevel;
        int board2NextLevel = startingLevel;
        int dropCount = 0; //Used for commands like 5drop
        vector<string> commandBuffer; //Used for sequence command
	string playerinput; //string for storing the command
	
	//if the startinglevel is 0, use the sequence files, otherwise, randomly select pieces
	if (startingLevel == 0) {
		theBoard1->setCurLevel(startingLevel, false, p1LevelZero);
		theBoard2->setCurLevel(startingLevel, false, p2LevelZero);
	} else {
		theBoard1->setCurLevel(startingLevel, true);
		theBoard2->setCurLevel(startingLevel, true);
	}
	
	//Create graphics display object if graphicsOn is enabled
	if (graphicsOn) {
		gd = new GraphicsDisplay{tileWidth, displayWidth, displayHeight, width, 
				height, theBoard1, theBoard2};  	
        	theBoard1->setObserver(gd);
        	theBoard2->setObserver(gd);
	}

	//Generate first 4 blocks and place them on the board
	theBoard1->setCurBlock((theBoard1->getCurLevel())->getNextBlock(0));
	theBoard1->setNextBlock((theBoard1->getCurLevel())->getNextBlock(1));
	theBoard2->setCurBlock((theBoard2->getCurLevel())->getNextBlock(0));
        theBoard2->setNextBlock((theBoard2->getCurLevel())->getNextBlock(1));
	theBoard1->moveBlock(0, 0, 0);
	theBoard2->moveBlock(0, 0, 0);
	
	//Game Loop
	while (true) {

		bool restart =  false; //Boolean to break out of nested loops if restart called 
			
		//Increment to next players turn if it was not a multiple drop
                if (dropCount == 0) {
                        counter++;
                        cout << td;
                }

		//Select the current players board
		Board* theBoard = (((counter % 2) == 0) ? theBoard1 : theBoard2);
		
		//Loop for the current players block movement
		while (true) {
			
			//If player entered multiple drop, execute it
			if (dropCount != 0) {
				//Repeat down until it is impossible
                                while(theBoard->validMove(0, 1, 0)) {
                                                theBoard->moveBlock(0, 1, 0);
                                }
                                theBoard->restBlock((counter % 2 == 0) ? board1CurLevel : board2CurLevel);
                                theBoard->checkLines();
				dropCount--;
                                break;
			}

			//Parsing Input
			string input;
			string cmd;
			int mult;
			
			//If keystrokes is not enabled read from cin or buffer
			if (!keystrokes) {
				//If command buffer is empty, take in command from command line.
				//Otherwise, read from buffer.
				if (commandBuffer.empty()) {
					cin  >> input;
				} else {
					input = commandBuffer.front();
					commandBuffer.erase(commandBuffer.begin());
				}
				//Send to command interpreter	
				cmd = CI.readinput(input);
				mult = CI.getmult(input);
			} else {
				//Otherwise, map keystroke to command
				
				//set mult to 1
				mult = 1;
				
				//Iterate for capturing mult values if given
				while (true) {

					//Read in char from unbuffered stream
					//Taken from https://media.geeksforgeeks.org/wp-content/uploads/conio.h
					char keystroke;
					struct termios oldattr, newattr;
    					tcgetattr( STDIN_FILENO, &oldattr );
    					newattr = oldattr;
    					newattr.c_lflag &= ~( ICANON | ECHO);
    					tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    					keystroke = getchar();
    					tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
					
					//map to command
					if (keystroke >= '0' && keystroke <= '9') {
						mult = keystroke - '0';
						cout << "Multiplier set to: " << mult << endl;
						continue;
					}
					else if (keystroke == '/') {
						cout << "keystrokes mode turned off." << endl; 
						keystrokes = false;
					}
					else if (keystroke == 'a') {cmd = "left";}
					else if (keystroke == 'd') {cmd = "right";}
					else if (keystroke == 's') {cmd = "down";}
					else if (keystroke == 'q') {cmd = "counterclockwise";}
					else if (keystroke == 'e') {cmd = "clockwise";}
					else if (keystroke == ' ') {cmd = "drop";}
					else if (keystroke == 'i') {cmd = "I";}
					else if (keystroke == 'j') {cmd = "J";}
					else if (keystroke == 'l') {cmd = "L";}
					else if (keystroke == 'o') {cmd = "O";}
					else if (keystroke == 's') {cmd = "S";}
					else if (keystroke == 'z') {cmd = "Z";}
					else if (keystroke == 't') {cmd = "T";}
					else if (keystroke == 'n') {cmd = "leveldown";}
					else if (keystroke == 'm') {cmd = "levelup";}
					else if (keystroke == ',') {cmd = "restart";}
					else if (keystroke == '.') {cmd = "quit";}
					else {continue;}
					break;
				}
			}	
			//If Command is invalid, reprompt command
			if (cmd == "ERROR") {
				cout << "Invalid Command" << endl;
				continue;
			}
			
			//If moving 0 units, dont bother moving unless heavy
			if (mult == 0) {
				if (!theBoard->getCurBlock()->isLevelHeavy() && !theBoard->getCurBlock()->isEffectHeavy()) {
					continue;
				}
			}

			if (cmd == "keystrokeson") {
				if (commandBuffer.empty()) {
                                    	cout << "keystrokes mode turned on." << endl;
                                	keystrokes = true;
					cout << td;
                                	continue;
                                }
				cout << "Error: keystrokes mode not compatable with sequence" << endl;
				cout << td;
				continue;
			}

			if (cmd == "rename") {
				//Get current command name and desired name
				string oldName, newName;

				//Read in from command buffer or cin respectively
				if (commandBuffer.empty()) {
					cin >> oldName;
                                } else {
					oldName = commandBuffer.front();
					commandBuffer.erase(commandBuffer.begin());
                                }
				if (commandBuffer.empty()) {
                                        cin >> newName;
                                } else {
                                        newName = commandBuffer.front();
                                        commandBuffer.erase(commandBuffer.begin());
                                }

				//Call the rename command
				CI.renamecommand(oldName, newName);
				
				//Reprint board and prompt next command
				cout << td;
				continue;
			}
			
			if (cmd == "left") {
				//Move left mult times until not possible
				for (int i = 0; i < mult; ++i) {
					if (theBoard->validMove(-1, 0, 0)) {
						theBoard->moveBlock(-1, 0, 0);
					} else break;
				}
			}

			if (cmd == "right") {
				//Move right mult times until not possible
				for (int i = 0; i < mult; ++i) {
                                	if (theBoard->validMove(1, 0, 0)) {
						theBoard->moveBlock(1, 0, 0);
					} else break;
				}	
                        }

			if (cmd == "down") {
				//Move down mult times until not possible
				for (int i = 0; i < mult; ++i) {
                                	if (theBoard->validMove(0, 1, 0)) {
						theBoard->moveBlock(0, 1, 0);
					} else break;
				}
                        }

			if (cmd == "clockwise") {
				//Rotate clockwise mult times until not possible
				for (int i = 0; i < mult; ++i) {
					if (theBoard->validMove(0, 0, 1)) {
						theBoard->moveBlock(0, 0, 1);
					} else break;
				}
			}

			if (cmd == "counterclockwise") {
				//Rotate counterclockwise mult times until not possible
				for (int i = 0; i < mult; ++i) {
					if (theBoard->validMove(0, 0, -1)) { 
						theBoard->moveBlock(0, 0, -1);
					} else break;
				}
			}

			if (cmd == "drop") {
				//Repeat down until it is impossible
				while(theBoard->validMove(0, 1, 0)) {
						theBoard->moveBlock(0, 1, 0);
				}

				//Check if cleared lines
				theBoard->restBlock((counter % 2 == 0) ? board1CurLevel : board2CurLevel);
				theBoard->checkLines();
				
				//If there was more than 1 drop, enter a drop loop
				if (mult > 1) {
					dropCount = mult - 1;
				}
				break;
			}
			
			if (cmd == "levelup") {
				size_t curLevel = theBoard->getLevel();
				
				//Make sure Level doesn't exceed 4	
				if (curLevel != 4) {
					for (int i = 0; i < mult; ++i) {
						if (curLevel == 4) break;
						curLevel++;
					}
					theBoard->setCurLevel(curLevel, true);

					//Set counters
                                        if (counter % 2 == 0) {
                                                board1CurLevel = curLevel;
                                                board1NextLevel = curLevel;
                                        } else {
                                                board2CurLevel = curLevel;
                                                board2NextLevel = curLevel;
                                        }
				}

				//Reprint Board
				cout << td;
				continue;
			}

			if (cmd == "leveldown") {
                                size_t curLevel = theBoard->getLevel();

				//Make sure level doesnt fall below 0
				if (curLevel != 0) {
                                	for (int i = 0; i < mult; ++i) { 
						if (curLevel == 0) break;
						curLevel--; 
					}
					if (curLevel == 0) {
						if (theBoard->getPlayer() == 1) {
							theBoard->setCurLevel(curLevel, false, p1LevelZero);
						} else theBoard->setCurLevel(curLevel, false, p2LevelZero);
					} 
					else theBoard->setCurLevel(curLevel, true);

					//Set counters
                                        if (counter % 2 == 0) {
                                                board1CurLevel = curLevel;
                                                board1NextLevel = curLevel;
                                        } else {
                                                board2CurLevel = curLevel;
                                                board2NextLevel = curLevel;
                                        }
				}
				
				//Reprint Board
				cout << td;
				continue;
                        }
			
			if (cmd == "norandom") {
				size_t curlevel = theBoard->getLevel();

				//Make sure it is a level that has random possible
				if (!curlevel == 0) {
					string filename;
                                	//Check if already executing a sequence
                                	if (commandBuffer.empty()) {
                                        	cin >> filename;
                                	} else {
                                        	filename = commandBuffer.front();
                                        	commandBuffer.erase(commandBuffer.begin());
					}

					//Set random if file valid
					ifstream f(filename);
					if (f.good()) theBoard->setCurLevel(curlevel, false, filename);
					else cout << "This is not an existing file!" << endl;
				}

				//Reprint Board
				cout << td;
				continue;
			}
			
			if (cmd == "random") {
				size_t curlevel = theBoard->getLevel();

				//Make sure it is a level that has random possible
                                if (!curlevel == 0) { 
					theBoard->setCurLevel(curlevel, true);
				}

				//Reprint Board
				cout << td;
				continue;
			}
			
			if (cmd == "sequence") {
				//Initialize variables
				string filename;
				string command;
				ifstream file;
				
				//Check if already executing a sequence
				if (commandBuffer.empty()) {
                                	cin >> filename;
				} else {
					filename = commandBuffer.front();
					commandBuffer.erase(commandBuffer.begin());
				}

				//Open file if possible
				file.open(filename);
				if (!file.good()) {
					cout << "This is not an existing file!" << endl;
					continue;
				}

				//Read commands into buffer and start next loop
                                while (file >> command) {
					commandBuffer.emplace_back(command);
				}
				continue;
			}
			if (cmd.length() == 1) {
				//To force the current block to be a certain block

				//Match heavy to level
				bool heavy = false;
				if (theBoard->getLevel() == 3 || theBoard->getLevel() == 4) {
					heavy = true;
				}
					
				//Find which block they want
				Block * oldBlock = theBoard->getCurBlock();
				Block * newBlock = nullptr;
				if (cmd == "I") {
					newBlock = new Iblock{heavy};
				}
				else if (cmd == "J") {
                                        newBlock = new Jblock{heavy};
                                }
				else if (cmd == "L") {
					newBlock = new Lblock{heavy};
                                }
				else if (cmd == "O") {
					newBlock = new Oblock{heavy};
                                }
				else if (cmd == "S") {
					newBlock = new Sblock{heavy};
                                }
				else if (cmd == "Z") {
					newBlock = new Zblock{heavy};
                                }
				else if (cmd == "T") {
					newBlock = new Tblock{heavy};
                                }
				else {
					continue;
				}
				
				//Set if valid and otherwise don't move
				newBlock->setX(oldBlock->getX());
				newBlock->setY(oldBlock->getY());
				theBoard->unsetBlock();
				theBoard->setCurBlock(newBlock);
				
				if (theBoard->validMove(0, 0, 0)) {
					theBoard->moveBlock(0, 0, 0);
					delete oldBlock;
				} else {
					theBoard->setCurBlock(oldBlock);
					theBoard->moveBlock(0, 0, 0);
					delete newBlock;
				}

				//Print the board
				cout << td;
				continue;
			}

			if (cmd == "restart") {
				//Set restart boolean to true
				restart = true;

				//Clear both boards
				theBoard1->resetBoard();
				theBoard2->resetBoard();
				
				//Reset counters
				counter = -1;
				board1counter = 1;
				board2counter = 1;

				//Update Blocks
				theBoard1->setCurBlock((theBoard1->getCurLevel())->getNextBlock(0));
 	      			theBoard1->setNextBlock((theBoard1->getCurLevel())->getNextBlock(1));
        			theBoard2->setCurBlock((theBoard2->getCurLevel())->getNextBlock(0));
        			theBoard2->setNextBlock((theBoard2->getCurLevel())->getNextBlock(1));
        			theBoard1->moveBlock(0, 0, 0);
        			theBoard2->moveBlock(0, 0, 0);

				break;

			}
			
			//End game prematurely
			if (cmd == "quit") {delete gd; return 0;}
			
			//Shift down if levelHeavy and check if reached bottom
			if (theBoard->getCurBlock()->isLevelHeavy()) {
			       if (theBoard->validMove(0, 1, 0)) {
				        theBoard->moveBlock(0, 1, 0);
			       } 
			       if (!theBoard->validMove(0, 1, 0)) {
				        theBoard->restBlock((counter % 2 == 0) ? board1CurLevel : board2CurLevel);
                                	theBoard->checkLines();
					break;
			       }
			}
			
			//Shift down if effectHeavy and check if reached bottom
			if (theBoard->getCurBlock()->isEffectHeavy()) {
			       if (cmd == "left" || cmd == "right") {
				       for (int i = 0; i < 2; i++) {
					       if (theBoard->validMove(0, 1, 0)) {
						       theBoard->moveBlock(0, 1, 0);
					       } else {break;}
			       	       }
				       if (!theBoard->validMove(0, 1, 0)) {
					       theBoard->restBlock((counter % 2 == 0) ? board1CurLevel : 
							       board2CurLevel);
					       theBoard->checkLines();
					       break;
                               	       }
                               }
			}
			
			//Print board after move
			cout << td;
		}
		
		//Post resting block activity

		//check for high score and update if higher than existing highscore
		size_t p1score = theBoard1->getScore();
                size_t p2score = theBoard2->getScore();
                if (p1score > hiscore || p2score > hiscore) {
                        hiscore = (p1score >= p2score) ? p1score : p2score;
                        theBoard1->setHiScore(hiscore);
                }
		
		//If restart, restart skip to next iteration of gameloop
		if (restart) {continue;}

		//if the board was blind and the turn has been ended, unblind it
		if (theBoard->isBlind()) {
			theBoard->setBlind(false);
		}

		//if the board was heavy and the turn has been ended, unblind it
                if (theBoard->isHeavy()) {
                        theBoard->setHeavy(false);
                }
		
		//if the board was force and the turn has been ended, unblind it
                if (theBoard->isForce()) {
                        theBoard->setForce(false);
                }

		//Checking for * block
                if (theBoard->getLevel() == 4) {
			Block * temp = theBoard->getCurLevel()->getNextBlock(0);

			//If present, drop and check lines
			if (temp->getType() == '*') {
				theBoard->setCurBlock(temp);
				//Drop the block
				while(theBoard->validMove(0, 1, 0)) {
					theBoard->moveBlock(0, 1, 0);
                                }
				theBoard->restBlock(4);
				theBoard->checkLines();
                        } else {
				delete temp;
			}
                }

		//see if a special effect is required
		if (theBoard->isEffectNeeded()) {
			cout << td;
			cout << "TYPE ONE OF THE FOLLOWING EFFECTS:" << endl;
			cout << "1) blind" << endl;
			cout << "2) heavy" << endl;
			cout << "3) force" << endl;
			cout << endl;
			string effect;
			
			while (true) {
				//Read in option from buffer or cin respectively
				if (commandBuffer.empty()) {
                                        cin >> effect;
                                } else {
                                        effect = commandBuffer.front();
                                        commandBuffer.erase(commandBuffer.begin());
                                }

				if (effect == "blind") {
					//Apply the effect to correct player
					if (theBoard->getPlayer() == 1) {
						theBoard2->setBlind(true);
						absBoard2.reset(new Blind{absBoard2});
                                		absBoard2->apply(*theBoard2);
						break;
					} else {
						theBoard1->setBlind(true);
						absBoard1.reset(new Blind{absBoard1});
						absBoard1->apply(*theBoard1);
						break;
					}

				}
				else if (effect == "force") {
					//Get which block
					char block;
					while (true) {
						cout << "Enter the letter of what block to add: " << endl;
						cout << endl;
						if (commandBuffer.empty()) {
                                        		cin >> block;
                                		} else {
                                        		block = commandBuffer.front().front();
                                        		commandBuffer.erase(commandBuffer.begin());
                                		}
						if (block == 'I' || block == 'J' || block == 'L' ||
								block == 'O' || block == 'S' ||
								block == 'Z' || block == 'T') {
						       break;
						}
				 		cout << "That is not a known block." << endl << endl;		
					}

					//Apply the effect to correct player
					if (theBoard->getPlayer() == 1) {
						theBoard2->setForce(true);
                                                absBoard2.reset(new Force{absBoard2, block});
                                                absBoard2->apply(*theBoard2);
						if(theBoard2->getDead()) {
							string s;
							cout << "Game Over!" << endl;
							cout << "Player 1 won!" << endl;
							cout << "Enter any character to win!" << endl;
							if (graphicsOn) gd->displayWinner(1);
                                			cin >> s;
							delete gd;
							return 0;
						}
                                                break;
                                        } else {
						theBoard1->setForce(true);
                                                absBoard1.reset(new Force{absBoard1, block});
                                                absBoard1->apply(*theBoard1);
						if(theBoard1->getDead()) {
							string s;
                                                        cout << "Game Over!" << endl;
                                                        cout << "Player 2 won!" << endl;
							cout << "Enter any character to win!" << endl;
							if (graphicsOn) gd->displayWinner(2);
                                			cin >> s;
                                                        delete gd;
                                                        return 0;
                                                }
                                                break;
                                        }
				}
				else if (effect == "heavy") {
					//Apply the effect to the correct player
					if (theBoard->getPlayer() == 1) {
						theBoard2->setHeavy(true);
                                                absBoard2.reset(new Heavy{absBoard2});
                                                absBoard2->apply(*theBoard2);
                                                break;
                                        } else {
						theBoard1->setHeavy(true);
                                                absBoard1.reset(new Heavy{absBoard1});
                                                absBoard1->apply(*theBoard1);
                                                break;
                                        }

				}
				else {cout << "That is not a valid effect." << endl;}
			}
			theBoard->setEffectNeeded(false);
		}

		//Place Next block on field
                size_t boardcounter = (((counter % 2) == 0) ? ++board1counter : ++board2counter);
                theBoard->setCurBlock(theBoard->getNextBlock());
                theBoard->setNextBlock(theBoard->getCurLevel()->getNextBlock(boardcounter));

		//Check Lose condition (if they cant move the second the they spawn)
                if (!theBoard->validMove(0, 0, 0)) {
			cout << "Game Over!" << endl;
			string s;
			if ((counter % 2) == 0) {
				cout << "Player 2 won!" << endl;
				if (graphicsOn) gd->displayWinner(2);
				cout << "Enter any character to win!" << endl;
				cin >> s;
			} else {
				cout << "Player 1 won!" << endl;
				if (graphicsOn) gd->displayWinner(1);
				cout << "Enter any character to win!" << endl;
				cin >> s;
			}
			delete gd;
                        return 0;
                }

		//Otherwise, set block in place for next time
                theBoard->moveBlock(0, 0, 0);

		//Set the level generated variables for the next turn;
                if (counter % 2 == 0) {
			//If It was Board 1's turn
			board1CurLevel = board1NextLevel;
			board1NextLevel = static_cast<int>(theBoard->getLevel());
		}
		if (counter % 2 != 0) {
			//If It was Board2's turn
			board2CurLevel = board2NextLevel;
			board2NextLevel = static_cast<int>(theBoard->getLevel());
		}
	}
}

