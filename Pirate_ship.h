/*
 *  Tel Hai College
 *
 *  @Date: 	17 June 2018
 *  @Author:   	Ibrahim Seh & noor bakriya
 *  @Id:	316237031 & 318586302
 *  @email:	abrahem-seh@hotmail.com & noor.bakrieh@yahoo.com
 */


#ifndef Pirate_ship_H_
#define Pirate_ship_H_

#include "Patrol_ship.h"
/*Pirate Class*/
class Pirate_ship: public Basic_Ship {
public:
	Pirate_ship();
	Pirate_ship(string stateN,double s,string courseN);
	Pirate_ship(string shipName,double xCor,double yCor);
	void set_force(double f){force=f;}
	void show_status();
	double attack();
	void add_force(int num){cruise_r=num;}
	void update();
	int get_kind(){return Basic_Ship::kind_Basic_Ship::Pirate_ship;}

	virtual ~Pirate_ship(){}
private:
	double force;
	int attacking;
	int cruise_r;
};

#endif /* Pirate_ship_H_ */
