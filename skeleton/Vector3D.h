#include <cmath>

#pragma once

using namespace std;

class Vector3D
{
public:

	Vector3D(float x_, float y_, float z_) {
		x = x_;
		y = y_;
		z = z_;
	};

#pragma region getters & setters
	void setX(float n) { x_ = n;}
	void setY(float n) { y_ = n;}
	void setZ(float n) { z_ = n;}
	float getX() { return x_;}
	float getY() { return y_;}
	float getZ() { return z_;}
#pragma endregion

	// magnitud
	float modulo() {
		return sqrt(x * x + y * y + z * z);
	}

	// dividir cada componente entre el modulo
	void normaliza() {
		float mod = modulo();
		if (mod != 0) {
			x /= mod;
			y /= mod;
			z /= mod;
		}
	}
	
	float prodEscalar(Vector3D& v) {
		return(x * v.x + y * v.y + z * v.z);
	}




private:

	float x, y, z;
};

