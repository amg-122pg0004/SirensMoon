/*****************************************************************//**
 * \file   Math.h
 * \brief  2D�x�N�g���v�Z
 * 
 * \author �y�������Y
 * \date   June 2022
 *********************************************************************/
#pragma once
#include <DxLib.h>
#include <cmath>

// 2D�x�N�g���N���X
class Vector2 {
public:
    // x����,y����
    double x, y;
    // �R���X�g���N�^
    Vector2() noexcept = default;
    constexpr Vector2(double inX, double inY) noexcept
        : x{ inX }
        , y{ inY } {
    }
    // �x�N�g���̉��Z a + b ���O���֐�
    friend Vector2 operator+(const Vector2& a, const Vector2& b) {
        return { a.x + b.x, a.y + b.y };
    }
    // �x�N�g���̌��Z a - b ���O���֐�
    friend Vector2 operator-(const Vector2& a, const Vector2& b) {
        return { a.x - b.x, a.y - b.y };
    }
    // �x�N�g���̃X�J���[�{ v * scalar ���O���֐�
    friend Vector2 operator*(const Vector2& v, double scalar) {
        return { v.x * scalar, v.y * scalar };
    }
    // �x�N�g���̃X�J���[�{ scalar * v ���O���֐�
    friend Vector2 operator*(double scalar, const Vector2& v) {
        return { v.x * scalar, v.y * scalar };
    }

    // �x�N�g���̃X�J���[���Z scalar * v ���O���֐�
    friend Vector2 operator/(const Vector2& v,double scalar) {
        return { v.x / scalar, v.y / scalar };
    }
    // �x�N�g�����Z���
    Vector2& operator+=(const Vector2& right) {
        x += right.x;
        y += right.y;
        return *this;
    }
    // �x�N�g�����Z���
    Vector2& operator-=(const Vector2& right) {
        x -= right.x;
        y -= right.y;
        return *this;
    }
    // �x�N�g���̃X�J����Z���
    Vector2& operator*=(double scalar) {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    // �x�N�g���̑傫��
    double Length() const {
        return std::sqrt(x * x + y * y);
    }
    // �x�N�g���̐��K��
    void Normalize() {
        auto length = Length();
        x /= length;
        y /= length;
    }
    static Vector2 Normalize(const Vector2& vec) {
        auto temp = vec;
        temp.Normalize();
        return temp;
    }
    // �x�N�g���̓���(Dot product) a�Eb
    static double Dot(const Vector2& a, const Vector2& b) {
        return (a.x * b.x + a.y * b.y);
    }
    // �x�N�g���̊O��(Cross product) a�~b
    static double Cross(const Vector2& a, const Vector2& b) {
        return (a.x * b.y - a.y * b.x);
    }

    /**
 * \brief ����AB��CD���������Ă��邩
 *
 * \param a�@����AB�̎n�_
 * \param b�@����AB�̏I�_
 * \param c�@����CD�̎n�_
 * \param d�@����CD�̎n�_
 * \return �@�������Ă����True
 */
   static bool IsCrossed(Vector2 a, Vector2 b, Vector2 c, Vector2 d) {
        Vector2 vec_a1 = b - a;
        Vector2 vec_a2 = c - a;
        Vector2 vec_a3 = d - a;

        Vector2 vec_c1 = a - c;
        Vector2 vec_c2 = b - c;
        Vector2 vec_c3 = d - c;

        if (Vector2::Cross(vec_a1, vec_a2) * Vector2::Cross(vec_a1, vec_a3) < 0) {
            if (Vector2::Cross(vec_c3, vec_c1) * Vector2::Cross(vec_c3, vec_c2) < 0) {
                return 1;
            }
        }
        return 0;
    }
};

namespace Math {
    // �~����
    constexpr float Pi = 3.1415926535f;
    constexpr float TwoPi = Pi * 2.0f;
    constexpr float PiOver2 = Pi / 2.0f;

    // �x������Ǔx(���W�A��)�ɕϊ�
    inline float ToRadians(float degrees) {
        return degrees * Pi / 180.0f;
    }
    // �Ǔx����x��(�f�B�O���[)�ɕϊ�
    inline float ToDegrees(float radians) {
        return radians * 180.0f / Pi;
    }
    // ��̒l�̑傫���l���擾
    template <typename T>
    T Max(const T& a, const T& b) {
        return (a < b ? b : a);
    }
    // ��̒l�̏������l���擾
    template <typename T>
    T Min(const T& a, const T& b) {
        return (a < b ? a : b);
    }
    // ��̒l�̊ԂŃN�����v����
    template <typename T>
    T Clamp(const T& value, const T& lower, const T& upper) {
        return Min(upper, Max(lower, value));
    }
}
