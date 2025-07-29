#ifndef DEF_GUI_UTILS_HPP
#define DEF_GUI_UTILS_HPP

#include <string>
#include <cmath>
#include <algorithm>

namespace def
{
	namespace gui
	{
//! START DECLARATION
		enum Align
		{
			ALIGN_LEFT = 1 << 0,
			ALIGN_CENTRE = 1 << 1,
			ALIGN_RIGHT = 1 << 2,
			ALIGN_TOP = 1 << 3,
			ALIGN_BOTTOM = 1 << 4
		};

		struct Colour
		{
			unsigned char r = 0;
			unsigned char g = 0;
			unsigned char b = 0;
			unsigned char a = 255;
		};

		template <class T>
		struct Vector2D
		{
			static_assert(std::is_arithmetic<T>::value, "Vector2D<T> must be numeric");

			Vector2D() = default;
			Vector2D(const T& x, const T& y) : x(x), y(y) {}

			Vector2D(const Vector2D&) = default;
			Vector2D& operator=(const Vector2D&) = default;

			T x = 0, y = 0;

			inline Vector2D Clamp(const Vector2D& start, const Vector2D& end) const;
			inline Vector2D Lerp(const Vector2D& v, const double t) const;

			inline T Distance(const Vector2D& v) const;
			inline T DotProduct(const Vector2D& v) const;
			inline T CrossProduct(const Vector2D& v) const;

			inline T Angle(const Vector2D& v) const;

			inline T Length2() const;
			inline T Length() const;

			inline T ManhattanDistance(const Vector2D& v) const;

			inline Vector2D Max(const Vector2D& v) const;
			inline Vector2D Min(const Vector2D& v) const;

			inline void Swap(Vector2D& v);

			inline Vector2D Normalise() const;
			inline Vector2D Abs() const;

			inline Vector2D Perpendicular() const;

			inline Vector2D Floor() const;
			inline Vector2D Ceil() const;
			inline Vector2D Round() const;

			inline Vector2D Cartesian() const;
			inline Vector2D Polar() const;

			inline std::string ToString() const;

			template <class F>
			inline operator Vector2D<F>() const
			{
				return { static_cast<F>(this->x), static_cast<F>(this->y) };
			}
		};

		typedef Vector2D<int> Vector2i;
		typedef Vector2D<float> Vector2f;
		typedef Vector2D<double> Vector2d;
//! END DECLARATION

//! START IMPLEMENTATION
		template <class T>
		inline Vector2D<T> Vector2D<T>::Clamp(const Vector2D& start, const Vector2D& end) const
		{
			return { std::clamp(x, start.x, end.x), std::clamp(y, start.y, end.y) };
		}

		template <class T>
		inline Vector2D<T> Vector2D<T>::Lerp(const Vector2D& v, const double t) const
		{
			return { (T)std::lerp(x, v.x, t), (T)std::lerp(y, v.y, t) };
		}

		template <class T>
		inline T Vector2D<T>::Distance(const Vector2D& v) const
		{
			return (*this - v).Length();
		}

		template <class T>
		inline T Vector2D<T>::DotProduct(const Vector2D& v) const
		{
			return x * v.x + y * v.y;
		}

		template <class T>
		inline T Vector2D<T>::CrossProduct(const Vector2D& v) const
		{
			return x * v.y - y * v.x;
		}

		template <class T>
		inline T Vector2D<T>::Angle(const Vector2D& v) const
		{
			return acos(DotProduct(v) / (Length() + v.Length()));
		}

		template <class T>
		inline T Vector2D<T>::Length2() const
		{
			return x * x + y * y;
		}

		template <class T>
		inline T Vector2D<T>::Length() const
		{
			return std::sqrt(x * x + y * y);
		}

		template <class T>
		inline T Vector2D<T>::ManhattanDistance(const Vector2D& v) const
		{
			return std::abs(x - v.x) + std::abs(y - v.y);
		}

		template <class T>
		inline Vector2D<T> Vector2D<T>::Max(const Vector2D& v) const
		{
			return Vector2D(std::max(x, v.x), std::max(y, v.y));
		}

		template <class T>
		inline Vector2D<T> Vector2D<T>::Min(const Vector2D& v) const
		{
			return Vector2D(std::min(x, v.x), std::min(y, v.y));
		}

