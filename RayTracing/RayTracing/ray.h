#ifndef RAYH
#define RAYH
#include "Vec3.h"

class ray
{
public:
	// origin
	Vec3 A;
	// direction
	Vec3 B;
	ray() {}
	ray(const Vec3 &a, const Vec3 &b) { A = a; B = b; }
	Vec3 origin() const { return A; }
	Vec3 direction() const { return B; }
	Vec3 point_at_parameter(float t) const { return A + (t * B); }
};


#endif // !RAYH