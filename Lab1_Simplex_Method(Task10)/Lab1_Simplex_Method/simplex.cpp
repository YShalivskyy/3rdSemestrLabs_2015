#include "Simplex.h"

void Simplex::swap(int& a, int& b) {
	int c = a;
	a = b;
	b = c;
}

int Simplex::findIndexOfMinRow(int indexY) {
	double max = 0;
	int indexX = -1;
	for (int i(0); i < numCoef; i++) {
		if (matrix[indexY][i] < 0 && abs(matrix[indexY][i]) > abs(max)) {
			max = matrix[indexY][i];
			indexX = i;
		}
	}

	return indexX;
}

// serching target element in a column in the optimal solution
int Simplex::findIndexOfMinColumn(int indexX) {
	double min = INT_MAX;
	int indexY = -1;
	for (int i(1); i < numRows + 1; i++) {
		if (matrix[i].back() / matrix[i][indexX] < min) {
			min = matrix[i].back() / matrix[i][indexX];
			indexY = i;
		}
	}

	return indexY;
}

// serching the target element in a column of the general solution
int Simplex::findIndexOfMinColumnHelp(int indexX) {
	int max = 0;
	int indexY = -1;
	for (int i(1); i < numRows + 1; i++) {
		if (matrix[i][indexX] < 0 && abs(matrix[i][indexX]) > abs(max)) {
			max = matrix[i][indexX];
			indexY = i;
		}
	}

	return indexY;
}

bool Simplex::findLeadingRow(int& indexX, int& indexY) {
	indexY = findIndexOfMinColumnHelp(matrix.size());
	if (indexY != -1) {
		indexX = findIndexOfMinRow(indexY);
		if (indexX == -1) {
			cout << "Impossible to find the appropriate solution" << endl;
			exit(0);
		}
		swap(functionRow[indexX], auxiliaryVarColumn[indexY - 1]); //swap the variables
		return true;
	}

	return false;
}

bool Simplex::findLeadingColumn(int& indexX, int& indexY) {
	double max = 0;
	indexX = -1;
	for (int i(0); i < numCoef - 1; i++) {
		if (matrix[0][i] < 0 && abs(matrix[0][i]) > abs(max)) {
			max = matrix[0][i];
			indexX = i;
		}
	}
	if (indexX != -1)  {
		indexY = findIndexOfMinColumn(indexX);

		swap(functionRow[indexX], auxiliaryVarColumn[indexY - 1]); // swap variables
		return true;
	}

	return false;
}

void Simplex::conversionSimplex(int indexX, int indexY) {
	copyMatrix();
	for (int i(0); i < numRows + 1; i++) {
		if (i != indexY) { // if not in a leading row
			for (int j(0); j < numCoef; j++) {
				if (j != indexX) { // if not in a leading column
					matrix[i][j] -= matrixCopy[indexY][j] * matrixCopy[i][indexX] / matrixCopy[indexY][indexX]; // using simplex conversions
				}
				else {
					matrix[i][j] *= -1 / matrixCopy[indexY][indexX];
				}
			}
		}
		else { // if row is leading
			for (int j(0); j < numCoef; j++) {
				if (j != indexX)
					matrix[i][j] *= 1 / matrixCopy[indexY][indexX];
			}
			matrix[indexY][indexX] = 1 / matrixCopy[indexY][indexX]; // excluding minus from the leading element
		}
	}
}

void Simplex::findOptimalPolinom() {
	int indexX = -1;
	int indexY = -1; // initializing the index of current leading element
	printSimplexMatrix();

	bool appropriateFound = findLeadingRow(indexX, indexY); // check if appropriate solution was found
	while (appropriateFound) {
		conversionSimplex(indexX, indexY);
		printSimplexMatrix();
		appropriateFound = findLeadingRow(indexX, indexY);
	}

	bool optimalFound = findLeadingColumn(indexX, indexY); // check if optimal solution was found
	while (optimalFound) {
		conversionSimplex(indexX, indexY);
		printSimplexMatrix();
		optimalFound = findLeadingColumn(indexX, indexY);
	}

	// creating the result vector, b0 - the maximum of the function
	double* result = new double[numCoef - 1];
	for (int i(0); i < numCoef - 1; i++)
		result[i] = 0;

	for (int i(0); i < numRows; i++) {
		if (auxiliaryVarColumn[i] < numCoef - 1) { // numCoef - 1 = ammount of variables
			result[auxiliaryVarColumn[i]] = matrix[i + 1].back();
		}
	}

	// printing final polinom
	cout << endl;
	for (int i(0); i < functionRow.size() - 1; i++) {
		cout << "x" << i << " = " << result[i] << endl;
	}
	cout << "Max function value: " << matrix[0].back() << endl;


}

void Simplex::copyMatrix() {
	if (matrixCopy.empty()) { // intializing the vector
		for (int i(0); i < matrix.size(); i++) {
			vector<double> v;
			v.push_back(matrix[i][0]);
			matrixCopy.push_back(v);
			for (int j(1); j < matrix[i].size(); j++) {
				matrixCopy[i].push_back(matrix[i][j]);
			}
		}
	}
	else { // change the values
		for (int i(0); i < matrix.size(); i++) {
			for (int j(0); j < matrix[i].size(); j++) {
				matrixCopy[i][j] = matrix[i][j];
			}
		}
	}
}

void Simplex::printSimplexMatrix() {
	cout << endl << "   ";
	for (int i(0); i < functionRow.size() - 1; i++) {
		cout << "x" << functionRow[i] << " ";
	}
	cout << "b0";
	cout << endl << "F  ";
	for (int i(0); i < numRows + 1; i++) {
		if (i > 0)
			cout << "x" << auxiliaryVarColumn[i - 1] << "  ";
		for (int j(0); j < numCoef; j++) {
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
}