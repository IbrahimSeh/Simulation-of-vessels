#include "Basic_Ship.h"

Basic_Ship::Basic_Ship()
:state("Stopping"),maxSpeed(0),consumptionFuel(0),fuel(0),max_fuel(0),angle(0),status(Stop)

{
	path.set_speed(0);

}

Basic_Ship::Basic_Ship(string shipName,double xCor,double yCor,double speed,double consumptionFuelN,double fuelN)
:ShipName(shipName),state("Stopping"),path(0),maxSpeed(speed),consumptionFuel(consumptionFuelN),fuel(fuelN),max_fuel(fuelN),angle(0),status(Stop)
{
	Point point(xCor,yCor);
	path.set_current(point);
	path.set_speed(0);

}

Point Basic_Ship::get_current()
{
	return path.get_current();

}

int Basic_Ship::get_kind()
{
	return PatrolBoats;

}


void Basic_Ship::Stopping()
{
	status=Stop;
}
void Basic_Ship::set_future_point(Point p)
{
	path.set_future_point(p);

}double Basic_Ship::get_speed()
{
	return maxSpeed;
}
void Basic_Ship::set_dst_ship(Point p, double speed,string namePort)
{
	set_dst_ship(p,speed);
	state="moving to"+namePort;
}


void Basic_Ship::destination(Point p, double speed,string namePort)
{
	status=Moving_to_dst;
	path.set_dst(p);
	path.set_ftr_speed(speed);
	path.set_port(namePort);
}


void Basic_Ship::Position(Point p, double speed)
{
	status=Moving_to;
	path.set_dst(p);
	path.set_ftr_speed(speed);
}
void Basic_Ship::set_dst_ship(Point point, double speed)
{
	int x=point.get_x();
	int y=point.get_y();

	state="Moving to";
	Point currentPoint =path.get_current();
	Point p(x,y);
	double dist = euclideanDistance(point, currentPoint);
	if(dist>=MaxDockingRange){
		path.set_future_point(p);
		path.set_speed(speed);
		return;
	}
	path.set_speed(speed);
	Cartesian_vector cartesian;
	cartesian.delta_x = x-currentPoint.get_x();
	cartesian.delta_y = y-currentPoint.get_y();
	Polar_vector polar(cartesian);
	angle=polar.theta;

	Polar_vector polar1;
	polar1.r = speed;
	polar1.theta = angle;
	Cartesian_vector cartesian1(polar1);
	Point future_p;
	future_p.x=currentPoint.x +cartesian1.delta_x;
	future_p.y=currentPoint.y + cartesian1.delta_y;

	path.set_future_point(future_p);
}

void Basic_Ship::Course(int angle,double speed)
{

	status=Direction;
	path.set_ftr_speed(speed);
	path.set_angle(angle);


}
void Basic_Ship::set_direction(int angle,double speed)
{
	state="Moving on course ...";
	path.set_speed(speed);
	Polar_vector polar;
	polar.r = speed;
	polar.theta = to_radians(CalculateCourse-angle);
	Cartesian_vector cartesian(polar);
	Point currentPoint =path.get_current();
	currentPoint.set_x(currentPoint.get_x() + cartesian.delta_x);
	currentPoint.set_y(currentPoint.get_y() +cartesian.delta_y);
	path.set_future_point(currentPoint);
}


void Basic_Ship::show_status()
{
	cout<<getName()<<" at ("<<path.get_current_x()<<","<<path.get_current_y()<<") , ";
}

//update individual by kind of ship/
void Basic_Ship::update()
{
	if(status==Stop)
	{
		path.set_speed(0);
		state="Stopped";
		return;

	}
	if(status!=Dead_in_the_water)
	{
		if(status==Moving_to_dst)
		{
			set_dst_ship(path.get_dst(),path.get_ftr_speed(),path.get_port());
			path.set_current(path.get_future_point());
			if(path.get_current()==path.get_dst()){
				state="Docked";
				status=Docking;
			}
		}
		if(status==Moving_to)
		{
			set_dst_ship(path.get_dst(),path.get_ftr_speed());
			path.set_current(path.get_future_point());
			if(path.get_current()==path.get_dst()){
				state="Docked";
				status=Docking;
			}

		}
		if(status==Direction)
		{
			set_direction(path.get_angle(),path.get_ftr_speed());
			path.set_current(path.get_future_point());

		}
		if(status==Docking)
			anchor_at();
	}
}
void Basic_Ship::anchor_at()
{
	path.set_speed(0);
	status=Docking;
	state="Docked at ";
	state.append(path.get_port());
	path.set_current(path.get_dst());
}
void Basic_Ship::anchoring(Point p,string portName)
{
	path.set_dst(p);
	path.set_port(portName);
	status=Docking;

}
double Basic_Ship::returnX()
{
	return path.get_current_x();
}
double Basic_Ship::returnY()
{
	return path.get_current_y();
}
bool Basic_Ship:: refuel(){

	string str="Docket at ";
	string shipName;
	size_t found = state.find(str);
	if (found==string::npos){
		//ship is not docked no refuel needed
		return false;
	}

	return true;
}
void Basic_Ship::refueling(double gas)
{
	fuel+=gas;

}
void Basic_Ship::get_in_queu()
{

}

string Basic_Ship:: get_docket_port_name(){

	string str="Docket at ";
	string shipName;

	for(int i=str.length();i<(int)state.length();i++){
		shipName+=state[i];
	}
	return shipName;
}

double Basic_Ship:: get_fuel_needed(){
	return max_fuel-fuel;
}


Point Basic_Ship::get_future()
{
	return path.get_future_point();

}
double Basic_Ship::attack()
{
	state="Stopping";
	status=Stop;
	return 0;

}

void Basic_Ship::set_point(int x,int y,double speed)
{
	Point currentPoint(path.get_current().get_x(),path.get_current().get_y());
	Point p(x,y);
	double dist = euclideanDistance(p, currentPoint);
	
	if(dist>=MaxDockingRange){
		path.set_future_point(p);
		path.set_speed(speed);
		return;
	}
	path.set_speed(speed);
	Cartesian_vector cartesian;
	cartesian.delta_x = x-currentPoint.get_x();
	cartesian.delta_y = y-currentPoint.get_y();
	Polar_vector polar(cartesian);
	angle=polar.theta;
	path.set_future_point(p);
}
void Basic_Ship::set_fuel(double f){
	fuel=f;
}

double Basic_Ship::get_fuel(){

	return fuel;
}
Basic_Ship::~Basic_Ship() {

}