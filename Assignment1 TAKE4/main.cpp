/*
Ben Dreyer
Computer Science 61
Assignment 1



*/

#include "stdafx.h" //Remove this if not compiling in visual studio WILL GIVE YOU ERRORS IF YOU DONT
#include "Position.h"
#include "gridElement.h"
#include "make2dArray.h"
//#include "Stack.h" //This my ths stack class I wrote, I couldn't get it working with the rest of my code
#include <stack>
#include <queue>
#include <ctime>
#include <iostream>
#include <fstream>
#define _SCL_SECURE_NO_WARNINGS //Using this because Visual Studio is giving me weird IDE errors

using namespace std;

//global variables
int dimension;
gridElement** grid;
gridElement** DFS;
gridElement** BFS;
stack<position> path;
queue<position> Qpath;

int main()
{
	
	srand(time(NULL));

	cout << "Enter the dimension of the grid(Value between 5 - 20): ";
	cin >> dimension;
	if (dimension < 5 || dimension > 20)
		dimension = 15;
	dimension += 2; //acommodate for the border of 0s

	make2dArray(grid, dimension, dimension);
	make2dArray(DFS, dimension, dimension);
	make2dArray(BFS, dimension, dimension);

	
	
	cout << "Enter the density of the grid(Value between 0 - 1): " << endl;
	float Density = 0;
	std::cin >> Density;
	if (Density < 0 || Density > 1)
		Density = 0.5;

	//Generate the Grid based on the user defined density 
	float random;
	for (int row = 0; row < dimension; row++) {
		for (int col = 0; col < dimension; col++) {
			random = (float)rand() / RAND_MAX;
			if (random < Density) {
				grid[row][col].label = 1;
				grid[row][col].order = 0;
			}
			else {
				grid[row][col].label = 0;
				grid[row][col].order = 0;
			}
			DFS[row][col] = grid[row][col]; //Copy the grid for DFS functionality
			BFS[row][col] = grid[row][col]; //Copy the grid for BFS functionality
		}
	}
	

	//Create the border of 0's
	for (int i = 0; i < dimension; i++) {
		grid[0][i].label = grid[dimension - 1][i].label = 0;
		grid[i][0].label = grid[i][dimension - 1].label = 0;
	}
	//Make sure DFS and BFS also have the border of 0's
	for (int i = 0; i < dimension; i++) {
		for (int j = 0; j < dimension; j++) {
			DFS[i][j] = grid[i][j]; //Copy the grid for DFS functionality
			BFS[i][j] = grid[i][j]; //Copy the grid for BFS functionality
		}
	}
	

	//Draw 2d Array to console
	for (int i = 0; i < dimension; i++) {
		for (int j = 0; j < dimension; j++) {
			cout << grid[i][j].label << "," << grid[i][j].order << "|";
		}
		cout << "" << endl;
	}
	cout << "\n" << endl;
	cout <<"DFS: " << endl;


	//START OF DFS 
	position currentPos;
	currentPos.row = 0;
	currentPos.col = 0;
	int label = 2;

	for (int i = 0; i < dimension; i++) { //iterate through row
		for (int j = 0; j < dimension; j++) { //iterate through col
			currentPos.row = i;
			currentPos.col = j;
			//cout << "checking Row: " << currentPos.row << " Col: " << currentPos.col << endl;
			if (DFS[i][j].label == 1) { //If a seed is found
				int order = 1;
				//cout << "Seed has been found at Row:" << currentPos.row <<" Col: " << currentPos.col << endl;
				while (!path.empty()) { //Make sure that the stack is empty
					//cout << "Stack is not empty" << endl;
					path.pop();
				}
				

				DFS[i][j].label = label; //Set the initial seed to the current label
				DFS[i][j].order = order;
				order++;

				//Initialize offsets
				position offset[4];
				offset[0].row = 0; offset[0].col = 1; //Right
				offset[1].row = -1; offset[1].col = 0; //Down
				offset[2].row = 0; offset[2].col = -1; //Left
				offset[3].row = 1; offset[3].col = 0; //Up
				int option = 0;
				int lastOption = 3;
				
				while (currentPos.row != dimension || currentPos.col != dimension) { //Infinite loop
					int r, c;
					while (option <= lastOption) {   //look right, down, left, and up for an adjacent 1
						r = currentPos.row + offset[option].row;
						c = currentPos.col + offset[option].col;
						if (DFS[r][c].label == 1) { //If a 1 is found
							//cout << "Adjacent 1 has been found!" << endl;
							break;
						}
						option++; //if there is no 1 for that direction, try a differnet direction	
						
					}
					if (option <= lastOption) {//If an adjacent 1 was found
						path.push(currentPos);
						//cout << "Position added to stack" << endl;
						//cout << path.size();
						currentPos.row = r;
						currentPos.col = c;
						DFS[r][c].label = label;
						DFS[r][c].order = order;
						order++;
						option = 0;
					}
					else { //If no adjacent 1 was found, backup to the last 1
						if (path.empty()) {//if there is nowhere else to backup to
							label++;
							//Draw 2d Array to console
							
							//cout << "Label going up, clump is done" << endl;
							break;
						}

						position next = path.top();
						path.pop();
						if (next.row == currentPos.row)
							option = 2 + next.col - currentPos.col;
						else
							option = 3 + next.row - currentPos.row;
						currentPos = next;
						
					} 
				} 
			}
		}
	}

	//Draw 2d Array to console
	
	for (int i = 1; i < dimension - 1; i++) {
		for (int j = 1; j < dimension - 1; j++) {

			if (DFS[i][j].label < 10 && DFS[i][j].order < 10)
				cout << " " << DFS[i][j].label << "," << " " << DFS[i][j].order << "|"; //These ifs are used clean up the grid, will get messy if the order is 3 digits
			else if (DFS[i][j].label < 10 && DFS[i][j].order >= 10)
				cout << " " << DFS[i][j].label << "," << DFS[i][j].order << "|";
			else if (DFS[i][j].label >= 10 && DFS[i][j].order < 10)
				cout << DFS[i][j].label << "," << " " << DFS[i][j].order << "|";
			else if (DFS[i][j].label >= 10 && DFS[i][j].order >= 10)
				cout << DFS[i][j].label << "," << DFS[i][j].order << "|";
			else
				cout << "" << DFS[i][j].label << "," << " " << DFS[i][j].order << "|";

		}
		cout << "" << endl;
	}
	cout << endl << "BFS:" << endl;

	//END OF DFS


	
	//START OF BFS

	currentPos.row = 0;
	currentPos.col = 0;
	label = 2;
	position nbr;
	for (int i = 0; i < dimension; i++) { //iterate through row
		for (int j = 0; j < dimension; j++) { //iterate through col
			//cout << "checking Row: " << currentPos.row << " Col: " << currentPos.col << endl;
			if (BFS[i][j].label == 1) { //If a seed is found
				int order = 1;
				bool isAdjacent = true;
				currentPos.row = i;
				currentPos.col = j;
				//cout << "Seed has been found at Row:" << currentPos.row <<" Col: " << currentPos.col << endl;
				while (!Qpath.empty()) { //Make sure that the queue is empty
					//cout << "Stack is not empty" << endl;
					Qpath.pop();
				}

				Qpath.push(currentPos);
				BFS[currentPos.row][currentPos.col].isVisited = true;
				BFS[i][j].label = label; //Set the initial seed to the current label
				BFS[i][j].order = order;
				order++;
				

				//Initialize offsets
				position offset[4];
				offset[0].row = 0; offset[0].col = 1; //Right
				offset[1].row = -1; offset[1].col = 0; //Down
				offset[2].row = 0; offset[2].col = -1; //Left
				offset[3].row = 1; offset[3].col = 0; //Up
				int option = 0;
				int lastOption = 3;
				

				do { //While there is still an adjacent 1
					isAdjacent = false;
					option = 0;
					while (option <= lastOption) {   //look right, down, left, and up for an adjacent 1
						nbr.row = currentPos.row + offset[option].row;
						nbr.col = currentPos.col + offset[option].col;
						//position tempPos = { r, c };
						if (BFS[nbr.row][nbr.col].label == 1) { //If a 1 is found add it to the queue
							Qpath.push(nbr);
							//cout << "adjacent 1 found, adding pos to the queue" << endl;
							BFS[nbr.row][nbr.col].label = label;
							BFS[nbr.row][nbr.col].order = order;
							order++;
							isAdjacent = true;
						}
						option++; //if there is no 1 for that direction, try a differnet direction	
					}

					currentPos = Qpath.front();
					Qpath.pop();
					//BFS[currentPos.row][currentPos.col].isVisited = true;
					if (Qpath.empty()) {
						label++;
						break;
					}

				} while (isAdjacent);
			}
		}
	}

	//Draw the 2D Array to Console
	for (int i = 1; i < dimension - 1; i++) {
		for (int j = 1; j < dimension - 1; j++) {

			if (BFS[i][j].label < 10 && BFS[i][j].order < 10)
				cout << " " << BFS[i][j].label << "," << " " << BFS[i][j].order << "|"; //These ifs are used clean up the grid, will get messy if the order is 3 digits
			else if (BFS[i][j].label < 10 && BFS[i][j].order >= 10)
				cout << " " << BFS[i][j].label << "," << BFS[i][j].order << "|";
			else if (BFS[i][j].label >= 10 && BFS[i][j].order < 10)
				cout << BFS[i][j].label << "," << " " << BFS[i][j].order << "|";
			else if (BFS[i][j].label >= 10 && BFS[i][j].order >= 10)
				cout << BFS[i][j].label << "," << BFS[i][j].order << "|";
			else
				cout << "" << BFS[i][j].label << "," << " " << BFS[i][j].order << "|";

		}
		cout << "" << endl;
	}


	//END OF BFS


	//Reallocate the heap memory
	for (int i = 0; i < dimension; i++) {
		delete[] grid[i];
		delete[] DFS[i];
		delete[] BFS[i];
	}
	delete[] grid;
	delete[] DFS;
	delete[] BFS;

	std::cin >> dimension;

	
	return 0;
}