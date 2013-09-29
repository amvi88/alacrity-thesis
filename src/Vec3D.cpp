#include "Vec3D.hxx"

Vec3D::Vec3D(float X, float Y, float Z)
{
    this->X = X / xRange;
    this->Y = Y / yRange;
    this->Z = Z;
}

Vec3D::~Vec3D()
{
    //dtor
}
