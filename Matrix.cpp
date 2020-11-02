#include <iostream>

#include "Matrix.h"

using namespace std;

namespace mat {
	size_t Matrix::static_id = 0;
	bool Matrix::debug = false;

	/* Конструктор для строки */
	Matrix::Row::Row(Matrix& owner, size_t i) {
		this->owner = &owner;
		this->index = i;
	}

	/* Конструктор */
	Matrix::Matrix(size_t n, size_t m, double* matrix) {
		this->id = ++static_id;
		this->n = n;
		this->m = m;
		if (n != 0 && m != 0)
			this->matrix = new double[n * m]();
		if (matrix != nullptr)
			copy(matrix, matrix + m * n, this->matrix);
		if (debug) 
			cout << "Конструктор " << this->id << endl;
	}

	/* Конструктор с параметрами размера матрицы */
	Matrix::Matrix(size_t n) : Matrix::Matrix(n, n) {}

	/* Деструктор */
	Matrix::~Matrix() {
		if (!this->is_empty()) {
			delete this->matrix;
			this->matrix = nullptr;
		}
		if (debug) cout << "Деструктор " << this->id << endl;
	}

	/* Копирующий конструктор */
	Matrix::Matrix(const Matrix& other) {
		*this = other;
		if (debug) cout << "Конструктор копирования " << this->id << endl;
	}

	/* Копирующий оператор = */
	const Matrix& Matrix::operator=(const Matrix& other) {
		if (this == &other) return *this;
		size_t size = other.get_size();
		if (this->get_size() != size) {
			if (this->matrix != nullptr) delete[] this->matrix;
			this->matrix = size > 0 ? new double[size] : nullptr;
		}
		this->m = other.m;
		this->n = other.n;
		if (size > 0) copy(other.matrix, other.matrix + size, this->matrix);
		return *this;
	}

	/* Перемещающий конструктор */
	Matrix::Matrix(Matrix&& other) : Matrix() {
		*this = move(other);
		if (debug) cout << "Конструктор перемещения " << other.id << endl;
	}

	/* Перемещающий оператор = */
	Matrix& Matrix::operator=(Matrix&& other) noexcept {
		if (this == &other) return *this;
		this->make_null();
		std::swap(this->matrix, other.matrix);
		std::swap(this->n, other.n);
		std::swap(this->m, other.m);
		return *this;
	}

	/* Сделать матрицу пустой */
	Matrix& Matrix::make_null() {
		this->m = this->n = 0;
		if (!this->is_empty()) {
			delete[] this->matrix;
			this->matrix = nullptr;
		}
		return *this;
	}

	/* Проверка возможности перемножения матриц */
	bool Matrix::allow_multiply(const Matrix& other) const {
		return this->n == other.m;
	}

	/* Проверка возможности сложения матриц */
	bool Matrix::allow_summ(const Matrix& other) const {
		return this->n == other.n && this->m == other.m;
	}

	/* Проверка матрицы на пустоту */
	bool Matrix::is_empty() const {
		return this->matrix == nullptr;
	}

	/* Получить максимальный элемент матрицы */
	double Matrix::get_max() const {
		if (this->is_empty()) throw "get_max - матрица пустая";
		double max = *this->matrix;
		for (size_t i = 1; i < this->get_size(); i++)
			if (max < *(this->matrix + i))
				max = *(this->matrix + i);
		return max;
	}

	/* Получить минимальный элемент матрицы */
	double Matrix::get_min() const {
		if (this->is_empty()) throw "get_min - матрица пустая";
		double min = *this->matrix;
		for (size_t i = 1; i < this->get_size(); i++)
			if (min > * (this->matrix + i))
				min = *(this->matrix + i);
		return min;
	}

	/* Геттеры */
	size_t Matrix::get_m() const { return this->m; }
	size_t Matrix::get_n() const { return this->n; }
	size_t Matrix::get_size() const { return this->n * this->m; }
	size_t Matrix::get_id() const { return this->id; }
	double* Matrix::get_matrix() const { return this->matrix; }

	/* Перегрузка оператора += */
	const Matrix& Matrix::operator+=(const Matrix& other) {
		if (!this->allow_summ(other)) throw "operator+= - матрицы разных размеров";
		if (other.is_empty()) throw "operator+= - матрица пустая";
		copy(other.matrix, other.matrix + other.m * other.n, this->matrix);
		return *this;
	}

	/* Перегрузка оператора -= */
	const Matrix& Matrix::operator-=(const Matrix& other) {
		if (!this->allow_summ(other)) throw "operator-= - матрицы разных размеров";
		if (other.is_empty()) throw "operator-= - матрица пустая";
		copy(other.matrix, other.matrix + other.m * other.n, this->matrix);
		return *this;
	}

