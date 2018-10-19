#ifndef HITABLEH
#define HITABLEH
#include "ray.h"
struct hit_record {
	float t;
	Vec3 p; //Œª÷√
	Vec3 normal;  //∑®œﬂ
	material *mat_ptr;
};
class hitable
{
public:
	virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec)const = 0;
};
#endif
