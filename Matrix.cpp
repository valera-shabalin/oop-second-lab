#include <iostream>

#include "Matrix.h"

using namespace std;

size_t Matrix::static_id = 0;

/* ����������� */
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
	cout << "����������� " << this->id << endl;
}

/* ����������� */
Matrix::Matrix(size_t n) : Matrix::Matrix(n, n) {}

/* ������������ ��-��������� */
Matrix::Matrix() : Matrix::Matrix(0, 0) {}

/* ���������� ����������� */
Matrix::Matrix(const Matrix& other) {
	this->id = ++static_id;
	this->n = other.n;
	this->m = other.m;
	this->matrix = new double[n * m];
	for (int i = 0; i < this->get_size(); i++)
		*(this->matrix + i) = *(other.matrix + i);
	cout << "����������� ����������� " << this->id << endl;
}

/* ���������� */
Matrix::~Matrix() {
	if (this->matrix) {
		delete this->matrix;
		this->matrix = nullptr;
	}
	cout << "���������� " << this->id << endl;
}

/* ����� ��� �������� ����������� ��������� */
bool Matrix::allow_multiply(const Matrix& other) const {
	return this->n == other.m;
}

/* ����� ��� �������� ����������� �������� */
bool Matrix::allow_summ(const Matrix& other) const {
	return this->n == other.n && this->m == other.m;
}

/* ����� ��� �������� ������� �� ������� */
bool Matrix::is_empty() const {
	return this->matrix == nullptr;
}

/* ����� ��� ��������� ������������� �������� */
double Matrix::get_max() const {
	if (this->matrix == nullptr) throw "get_max - ������� ������";
	double max = *this->matrix;
	for (int i = 1; i < this->get_size(); i++)
		if (max < *(this->matrix + i))
			max = *(this->matrix + i);
	return max;
}

/* ����� ��� ��������� ������������ �������� */
double Matrix::get_min() const {
	if (this->matrix == nullptr) throw "get_min - ������� ������";
	double min = *this->matrix;
	for (int i = 1; i < this->get_size(); i++)
		if (min > * (this->matrix + i))
			min = *(this->matrix + i);
	return min;
}

/* ������� */
int Matrix::get_m() const { return this->m; }
int Matrix::get_n() const { return this->n; }
int Matrix::get_size() const { return this->n * this->m; }
int Matrix::get_id() const { return this->id; }
double* Matrix::get_matrix() const { return this->matrix; }

/* ���������� ��������� = */
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

/* ���������� ��������� += */
const Matrix& Matrix::operator+=(const Matrix& other) {
	if (!this->allow_summ(other)) throw "operator+= - ������� �������� ������ ������ ��������";
	if (other.matrix == nullptr) throw "operator+= - ������� ������";
	for (int i = 0; i < this->get_size(); i++)
		*(this->matrix + i) += *(other.matrix + i);
	return *this;
}

/* ���������� ��������� -= */
const Matrix& Matrix::operator-=(const Matrix& other) {
	if (!this->allow_summ(other)) throw "operator-= - ������� ��������� ������ ������ ��������";
	if (other.is_empty()) throw "operator-= - ������� ������";
	for (int i = 0; i < this->get_size(); i++)
		*(this->matrix + i) -= *(other.matrix + i);
	return *this;
}

/* ���������� ��������� *= */ // TODO
/*const Matrix& Matrix::operator*=(const Matrix& other) {
	if (!this->allow_multiply(other)) throw "operator-= - ������� ������������ ������ ������ ��������";
	if (other.matrix == nullptr) throw "operator-= - ������� ������";
	for (int i = 0; i < this->n; i++)
		for (int j = 0; j < this->m; j++)
			*(this->matrix + i * this->n + j) -= *(other.matrix + i * this->n + j);
	return *this;
}*/

/* ���������� ��������� *= ��� ������� */
const Matrix& Matrix::operator*=(double k) {
	for (int i = 0; i < this->get_size(); i++)
		*(this->matrix + i) *= k;
	return *this;
}

/* ���������� ��������� << */
ostream& operator << (ostream& out, Matrix& matrix) {
	if (matrix.is_empty()) throw "operator << - ������� ������� ������ �������";
	out << matrix.id << " �������: " << endl;
	for (int i = 0; i < matrix.n; i++) {
		for (int j = 0; j < matrix.m; j++)
			out << *(matrix.matrix + i * matrix.m + j) << " ";
		out << endl;
	}
	return out;
}

/* ������� ��� �������� ������� */
double* create_matrix(size_t n, size_t m) {
	double* matrix = new double[n * m], x = 0;
	cout << "��������� �������: ";
	for (int i = 0; i < n * m; i++) {
		cin >> x;
		*(matrix + i) = x;
	}
	return matrix;
}

/* ������� �������� ���� ������ */
Matrix summ_matrix(const Matrix& f_matrix, const Matrix& s_matrix) {
	if (!f_matrix.allow_summ(s_matrix)) throw "summ_matrix - ������� �������� ������ ������ ��������";
	size_t n = f_matrix.get_n(), m = f_matrix.get_m();
	double* matrix = new double[n * m];
	for (int i = 0; i < n * m; i++)
		*(matrix + i) = *(f_matrix.get_matrix() + i) + *(s_matrix.get_matrix() + i);
	return Matrix(n, m, matrix);
}

/* ������� ��������� ���� ������ */
Matrix diff_matrix(const Matrix& f_matrix, const Matrix& s_matrix) {
	if (!f_matrix.allow_summ(s_matrix)) throw "diff_matrix - ������� ��������� ������ ������ ��������";
	size_t n = f_matrix.get_n(), m = f_matrix.get_m();
	double* matrix = new double[n * m];
	for (int i = 0; i < n * m; i++)
		*(matrix + i) = *(f_matrix.get_matrix() + i) - *(s_matrix.get_matrix() + i);
	return Matrix(n, m, matrix);
}

/* ������� ��������� ������� �� ������ */
Matrix scalar_multiply_matrix(const Matrix& matrix, double k) {
	if (matrix.is_empty()) throw "scalar_multiply_matrix - ������ �������";
	size_t n = matrix.get_n(), m = matrix.get_m();
	double* new_matrix = new double[n * m];
	for (int i = 0; i < n * m; i++)
		*(new_matrix + i) = *(matrix.get_matrix() + i) * k;
	return Matrix(n, m, new_matrix);
}


