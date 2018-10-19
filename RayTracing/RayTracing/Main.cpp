#include "Main.h"
using namespace std;
int nx = 200;
int ny = 100;
int ns = 100;

float hit_sphere(const Vec3& center, float radius, const ray& r) {
	Vec3 oc = r.origin() - center;
	// (A+Bt-C)*(A+Bt-C) = R*R
	// t*t*dot(B,B) + 2*t*(B,A-C)+ dot(A-C,A-C)-R*R = 0;
	float a = dot(r.direction(), r.direction());
	float b = 2.0*dot(oc, r.direction());
	float c = dot(oc, oc) - radius * radius;
	float discriminant = b * b - 4 * a*c;
	if (discriminant < 0) {
		return -1.0;
	}
	else {
		// 返回光线与圆的第一个碰撞点用于计算圆的法线
		return (-b - sqrt(discriminant)) / (2.0*a);
	}
}

Vec3 color(const ray& r, hitable *world) {
	hit_record rec;
	if (world->hit(r, 0.0, 999, rec)) {
		return 0.5*Vec3(rec.normal.x() + 1, rec.normal.y() + 1, rec.normal.z() + 1);
	}
	else {
		Vec3 unit_direction = unit_vector(r.direction());
		float t = 0.5*(unit_direction.y() + 1.0);
		return (1.0 - t)*Vec3(1.0, 1.0, 1.0) + t * Vec3(0.5, 0.7, 1.0);
	}
}

Vec3 color(const ray&r) {
	float t = hit_sphere(Vec3(0, 0, -1), 0.5, r);
	if (t > 0.0) {
		// N为单位化的法线（-1到1），法线为碰撞点减去球体中心
		Vec3 N = unit_vector(r.point_at_parameter(t) - Vec3(0, 0, -1));
		// rgb的范围为0到1
		return 0.5*Vec3(N.x() + 1, N.y() + 1, N.z() + 1);
	}
	//返回背景的颜色，没有碰到球形是简单的梯度下降
	Vec3 unit_direction = unit_vector(r.point_at_parameter(t) - Vec3(0, 0, -1));
	// 只与y坐标相关，由深到浅
	t = 0.5*(unit_direction.y() + 1.0);
	return (1.0 - t)*Vec3(1.0, 1.0, 1.0) + t * Vec3(0.5, 0.7, 1.0);
}

void Chapter1_2() {
	for (int j = ny - 1; j >= 0; j--) {
		for (int i = 0; i < nx; i++) {
			Vec3 col(float(i) / float(nx), float(j) / float(ny), 0.2);
			int ir = int(255.99*col[0]);
			int ig = int(255.99*col[1]);
			int ib = int(255.99*col[2]);
			std::cout << ir << " " << ig << " " << ib << "\n";
		}
	}
	//红色和绿色混合变黄色
}


void Chapter3_AddSphere() {
	// camera或者眼睛固定在(0,0,0)
	Vec3 lower_left_corner(-2.0, -1.0, -1.0);
	Vec3 horizontal(4.0, 0.0, 0.0);
	Vec3 vertical(0.0, 2.0, 0.0);
	Vec3 origin(0.0, 0.0, 0.0);
	for (int j = ny - 1; j >= 0; j--) {
		for (int i = 0; i < nx; i++) {
			float u = float(i) / float(nx);
			float v = float(j) / float(ny);
			// 根据起始点和遍历到的屏幕上的点确定了射线
			ray r(origin, lower_left_corner + u * horizontal + v * vertical);
			Vec3 col = color(r);
			int ir = int(255.99*col[0]);
			int ig = int(255.99*col[1]);
			int ib = int(255.99*col[2]);
			std::cout << ir << " " << ig << " " << ib << "\n";
		}
	}
}


void Chapter5() {
	Vec3 lower_left_corner(-2.0, -1.0, -1.0);
	Vec3 horizontal(4.0, 0.0, 0.0);
	Vec3 vertical(0.0, 2.0, 0.0);
	Vec3 origin(0.0, 0.0, 0.0);
	hitable *list[2];
	list[0] = new sphere(Vec3(0, 0, -1), 0.5);
	list[1] = new sphere(Vec3(0, -100.5, -1), 100);
	hitable *world = new hitable_list(list, 2);
	for (int j = ny - 1; j >= 0; j--) {
		for (int i = 0; i < nx; i++) {
			float u = float(i) / float(nx);
			float v = float(j) / float(ny);
			ray r(origin, lower_left_corner + u * horizontal + v * vertical);
			Vec3 p = r.point_at_parameter(2.0);
			Vec3 col = color(r, world);
			int ir = int(255.99*col[0]);
			int ig = int(255.99*col[1]);
			int ib = int(255.99*col[2]);
			std::cout << ir << " " << ig << " " << ib << "\n";
		}
	}
}

void Chapter6() {
	hitable *list[2];
	list[0] = new sphere(Vec3(0, 0, -1), 0.5);
	list[1] = new sphere(Vec3(0, -100.5, -1), 100);
	hitable *world = new hitable_list(list, 2);
	camera cam;
	for (int j = ny - 1; j >= 0; j--) {
		for (int i = 0; i < nx; i++) {
			Vec3 col(0, 0, 0);
			for (int s = 0; s < ns; s++) {
				float u = float(i + rand()) / float(nx);
				float v = float(j + rand()) / float(ny);
				ray r = cam.get_ray(u, v);
				Vec3 p = r.point_at_parameter(2.0);
				col += color(r, world);
			}
			col /= float(ns);
			int ir = int(255.99*col[0]);
			int ig = int(255.99*col[1]);
			int ib = int(255.99*col[2]);
			std::cout << ir << " " << ig << " " << ib << "\n";
		}
	}
}

int main() {
	ofstream outf("Chapter6.ppm");
	streambuf *default_buf = cout.rdbuf();
	cout.rdbuf(outf.rdbuf());
	std::cout << "P3\n" << nx << " " << ny << "\n255\n";
	Chapter6();
}




