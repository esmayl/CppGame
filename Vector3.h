#ifndef VECTOR3_H
#define VECTOR3_H
class Vector3
{
  public:
    Vector3();
    Vector3(int newX, int newY, int newZ);
    float x;
    float y;
    float z;
    float magnitude();
    void Normalize();
    void Clear();
    Vector3 operator *=(float times);
    Vector3 operator *=(int times);
};
#endif