/*****************************************************************//**
 * \file   Math.h
 * \brief  2Dベクトル計算
 * 
 * \author 土居将太郎
 * \date   June 2022
 *********************************************************************/
#pragma once
#include <DxLib.h>
#include <cmath>

// 2Dベクトルクラス
class Vector2 {
public:
    // x成分,y成分
    double x, y;
    // コンストラクタ
    Vector2() noexcept = default;
    constexpr Vector2(double inX, double inY) noexcept
        : x{ inX }
        , y{ inY } {
    }
    // ベクトルの加算 a + b ※外部関数
    friend Vector2 operator+(const Vector2& a, const Vector2& b) {
        return { a.x + b.x, a.y + b.y };
    }
    // ベクトルの減算 a - b ※外部関数
    friend Vector2 operator-(const Vector2& a, const Vector2& b) {
        return { a.x - b.x, a.y - b.y };
    }
    // ベクトルのスカラー倍 v * scalar ※外部関数
    friend Vector2 operator*(const Vector2& v, double scalar) {
        return { v.x * scalar, v.y * scalar };
    }
    // ベクトルのスカラー倍 scalar * v ※外部関数
    friend Vector2 operator*(double scalar, const Vector2& v) {
        return { v.x * scalar, v.y * scalar };
    }

    // ベクトルのスカラー除算 scalar * v ※外部関数
    friend Vector2 operator/(const Vector2& v,double scalar) {
        return { v.x / scalar, v.y / scalar };
    }
    // ベクトル加算代入
    Vector2& operator+=(const Vector2& right) {
        x += right.x;
        y += right.y;
        return *this;
    }
    // ベクトル減算代入
    Vector2& operator-=(const Vector2& right) {
        x -= right.x;
        y -= right.y;
        return *this;
    }
    // ベクトルのスカラ乗算代入
    Vector2& operator*=(double scalar) {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    // ベクトルの大きさ
    double Length() const {
        return std::sqrt(x * x + y * y);
    }
    // ベクトルの正規化
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
    // ベクトルの内積(Dot product) a・b
    static double Dot(const Vector2& a, const Vector2& b) {
        return (a.x * b.x + a.y * b.y);
    }
    // ベクトルの外積(Cross product) a×b
    static double Cross(const Vector2& a, const Vector2& b) {
        return (a.x * b.y - a.y * b.x);
    }

    /**
 * \brief 線分ABとCDが交差しているか
 *
 * \param a　線分ABの始点
 * \param b　線分ABの終点
 * \param c　線分CDの始点
 * \param d　線分CDの始点
 * \return 　交差していればTrue
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
    // 円周率
    constexpr float Pi = 3.1415926535f;
    constexpr float TwoPi = Pi * 2.0f;
    constexpr float PiOver2 = Pi / 2.0f;

    // 度数から孤度(ラジアン)に変換
    inline float ToRadians(float degrees) {
        return degrees * Pi / 180.0f;
    }
    // 孤度から度数(ディグリー)に変換
    inline float ToDegrees(float radians) {
        return radians * 180.0f / Pi;
    }
    // 二つの値の大きい値を取得
    template <typename T>
    T Max(const T& a, const T& b) {
        return (a < b ? b : a);
    }
    // 二つの値の小さい値を取得
    template <typename T>
    T Min(const T& a, const T& b) {
        return (a < b ? a : b);
    }
    // 二つの値の間でクランプする
    template <typename T>
    T Clamp(const T& value, const T& lower, const T& upper) {
        return Min(upper, Max(lower, value));
    }
}
