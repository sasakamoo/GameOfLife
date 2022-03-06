/**
 * @file utils.h
 * @author Matthew Sasakamoose (matt.sasakamoose@gmail.com)
 * @brief utility function declarations 
 * @version 0.1
 * @date 2022-01-22
 */

#ifndef UTIL_H_DEF
#define UTIL_H_DEF

#include "../pge/olcPixelGameEngine.h"

#include <cstdint>
#include <cmath>

float map (float input, float inputStart, float inputEnd, float outputStart, float outputEnd);
int random(int a, int b);
uint32_t gradient(float ratio);

// Generic 3d vector type, based from olcPixelGameEngine 2d vector type
namespace olc {

    template <class T>
    struct v3d_generic
    {
        T x = 0;
        T y = 0;
        T z = 0;
        v3d_generic() : x(0), y(0), z(0) {}
        v3d_generic(T _x, T _y, T _z) : x(_x), y(_y), z(_z) {}
        v3d_generic(const v3d_generic& v) : x(v.x), y(v.y), z(v.z) {}
        v3d_generic& operator=(const v3d_generic& v) = default;
        T mag() const { return T(std::sqrt(x * x + y * y + z * z)); }
        T mag2() const { return x * x + y * y + z * z; }
        v3d_generic  norm() const { T r = 1 / mag(); return v3d_generic(x * r, y * r, z * r); }
        v3d_generic  perp() const { return v3d_generic(-y, x, z); }
        v3d_generic  floor() const { return v3d_generic(std::floor(x), std::floor(y), std::floor(z)); }
        v3d_generic  ceil() const { return v3d_generic(std::ceil(x), std::ceil(y), std::ceil(z)); }
        v3d_generic  max(const v3d_generic& v) const { return v3d_generic(std::max(x, v.x), std::max(y, v.y), std::max(z, v.z)); }
        v3d_generic  min(const v3d_generic& v) const { return v3d_generic(std::min(x, v.x), std::min(y, v.y), std::min(z, v.z)); }
        v3d_generic  cart() { return { std::sin(z) * std::cos(y) * x, std::sin(z) * std::sin(y) * x, std::cos(z) * x}; }    
        v3d_generic  spherical() { return { mag(), std::atan2(y, x) , std::acos(z / mag())}; }
        v3d_generic  cross(const v3d_generic& v) const { return v3d_generic(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x); }
        T dot(const v3d_generic& rhs) const { return this->x * rhs.x + this->y * rhs.y + this->z * rhs.z; }
        v3d_generic  operator +  (const v3d_generic& rhs) const { return v3d_generic(this->x + rhs.x, this->y + rhs.y, this->z + rhs.z); }
        v3d_generic  operator -  (const v3d_generic& rhs) const { return v3d_generic(this->x - rhs.x, this->y - rhs.y, this->z - rhs.z); }
        v3d_generic  operator *  (const T& rhs)           const { return v3d_generic(this->x * rhs, this->y * rhs, this->z * rhs); }
        v3d_generic  operator *  (const v3d_generic& rhs) const { return v3d_generic(this->x * rhs.x, this->y * rhs.y, this->z * rhs.z); }
        v3d_generic  operator /  (const T& rhs)           const { return v3d_generic(this->x / rhs, this->y / rhs, this->z / rhs); }
        v3d_generic  operator /  (const v3d_generic& rhs) const { return v3d_generic(this->x / rhs.x, this->y / rhs.y, this->z / rhs.z); }
        v3d_generic& operator += (const v3d_generic& rhs) { this->x += rhs.x; this->y += rhs.y; this->z += rhs.z; return *this; }
        v3d_generic& operator -= (const v3d_generic& rhs) { this->x -= rhs.x; this->y -= rhs.y; this->z -= rhs.z; return *this; }
        v3d_generic& operator *= (const T& rhs) { this->x *= rhs; this->y *= rhs; this->z *= rhs; return *this; }
        v3d_generic& operator /= (const T& rhs) { this->x /= rhs; this->y /= rhs; this->z /= rhs; return *this; }
        v3d_generic& operator *= (const v3d_generic& rhs) { this->x *= rhs.x; this->y *= rhs.y; this->z *= rhs.z; return *this; }
        v3d_generic& operator /= (const v3d_generic& rhs) { this->x /= rhs.x; this->y /= rhs.y; this->z /= rhs.z; return *this; }
        v3d_generic  operator +  () const { return { +x, +y, +z }; }
        v3d_generic  operator -  () const { return { -x, -y, -z }; }
        bool operator == (const v3d_generic& rhs) const { return (this->x == rhs.x && this->y == rhs.y && this->z == rhs.z); }
        bool operator != (const v3d_generic& rhs) const { return (this->x != rhs.x || this->y != rhs.y || this->z != rhs.z); }
        const std::string str() const { return std::string("(") + std::to_string(this->x) + ", " + std::to_string(this->y) + ", " + std::to_string(this->z) + ")"; }
        friend std::ostream& operator << (std::ostream& os, const v3d_generic& rhs) { os << rhs.str(); return os; }
        operator v3d_generic<int32_t>() const { return { static_cast<int32_t>(this->x), static_cast<int32_t>(this->y), static_cast<int32_t>(this->z) }; }
        operator v3d_generic<float>() const { return { static_cast<float>(this->x), static_cast<float>(this->y), static_cast<float>(this->z) }; }
        operator v3d_generic<double>() const { return { static_cast<double>(this->x), static_cast<double>(this->y), static_cast<double>(this->z) }; }
    };

