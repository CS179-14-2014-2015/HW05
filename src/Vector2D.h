/*
 * Vector.h
 *
 *  Created on: Jan 14, 2015
 *      Author: guillaume
 */

#ifndef VECTOR_H_
#define VECTOR_H_

#include<SFML/System/Vector2.hpp>
#include <math.h>
#include <iostream>

using namespace sf;
using namespace std;

#define PI 3.14159265

template<typename T>
class Vector2D : public Vector2<T>{
public:

	//Constructors
	Vector2D(T x, T y);
	Vector2D(Vector2<T> const& v);
	Vector2D();

	//return a unit vector for an angle
	static Vector2D getVectorFromAngle(float angle);

	//give the magnitude of a vector
	float getMagnitude();
	Vector2D& setMagnitude(float const& magnitude);

	//dot product
	T dot(const Vector2D &other);

	//cross product
	T cross(const Vector2D &other);

	//give the angle with another vector
	float getAngleWith(const Vector2D &other) const;

	//give the angle of the vector (with the vector x)
	float getAngle() const;

	//rotate the vector
	Vector2D& rotate(float angle);

	//normalize the vector
	Vector2D& normalize();

	//say if the vector is null
	bool isNull() const;

	//give a unit normal vector
	Vector2D getNormal() const;
};

#endif
/* VECTOR_H_ */

//Most common type of vector
typedef Vector2D<float> Vector2Df;
typedef Vector2D<int> Vector2Di;
typedef Vector2D<unsigned int> Vector2Du;

template<typename T>
Vector2D<T>::Vector2D(T x, T y) : Vector2<T>(x,y){}
template<typename T>
Vector2D<T>::Vector2D() : Vector2<T>(){}
template<typename T>
Vector2D<T>::Vector2D(Vector2<T> const& v) : Vector2<T>(v) {}


template<typename T>
ostream &operator<<(ostream &output, const Vector2D<T> &v){
	cout << '(' << v.x << ", " << v.y << ')';
	return output;
}

template<typename T>
Vector2D<T> Vector2D<T>::getVectorFromAngle(float angle) {
	angle = angle * PI / 180;	//degree -> rad
	return Vector2D<T>(cos(angle), sin(angle));
}

template<typename T>
float Vector2D<T>::getMagnitude() {
	return sqrt(this->x * this->x + this->y * this->y);
}
template<typename T>
Vector2D<T>& Vector2D<T>::setMagnitude(float const& magnitude){
	if(isNull())
		return *this;
	T ratio = magnitude / getMagnitude();
	*this *= ratio;
	return *this;
}

template<typename T>
T Vector2D<T>::dot(const Vector2D &other) {
	return this->x * other.x + this->y * other.y;
}

template<typename T>
T Vector2D<T>::cross(const Vector2D &other) {
	return this->x * other.y - this->y * other.x;
}

template<typename T>
float Vector2D<T>::getAngleWith(const Vector2D &other) const {
	return 180 / PI * atan2( this->x * other.y - this->y * other.x , this->x * other.x + this->y * other.y );
}

template<typename T>
float Vector2D<T>::getAngle() const {
	return this->getAngleWith(Vector2D<T>(1, 0));
}

template<typename T>
Vector2D<T>& Vector2D<T>::rotate(float angle) {
	angle = angle * PI / 180;
	T xr = this->x * cos(angle) - this->y * sin(angle);
	T yr = this->x * sin(angle) + this->y * cos(angle);
	this->x = xr;
	this->y = yr;
	return *this;
}

template<typename T>
Vector2D<T>& Vector2D<T>::normalize() {
	if(this->isNull())
		return *this;

	float magnitude = this->getMagnitude();
	this->x /= magnitude;
	this->y /= magnitude;
	return *this;
}

template<typename T>
bool Vector2D<T>::isNull() const {
	return this->x == 0 && this->y == 0;
}

template<typename T>
Vector2D<T> Vector2D<T>::getNormal() const{
	return Vector2D(*this).normalize().rotate(90);
}
