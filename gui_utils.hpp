#pragma once

#include <string>
#include <cmath>
#include <algorithm>

namespace def
{
	namespace gui
	{
		enum class Align
		{
			LEFT,
			CENTRE,
			RIGHT
		};
	}

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

		constexpr Vector2D() = default;
		constexpr Vector2D(const T& x, const T& y) : x(x), y(y)
		{

		}

		constexpr Vector2D(const Vector2D&) = default;
		constexpr Vector2D& operator=(const Vector2D&) = default;

		T x = 0, y = 0;

		constexpr Vector2D<T> clamp(const Vector2D& start, const Vector2D& end) const
		{
			return { std::clamp(x, start.x, end.x), std::clamp(y, start.y, end.y) };
		}

		constexpr Vector2D<T> lerp(const Vector2D& v, const double t) const
		{
			return { (T)std::lerp(x, v.x, t), (T)std::lerp(y, v.y, t) };
		}

		constexpr auto dist(const Vector2D<T>& v) const
		{
			return (*this - v).length();
		}

		constexpr auto dot(const Vector2D& v) const
		{
			return x * v.x + y * v.y;
		}

		constexpr auto cross(const Vector2D& v) const
		{
			return x * v.y - y * v.x;
		}

		constexpr auto angle(const Vector2D& v) const
		{
			return acos(dot(v) / (length() + v.length()));
		}

		constexpr auto length() const
		{
			return mag();
		}

		constexpr auto mag() const
		{
			return static_cast<T>(std::sqrt(x * x + y * y));
		}

		constexpr auto mag2() const
		{
			return static_cast<T>(x * x + y * y);
		}

		constexpr auto man(const Vector2D& v) const
		{
			return std::abs(x - v.x) + std::abs(y - v.y);
		}

		constexpr Vector2D<T> max(const Vector2D& v) const
		{
			return Vector2D(std::max(x, v.x), std::max(y, v.y));
		}

		constexpr Vector2D<T> min(const Vector2D& v) const
		{
			return Vector2D(std::min(x, v.x), std::min(y, v.y));
		}

		constexpr void swap(Vector2D& v)
		{
			std::swap(x, v.x);
			std::swap(y, v.y);
		}

		constexpr Vector2D<T> norm() const
		{
			auto n = (T)1 / mag();
			return Vector2D(x * n, y * n);
		}

		constexpr Vector2D<T> abs() const
		{
			return Vector2D(std::abs(x), std::abs(y));
		}

		constexpr Vector2D<T> perp() const
		{
			return Vector2D(-y, x);
		}

		constexpr Vector2D<T> floor() const
		{
			return Vector2D(std::floor(x), std::floor(y));
		}

		constexpr Vector2D<T> ceil() const
		{
			return Vector2D(std::ceil(x), std::ceil(y));
		}

		constexpr Vector2D<T> round() const
		{
			return Vector2D(std::round(x), std::round(y));
		}

		constexpr Vector2D<T> cart() const
		{
			return Vector2D(cos(y) * x, sin(y) * x);
		}

		constexpr Vector2D<T> polar() const
		{
			return Vector2D(mag(), atan2(y, x));
		}

		constexpr std::string str() const
		{
			return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
		}

