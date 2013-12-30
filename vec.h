#ifndef _VEC_H_
#define _VEC_H_

#include <cmath>
#define x_error_metric 1.0e-5
#define y_error_metric 1.0e-4
#define z_error_metric 1.0e-4


struct Face{
	int x;
	int y;
	int z;
};

template <class T>
struct vec3g {
	typedef vec3g<T> thisclass ;

	vec3g() : x(0), y(0), z(0) { }
	vec3g(T x_in, T y_in, T z_in) : x(x_in), y(y_in), z(z_in) {  }

	inline T length2() const { return x*x+y*y+z*z ; }
	inline T length() const { return sqrt(x*x+y*y+z*z) ; }

	// operators
	inline thisclass& operator+=(const thisclass& v) { x += v.x ; y += v.y ; z += v.z ; return *this ; }
	inline thisclass& operator-=(const thisclass& v) { x -= v.x ; y -= v.y ; z -= v.z ; return *this ; }
	inline thisclass& operator*=(const thisclass& v) { x *= v.x ; y *= v.y ; z *= v.z ; return *this ; }
	inline thisclass& operator/=(const thisclass& v) { x /= v.x ; y /= v.y ; z /= v.z ; return *this ; }
	template <class T2> inline thisclass& operator*=(T2 s) { x *= T(s) ; y *= T(s) ; z *= T(s) ; return *this ; }
	template <class T2> inline thisclass& operator/=(T2 s) { x /= T(s) ; y /= T(s) ; z /= T(s) ; return *this ; }

	bool operator < (const thisclass& v) const { return (x < v.x && std::abs(x - v.x) > x_error_metric) ||  
	(std::abs(x - v.x) <= x_error_metric && y < v.y && std::abs(y - v.y) > y_error_metric) ||
	(std::abs(x - v.x) <= x_error_metric &&  std::abs(y - v.y) <= y_error_metric && z < v.z && std::abs(z - v.z) > z_error_metric); };

	inline thisclass operator+ (const thisclass& v) const {return thisclass(x+v.x, y+v.y, z+v.z); }
	inline thisclass operator- (const thisclass& v) const {return thisclass(x-v.x, y-v.y, z-v.z); }
	template <class T2> inline thisclass operator* (T2 s) const {return thisclass(x*T(s), y*T(s), z*T(s)); }
	template <class T2> inline thisclass operator/ (T2 s) const {return thisclass(x/T(s), y/T(s), z/T(s)); }

	inline thisclass operator- () const {return thisclass(-x, -y, -z);}

	inline T& operator[](int idx) {
		switch(idx) {
		case 0: return x ; break ;
		case 1: return y ; break ;
		case 2: return z ; break ;
		default: gx_assert_not_reached ;
		}
		return x ;
	}

	inline const T& operator[](int idx) const {
		switch(idx) {
		case 0: return x ; break ;
		case 1: return y ; break ;
		case 2: return z ; break ;
		default: gx_assert_not_reached ;
		}
		return x ;
	}

	T x ;
	T y ;
	T z ;
} ;

template <class T> inline T dot(const vec3g<T>& v1, const vec3g<T>& v2) {  return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;  }

template <class T> inline  vec3g<T> cross(const vec3g<T>& v1, const vec3g<T>& v2) {
	return vec3g<T>(
		v1.y*v2.z - v1.z*v2.y,
		v1.z*v2.x - v1.x*v2.z,
		v1.x*v2.y - v1.y*v2.x
		) ;
}

template <class T> inline vec3g<T> operator-(const vec3g<T>& v1) { return vec3g<T>(-v1.x, -v1.y, -v1.z) ; }
template <class T2, class T> inline vec3g<T> operator*(T2 s, const vec3g<T>& v) { 
	return vec3g<T>(T(s)*v.x, T(s)*v.y, T(s)*v.z) ;   
}

template <class T> inline vec3g<T> operator+(const vec3g<T>& v1, const vec3g<T>& v2) { 
	return vec3g<T>(v1.x+v2.x, v1.y+v2.y, v1.z+v2.z) ; 
}

template <class T> inline vec3g<T> operator-(const vec3g<T>& v1, const vec3g<T>& v2) { 
	return vec3g<T>(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z) ; 
}

// Compatibility with GLSL
template <class T> inline T length(const vec3g<T>& v) { return v.length() ; }
template <class T> inline T length2(const vec3g<T>& v) { return v.length2() ; }
template <class T> inline T distance2(const vec3g<T>& v1, const vec3g<T>& v2) { return length2(v2 - v1) ; }
template <class T> inline T distance(const vec3g<T>& v1, const vec3g<T>& v2) { return length(v2 - v1) ; }
template <class T> inline vec3g<T> normalize(const vec3g<T>& v) { return (T(1) / length(v)) * v ;   }
template <class T> inline vec3g<T> mix(const vec3g<T>& v1, const vec3g<T>& v2, double s) { return (T(1) - s) * v1 + s * v2 ; }




template <class T> inline std::ostream& operator<<(std::ostream& out, const vec3g<T>& v) {
	return out << v.x << "  " << v.y << "  " << v.z  ;
}

template <class T> inline std::istream& operator>>(std::istream& in, vec3g<T>& v) {
	return in >> v.x >> v.y >> v.z ;
}




#endif