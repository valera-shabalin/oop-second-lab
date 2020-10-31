#include <iostream>
#include <clocale>

#include "Matrix.h"

using namespace std;

int main()
{
	setlocale(LC_CTYPE, "Rus");

	/* Инициализация переменных */
	size_t n = 0, m = 0;

	cout << "Введите размеры матрицы: ";
	cin >> n >> m;

	double* array = create_matrix(n, m);

	Matrix e_matrix = Matrix(n, m, array);
	Matrix g_matrix = Matrix(2, 2);

	/* Проверка перегрузок */
	e_matrix += e_matrix;

	/* Проверка внешних функций */
	Matrix summ = std::move(summ_matrix(e_matrix, e_matrix));
	Matrix diff = std::move(diff_matrix(e_matrix, e_matrix));
	Matrix multiply = std::move(multiply_matrix(e_matrix, e_matrix));
	Matrix scalar_multiply = std::move(scalar_multiply_matrix(e_matrix, 5));

	/* Вывод результатов */
	cout << e_matrix << summ << diff << multiply << scalar_multiply;

	/* Перегрузка оператора [][] */
	cout << multiply[2][2];

	return 0;
}