		template <class T>
		inline void Vector2D<T>::Swap(Vector2D& v)
		{
			std::swap(x, v.x);
			std::swap(y, v.y);
		}

		template <class T>
		inline Vector2D<T> Vector2D<T>::Normalise() const
		{
			const T n = (T)1 / Length();
			return Vector2D(x * n, y * n);
		}

		template <class T>
		inline Vector2D<T> Vector2D<T>::Abs() const
		{
			return Vector2D(std::abs(x), std::abs(y));
		}

		template <class T>
		inline Vector2D<T> Vector2D<T>::Perpendicular() const
		{
			return Vector2D(-y, x);
		}

		template <class T>
		inline Vector2D<T> Vector2D<T>::Floor() const
		{
			return Vector2D(std::floor(x), std::floor(y));
		}

		template <class T>
		inline Vector2D<T> Vector2D<T>::Ceil() const
		{
			return Vector2D(std::ceil(x), std::ceil(y));
		}

		template <class T>
		inline Vector2D<T> Vector2D<T>::Round() const
		{
			return Vector2D(std::round(x), std::round(y));
		}

		template <class T>
		inline Vector2D<T> Vector2D<T>::Cartesian() const
		{
			return Vector2D(std::cos(y) * x, std::sin(y) * x);
		}

		template <class T>
		inline Vector2D<T> Vector2D<T>::Polar() const
		{
			return Vector2D(Length(), atan2(y, x));
		}

		template <class T>
		inline std::string Vector2D<T>::ToString() const
		{
			return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
		}

		template <class T1, class T2>
		Vector2D<T1>& operator+=(Vector2D<T1>& v1, const Vector2D<T2>& v2)
		{
			v1.x += v2.x;
			v1.y += v2.y;
			return v1;
		}

		template <class T1, class T2>
		Vector2D<T1>& operator-=(Vector2D<T1>& v1, const Vector2D<T2>& v2)
		{
			v1.x -= v2.x;
			v1.y -= v2.y;
			return v1;
		}

		template <class T1, class T2>
		Vector2D<T1>& operator*=(Vector2D<T1>& v1, const Vector2D<T2>& v2)
		{
			v1.x *= v2.x;
			v1.y *= v2.y;
			return v1;
		}

		template <class T1, class T2>
		Vector2D<T1>& operator/=(Vector2D<T1>& v1, const Vector2D<T2>& v2)
		{
			v1.x /= v2.x;
			v1.y /= v2.y;
			return v1;
		}

		template <class T1, class T2>
		Vector2D<T1>& operator%=(Vector2D<T1>& v1, const Vector2D<T2>& v2)
		{
			v1.x %= v2.x;
			v1.y %= v2.y;
			return v1;
		}

		template <class T1, class T2>
		Vector2D<T1>& operator+=(Vector2D<T1>& v1, const T2& v2)
		{
			v1.x += v2;
			v1.y += v2;
			return v1;
		}

		template <class T1, class T2>
		Vector2D<T1>& operator-=(Vector2D<T1>& v1, const T2& v2)
		{
			v1.x -= v2;
			v1.y -= v2;
			return v1;
		}

		template <class T1, class T2>
		Vector2D<T1>& operator*=(Vector2D<T1>& v1, const T2& v2)
		{
			v1.x *= v2;
			v1.y *= v2;
			return v1;
		}

		template <class T1, class T2>
		Vector2D<T1>& operator/=(Vector2D<T1>& v1, const T2& v2)
		{
			v1.x /= v2;
			v1.y /= v2;
			return v1;
		}

		template <class T1, class T2>
		Vector2D<T1>& operator%=(Vector2D<T1>& v1, const T2& v2)
		{
			v1.x %= v2;
			v1.y %= v2;
			return v1;
		}

		template <class T1, class T2>
		Vector2D<decltype(T1(1) + T2(1))> operator+(const Vector2D<T1>& v1, const Vector2D<T2>& v2)
		{
			return Vector2D(v1.x + v2.x, v1.y + v2.y);
		}

		template <class T1, class T2>
		Vector2D<decltype(T1(1) + T2(1))> operator-(const Vector2D<T1>& v1, const Vector2D<T2>& v2)
		{
			return Vector2D(v1.x - v2.x, v1.y - v2.y);
		}

