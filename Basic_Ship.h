/*
 *  Tel Hai College
 *
 *  @Date: 	17 June 2018
 *  @Author:   	Ibrahim Seh & noor bakriya
 *  @Id:	316237031 & 318586302
 *  @email:	abrahem-seh@hotmail.com & noor.bakrieh@yahoo.com
 */
#ifndef Basic_Ship_H_
#define Basic_Ship_H_

#include "ship_path.h"
/*This base class for all Basic_Ship*/

const int CalculateCourse = 450;
const double MaxDockingRange = 50.0;

class Basic_Ship {
public:
	enum class ShipKind { Pirate , Patrol , Freighter};
	Basic_Ship(); /*default ctr*/
	Basic_Ship(string shipName,double xCor,double yCor,double speed,double consumptionFuelN,double fuelN);
	void destination(Point p, double speed,string namePort);/* make dst by point and speed*/
	void Position(Point p, double speed);/* make position by point and speed*/
	void Course(int angle,double speed);/* make Course by point and speed*/
	virtual void Stopping();            /*stop the ship*/
	void set_future_point(Point p);
	void set_detination(string port_name);
	void set_direction(int angle,double speed);
	void set_dst_ship(Point p, double speed,string namePort);
	void set_dst_ship(Point point, double speed);
	double returnX();
	double returnY();
	Point get_current();
	virtual int get_kind();                /*return the kind of the ship*/
	virtual void show_status();
	string getName(){return ShipName;} 
	void update();                 /*update individual by kind of ship*/
	virtual void anchoring(Point p,string portName);
	virtual void anchor_at();
	virtual void refueling(double gas);
	virtual void get_in_queu();             /*get in queu of port for get fuel*/
	double get_fuel_needed();
	Point get_future();
	void set_point(int x,int y,double speed);
	double get_speed();
	bool refuel();
	string get_docket_port_name();
	double get_consumptionFuel();               /*return the fuel need to refuel*/
	void set_consumptionFuel(double fuel);
	virtual double attack();
	void set_fuel(double f);
	double get_fuel();
	virtual ~Basic_Ship();
	enum kind_Basic_Ship{ Pirate_ship=1, PatrolBoats=2, Freighter=3};
protected:
	string state;
	string ShipName;
	ship_path path;
	double maxSpeed;
	double consumptionFuel;
	double fuel;
	double max_fuel;
	double angle;
	enum state {Stop=1, Docking=2, Dead_in_the_water=3, Moving_to=4, Moving_to_dst=5,Direction=6,Attack=7,Load=8,Unload=9};
	int status;
};

#endif /* Basic_Ship_H_ */
