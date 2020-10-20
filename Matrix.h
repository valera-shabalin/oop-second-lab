#ifndef MATRIX_H
#define MATRIX_H

class Matrix
{
private:
	static int static_id;

	double* matrix = nullptr;
	int n = 0, m = 0, id = 0;
public:
	Matrix(int const n, int const m, double* const matrix = nullptr);
	Matrix(int const n);
	Matrix();
	Matrix(Matrix& const other);
	~Matrix();

	bool allow_multiply(Matrix& const other) const;
	bool allow_summ(Matrix& const other) const;

	double get_max() const;
	double get_min() const;
	int get_m() const;
	int get_n() const;
	int get_id() const;

	friend std::ostream& operator << (std::ostream& out, Matrix& matrix);
};

double* create_matrix(int const n, int const m);

#endif