		template <class T1, class T2>
		Vector2D<decltype(T1(1) + T2(1))> operator*(const Vector2D<T1>& v1, const Vector2D<T2>& v2)
		{
			return Vector2D(v1.x * v2.x, v1.y * v2.y);
		}

		template <class T1, class T2>
		Vector2D<decltype(T1(1) + T2(1))> operator/(const Vector2D<T1>& v1, const Vector2D<T2>& v2)
		{
			return Vector2D(v1.x / v2.x, v1.y / v2.y);
		}

		template <class T1, class T2>
		Vector2D<decltype(T1(1) + T2(1))> operator%(const Vector2D<T1>& v1, const Vector2D<T2>& v2)
		{
			return Vector2D(v1.x % v2.x, v1.y % v2.y);
		}

		template <class T1, class T2>
		Vector2D<decltype(T1(1) + T2(1))> operator+(const Vector2D<T1>& v1, const T2& v2)
		{
			return Vector2D(v1.x + v2, v1.y + v2);
		}

		template <class T1, class T2>
		Vector2D<decltype(T1(1) + T2(1))> operator-(const Vector2D<T1>& v1, const T2& v2)
		{
			return Vector2D(v1.x - v2, v1.y - v2);
		}

		template <class T1, class T2>
		Vector2D<decltype(T1(1) + T2(1))> operator*(const Vector2D<T1>& v1, const T2& v2)
		{
			return Vector2D(v1.x * v2, v1.y * v2);
		}

		template <class T1, class T2>
		Vector2D<decltype(T1(1) + T2(1))> operator/(const Vector2D<T1>& v1, const T2& v2)
		{
			return Vector2D(v1.x / v2, v1.y / v2);
		}

		template <class T1, class T2>
		Vector2D<decltype(T1(1) + T2(1))> operator+(const T1& v1, const Vector2D<T2>& v2)
		{
			return Vector2D(v1 + v2.x, v1 + v2.y);
		}

		template <class T1, class T2>
		Vector2D<decltype(T1(1) + T2(1))> operator-(const T1& v1, const Vector2D<T2>& v2)
		{
			return Vector2D(v1 - v2.x, v1 - v2.y);
		}

		template <class T1, class T2>
		Vector2D<decltype(T1(1) + T2(1))> operator*(const T1& v1, const Vector2D<T2>& v2)
		{
			return Vector2D(v1 * v2.x, v1 * v2.y);
		}

		template <class T1, class T2>
		Vector2D<decltype(T1(1) + T2(1))> operator/(const T1& v1, const Vector2D<T2>& v2)
		{
			return Vector2D(v1 / v2.x, v1 / v2.y);
		}

		template <class T1, class T2>
		Vector2D<decltype(T1(1) + T2(1))> operator%(const T1& v1, const Vector2D<T2>& v2)
		{
			return Vector2D(v1 % v2.x, v1 % v2.y);
		}

		template <class T>
		Vector2D<T> operator-(const Vector2D<T>& v)
		{
			return Vector2D(-v.x, -v.y);
		}

		template <class T1, class T2>
		bool operator==(const Vector2D<T1>& v1, const Vector2D<T2>& v2)
		{
			return v1.x == v2.x && v1.y == v2.y;
		}

		template <class T1, class T2>
		bool operator<=(const Vector2D<T1>& v1, const Vector2D<T2>& v2)
		{
			return v1.x <= v2.x && v1.y <= v2.y;
		}

		template <class T1, class T2>
		bool operator>=(const Vector2D<T1>& v1, const Vector2D<T2>& v2)
		{
			return v1.x >= v2.x && v1.y >= v2.y;
		}

		template <class T1, class T2>
		bool operator<(const Vector2D<T1>& v1, const Vector2D<T2>& v2)
		{
			return v1.x < v2.x && v1.y < v2.y;
		}

		template <class T1, class T2>
		bool operator>(const Vector2D<T1>& v1, const Vector2D<T2>& v2)
		{
			return v1.x > v2.x && v1.y > v2.y;
		}

		template <class T1, class T2>
		bool operator!=(const Vector2D<T1>& v1, const Vector2D<T2>& v2)
		{
			return v1.x != v2.x || v1.y != v2.y;
		}

		inline bool IsPointInRect(const Vector2i& point, const Vector2i& rect_pos, const Vector2i& rect_size)
		{
			return point >= rect_pos && point < rect_pos + rect_size;
		}
//! END IMPLEMENTATION
	}
}

#endif
