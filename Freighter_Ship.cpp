
#include "Freighter_Ship.h"

Freighter_Ship::Freighter_Ship()
:resistance(0),duck(false),wait_fuel(false),get_attackt(false),con(0),con_remove(0)
{
	// TODO Auto-generated constructor stub

}
int Freighter_Ship::get_kind()
{
	return Freighter;
}


Freighter_Ship::Freighter_Ship(string shipName,double xCor,double yCor)
:Basic_Ship(shipName,xCor,yCor,40,1000,500000),resistance(0),duck(false),wait_fuel(false),get_attackt(false),con(0),con_remove(0)
{
	path.set_speed(40);
}
void Freighter_Ship::set_fuel(double gas)
{

	fuel=gas;
}
void Freighter_Ship::set_contianer(int conN)
{
	con=conN;

}
void Freighter_Ship::set_resistance(double res)
{
	resistance=res;
}

void Freighter_Ship::show_status()
{
	int count=0;
	cout<<"Freighter ";
	Basic_Ship::show_status();

	cout<<"fuel:"<<fuel/1000<<" kl, resistance: "<<resistance<< " ";
	cout<<"state: " <<state <<", " << "speed " << path.get_speed()<<" nm/hr,";
	cout<<" Container : "<<con;
	cout<< count <<endl;

}

void Freighter_Ship::unload()
{
	con=con-con_remove;
	con_remove=0;
	state="UNLoad at ";
	state.append(path.get_port());
	path.set_current(path.get_dst());
}

void Freighter_Ship::unloading(int contianer)
{
	if(status==Docking)
		status=Unload;
	con_remove=contianer;

}

void Freighter_Ship::load_at()
{
	con=MAX_CONTIANER;
	state="Load at ";
	state.append(path.get_port());
	path.set_current(path.get_dst());
}

void Freighter_Ship::loading()
{
	cout<<status;
	if(status==Docking){
		status=Load;
	}

}
void Freighter_Ship::refueling(double gas)
{
	wait_fuel=false;
	fuel+=gas;

}
void Freighter_Ship::get_in_queu()
{
	wait_fuel=true;

}
/*virtual function of update*/
void Freighter_Ship::update()
{
	if( !wait_fuel){
		if(status==Attack)
		{
			con=0;
			status=Stop;
			state="Stopping";
			return;
		}
		if( status!=Dead_in_the_water)
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
			if(status==Load)
			{
				load_at();
			}
			if(status==Unload)
			{
				unload();
			}
			if(status==Docking){
				anchor_at();
			}
		}


	}
	fuel-=consumptionFuel;
	if(fuel<0)
	{
		status=Dead_in_the_water;
		state="Dead in water bye bye!";
	}

}
void Freighter_Ship::being_attackt()
{
	get_attackt=true;

}
double Freighter_Ship::attack()
{
	status=Attack;
	return resistance;

}

