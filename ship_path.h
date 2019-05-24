
#ifndef ship_path_H_
#define ship_path_H_



#include "Geometry.h"


//using namespace std;
class ship_path {
public:
	ship_path();
	ship_path(double s);
	void set_speed(double speedN){speed=speedN;}
	void set_ftr_speed(double speedN){future_speed=speedN;}
	void set_dst(double xN,double yN){dst.set_x(xN); dst.set_y(yN);}
	void set_dst(Point p){dst=p;}
	void set_current(Point p){current=p;}
	double get_speed(){return speed;}
	double get_ftr_speed(){return future_speed;}
	double get_current_x(){return current.get_x();}
	double get_current_y(){return current.get_y();}
	Point get_current(){return current;}
	Point get_dst(){return dst;}
	Point get_future_point(){return future_point;}
	void set_future_point(Point p){future_point=p;}
	void set_port(string port){portName=port;}
	string get_port(){return portName;}
	void set_angle(double a){angle=a;}
	int get_angle(){return angle;}
	virtual ~ship_path(){}
private:
	double speed;
	Point dst;
	Point current;
	Point future_point;
	string portName;
	int angle;
	double future_speed;
};

#endif /* ship_path_H_ */
