#include "Port.h"

Port::Port()
:xCor(0),yCor(0),fuel(0),createFuel(0)
{
}

Port::Port(string name, double x, double y,double gas,double createFuelN)
:portName(name),xCor(x),yCor(y),fuel(gas),createFuel(createFuelN)
{
}

void Port::show_status()
{
	cout<<"Port "<<portName<<" at position ("<<xCor<<" , "<<yCor<<") Fuel available "<<fuel/1000<<" kl"<<endl;
}

void Port:: add_to_queue(shared_ptr<Basic_Ship> in){

	fuel_queue.push(in);

}

void Port::update()
{
	fuel+=createFuel;
	if( !fuel_queue.empty()){
		double fuel_ship=fuel_queue.front()->get_fuel_needed();
		if(fuel>=fuel_ship){
			shared_ptr<Basic_Ship> ship=fuel_queue.front();
			ship->set_fuel(ship->get_fuel()+fuel_ship);
			fuel-= fuel_ship;
			if(fuel <0)
				fuel=0;
			fuel_queue.pop();
		}
	}

}
Port::~Port() {
	while(!fuel_queue.empty()) fuel_queue.pop();
}