﻿#ifndef MATRIX_H
#define MATRIX_H

class Row {
	friend class Row;
private:
	size_t index;
	class Matrix* owner;
public:
	/* Конструктор */
	Row(Matrix& owner, size_t i);
	/* Перегрузка оператора [] */
	double operator[](size_t x);
};

class Matrix
{
private:
	static size_t static_id;
	static bool debug;

	double* matrix = nullptr;
	size_t n = 0, m = 0, id = 0;
public:
	/* Конструкторы и деструктор */
	Matrix(size_t n, size_t m, double* matrix = nullptr);
	Matrix(size_t n);
	Matrix();
	Matrix(const Matrix& other);
	Matrix(Matrix&& other);
	~Matrix();

	/* Функции проверки */
	bool allow_multiply(const Matrix& other) const;
	bool allow_summ(const Matrix& other) const;
	bool is_empty() const;

	/* Геттеры */
	double get_max() const;
	double get_min() const;
	int get_m() const;
	int get_n() const;
	int get_size() const;
	int get_id() const;
	double* get_matrix() const;

	/* Перегрузки операторов */
	const Matrix& operator=(const Matrix& other);
	Matrix& operator=(Matrix&& other) noexcept;
	const Matrix& operator+=(const Matrix& other);
	const Matrix& operator-=(const Matrix& other);
	Matrix operator*=(const Matrix& other);
	const Matrix& operator*=(double k);
	Row operator[](size_t x);
	double cell(size_t x, size_t y);
	friend std::ostream& operator << (std::ostream& out, Matrix& matrix);
};

/* Внешние функции */
double* create_matrix(size_t n, size_t m);
Matrix summ_matrix(const Matrix& f_matrix, const Matrix& s_matrix);
Matrix diff_matrix(const Matrix& f_matrix, const Matrix& s_matrix);
Matrix multiply_matrix(const Matrix& f_matrix, const Matrix& s_matrix);
Matrix scalar_multiply_matrix(const Matrix& matrix, double k);

#endif

