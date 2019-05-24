
#include "Pirate_ship.h"

Pirate_ship::Pirate_ship():force(0),attacking(0),cruise_r(0) {
	// TODO Auto-generated constructor stub

}


Pirate_ship::Pirate_ship(string shipName,double xCor,double yCor)
:Basic_Ship(shipName,xCor,yCor,75,0,0),force(0),attacking(0),cruise_r(0) {
	path.set_speed(75);

}

double Pirate_ship::attack()
{
	status=Attack;
	return force;

}

void Pirate_ship::show_status()
{
	cout<<"Cruiser ";
	Basic_Ship::show_status();
	cout <<"force: "<<force;
	cout<<", state: " <<state <<", " << "speed " << path.get_speed()<<" nm/hr,"<<endl;
}

void Pirate_ship::update(){
	if(status==Attack)
	{
		force+=cruise_r;
		cruise_r=0;
		status=Stop;
		state="Stopping";
		path.set_speed(0);
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


