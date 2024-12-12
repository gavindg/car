#ifndef VECTORHPP
#define VECTORHPP

#include <cmath>
#include <iostream>

class Vector {
protected:
    double * _data;
    size_t _len;

    virtual void print(std::ostream & os) const {
        os << '(';
        for (size_t i{0}; i < _len; ++i) {
            os << _data[i];
            if (i != _len - 1) os << ',';
        }
        os << ')';
    }

public:
    Vector(size_t length) : _data(new double [length]), _len(length) {}
    Vector(std::initializer_list<double> l) : _data(new double [l.size()]), _len(l.size()) {
        size_t ind{0};
        for (auto it{l.begin()}; it != l.end(); ++it) {
            _data[ind] = *it;
            ++ind;
        }
    }

    Vector(const Vector & other) : _data(new double [other._len]), _len(other._len) {
        for (size_t i{0}; i < _len; ++i) {
            _data[i] = other._data[i];
        }
    }
    
    virtual ~Vector() {
        delete [] _data;
    }

    virtual double magnitude() const {
        double sum{0.0};
        for (size_t i{0}; i < _len; ++i) {
            sum += _data[i] * _data[i];
        }
        return std::sqrt(sum);
    }

    void normalize() {
        double mag{magnitude()};
        if (mag == 0.0) return;
        for (size_t i{0}; i < _len; ++i) {
            _data[i] /= mag;
        }
    }

    Vector & operator=(const Vector & other) {
        if (this == &other) return *this;

        delete [] _data;
        _len = other._len;
        _data = new double[_len];
        for (size_t i{0}; i < _len; ++i) {
            _data[i] = other._data[i];
        }
        return *this;
    }

    Vector operator*(double s) const {
        Vector scaled(_len);
        for (size_t i{0}; i < _len; ++i) {
            scaled._data[i] = s * _data[i];
        }
        return scaled;
    }

    friend Vector operator*(double s, const Vector & v) {
        Vector scaled(v._len);
        for (size_t i{0}; i < v._len; ++i) {
            scaled._data[i] = s * v._data[i];
        }
        return scaled;
        
    }

    virtual Vector operator+(const Vector & that) const {
        if (_len != that._len) throw;
        Vector sum(_len);
        for (size_t i{0}; i < _len; ++i) {
            sum._data[i] = _data[i] + that._data[i];
        }
        return sum;
    }

    virtual Vector operator-(const Vector & that) const {
        if (_len != that._len) throw;
        Vector sum(_len);
        for (size_t i{0}; i < _len; ++i) {
            sum._data[i] = _data[i] - that._data[i];
        }
        return sum;
    }

    virtual bool operator==(const Vector & to)  {
        if (_len != to._len) return false;
        for (size_t i{0}; i < _len; ++i) {
            if (_data[i] != to._data[i]) {
                return false;
            }
        }
        return true;
    }

    // not really recommended for use,
    // just used in some cases for faster math
    double & operator[](size_t ind) {
        return _data[ind];
    }

    const double & operator[](size_t ind) const {
        return _data[ind];
    }

    friend std::ostream & operator<<(std::ostream & stream, Vector vec) {
        stream << '(';
        for (size_t i{0}; i < vec._len; ++i) {
            stream << vec._data[i];
            if (i <= vec._len - 2) {
                stream << ',';
            }
        }
        stream << ')';
        return stream;
    }
};

class Vector2 : public Vector {
public:
    Vector2() : Vector(2) {};
    Vector2(double x, double y) : Vector({x, y}) {};

    ~Vector2() override = default;

    const double & x() const {
        return Vector::_data[0];
    }
    double & x() {
        return Vector::_data[0];
    }

    const double & y() const {
        return Vector::_data[1];
    }
    double & y() {
        return Vector::_data[1];
    }

    virtual Vector2 operator+(const Vector2 & that) const {
        return Vector2(this->x() + that.x(),
                this->y() + that.y());
    }

    virtual Vector2 operator-(const Vector2 & that) const {
        return Vector2(this->x() - that.x(),
                this->y() - that.y());
    }

};

class Vector3 : public Vector {
public:
    Vector3() : Vector(3) {};
    Vector3(double x, double y, double z) : Vector({x, y, z}) {};

    ~Vector3() override = default;

    const double & x() const {
        return Vector::_data[0];
    }
    double & x() {
        return Vector::_data[0];
    }

    const double & y() const {
        return Vector::_data[1];
    }
    double & y() {
        return Vector::_data[1];
    }

    const double & z() const {
        return Vector::_data[2]; 
    }

    double & z() {
        return Vector::_data[3];
    }

    virtual Vector3 operator+(const Vector3 & that) const {
        return Vector3(this->x() + that.x(),
                this->y() + that.y(),
                this->z() + that.z());
    }

    virtual Vector3 operator-(const Vector3 & that) const {
        return Vector3(this->x() - that.x(),
                this->y() - that.y(),
                this->z() - that.z());
    }


    /*
    friend std::ostream & operator<<(std::ostream & os, const Vector3 & vec) {
        vec.print(os);
        return os;
    }
    */
};


class Vector4 : public Vector {
public:
    Vector4() : Vector({0, 0, 0, 0}) {}

    Vector4(double x, double y, double z, double w=0) 
        : Vector({x, y, z, w}) {}

    double magnitude() const {
        return std::sqrt((x() * x()) + (y() * y()) + (z() * z()));
    }

    const double & x() const {
        return Vector::_data[0];
    }
    double & x() {
        return Vector::_data[0];
    }

    const double & y() const {
        return Vector::_data[1];
    }
    double & y() {
        return Vector::_data[1];
    }

    const double & z() const {
        return Vector::_data[2];
    }
    double & z() {
        return Vector::_data[2];
    }

    const double & w() const {
        return Vector::_data[3];
    }
    double & w() {
        return Vector::_data[3];
    }

    virtual Vector4 operator+(const Vector4 & that) const {
        return Vector4(this->x() + that.x(),
                this->y() + that.y(),
                this->z() + that.z());
    }

    virtual Vector4 operator-(const Vector4 & that) const {
        return Vector4(this->x() - that.x(),
                this->y() - that.y(),
                this->z() - that.z());
    }

    Vector4 operator*(double s) const {
        Vector4 scaled;
        for (size_t i{0}; i < _len; ++i) {
            scaled._data[i] = s * _data[i];
        }
        return scaled;
    }

    friend Vector4 operator*(double s, const Vector4 & v) {
        Vector4 scaled;
        for (size_t i{0}; i < v._len; ++i) {
            scaled._data[i] = s * v._data[i];
        }
        return scaled;
    }

    /* this needs to be friend or else it cant view the members on vec !
     * though honestly why this doesn't just operate on 'this' is weird... */
    /*
    friend std::ostream & operator<<(std::ostream & os, const Vector4 & vec) {
        os << '(' << vec.x() << ", " << vec.y() << ", " << vec.z() << ", " << vec.w() << ')';
        return os;
    }
    */
};


class VMath {
public:
    static double distance(const Vector4 & from, const Vector4 & to) {
        return std::sqrt(
            std::pow(to.x() - from.x(), 2) +
            std::pow(to.y() - from.y(), 2) +
            std::pow(to.z() - from.z(), 2)
        );
    }

    

    VMath() = delete;   //static class
};

#endif
