#ifndef COMPLEX_HPP
#define COMPLEX_HPP

#include <iostream>
#include <cmath>
#include <sstream>
#include <iomanip>

class Complex {
public:
    double real;
    double imag;

    Complex(double r = 0.0, double i = 0.0) : real(r), imag(i) {}

    // Addition
    Complex operator+(const Complex& other) const {
        return Complex(real + other.real, imag + other.imag);
    }

    // Subtraction
    Complex operator-(const Complex& other) const {
        return Complex(real - other.real, imag - other.imag);
    }

    // Multiplication
    Complex operator*(const Complex& other) const {
        return Complex(real * other.real - imag * other.imag, real * other.imag + imag * other.real);
    }

    // Division
    Complex operator/(const Complex& other) const {
        double denominator = other.real * other.real + other.imag * other.imag;
        return Complex((real * other.real + imag * other.imag) / denominator,
                       (imag * other.real - real * other.imag) / denominator);
    }

    // Comparison
    bool operator==(const Complex& other) const {
        return real == other.real && imag == other.imag;
    }

    bool operator>(const Complex& other) const {
        return this->magnitude() > other.magnitude();
    }

    // Magnitude
    double magnitude() const {
        return sqrt(real * real + imag * imag);
    }

    double magnitudeSquared() const {
        return real * real + imag * imag;
    }

    // Phase
    double phase() const {
        return atan2(imag, real);
    }

    friend std::ostream& operator<<(std::ostream& os, const Complex& c) {
        os << "(" << c.real << ", " << c.imag << ")";
        return os;
    }

    std::string to_string(const Complex& c)  {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2); // Set fixed-point notation and precision
    oss << "(" << real << ", " << imag << "i)";
    return oss.str();
}

    
};

#endif // COMPLEX_HPP
