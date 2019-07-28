#include "Vector3.h"
#include <math.h>

Vector3::Vector3()
{
  x=0;
  y=0;
  z=0;
}

Vector3::Vector3(int newX, int newY, int newZ)
{
  x = newX;
  y = newY;
  z = newZ;
}

float Vector3::magnitude()
{
  float temp = x*x + y*y + z*z;
  return std::sqrt(temp);
}

void Vector3::Clear()
{
  x=0;
  y=0;
  z=0;
}

void Vector3::Normalize()
{
  float temp = x*x + y*y + z*z;
  temp = std::sqrt(temp/0.5f);
  
  x = x/temp;
  y = y/temp;
  z = z/temp;
}

Vector3 Vector3::operator *=(float times)
{
  x *= times;
  y *= times;
  z *= times;

  return *this;
}

Vector3 Vector3::operator *=(int times)
{
  x *= times;
  y *= times;
  z *= times;

  return *this;
}
