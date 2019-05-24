

#include "Patrol_ship.h"

Patrol_ship::Patrol_ship()
:resistance(0),duck(0),wait_fuel(false),start(false)
{
}

Patrol_ship::Patrol_ship(string shipName,double xCor,double yCor)
:Basic_Ship(shipName,xCor,yCor,15,2000,900000),resistance(0),duck(0),wait_fuel(false),start(false)
{
	Point p;
	path.set_speed(15);
}
void Patrol_ship::update()
{
	if(duck!=0 && !wait_fuel){
		if(status==Attack)
		{
			status=Stop;
			state="Stopping";
			return;
		}
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
	else
	{
		duck--;
		if(duck==0)
		{
			update_closest_port();
			status=Moving_to_dst;

		}
	}
	fuel-=consumptionFuel;
	if(fuel<0)
	{
		status=Dead_in_the_water;
		state="Dead in water";
	}



}

void Patrol_ship::refueling(double gas)
{
	wait_fuel=false;
	fuel+=gas;

}
void Patrol_ship::anchoring(Point p,string portName)
{
	duck=3;
	if(start==false)
	{
		start=true;
	}
	status=Docking;
	mapPort.erase(portName);

}
void Patrol_ship::update_closest_port()
{
	double min_dist,dist;
	string portName;
	Point pointPort=mapPort.begin()->second;
	min_dist=euclideanDistance(pointPort, path.get_current());
	std::map<string,Point>::iterator it = mapPort.begin();
	for (it=mapPort.begin(); it!=mapPort.end(); ++it)
	{
		dist = euclideanDistance(it->second, path.get_current());
		if(min_dist > dist) {
			pointPort=it->second;
			portName=it->first;
		}

	}
	path.set_port(portName);
	path.set_speed(15);
	path.set_dst(pointPort);
}
double Patrol_ship::attack()
{
	status=Attack;
	return -1;

}
void Patrol_ship::add_port(Point p,string portName)
{
	mapPort.insert(pair<string,Point>(portName,p));

}
void Patrol_ship:: show_status(){


	cout<<"Patrol Boat ";
	Basic_Ship::show_status();

	cout<<"fuel:"<<fuel/1000<< " kl,";
	cout<<"state: " <<state <<", " << "speed " << path.get_speed()<< " nm/hr,"<<endl;

}
Patrol_ship::~Patrol_ship() {
	mapPort.clear();
}

