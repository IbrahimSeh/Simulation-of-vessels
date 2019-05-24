/*
 *  Tel Hai College
 *
 *  @Date: 	17 June 2018
 *  @Author:   	Ibrahim Seh & noor bakriya
 *  @Id:	316237031 & 318586302
 *  @email:	abrahem-seh@hotmail.com & noor.bakrieh@yahoo.com
 */

#ifndef PORT_H_
#define PORT_H_

#include "Freighter_Ship.h"
#include <queue>

class Port {
public:
	Port();
	Port(string name, double x, double y,double gas,double createFuelN);
	void show_status();
	void update();
	double get_x(){return xCor;}
	double get_y(){return yCor;}
	Point get_point(){Point p(xCor,yCor); return p;}
	string getName(){return portName;}
	virtual ~Port();
	void add_to_queue(shared_ptr<Basic_Ship> in);
private:
	string portName;
	double xCor;
	double yCor;
	double fuel;  
	double createFuel;
	queue< shared_ptr<Basic_Ship> > fuel_queue;
};

#endif /* PORT_H_ */
