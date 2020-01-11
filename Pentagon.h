#pragma once
#include<math.h>
#include<stdio.h>
#include<iostream>
#include"Vertex.h"

template<class T>
class Pentagon
{
public:
	vertex<T> vertices[5];
	Pentagon() = default;
	Pentagon(std::istream& in);
	void Read(std::istream& in);
	double Area() const;
	void Print(std::ostream& os) const;
	friend std::ostream& operator<< (std::ostream& out, const Pentagon<T>& point);
};

	template<class T>
    Pentagon<T>::Pentagon(std::istream& is)
    {
		for (int i = 0; i < 5; i++) {
			is >> this->vertices[i];
		}
	}

	template<class T>
    double Pentagon<T>::Area() const
    {
		double Area = 0;
        for (int i = 0; i < 5; i++)
            Area += (vertices[i].coord.first) * (vertices[(i + 1) % 5].coord.second) - (vertices[(i + 1) % 5].coord.first) * (vertices[i].coord.second);
		Area *= 0.5;
		return abs(Area);
	}

	template<class T>
    void Pentagon<T>::Print(std::ostream& os) const
    {
        std::cout << "Coordinates of pentagon's vertexes: ";
        for (int i = 0; i < 5; i++)
        {
			os << this->vertices[i];
			if (i != 4) {
				os << ',';
			}
		}
		os << std::endl;
	}

    template<class T>
    void Pentagon<T>::Read(std::istream& in) {
        for (int i = 0; i < 5; i++)
        {
            std::cout << "Coordinates of " << i+1 << " vertex: \n";
            in >> this->vertices[i];
        }
    }

	template<class T>
    std::ostream& operator<<(std::ostream& os, const Pentagon<T>& point)
    {
		for (int i = 0; i < 5; i++) {
			os << point.vertices[i];
			if (i != 5) {
				os << ',';
			}
		}
	}


