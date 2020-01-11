#pragma once
#include <iostream>
#include <type_traits>
#include <cmath>


template<class T>
struct vertex {
    using coordinates = std::pair<T,T>;
    coordinates coord;
	vertex<T>& operator=(vertex<T> A);
};

template<class T>
std::istream& operator>>(std::istream& is, vertex<T>& p) {
    std::cout << "Coordinate 'x': ";
    is >> p.coord.first;
    std::cout << "Coordinate 'y': ";
    is >> p.coord.second;
	return is;
}

template<class T>
std::ostream& operator<<(std::ostream& os, vertex<T> p) {
    os << '(' << p.coord.first << ' ' << p.coord.second << ')';
	return os;
}

template<class T>
vertex<T> operator+(const vertex<T>& A, const vertex<T>& B) {
	vertex<T> res;
    res.coord.first = A.coord.first + B.coord.first;
    res.coord.second = A.coord.second + B.coord.second;
	return res;
}

template<class T>
vertex<T>& vertex<T>::operator=(const vertex<T> A) {
    this->x = A.coord.first;
    this->y = A.coord.second;
	return *this;
}

template<class T>
vertex<T> operator+=(vertex<T>& A, const vertex<T>& B) {
    A.coord.first += B.coord.first;
    A.coord.second += B.coord.second;
	return A;
}

template<class T>
double vector (vertex<T>& A, vertex<T>& B) {
    double res = sqrt(pow(B.coord.first - A.coord.first, 2) + pow(B.coord.second - A.coord.second, 2));
	return res;
}

template<class T>
struct is_vertex : std::false_type {};

template<class T>
struct is_vertex<vertex<T>> : std::true_type {};