	/* Перегрузка оператора *= на другую матрицу */
	Matrix Matrix::operator*=(const Matrix& other) {
		if (!this->allow_summ(other)) throw "operator*= - матрицы разных размеров";
		if (other.is_empty()) throw "operator*= - матрица пустая";
		double* matrix = new double[this->n * other.m];
		for (size_t i = 0; i < this->n * other.m; i++)
			*(matrix + i) = 0;
		for (size_t i = 0; i < this->n; i++)
			for (size_t j = 0; j < other.m; j++)
				for (size_t k = 0; k < this->m; k++)
					*(matrix + i * other.m + j) += *(this->matrix + i * this->m + k) * *(other.matrix + k * other.m + j);
		delete[] this->matrix;
		this->matrix = matrix;
		this->m = this->n;
		this->n = other.m;
		return *this;
	}

	/* Перегрузка оператора *= на скаляр */
	const Matrix& Matrix::operator*=(double k) {
		for (size_t i = 0; i < this->get_size(); i++)
			*(this->matrix + i) *= k;
		return *this;
	}

	/* Переопределение оператора вывода на поток << */
	ostream& operator << (ostream& out, Matrix& matrix) {
		if (matrix.is_empty()) throw "operator << - матрица пустая";
		out << matrix.get_id() << " матрица: " << endl;
		for (size_t i = 0; i < matrix.get_n(); i++) {
			for (size_t j = 0; j < matrix.get_m(); j++)
				out << *(matrix.get_matrix() + i * matrix.get_m() + j) << " ";
			out << endl;
		}
		return out;
	}

	/* Перегрузка оператора [] */
	Matrix::Row Matrix::operator[](size_t x) {
		return Matrix::Row(*this, x);
	}

	double Matrix::Row::operator[](size_t x) {
		return owner->cell(this->index, x);
	}

	/* Получить ячеейку матрицы */
	double Matrix::cell(size_t x, size_t y) {
		return *(this->matrix + x * this->n + y);
	}

	/* Функция для создания матрицы */
	double* create_matrix(size_t n, size_t m) {
		double* matrix = new double[n * m], x = 0;
		cout << "Заполните матрицу: ";
		for (size_t i = 0; i < n * m; i++) {
			cin >> x;
			*(matrix + i) = x;
		}
		return matrix;
	}

	/* Сумма матриц */
	Matrix summ_matrix(const Matrix& f_matrix, const Matrix& s_matrix) {
		if (!f_matrix.allow_summ(s_matrix)) throw "summ_matrix - матрицы разных размеров";
		size_t n = f_matrix.get_n(), m = f_matrix.get_m();
		double* matrix = new double[n * m];
		for (size_t i = 0; i < n * m; i++)
			*(matrix + i) = *(f_matrix.get_matrix() + i) + *(s_matrix.get_matrix() + i);
		return Matrix(n, m, matrix);
	}

	/* Разность матриц */
	Matrix diff_matrix(const Matrix& f_matrix, const Matrix& s_matrix) {
		if (!f_matrix.allow_summ(s_matrix)) throw "diff_matrix - матрицы разных размеров";
		size_t n = f_matrix.get_n(), m = f_matrix.get_m();
		double* matrix = new double[n * m];
		for (size_t i = 0; i < n * m; i++)
			*(matrix + i) = *(f_matrix.get_matrix() + i) - *(s_matrix.get_matrix() + i);
		return Matrix(n, m, matrix);
	}

	/* Перемножение матриц */
	Matrix multiply_matrix(const Matrix& f_matrix, const Matrix& s_matrix) {
		if (!f_matrix.allow_multiply(s_matrix)) throw "multiply_matrix - не перемножить данные матрицы";
		size_t fn = f_matrix.get_n(), sm = s_matrix.get_m(), fm = f_matrix.get_m();
		double* matrix = new double[fn * sm];
		for (size_t i = 0; i < fn * sm; i++)
			*(matrix + i) = 0;
		for (size_t i = 0; i < fn; i++)
			for (size_t j = 0; j < sm; j++)
				for (size_t k = 0; k < fm; k++)
					*(matrix + i * sm + j) += *(f_matrix.get_matrix() + i * fm + k) * *(s_matrix.get_matrix() + k * sm + j);
		return Matrix(fn, sm, matrix);
	}

	/* Умножение матрицы на скаляр */
	Matrix scalar_multiply_matrix(const Matrix& matrix, double k) {
		if (matrix.is_empty()) throw "scalar_multiply_matrix - матрица пустая";
		size_t n = matrix.get_n(), m = matrix.get_m();
		double* new_matrix = new double[n * m];
		for (size_t i = 0; i < n * m; i++)
			*(new_matrix + i) = *(matrix.get_matrix() + i) * k;
		return Matrix(n, m, new_matrix);
	}
}



