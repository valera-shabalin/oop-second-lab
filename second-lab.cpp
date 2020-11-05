#include <iostream>
#include <clocale>

#include "Matrix.h"

using namespace std;
using namespace mat;

int main() {
	setlocale(LC_CTYPE, "Rus");

	/* Инициализация переменных */
	size_t n = 0, m = 0, x = 0, y = 0;

	cout << "Введите размер первой матрицы: ";
	cin >> n >> m;
	double* f_array = create_matrix(n, m);

	cout << "Введите размер второй матрицы: ";
	cin >> x >> y;
	double* s_array = create_matrix(n, m);

	Matrix e_matrix = Matrix(n, m, f_array);
	Matrix t_matrix = Matrix(x, y, s_array);

	/* Проверка перегрузок */
	cout << "Проверка перегрузок *=, +=, -=: " << endl 
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
	cout << t_matrix;

	/* Перегрузка оператора [][] */
	cout << "Проверка перегрузки [][]. Получим элемент e_matrix[1][1]: " << e_matrix[1][1] << endl;
	e_matrix[1][1] = 100;
	cout << "Проверка перегрузки [][]. Получим элемент e_matrix[1][1]: " << e_matrix[1][1] << endl;

	return 0;
}