    template<class T> inline v3d_generic<T> operator * (const float& lhs, const v3d_generic<T>& rhs)
    { return v3d_generic<T>((T)(lhs * (float)rhs.x), (T)(lhs * (float)rhs.y), (T)(lhs * (float)rhs.z)); }
    template<class T> inline v3d_generic<T> operator * (const double& lhs, const v3d_generic<T>& rhs)
    { return v3d_generic<T>((T)(lhs * (double)rhs.x), (T)(lhs * (double)rhs.y), (T)(lhs * (double)rhs.z)); }
    template<class T> inline v3d_generic<T> operator * (const int& lhs, const v3d_generic<T>& rhs)
    { return v3d_generic<T>((T)(lhs * (int)rhs.x), (T)(lhs * (int)rhs.y), (T)(lhs * (int)rhs.z)); }
    template<class T> inline v3d_generic<T> operator / (const float& lhs, const v3d_generic<T>& rhs)
    { return v3d_generic<T>((T)(lhs / (float)rhs.x), (T)(lhs / (float)rhs.y), (T)(lhs / (float)rhs.z)); }
    template<class T> inline v3d_generic<T> operator / (const double& lhs, const v3d_generic<T>& rhs)
    { return v3d_generic<T>((T)(lhs / (double)rhs.x), (T)(lhs / (double)rhs.y), (T)(lhs / (double)rhs.z)); }
    template<class T> inline v3d_generic<T> operator / (const int& lhs, const v3d_generic<T>& rhs)
    { return v3d_generic<T>((T)(lhs / (int)rhs.x), (T)(lhs / (int)rhs.y), (T)(lhs / (int)rhs.z)); }

    template<class T, class U> inline bool operator < (const v3d_generic<T>& lhs, const v3d_generic<U>& rhs)
    { return lhs.y < rhs.y || (lhs.y == rhs.y && lhs.x < rhs.x) || (lhs.y == rhs.y && lhs.x == rhs.x && lhs.z < rhs.z); }
    template<class T, class U> inline bool operator > (const v3d_generic<T>& lhs, const v3d_generic<U>& rhs)
    { return lhs.y > rhs.y || (lhs.y == rhs.y && lhs.x > rhs.x) || (lhs.y == rhs.y && lhs.x == rhs.x && lhs.z > rhs.z); }

    template <class T>
    olc::v2d_generic<T> v3dTov2d(v3d_generic<T> v) {
        return olc::v2d_generic<T>(v.x, v.y);
    }

    typedef v3d_generic<int32_t> vi3d;
    typedef v3d_generic<uint32_t> vu3d;
    typedef v3d_generic<float> vf3d;
    typedef v3d_generic<double> vd3d;

}

#endif