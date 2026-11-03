#pragma once
#include <cstddef>
#include <cassert>
#include <optional>
#include <type_traits>
#include <initializer_list>

#include "Core.h"
#include <Pixel/Vector.h>

/*

	***REQUIRES C++17 OR GREATER***
	
	USAGE
	=====

	- Pixel::Matrix<float, 4, 4> m;
	- Pixel::Matrix<float, 2, 3> a; Pixel::Matrix<float, 3, 4> b; auto c = a * b;
	- for (float& v : m) v *= 2.0f;
	- for (const float& v : m) sum += v;
	- if (auto inv = m.inverse()) { use(*inv); }
	- a.approxEqual(b) or a.approxEqual(b, 1e-4f)
	- Pixel::Matrix<float, 4, 4> result = Pixel::Matrix<float, 4, 4>::identity();

*/


namespace Pixel
{	
	template<typename T, std::size_t ROWS, std::size_t COLS>
	class Matrix
	{
	public:

		static_assert(ROWS > 0 && COLS > 0); //MATRICES MUST HAVE NON_ZERO DIMENSIONS

		constexpr T& operator()(std::size_t r, std::size_t c) { return m_Data[r * COLS + c]; }
		constexpr const T& operator()(std::size_t r, std::size_t c) const { return m_Data[r * COLS + c]; }
		static constexpr std::size_t rows() { return ROWS; }
		static constexpr std::size_t cols() { return COLS; }

		constexpr Matrix() = default;
		constexpr Matrix(std::initializer_list<T> values)
		{
			assert(values.size() <= ROWS * COLS);
			std::size_t i = 0;
			for (const T& v : values)
				if (i < ROWS * COLS) m_Data[i++] = v;
		}

		constexpr void fill(const T& v)
		{
			for (std::size_t i = 0; i < ROWS*COLS; i++)
			{
				m_Data[i] = v;	
			}
		}

		static constexpr Matrix identity()
		{
			static_assert(ROWS == COLS, "identity() is only valid for square matrices");
			Matrix result{};
			for (std::size_t r = 0; r < ROWS; r++)
			{
				result(r, r) = T{ 1 };
			}
			return result;
		}

		constexpr T* data() { return m_Data; }
		constexpr const T* data() const { return m_Data; }

		//Elementwise and Scalar Ops
		constexpr Matrix& operator+=(const Matrix& rhs)
		{
			for (std::size_t i = 0; i < ROWS * COLS; ++i)
			{
				m_Data[i] += rhs.m_Data[i];
			}
			return *this;
		}
		constexpr friend Matrix operator+(Matrix l, const Matrix& r) { return l += r; }

		constexpr Matrix& operator-=(const Matrix& rhs)
		{
			for (std::size_t i = 0; i < ROWS * COLS; ++i)
			{
				m_Data[i] -= rhs.m_Data[i];
			}
			return *this;
		}
		constexpr friend Matrix operator-(Matrix l, const Matrix& r) { return l -= r; }

		constexpr Matrix& operator*=(const T& s)
		{
			for (std::size_t i = 0; i < ROWS * COLS; ++i)
			{
				m_Data[i] *= s;
			}
			return *this;
		}
		constexpr friend Matrix operator*(Matrix l, const T& s) { return l *= s; }
		constexpr friend Matrix operator*(const T& s, Matrix m) { return m *= s; }

		template<std::size_t N>
		constexpr Matrix<T, ROWS, N> operator*(const Matrix<T, COLS, N>& rhs) const
		{
			Matrix<T, ROWS, N> result{};
			for (std::size_t i = 0; i < ROWS; ++i)
			{
				for (std::size_t j = 0; j < N; ++j)
				{
					for (std::size_t k = 0; k < COLS; ++k)
					{
						result(i, j) += (*this)(i, k) * rhs(k, j);
					}
				}
			}
			return result;
		}

