#ifndef MATRIX_H
#define MATRIX_H

class Matrix {
private:
	static int static_id;

	int* matrix;


public:
	/* ����������� */
	Matrix();
	/* ���������� ����������� */
	Matrix(const Matrix& other);
	/* ���������� */
	~Matrix();

};

#endif

