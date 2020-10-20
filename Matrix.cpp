#include <iostream>

#include "Matrix.h"

using namespace std;

int Matrix::static_id = 0;

Matrix::Matrix(int const n, int const m, double* const matrix) {
	this->id = ++static_id;
	this->n = n;
	this->m = m;
	this->matrix = new double[n * m];
	if (matrix != nullptr) {
		for (int i = 0; i < this->n; i++)
			for (int j = 0; j < this->m; j++)
				*(this->matrix + i * this->m + j) = *(matrix + i * this->m + j);
	}
	else {
		for (int i = 0; i < this->n; i++)
			for (int j = 0; j < this->m; j++)
				*(this->matrix + i * this->m + j) = 0;
	}
	cout << "Конструктор " << this->id << endl;
}

Matrix::Matrix(int const n) : Matrix::Matrix(n, n) {}

Matrix::Matrix() : Matrix::Matrix(0, 0) {}

Matrix::Matrix(Matrix& const other) {

}

Matrix::~Matrix() {
	if (this->matrix) {
		delete this->matrix;
		this->matrix = nullptr;
	}
	cout << "Деструктор " << this->id << endl;
}

bool Matrix::allow_multiply(Matrix& const other) const {
	return this->n == other.get_m() ? true : false;
}

bool Matrix::allow_summ(Matrix& const other) const {
	return (this->n == other.get_n()) && (this->m == other.get_m()) ? true : false;
}

double Matrix::get_max() const {
	double max = *this->matrix;
	for (int i = 1; i < this->n * this->m; i++)
		if (max < *(this->matrix + i))
			max = *(this->matrix + i);
	return max;
}

double Matrix::get_min() const {
	double min = *this->matrix;
	for (int i = 1; i < this->n * this->m; i++)
		if (min > * (this->matrix + i))
			min = *(this->matrix + i);
	return min;
}

int Matrix::get_m() const { return this->m; }
int Matrix::get_n() const { return this->n; }
int Matrix::get_id() const { return this->id; }

ostream& operator << (ostream& out, Matrix& matrix) {
	out << matrix.id << " матрица: " << endl;
	for (int i = 0; i < matrix.n; i++) {
		for (int j = 0; j < matrix.m; j++)
			out << *(matrix.matrix + i * matrix.m + j) << " ";
		out << endl;
	}
	return out;
}

double* create_matrix(int const n, int const m) {
	double* matrix = new double[n * m], x = 0;
	cout << "Заполните матрицу: ";
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> x;
			*(matrix + i * m + j) = x;
		}
	}
	return matrix;
}