		template <class F>
		constexpr operator Vector2D<F>() const
		{
			return { static_cast<F>(this->x), static_cast<F>(this->y) };
		}
	};

	typedef Vector2D<int> Vector2i;
	typedef Vector2D<float> Vector2f;
	typedef Vector2D<double> Vector2d;

	template <class T1, class T2>
	constexpr Vector2D<T1>& operator+=(Vector2D<T1>& v1, const Vector2D<T2>& v2)
	{
		v1.x += v2.x;
		v1.y += v2.y;
		return v1;
	}

	template <class T1, class T2>
	constexpr Vector2D<T1>& operator-=(Vector2D<T1>& v1, const Vector2D<T2>& v2)
	{
		v1.x -= v2.x;
		v1.y -= v2.y;
		return v1;
	}

	template <class T1, class T2>
	constexpr Vector2D<T1>& operator*=(Vector2D<T1>& v1, const Vector2D<T2>& v2)
	{
		v1.x *= v2.x;
		v1.y *= v2.y;
		return v1;
	}

	template <class T1, class T2>
	constexpr Vector2D<T1>& operator/=(Vector2D<T1>& v1, const Vector2D<T2>& v2)
	{
		v1.x /= v2.x;
		v1.y /= v2.y;
		return v1;
	}

	template <class T1, class T2>
	constexpr Vector2D<T1>& operator%=(Vector2D<T1>& v1, const Vector2D<T2>& v2)
	{
		v1.x %= v2.x;
		v1.y %= v2.y;
		return v1;
	}

	template <class T1, class T2>
	constexpr Vector2D<T1>& operator+=(Vector2D<T1>& v1, const T2& v2)
	{
		v1.x += v2;
		v1.y += v2;
		return v1;
	}

	template <class T1, class T2>
	constexpr Vector2D<T1>& operator-=(Vector2D<T1>& v1, const T2& v2)
	{
		v1.x -= v2;
		v1.y -= v2;
		return v1;
	}

	template <class T1, class T2>
	constexpr Vector2D<T1>& operator*=(Vector2D<T1>& v1, const T2& v2)
	{
		v1.x *= v2;
		v1.y *= v2;
		return v1;
	}

	template <class T1, class T2>
	constexpr Vector2D<T1>& operator/=(Vector2D<T1>& v1, const T2& v2)
	{
		v1.x /= v2;
		v1.y /= v2;
		return v1;
	}

	template <class T1, class T2>
	constexpr Vector2D<T1>& operator%=(Vector2D<T1>& v1, const T2& v2)
	{
		v1.x %= v2;
		v1.y %= v2;
		return v1;
	}

	template <class T1, class T2>
	constexpr Vector2D<decltype(T1(1) + T2(1))> operator+(const Vector2D<T1>& v1, const Vector2D<T2>& v2)
	{
		return Vector2D(v1.x + v2.x, v1.y + v2.y);
	}

	template <class T1, class T2>
	constexpr Vector2D<decltype(T1(1) + T2(1))> operator-(const Vector2D<T1>& v1, const Vector2D<T2>& v2)
	{
		return Vector2D(v1.x - v2.x, v1.y - v2.y);
	}

	template <class T1, class T2>
	constexpr Vector2D<decltype(T1(1) + T2(1))> operator*(const Vector2D<T1>& v1, const Vector2D<T2>& v2)
	{
		return Vector2D(v1.x * v2.x, v1.y * v2.y);
	}

	template <class T1, class T2>
	constexpr Vector2D<decltype(T1(1) + T2(1))> operator/(const Vector2D<T1>& v1, const Vector2D<T2>& v2)
	{
		return Vector2D(v1.x / v2.x, v1.y / v2.y);
	}

	template <class T1, class T2>
	constexpr Vector2D<decltype(T1(1) + T2(1))> operator%(const Vector2D<T1>& v1, const Vector2D<T2>& v2)
	{
		return Vector2D(v1.x % v2.x, v1.y % v2.y);
	}

	template <class T1, class T2>
	constexpr Vector2D<decltype(T1(1) + T2(1))> operator+(const Vector2D<T1>& v1, const T2& v2)
	{
		return Vector2D(v1.x + v2, v1.y + v2);
	}

	template <class T1, class T2>
	constexpr Vector2D<decltype(T1(1) + T2(1))> operator-(const Vector2D<T1>& v1, const T2& v2)
	{
		return Vector2D(v1.x - v2, v1.y - v2);
	}

	template <class T1, class T2>
	constexpr Vector2D<decltype(T1(1) + T2(1))> operator*(const Vector2D<T1>& v1, const T2& v2)
	{
		return Vector2D(v1.x * v2, v1.y * v2);
	}

	template <class T1, class T2>
	constexpr Vector2D<decltype(T1(1) + T2(1))> operator/(const Vector2D<T1>& v1, const T2& v2)
	{
		return Vector2D(v1.x / v2, v1.y / v2);
	}

	template <class T1, class T2>
	constexpr Vector2D<decltype(T1(1) + T2(1))> operator+(const T1& v1, const Vector2D<T2>& v2)
	{
		return Vector2D(v1 + v2.x, v1 + v2.y);
	}

	template <class T1, class T2>
	constexpr Vector2D<decltype(T1(1) + T2(1))> operator-(const T1& v1, const Vector2D<T2>& v2)
	{
		return Vector2D(v1 - v2.x, v1 - v2.y);
	}

	template <class T1, class T2>
	constexpr Vector2D<decltype(T1(1) + T2(1))> operator*(const T1& v1, const Vector2D<T2>& v2)
	{
		return Vector2D(v1 * v2.x, v1 * v2.y);
	}

	template <class T1, class T2>
	constexpr Vector2D<decltype(T1(1) + T2(1))> operator/(const T1& v1, const Vector2D<T2>& v2)
	{
		return Vector2D(v1 / v2.x, v1 / v2.y);
	}

	template <class T1, class T2>
	constexpr Vector2D<decltype(T1(1) + T2(1))> operator%(const T1& v1, const Vector2D<T2>& v2)
	{
		return Vector2D(v1 % v2.x, v1 % v2.y);
	}

	template <class T>
	constexpr Vector2D<T> operator-(const Vector2D<T>& v)
	{
		return Vector2D(-v.x, -v.y);
	}

	template <class T1, class T2>
	constexpr bool operator==(const Vector2D<T1>& v1, const Vector2D<T2>& v2)
	{
		return v1.x == v2.x && v1.y == v2.y;
	}

	template <class T1, class T2>
	constexpr bool operator<=(const Vector2D<T1>& v1, const Vector2D<T2>& v2)
	{
		return v1.x <= v2.x && v1.y <= v2.y;
	}

	template <class T1, class T2>
	constexpr bool operator>=(const Vector2D<T1>& v1, const Vector2D<T2>& v2)
	{
		return v1.x >= v2.x && v1.y >= v2.y;
	}

	template <class T1, class T2>
	constexpr bool operator<(const Vector2D<T1>& v1, const Vector2D<T2>& v2)
	{
		return v1.x < v2.x && v1.y < v2.y;
	}

	template <class T1, class T2>
	constexpr bool operator>(const Vector2D<T1>& v1, const Vector2D<T2>& v2)
	{
		return v1.x > v2.x && v1.y > v2.y;
	}

	template <class T1, class T2>
	constexpr bool operator!=(const Vector2D<T1>& v1, const Vector2D<T2>& v2)
	{
		return v1.x != v2.x || v1.y != v2.y;
	}

	bool IsPointInRect(const Vector2i& point, const Vector2i& rect_pos, const Vector2i& rect_size);
}