		constexpr bool operator==(const Matrix& rhs) const
		{
			for (std::size_t i = 0; i < ROWS * COLS; ++i)
				if (m_Data[i] != rhs.m_Data[i])
					return false;
			return true;
		}
		constexpr bool operator!=(const Matrix& rhs) const { return !(*this == rhs); }

		constexpr bool approxEqual(const Matrix& rhs, T eps = T(1e-5)) const
		{
			for (std::size_t i = 0; i < ROWS * COLS; ++i)
			{
				const T d = m_Data[i] - rhs.m_Data[i];
				if ((d < T{} ? -d : d) > eps)
					return false;
			}
			return true;
		}

		constexpr Matrix<T, COLS, ROWS> transposed() const
		{
			Matrix<T, COLS, ROWS> result{};
			for (std::size_t r = 0; r < ROWS; ++r)
				for (std::size_t c = 0; c < COLS; ++c)
					result(c, r) = (*this)(r, c);
			return result;
		}
	
		constexpr T& at(std::size_t r, std::size_t c)
		{
			assert(r < ROWS && c < COLS);
			return m_Data[r * COLS + c];
		}

		constexpr const T& at(std::size_t r, std::size_t c) const
		{
			assert(r < ROWS && c < COLS);
			return m_Data[r * COLS + c];
		}

		constexpr T* begin() { return m_Data; }
		constexpr T* end() { return m_Data + ROWS * COLS; }
		constexpr const T* begin() const { return m_Data; }
		constexpr const T* end() const { return m_Data + ROWS * COLS; }
		constexpr const T* cbegin() const { return m_Data; }
		constexpr const T* cend() const { return m_Data + ROWS * COLS; }

		//The trace is the sum of a square matrix’s diagonal elements
		constexpr T trace() const
		{
			static_assert(ROWS == COLS, "trace() is only valid for square matrices");
			T sum{};
			for (std::size_t i = 0; i < ROWS; ++i)
				sum += (*this)(i, i);
			return sum;
		}

		constexpr T determinant() const
		{
			static_assert(ROWS == COLS, "determinant() is only valid for square matrices");
			static_assert(ROWS >= 1 && ROWS <= 4, "determinant() is implemented for sizes 1 to 4");

			const auto& m = *this;

			if constexpr (ROWS == 1)
			{
				return m(0, 0);
			}
			else if constexpr (ROWS == 2)
			{
				return m(0, 0) * m(1, 1) - m(0, 1) * m(1, 0);
			}
			else if constexpr (ROWS == 3)
			{
				return m(0, 0) * (m(1, 1) * m(2, 2) - m(1, 2) * m(2, 1))
					- m(0, 1) * (m(1, 0) * m(2, 2) - m(1, 2) * m(2, 0))
					+ m(0, 2) * (m(1, 0) * m(2, 1) - m(1, 1) * m(2, 0));
			}
			else // 4x4, Laplace expansion using 2x2 sub-determinants
			{
				const T s0 = m(0, 0) * m(1, 1) - m(1, 0) * m(0, 1);
				const T s1 = m(0, 0) * m(1, 2) - m(1, 0) * m(0, 2);
				const T s2 = m(0, 0) * m(1, 3) - m(1, 0) * m(0, 3);
				const T s3 = m(0, 1) * m(1, 2) - m(1, 1) * m(0, 2);
				const T s4 = m(0, 1) * m(1, 3) - m(1, 1) * m(0, 3);
				const T s5 = m(0, 2) * m(1, 3) - m(1, 2) * m(0, 3);

				const T c5 = m(2, 2) * m(3, 3) - m(3, 2) * m(2, 3);
				const T c4 = m(2, 1) * m(3, 3) - m(3, 1) * m(2, 3);
				const T c3 = m(2, 1) * m(3, 2) - m(3, 1) * m(2, 2);
				const T c2 = m(2, 0) * m(3, 3) - m(3, 0) * m(2, 3);
				const T c1 = m(2, 0) * m(3, 2) - m(3, 0) * m(2, 2);
				const T c0 = m(2, 0) * m(3, 1) - m(3, 0) * m(2, 1);

				return s0 * c5 - s1 * c4 + s2 * c3 + s3 * c2 - s4 * c1 + s5 * c0;
			}
		}

