#pragma once
#include <cstdint>
#include <string>
#include <cstdlib>

class Fraction {
private:
    int64_t num_;
    uint64_t den_;

    static uint64_t gcd_uint64(uint64_t a, uint64_t b) {
        while (b != 0) {
            uint64_t t = a % b;
            a = b;
            b = t;
        }
        return a;
    }

    // Нормализация знака и сокращение
    static void normalize(int64_t &n, uint64_t &d) {
        if ((int64_t)d < 0) {
            n = -n;
            d = (uint64_t)(-(int64_t)d);
        }

        uint64_t g = gcd_uint64((uint64_t)llabs(n), d);
        if (g == 0) g = 1;

        n /= (int64_t)g;
        d /= g;
    }

public:
    // 0/1
    Fraction() : num_(0), den_(1) {}

    // От целого
    Fraction(int64_t x) : num_(x), den_(1) {}

    // От числителя и знаменателя
    Fraction(int64_t n, int64_t d) {
        uint64_t den = (uint64_t)d;
        normalize(n, den);
        num_ = n;
        den_ = den;
    }

    // Геттеры
    int64_t numerator() const { return num_; }
    uint64_t denominator() const { return den_; }

    // Преобразование к double
    explicit operator double() const {
        return (double)num_ / (double)den_;
    }

    // Строка
    std::string str() const {
        return std::to_string(num_) + "/" + std::to_string(den_);
    }

    // Унарный минус
    Fraction operator-() const {
        return Fraction(-num_, (int64_t)den_);
    }

    // +=
    Fraction& operator+=(const Fraction& other) {
        // уменьшаем риск переполнения
        uint64_t g = gcd_uint64(den_, other.den_);
        uint64_t l = den_ / g;

        int64_t new_num = num_ * (other.den_ / g) + other.num_ * (int64_t)l;
        uint64_t new_den = l * other.den_;

        normalize(new_num, new_den);
        num_ = new_num;
        den_ = new_den;
        return *this;
    }

    Fraction& operator-=(const Fraction& other) {
        *this += (-other);
        return *this;
    }

    Fraction& operator*=(const Fraction& other) {
        // (a/b)*(c/d) = (a*c)/(b*d)
        // перекрёстное сокращение
        uint64_t g1 = gcd_uint64((uint64_t)llabs(num_), other.den_);
        uint64_t g2 = gcd_uint64((uint64_t)llabs(other.num_), den_);

        int64_t n1 = num_ / (int64_t)g1;
        uint64_t d1 = den_ / g2;

        int64_t n2 = other.num_ / (int64_t)g2;
        uint64_t d2 = other.den_ / g1;

        int64_t new_num = n1 * n2;
        uint64_t new_den = d1 * d2;

        normalize(new_num, new_den);
        num_ = new_num;
        den_ = new_den;
        return *this;
    }

    Fraction& operator/=(const Fraction& other) {
        // (a/b)/(c/d) = (a*d)/(b*c)
        Fraction t(other.den_, other.num_);
        return *this *= t;
    }

    // Бинарные операторы
    friend Fraction operator+(Fraction a, const Fraction& b) {
        return a += b;
    }

    friend Fraction operator-(Fraction a, const Fraction& b) {
        return a -= b;
    }

    friend Fraction operator*(Fraction a, const Fraction& b) {
        return a *= b;
    }

    friend Fraction operator/(Fraction a, const Fraction& b) {
        return a /= b;
    }

    // Сравнения
    friend bool operator==(const Fraction& a, const Fraction& b) {
        return a.num_ == b.num_ && a.den_ == b.den_;
    }

    friend bool operator!=(const Fraction& a, const Fraction& b) {
        return !(a == b);
    }

    friend bool operator<(const Fraction& a, const Fraction& b) {
        // сравнение перекрёстным умножением
        // a.num / a.den < b.num / b.den    a.num * b.den < b.num * a.den
        long double lhs = (long double)a.num_ * (long double)b.den_;
        long double rhs = (long double)b.num_ * (long double)a.den_;
        return lhs < rhs;
    }

    friend bool operator>(const Fraction& a, const Fraction& b) {
        return b < a;
    }

    friend bool operator<=(const Fraction& a, const Fraction& b) {
        return !(b < a);
    }

    friend bool operator>=(const Fraction& a, const Fraction& b) {
        return !(a < b);
    }
};
