#ifndef __VECTOR3_H__
#define __VECTOR3_H__

#pragma once

#include <glm/vec3.hpp>
#include <glm/glm.hpp>

namespace ArenaBoss::Math
{
    template <class T, class P>
    class TVector2;

    template <class T, class P>
    class TVector3 final
    {
    public:
        constexpr static TVector3 ONE();
        constexpr static TVector3 ZERO();

        constexpr static TVector3 UP();
        constexpr static TVector3 DOWN();

        constexpr static TVector3 RIGHT();
        constexpr static TVector3 LEFT();

        constexpr static TVector3 FORWARD();
        constexpr static TVector3 BACKWARD();

    public:
        union
        {
            P value;

            struct
            {
                T x;
                T y;
                T z;
            };
        };

    public:
        constexpr TVector3() noexcept : value() {}

        constexpr TVector3(const TVector3& other) noexcept
            : value(other.value) {}

        constexpr TVector3(TVector3&& other) noexcept
            : value(other.value) {}

        explicit constexpr TVector3(T scalar) noexcept
            : value(scalar) {}

        explicit constexpr TVector3(T inX, T inY, T inZ) noexcept
            : value(inX, inY, inZ) {}

        explicit constexpr TVector3(const T* elems) noexcept
            : value(elems[0], elems[1], elems[2]) {}

        TVector3(const TVector2<T, P>& xy, float z = 0.0f) noexcept;

        constexpr TVector3(const P& vec) noexcept
            : value(vec) {}

        constexpr TVector3(P&& vec) noexcept
            : value(std::move(vec)) {}

        constexpr TVector3& operator=(const TVector3& other) noexcept
        {
            value = other.value;
            return *this;
        }

        constexpr TVector3& operator=(TVector3&& other) noexcept
        {
            value = std::move(other.value);
            return *this;
        }

        TVector3& operator=(const TVector2<T, P>& xy) noexcept;

        constexpr TVector3& operator=(const P& vec) noexcept
        {
            value = vec;
            return *this;
        }

        constexpr TVector3& operator=(P&& vec) noexcept
        {
            value = std::move(vec);
            return *this;
        }

        constexpr operator P& () noexcept { return value; }
        constexpr operator const P& () const noexcept { return value; }

        constexpr operator float* () noexcept { return &x; }
        constexpr operator const float* () const noexcept { return &x; }

        operator TVector2<T, P>() const noexcept;

        void Set(float inX, float inY, float inZ) noexcept;

        inline void Set(const float* elems) noexcept
        {
            Set(elems[0], elems[1], elems[2]);
        }

        inline float Length() const noexcept { return glm::sqrt(LengthSqrt()); }
        inline float LengthSqrt() const noexcept { return Dot(value, value); }

        inline TVector3 Normalized() const noexcept
        {
            return glm::normalize(value);
        }

        inline void Normalize() noexcept
        {
            *this = Normalized();
        }
        
        inline float& operator[](glm::length_t idx) { return value[idx]; }
        inline float operator[](glm::length_t idx) const { return value[idx]; }

        constexpr TVector3& operator+=(const TVector3& other) noexcept
        {
            value += other.value;
            return *this;
        }

        constexpr TVector3& operator-=(const TVector3& other) noexcept
        {
            value -= other.value;
            return *this;
        }

        constexpr TVector3& operator*=(const TVector3& other) noexcept
        {
            value *= other.value;
            return *this;
        }

        constexpr TVector3& operator*=(float scaler) noexcept
        {
            value *= scaler;
            return *this;
        }

        constexpr TVector3& operator/=(const TVector3& other) noexcept
        {
            value /= other.value;
            return *this;
        }

        constexpr TVector3& operator/=(float scaler) noexcept
        {
            value /= scaler;
            return *this;
        }

        inline TVector3& operator^=(const TVector3& other) noexcept
        {
            value = glm::cross(value, other.value);
            return *this;
        }

        inline static float Dot(const TVector3& lhs, const TVector3& rhs)
        {
            return glm::dot(lhs.value, rhs.value);
        }

        inline static TVector3 Cross(const TVector3& lhs, const TVector3& rhs)
        {
            return glm::cross(lhs.value, rhs.value);
        }

    private:
        friend bool operator==(const TVector3& lhs, const TVector3& rhs) noexcept;
    };

    template <class T, class P>
    constexpr bool operator==(const TVector3<T, P>& lhs, const TVector3<T, P>& rhs) noexcept
    {
        return lhs.value == rhs.value;
    }

    template <class T, class P>
    constexpr bool operator!=(const TVector3<T, P>& lhs, const TVector3<T, P>& rhs) noexcept
    {
        return !(lhs == rhs);
    }

    template <class T, class P>
    inline TVector3<T, P> operator+(const TVector3<T, P>& lhs, const TVector3<T, P>& rhs) { return TVector3{ lhs } += rhs; }

    template <class T, class P>
    inline TVector3<T, P> operator-(const TVector3<T, P>& lhs, const TVector3<T, P>& rhs) { return TVector3{ lhs } -= rhs; }

    template <class T, class P>
    inline TVector3<T, P> operator*(const TVector3<T, P>& lhs, const TVector3<T, P>& rhs) { return TVector3{ lhs } *= rhs; }

    template <class T, class P>
    inline TVector3<T, P> operator*(const TVector3<T, P>& lhs, float rhs) { return TVector3{ lhs } *= rhs; }

    template <class T, class P>
    inline TVector3<T, P> operator*(float lhs, const TVector3<T, P>& rhs) { return TVector3{ rhs } *= lhs; }

    template <class T, class P>
    inline TVector3<T, P> operator/(const TVector3<T, P>& lhs, const TVector3<T, P>& rhs) { return TVector3{ lhs } /= rhs; }

    template <class T, class P>
    inline TVector3<T, P> operator/(const TVector3<T, P>& lhs, float rhs) { return TVector3{ lhs } /= rhs; }

    template <class T, class P>
    inline float operator|(const TVector3<T, P>& lhs, const TVector3<T, P>& rhs) { return TVector3::Dot(lhs, rhs); }

    template <class T, class P>
    inline TVector3<T, P> operator^(const TVector3<T, P>& lhs, const TVector3<T, P>& rhs) { return TVector3::Cross(lhs, rhs); }

    template <class T, class P>
    inline TVector3<T, P> operator+(const TVector3<T, P>& vec) noexcept { return vec; }

    template <class T, class P>
    inline TVector3<T, P> operator-(const TVector3<T, P>& vec) noexcept { return vec * -1.0f; }

    using Vector3 = TVector3<float, glm::vec3>;
    using IntVector3 = TVector3<int32_t, glm::i32vec3>;
    using UintVector3 = TVector3<uint32_t, glm::u32vec3>;
}

#include "Vector3.hpp"

#endif