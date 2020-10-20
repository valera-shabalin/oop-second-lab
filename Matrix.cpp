#include <iostream>

#include "Matrix.h"

using namespace std;

size_t Matrix::static_id = 0;

/* Конструктор */
Matrix::Matrix(size_t n, size_t m, double* matrix) {
	this->id = ++static_id;
	this->n = n;
	this->m = m;
	this->matrix = new double[n * m];
	if (matrix != nullptr)
		for (int i = 0; i < this->get_size(); i++)
			*(this->matrix + i) = *(matrix + i);
	else
		for (int i = 0; i < n * m; i++) 
			*(this->matrix + i) = 0;
	cout << "Конструктор " << this->id << endl;
}

/* Конструктор */
Matrix::Matrix(size_t n) : Matrix::Matrix(n, n) {}

/* Конструкторы по-умолчанию */
Matrix::Matrix() : Matrix::Matrix(0, 0) {}

/* Копирующий конструктор */
Matrix::Matrix(const Matrix& other) {
	this->id = ++static_id;
	this->n = other.n;
	this->m = other.m;
	this->matrix = new double[n * m];
	for (int i = 0; i < this->get_size(); i++)
		*(this->matrix + i) = *(other.matrix + i);
	cout << "Конструктор копирования " << this->id << endl;
}

/* Деструктор */
Matrix::~Matrix() {
	if (this->matrix) {
		delete this->matrix;
		this->matrix = nullptr;
	}
	cout << "Деструктор " << this->id << endl;
}

/* Метод для проверки возможности умножения */
bool Matrix::allow_multiply(const Matrix& other) const {
	return this->n == other.m;
}

/* Метод для проверки возможности сложения */
bool Matrix::allow_summ(const Matrix& other) const {
	return this->n == other.n && this->m == other.m;
}

/* Метод для проверки матрицы на пустоту */
bool Matrix::is_empty() const {
	return this->matrix == nullptr;
}

/* Метод для получения максимального элемента */
double Matrix::get_max() const {
	if (this->matrix == nullptr) throw "get_max - Матрица пустая";
	double max = *this->matrix;
	for (int i = 1; i < this->get_size(); i++)
		if (max < *(this->matrix + i))
			max = *(this->matrix + i);
	return max;
}

/* Метод для получения минимального элемента */
double Matrix::get_min() const {
	if (this->matrix == nullptr) throw "get_min - Матрица пустая";
	double min = *this->matrix;
	for (int i = 1; i < this->get_size(); i++)
		if (min > * (this->matrix + i))
			min = *(this->matrix + i);
	return min;
}

/* Геттеры */
int Matrix::get_m() const { return this->m; }
int Matrix::get_n() const { return this->n; }
int Matrix::get_size() const { return this->n * this->m; }
int Matrix::get_id() const { return this->id; }
double* Matrix::get_matrix() const { return this->matrix; }

/* Перегрузка оператора = */
const Matrix& Matrix::operator=(const Matrix& other) {
	if (this == &other) return *this;
	this->n = other.n;
	this->m = other.m;
	if (this->matrix != nullptr) delete this->matrix;
	this->matrix = new double[this->n * this->m];
	for (int i = 0; i < this->get_size(); i++)
		*(this->matrix + i) = *(other.matrix + i);
	return *this;
}

/* Перегрузка оператора += */
const Matrix& Matrix::operator+=(const Matrix& other) {
	if (!this->allow_summ(other)) throw "operator+= - Попытка сложения матриц разных размеров";
	if (other.matrix == nullptr) throw "operator+= - Матрица пустая";
	for (int i = 0; i < this->get_size(); i++)
		*(this->matrix + i) += *(other.matrix + i);
	return *this;
}

/* Перегрузка оператора -= */
const Matrix& Matrix::operator-=(const Matrix& other) {
	if (!this->allow_summ(other)) throw "operator-= - Попытка вычитания матриц разных размеров";
	if (other.is_empty()) throw "operator-= - Матрица пустая";
	for (int i = 0; i < this->get_size(); i++)
		*(this->matrix + i) -= *(other.matrix + i);
	return *this;
}

/* Перегрузка оператора *= */ // TODO
/*const Matrix& Matrix::operator*=(const Matrix& other) {
	if (!this->allow_multiply(other)) throw "operator-= - Попытка перемножения матриц разных размеров";
	if (other.matrix == nullptr) throw "operator-= - Матрица пустая";
	for (int i = 0; i < this->n; i++)
		for (int j = 0; j < this->m; j++)
			*(this->matrix + i * this->n + j) -= *(other.matrix + i * this->n + j);
	return *this;
}*/

/* Перегрузка оператора *= для скаляра */
const Matrix& Matrix::operator*=(double k) {
	for (int i = 0; i < this->get_size(); i++)
		*(this->matrix + i) *= k;
	return *this;
}

/* Перегрузка оператора << */
ostream& operator << (ostream& out, Matrix& matrix) {
	if (matrix.is_empty()) throw "operator << - Попытка вывести пустую матрицу";
	out << matrix.id << " матрица: " << endl;
	for (int i = 0; i < matrix.n; i++) {
		for (int j = 0; j < matrix.m; j++)
			out << *(matrix.matrix + i * matrix.m + j) << " ";
		out << endl;
	}
	return out;
}

/* Функция для создания матрицы */
double* create_matrix(size_t n, size_t m) {
	double* matrix = new double[n * m], x = 0;
	cout << "Заполните матрицу: ";
	for (int i = 0; i < n * m; i++) {
		cin >> x;
		*(matrix + i) = x;
	}
	return matrix;
}

/* Функция сложения двух матриц */
Matrix summ_matrix(const Matrix& f_matrix, const Matrix& s_matrix) {
	if (!f_matrix.allow_summ(s_matrix)) throw "summ_matrix - Попытка сложения матриц разных размеров";
	size_t n = f_matrix.get_n(), m = f_matrix.get_m();
	double* matrix = new double[n * m];
	for (int i = 0; i < n * m; i++)
		*(matrix + i) = *(f_matrix.get_matrix() + i) + *(s_matrix.get_matrix() + i);
	return Matrix(n, m, matrix);
}

/* Функция вычитания двух матриц */
Matrix diff_matrix(const Matrix& f_matrix, const Matrix& s_matrix) {
	if (!f_matrix.allow_summ(s_matrix)) throw "diff_matrix - Попытка вычитания матриц разных размеров";
	size_t n = f_matrix.get_n(), m = f_matrix.get_m();
	double* matrix = new double[n * m];
	for (int i = 0; i < n * m; i++)
		*(matrix + i) = *(f_matrix.get_matrix() + i) - *(s_matrix.get_matrix() + i);
	return Matrix(n, m, matrix);
}

/* Функция умножения матрицы на скаляр */
Matrix scalar_multiply_matrix(const Matrix& matrix, double k) {
	if (matrix.is_empty()) throw "scalar_multiply_matrix - Пустая матрица";
	size_t n = matrix.get_n(), m = matrix.get_m();
	double* new_matrix = new double[n * m];
	for (int i = 0; i < n * m; i++)
		*(new_matrix + i) = *(matrix.get_matrix() + i) * k;
	return Matrix(n, m, new_matrix);
}


