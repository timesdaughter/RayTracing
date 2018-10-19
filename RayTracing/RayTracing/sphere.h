#ifndef SPHEREH
#define SPHEREH
#include "hitable.h"
class sphere:public hitable
{
public:
	Vec3 center;
	float radius;
	sphere() {};
	sphere(Vec3 cen, float r) :center(cen), radius(r) {};
	virtual bool hit(const ray &r, float tmin, float tmax, hit_record& rec) const;
};



#endif