/*
 *  Tel Hai College
 *
 *  @Date: 	17 June 2018
 *  @Author:   	Ibrahim Seh & noor bakriya
 *  @Id:	316237031 & 318586302
 *  @email:	abrahem-seh@hotmail.com & noor.bakrieh@yahoo.com
 */

#ifndef Patrol_ship_H_
#define Patrol_ship_H_
#include "Basic_Ship.h"
class Patrol_ship: public Basic_Ship {
public:
	Patrol_ship();
	Patrol_ship(string shipName,double xCor,double yCor);
	void refueling(double gas);
	void anchoring(Point p, string portName);
	void add_port(Point p,string portName);
	void update();
	void get_in_queu(){wait_fuel=true;}
	void update_closest_port();
	double attack();
	void show_status();

	virtual ~Patrol_ship();
private:
	int resistance;
	int duck;
	bool wait_fuel;
	map<string,Point> mapPort;
	bool start;

};

#endif /* Patrol_ship_H_ */
