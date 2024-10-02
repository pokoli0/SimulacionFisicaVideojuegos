#include <iostream>
#include <cmath>

using namespace std;

class Vector3D {
private:
    double x, y, z;

public:
    // Constructor
    Vector3D(double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z) {}

    // Getters
    double getX() const { return x; }
    double getY() const { return y; }
    double getZ() const { return z; }

    // Setters
    void setX(double newX) { x = newX; }
    void setY(double newY) { y = newY; }
    void setZ(double newZ) { z = newZ; }

    // Método para obtener el módulo del vector
    double modulo() const {
        return sqrt(x * x + y * y + z * z);
    }

    // Método para normalizar el vector
    Vector3D normalizar() const {
        double m = modulo();
        if (m == 0) cout << "No se puede normalizar" << endl;
        return Vector3D(x / m, y / m, z / m);
    }

    // Producto escalar con otro vector
    double productoEscalar(const Vector3D& otro) const {
        return x * otro.x + y * otro.y + z * otro.z;
    }

    // Multiplicar el vector por un escalar
    Vector3D operator*(double escalar) const {
        return Vector3D(x * escalar, y * escalar, z * escalar);
    }

    // Sobrecarga del operador +
    Vector3D operator+(const Vector3D& otro) const {
        return Vector3D(x + otro.x, y + otro.y, z + otro.z);
    }

    // Sobrecarga del operador -
    Vector3D operator-(const Vector3D& otro) const {
        return Vector3D(x - otro.x, y - otro.y, z - otro.z);
    }

    // Sobrecarga del operador =
    Vector3D& operator=(const Vector3D& otro) {
        if (this != &otro) {
            x = otro.x;
            y = otro.y;
            z = otro.z;
        }
        return *this;
    }

    // Método para mostrar el vector
    void imprimir() const {
        std::cout << "Vector3D(" << x << ", " << y << ", " << z << ")\n";
    }
};