		constexpr std::optional<Matrix> inverse() const
		{
			static_assert(ROWS == COLS, "inverse() is only valid for square matrices");
			static_assert(std::is_floating_point_v<T>, "inverse() requires a floating-point type");

			constexpr T epsilon = T(1e-6);

			Matrix a = *this;
			Matrix inv = identity();

			for (std::size_t col = 0; col < ROWS; ++col)
			{
				// Partial pivoting: pick the row with the largest magnitude in this column
				std::size_t pivot = col;
				T best = a(col, col) < T{} ? -a(col, col) : a(col, col);
				for (std::size_t r = col + 1; r < ROWS; ++r)
				{
					T v = a(r, col) < T{} ? -a(r, col) : a(r, col);
					if (v > best)
					{
						best = v;
						pivot = r;
					}
				}

				if (best < epsilon)
					return std::nullopt; // singular or near-singular

				if (pivot != col)
				{
					for (std::size_t c = 0; c < COLS; ++c)
					{
						T t = a(col, c);   a(col, c) = a(pivot, c);     a(pivot, c) = t;
						t = inv(col, c);   inv(col, c) = inv(pivot, c); inv(pivot, c) = t;
					}
				}

				// Normalise pivot row
				const T p = a(col, col);
				for (std::size_t c = 0; c < COLS; ++c)
				{
					a(col, c) /= p;
					inv(col, c) /= p;
				}

				// Eliminate this column from every other row
				for (std::size_t r = 0; r < ROWS; ++r)
				{
					if (r == col) continue;
					const T f = a(r, col);
					if (f == T{}) continue;
					for (std::size_t c = 0; c < COLS; ++c)
					{
						a(r, c) -= f * a(col, c);
						inv(r, c) -= f * inv(col, c);
					}
				}
			}
			return inv;
		}

		Matrix& translate(const Vec3f& v)
		{
			static_assert(ROWS == 4 && COLS == 4,"translate(Vec3f) requires a 4x4 matrix");

			*this = identity();
			(*this)(0, 3) = v.x;
			(*this)(1, 3) = v.y;
			(*this)(2, 3) = v.z;
			return *this;
		}

		Matrix& scale(const Vec3f& v)
		{
			static_assert(ROWS == 4 && COLS == 4, "scale(Vec3f) requires a 4x4 matrix");

			*this = identity();
			(*this)(0, 0) = v.x;
			(*this)(1, 1) = v.y;
			(*this)(2, 2) = v.z;
			return *this;
		}

		Matrix& rotate(const Vec3f& axis, float angleInRads)
		{
			static_assert(ROWS == 4 && COLS == 4,
				"rotate requires a 4x4 matrix");
			static_assert(std::is_floating_point_v<T>,
				"rotate requires a floating-point matrix type");

			const float c = std::cos(angleInRads);
			const float s = std::sin(angleInRads);
			const float t = 1.0f - c;
			const float x = axis.x;
			const float y = axis.y;
			const float z = axis.z;

			// The Rodrigues formula requires a normalized axis.
			axis.normalized();
			*this = identity();

			(*this)(0, 0) = c + x * x * t;
			(*this)(0, 1) = x * y * t - z * s;
			(*this)(0, 2) = x * z * t + y * s;

			(*this)(1, 0) = y * x * t + z * s;
			(*this)(1, 1) = c + y * y * t;
			(*this)(1, 2) = y * z * t - x * s;

			(*this)(2, 0) = z * x * t - y * s;
			(*this)(2, 1) = z * y * t + x * s;
			(*this)(2, 2) = c + z * z * t;

			return *this;
		}


	private:
		T m_Data[ROWS*COLS]{};
	};
}