#include <iostream>
#include <clocale>

#include "Matrix.h"

using namespace std;
using namespace mat;

int rand_int(int min, int max) {
	return min + rand() % (max - min);
}

double rand_double(double min, double max) {
	return min + (double)rand() / RAND_MAX * (max - min);
}

int main() {
	setlocale(LC_CTYPE, "Rus");

	/*Matrix e_matrix = Matrix(n, m, f_array);
	Matrix t_matrix = Matrix(x, y, s_array);
	Matrix m_matrix = Matrix(3);*/

	/* Проверка перегрузок */
	/*cout << "Проверка перегрузок *=, +=, -=: " << endl 
		 << "e_matrix: " << endl << e_matrix
		 << "t_matrix: " << endl << t_matrix;

	cout << "Перегрузка e_matrix += e_matrix: " << endl;
	e_matrix += e_matrix;
	cout << e_matrix;

	cout << "Перегрузка e_matrix -= t_matrix: " << endl;
	e_matrix -= t_matrix;
	cout << e_matrix;

	cout << "Перегрузка e_matrix *= t_matrix: " << endl;
	e_matrix *= t_matrix;
	cout << e_matrix;

	cout << "Перегрузка t_matrix *= 5: " << endl;
	t_matrix *= 5;
	cout << t_matrix;*/

	/* Проверка внешних операторов */
	/*Matrix summ_matrix = e_matrix + t_matrix;
	cout << "e_matrix + t_matrix = " << endl << summ_matrix;
	Matrix diff_matrix = e_matrix - t_matrix;
	cout << "e_matrix - t_matrix = " << endl << diff_matrix;
	Matrix multiply_matrix = e_matrix * t_matrix;
	cout << "e_matrix * t_matrix = " << endl << multiply_matrix;*/

	auto func1 = [](size_t x, size_t y)->double { return rand_int(0, 10); };
	auto func2 = [](size_t x, size_t y)->double { return rand_int(0, 20); };

	Matrix m1(2, 2, func1);
	Matrix m2(2, 2, func2);

	cout << "Первая матрица: " << endl << m1;
	cout << "Вторая матрица: " << endl << m2;

	/* Перегрузка оператора [][] */
	/*cout << "Проверка перегрузки [][]. Получим элемент e_matrix[1][1]: " << e_matrix[1][1] << endl;
	e_matrix[1][1] = 100;
	cout << "Проверка перегрузки [][]. Сохранили в элемент e_matrix[1][1] значение 100: " << e_matrix[1][1] << endl;*/

	return 0;
}
