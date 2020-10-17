#ifndef MATRIX_H
#define MATRIX_H

class Matrix {
private:
	static int static_id;

	int* matrix;


public:
	/* Конструктор */
	Matrix();
	/* Копирующий конструктор */
	Matrix(const Matrix& other);
	/* Дестркутор */
	~Matrix();

};

#endif

