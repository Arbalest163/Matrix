#include <iostream>
#include <time.h>
using namespace std;


template<class T>
class Matrix {
	T** matrix;
	int row, col;
	
public:
	Matrix() :Matrix(2, 2) {}
	Matrix(unsigned int _row, unsigned int _col);
	Matrix(const Matrix<T>& _matrix);
	~Matrix();
	T maxElement();
	T minElement();
	Matrix<T>& operator=(const Matrix<T>& _matrix);
	Matrix<T>& operator+(const Matrix<T>& _matrix);
	Matrix<T>& operator-(const Matrix<T>& _matrix);
	Matrix<T>& operator*(const Matrix<T>& _matrix);
	Matrix<T>& reset();
	template<class T>
	friend ostream& operator<<(ostream& out, const Matrix<T>& _matrix);
	T operator()(int _row, int _col);
	

};
template<class T>
T Matrix<T>::maxElement() {
	T max{ matrix[0][0] };
	for (int i{ 0 }; i < row; ++i)
		for (int j{ 0 }; j < col; ++j)
			if (matrix[i][j] > max) max = matrix[i][j];
	return max;
}
template<class T>
T Matrix<T>::minElement() {
	T min{ matrix[0][0] };
	for (int i{ 0 }; i < row; ++i)
		for (int j{ 0 }; j < col; ++j)
			if (matrix[i][j] < min) min = matrix[i][j];
	return min;
}
template<class T>
Matrix<T>& Matrix<T>::reset() {
	for (int i{ 0 }; i < row; ++i)
		for (int j{ 0 }; j < col; ++j)
			matrix[i][j] = 0;
	return *this;
}
template<class T>
ostream& operator<<(ostream& out, const Matrix<T>& _matrix) {
	for (int i{ 0 }; i < _matrix.row; ++i) {
		for (int j{ 0 }; j < _matrix.col; ++j)
			out << _matrix.matrix[i][j] << " ";
		out << endl;
	}
	return out;
}
template<class T>
Matrix<T>::Matrix(unsigned int _row, unsigned int _col)
	:row(_row), col(_col)
{
	if (row <= 0) row = 1;
	if (col <= 0) col = 1;
	matrix = new T * [row];
	for (int i{ 0 }; i < row; ++i) {
		matrix[i] = new T[col];
	}
	for (int i{ 0 }; i < row; ++i)
		for (int j{ 0 }; j < col; ++j)
			matrix[i][j] = rand() % 10;
}
template<class T>
Matrix<T>::~Matrix() {
	for (int i{ 0 }; i < row;++i)
		delete[]matrix[i];
	delete[]matrix;
}
template<class T>
T Matrix<T>::operator()(int _row, int _col) {
	try {
		if (_row <= 0 || _row > row || _col <= 0 || _col > col)
			throw "Going beyond the dimensions of the matrix ";
		else return matrix[_row - 1][_col - 1];
	}
	catch (const char* error) {

		if (_row <= 0 || _row > row) {
			cout << error << "ROWS = ";
			return row;
		}
		if (_col <= 0 || _col > col) {
			cout << error << "COLUMNS = ";
			return col;
		}

	}
}
template<class T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& _matrix) {
	
		if (this == &_matrix) return *this;
		for (int i{ 0 }; i < row; ++i)
			delete[]matrix[i];
		delete[]matrix;
		row = _matrix.row;
		col = _matrix.col;
		matrix = new T * [row];
		for (int i{ 0 }; i < row; ++i) {
			matrix[i] = new T[col];
		}
		for (int i{ 0 }; i < row; ++i)
			for (int j{ 0 }; j < col; ++j)
				matrix[i][j] = _matrix.matrix[i][j];
		return *this;
}
template<class T>
Matrix<T>::Matrix(const Matrix<T>& _matrix) {
	*this = _matrix;
}
template<class T>
Matrix<T>& Matrix<T>::operator+(const Matrix<T>& _matrix) {
	try {
		if (row != _matrix.row || col != _matrix.col)
			throw "Matrices of different sizes cannot be folded!";
		Matrix<T>* tmp = new Matrix<T>(row, col);
		for (int i{ 0 }; i < row; ++i)
			for (int j{ 0 }; j < col; ++j)
				tmp->matrix[i][j] = matrix[i][j] + _matrix.matrix[i][j];
		return *tmp;

	}
	catch (const char* error) {
		cout << error << endl;
		return *this;
	}

}
template<class T>
Matrix<T>& Matrix<T>::operator-(const Matrix<T>& _matrix){
	try {
		if (row != _matrix.row || col != _matrix.col)
			throw "Matrices of different sizes cannot be subtracted!";
		Matrix<T>* tmp = new Matrix<T>(row, col);
		for (int i{ 0 }; i < row; ++i)
			for (int j{ 0 }; j < col; ++j)
				tmp->matrix[i][j] = matrix[i][j] - _matrix.matrix[i][j];
		return *tmp;

	}
	catch (const char* error) {
		cout << error << endl;
		return *this;
	}

}
template<class T>
Matrix<T>& Matrix<T>::operator*(const Matrix<T>& _matrix){
	try {
		if (col != _matrix.row)
			throw "The number of rows in matrix A does not correspond to the number of columns in matrix B!";
		Matrix<T> * tmp = new Matrix<T>(row, _matrix.col);
		tmp->reset();
		for (int i{ 0 }; i < tmp->row; ++i)
			for (int j{ 0 }; j < tmp->col; ++j)
				for (int k{0}; k < _matrix.row; ++k)
				tmp->matrix[i][j] += matrix[i][k] * _matrix.matrix[k][j];
		return *tmp;

	}
	catch (const char* error) {
		cout << error << endl;
		return *this;
	}

}

int main()
{
	srand(time(0));
	setlocale(0, "");
	cout << "Даны две матрицы: \n";
	cout << "Матрица А: \n";
	Matrix<int> A(3,3);
	cout << A << endl;
	cout << "Матрица B: \n";
	Matrix<int> B(3,3);
	cout << B << endl;
	cout << "Сложение двух матриц: \n";
	Matrix<int> C;
	cout << "Матрица A + B: \n";
	C = A + B;
	cout << C << endl;
	cout << "Вычитаине двух матриц: \n";
	cout << "Матрица A - B: \n";
	C = A - B;
	cout << C << endl;
	cout << "Даны две матрицы: \n";
	cout << "Матрица А: \n";
	Matrix<int> A1(3, 2);
	cout << A1 << endl;
	cout << "Матрица B: \n";
	Matrix<int> B1(2, 3);
	cout << B1 << endl;
	cout << "Умножение двух матриц: \n";
	cout << "Матрица A * B: \n";
	C = A * B;
	cout << C << endl;
	cout << "Максимальный элемент матрицы АВ: " << C.maxElement() << endl;
	cout << "Минимальный элемент матрицы АВ: " << C.minElement() << endl;
}
