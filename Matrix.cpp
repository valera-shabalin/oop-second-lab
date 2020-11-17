#include <iostream>
#include <iomanip> 

#include "Matrix.h"

using namespace std;

namespace mat {
	size_t Matrix::static_id = 0;
	bool Matrix::debug = true;

	/* Конструктор для строки */
	Matrix::Row::Row(const Matrix* owner, size_t i) {
		this->owner = owner;
		this->index = i;
	}

	/* Конструктор */
	Matrix::Matrix(size_t n, size_t m, double* matrix) {
		this->id = ++static_id;
		
		if (n != 0 && m != 0) {
			this->matrix = new double[n * m]();
			this->n = n;
			this->m = m;
		}

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
	Matrix::Matrix(const Matrix& other) : Matrix() {
		*this = other;
		if (debug) cout << "Конструктор копирования - копируем " << this->id << " <- " << other.id << endl;
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
		if (this->is_empty())
			throw "get_max - матрица пустая";

		double max = *this->matrix;

		for (size_t i = 1; i < this->get_size(); i++)
			if (max < *(this->matrix + i))
				max = *(this->matrix + i);

		return max;
	}

	/* Получить минимальный элемент матрицы */
	double Matrix::get_min() const {
		if (this->is_empty()) 
			throw "get_min - матрица пустая";

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

	/* Перегрузка оператора += */
	Matrix& Matrix::operator+=(const Matrix& other) {
		for (size_t i = 0; i < this->get_size(); i++)
			*(this->matrix + i) += *(other.matrix + i);

		return *this;
	}

	/* Перегрузка оператора + */
	Matrix Matrix::operator+(const Matrix& other) {
		if (!this->allow_summ(other)) 
			throw "operator+ - матрицы разных размеров";

		if (other.is_empty()) 
			throw "operator+ - матрица пустая";

		Matrix tmp(*this);
		tmp += other;

		return move(tmp);
	}

	/* Перегрузка оператора -= */
	Matrix& Matrix::operator-=(const Matrix& other) {
		if (!this->allow_summ(other))
			throw "operator-= - матрицы разных размеров";

		if (other.is_empty())
			throw "operator-= - матрица пустая";

		for (size_t i = 0; i < this->get_size(); i++)
			*(this->matrix + i) -= *(other.matrix + i);

		return *this;
	}

	/* Перегрузка оператора - */
	Matrix Matrix::operator-(const Matrix& other) {
		Matrix tmp(*this);
		tmp -= other;

		return move(tmp);
	}
	
	/* Перегрузка оператора *= на другую матрицу */
	Matrix& Matrix::operator*=(const Matrix& other) {
		if (!this->allow_multiply(other)) 
			throw "operator*= - матрицы разных размеров";

		if (other.is_empty()) 
			throw "operator*= - матрица пустая";

		size_t new_size = this->n * other.m;
		double* matrix = new double[new_size];

		for (size_t i = 0; i < new_size; i++)
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

	/* Перегрузка оператора * */
	Matrix Matrix::operator*(const Matrix& other) {
		Matrix tmp(*this);
		tmp *= other;

		return move(tmp);
	}

	/* Перегрузка оператора *= на скаляр */
	Matrix& Matrix::operator*=(double k) {
		if (this->is_empty())
			throw "operator* - матрица пустая";

		for (size_t i = 0; i < this->get_size(); i++)
			*(this->matrix + i) *= k;
		return *this;
	}

	/* Перегрузка оператора * на скаляр */
	Matrix Matrix::operator*(double k) {
		Matrix tmp(*this);
		tmp *= k;

		return move(tmp);
	}

	/* Переопределение оператора вывода на поток << */
	ostream& operator << (ostream& os, Matrix& matrix) {
		auto width = os.width();
		if (width == 0) width = 8;

		if (matrix.is_empty()) {
			os << setw(width) << "Матрица пустая" << endl;
			return os;
		}

		for (size_t i = 0; i < matrix.n; i++) {
			for (size_t j = 0; j < matrix.m; j++)
				os << setw(width) << *(matrix.matrix + i * matrix.m + j) << " ";
			os << endl;
		}

		return os;
	}

	/* Перегрузка оператора [] */
	Matrix::Row Matrix::operator[](size_t x) {
		if (x <= 0 || x >= this->n) throw "Выход за пределы.";
		return Row(this, x);
	}

	const Matrix::Row Matrix::operator[](size_t x) const {
		if (x <= 0 || x >= this->n) throw "Выход за пределы.";
		return Row(this, x);
	}

	double Matrix::Row::operator[](size_t x) const {
		if (x <= 0 || x >= this->owner->m) throw "Выход за пределы.";
		return *(this->owner->matrix + this->index * this->owner->n + x);
	}

	double& Matrix::Row::operator[](size_t x) {
		if (x <= 0 || x >= this->owner->m) throw "Выход за пределы.";
		return *(this->owner->matrix + this->index * this->owner->n + x);
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

	/* Функция для генерации случайных матриц */
	Matrix generate_matrix(size_t n, size_t m, double min, double max) {
		double* matrix = new double[n * m];
		for (size_t i = 0; i < n * m; i++)
			*(matrix + i) = min + (double)rand() / RAND_MAX * (max - min);
		return move(Matrix(n, m, matrix));
	}
}




