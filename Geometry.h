#include <cstring>
#include <memory>
#include <map>
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;
double to_radians(double theta_d);
double to_degrees(double theta_r);
typedef struct Point {
	double x;
	double y;
	Point(double x, double y);
	Point();
	double get_x();
	double get_y();
	void  set_x(double xN);
	void  set_y(double yN);
	void print() const;
	bool operator==(const Point& rhs);
} Point;
double euclideanDistance(const Point& point1, const Point& point2);
struct Polar_vector;
typedef struct Cartesian_vector {
	Cartesian_vector(const struct Polar_vector & pv);
	Cartesian_vector();
	void operator=(const struct Polar_vector & pv);
	double delta_x;
	double delta_y;
} Cartesian_vector;
typedef struct Polar_vector {
	Polar_vector(const Cartesian_vector & cv);
	Polar_vector();
	void operator=(const Cartesian_vector & cv);
	double r;
	double theta;
} Polar_vector;
