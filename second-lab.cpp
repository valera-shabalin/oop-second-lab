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

	/* Проверка перегрузок */
	e_matrix *= e_matrix;

	/* Проверка внешних функций */
	Matrix m_matrix = std::move(multiply_matrix(e_matrix, e_matrix));

	/* Вывод результатов */
	cout << e_matrix << m_matrix;

	return 0;
}
