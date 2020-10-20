#ifndef MATRIX_H
#define MATRIX_H

class Matrix
{
private:
	static int static_id;

	double* matrix = nullptr;
	int n = 0, m = 0, id = 0;
public:
	/* Конструкторы и деструктор */
	Matrix(int n, int m, double* matrix = nullptr);
	Matrix(int n);
	Matrix();
	Matrix(const Matrix& other);
	~Matrix();

	/* Методы */
	bool allow_multiply(const Matrix& other) const;
	bool allow_summ(const Matrix& other) const;

	/* Геттеры */
	double get_max() const;
	double get_min() const;
	int get_m() const;
	int get_n() const;
	int get_size() const;
	int get_id() const;

	/* Сетторы */
	void set_size(int n, int m);

	/* Перегрузки операторов */
	const Matrix& operator=(const Matrix& other);
	const Matrix& operator+=(const Matrix& other);
	const Matrix& operator-=(const Matrix& other);
	const Matrix& operator*=(double k);

	friend std::ostream& operator << (std::ostream& out, Matrix& matrix);
};

/* Внешнии функции */
double* create_matrix(int const n, int const m);

#endif

