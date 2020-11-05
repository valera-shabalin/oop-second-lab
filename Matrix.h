#ifndef MATRIX_H
#define MATRIX_H

namespace mat {
	class Matrix
	{
	private:
		static size_t static_id;
		static bool debug;

		double* matrix;
		size_t n = 0, m = 0, id = 0;

		class Row {
		private:
			size_t index;
			class Matrix* owner;
		public:
			/* Конструктор */
			Row(Matrix& owner, size_t i);
			/* Перегрузка оператора [] */
			double operator[](size_t x);
		};
	public:
		/* Конструкторы и деструктор */
		Matrix(size_t n = 0, size_t m = 0, double* matrix = nullptr);
		explicit Matrix(size_t n);
		
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
		double* get_matrix() const;

		/* Перегрузки операторов */
		Matrix& operator+=(const Matrix& other);
		Matrix& operator-=(const Matrix& other);
		Matrix& operator*=(const Matrix& other);
		Matrix& operator*=(double k);
		Row operator[](size_t x);
		double cell(size_t x, size_t y);
		friend std::ostream& operator << (std::ostream& out, Matrix& matrix);

		/* Перегрузки операторов для внешних операций */
		Matrix operator+(const Matrix& other);
		Matrix operator-(const Matrix& other);
		Matrix operator*(const Matrix& other);
		Matrix operator*(double k);
	};

	/* Внешние функции */
	double* create_matrix(size_t n, size_t m);
}


#endif

