#ifndef MATRIX_H
#define MATRIX_H

namespace mat {
	class Matrix
	{
	private:
		static size_t static_id;
		static bool debug;

		double* matrix = nullptr;
		size_t n = 0, m = 0, id = 0;

		class Row {
		private:
			size_t index;
			const Matrix* owner;
		public:
			/* Конструктор */
			Row(const Matrix* owner, size_t i);
			/* Перегрузка оператора [] */
			double operator[](size_t x) const;
			double& operator[](size_t x);
		};
	public:
		/* Конструкторы и деструктор */
		Matrix(size_t n, size_t m, double* matrix = nullptr);
		explicit Matrix(size_t n = 0);
		
		~Matrix();

		/* Копирования */
		Matrix(const Matrix& other);
		const Matrix& operator=(const Matrix& other);

		/* Перемещения */
		Matrix(Matrix&& other);
		Matrix& operator=(Matrix&& other) noexcept;

		/* Сделать матрицу пустой */
		Matrix& make_null();

		/* Функции проверки */
		bool allow_multiply(const Matrix& other) const;
		bool allow_summ(const Matrix& other) const;
		bool is_empty() const;

		/* Геттеры */
		double get_max() const;
		double get_min() const;
		size_t get_m() const;
		size_t get_n() const;
		size_t get_size() const;
		size_t get_id() const;

		/* Перегрузки операторов */
		Matrix& operator+=(const Matrix& other);
		Matrix& operator-=(const Matrix& other);
		Matrix& operator*=(const Matrix& other);
		Matrix& operator*=(double k);
		
		/* Перегрузки операторов для внешних операций */
		Matrix operator+(const Matrix& other);
		Matrix operator-(const Matrix& other);
		Matrix operator*(const Matrix& other);
		Matrix operator*(double k);

		/* Перегрузка оператора [][] */
		Matrix::Row operator[](size_t x);
		const Matrix::Row operator[](size_t x) const;

		/* Перегрузка внешних операторов */
		friend std::ostream& operator << (std::ostream& out, Matrix& matrix);
	};

	/* Внешние функции */
	double* create_matrix(size_t n, size_t m);
	Matrix generate_matrix(size_t n = 2, size_t m = 2, double min = 0, double max = 20);
}

#endif

