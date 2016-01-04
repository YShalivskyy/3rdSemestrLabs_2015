/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Task: find the maximum value of the input function represented as the first-degree polinom with n coefficients
//       with consideration of executing of m inequalities
//
// Input (text file): number of coefficients + free member, number of inequalities
//                    coefficients of input function
//                    coefficients of restrictions(inequalities)
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Reference: http://www.uchimatchast.ru/teory/tabl_simplex.php
// Lab 1, task ¹10

#pragma once

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

class Simplex {
private:
	vector<int> functionRow; // variables of input polinom
	vector<int> auxiliaryVarColumn; // help variables to make leading row
	vector<double> coefOfPolinom; // coefitients of the input polinom
	vector<vector<double>> matrix; // matrix to store simplex table
	vector<vector<double>> matrixCopy; // matrix to store a copy of the original matrix for calculating using simplex method 
	int numCoef; // ammount of variables + free member ( a0x0 + a1x1 <= b0, b0 - free member, the result, max value the function can be)
	int numRows; // ammount of restrictions 

	void swap(int& a, int& b);
	// function which creates copy of a current matrix ans store it in matrixCope vector
	void copyMatrix();

	// find minimal index in a row
	int findIndexOfMinRow(int indexY);

	// find minimal index in a column
	int findIndexOfMinColumn(int indexX);
	int findIndexOfMinColumnHelp(int indexX);

	// find leading rows to create an appropriate solution
	bool findLeadingRow(int& indexX, int& indexY);

	// find leading rows to create the optimal solution
	bool findLeadingColumn(int& indexX, int& indexY);

	// change values in the table using simplex conversions
	void conversionSimplex(int indexX, int indexY);

public:
	Simplex(string inputString) {
		ifstream input(inputString);
		input >> numCoef;
		input >> numRows;

		double help;

		for (int i(0); i < numCoef; i++) { // filling vector with polinom coefitiens and the first roe of matrix
			functionRow.push_back(i); // pushing variables
			input >> help;

			coefOfPolinom.push_back(help);
			if (i == 0) { // creating the first vector 
				vector<double> v;
				v.push_back(help);
				matrix.push_back(v);
			}
			else
				matrix[0].push_back(help);
		}
		functionRow.back() = 0;

		for (int i(0); i < numRows; i++) { // filing the rest of the simplex table
			auxiliaryVarColumn.push_back(numCoef - 1 + i); // adding a column of auxiliary variables
			for (int j(0); j < numCoef; j++) {
				input >> help;
				if (j == 0) {
					vector<double> v;
					v.push_back(help);
					matrix.push_back(v);
				}
				else
					matrix[i + 1].push_back(help);
			}
		}
	}

	void findOptimalPolinom();
	void printSimplexMatrix(); // print matrix with row and column vectors
};