/*
 *  Tel Hai College
 *
 *  @Date: 	17 June 2018
 *  @Author:   	Ibrahim Seh & noor bakriya
 *  @Id:	316237031 & 318586302
 *  @email:	abrahem-seh@hotmail.com & noor.bakrieh@yahoo.com
 */

#ifndef Freighter_Ship_H_
#define Freighter_Ship_H_

#include "Pirate_ship.h"
#define MAX_CONTIANER 60
class Freighter_Ship: public Basic_Ship {
public:
	Freighter_Ship();
	Freighter_Ship(string shipName,double xCor,double yCor);
	void set_fuel(double gas);
	void set_resistance(double res);
	void show_status();
	void unloading(int contianer);
	void loading();
	void load_at();
	void unload();
	void refueling(double gas);
	void update(); 
	void get_in_queu();
	double attack();
	void being_attackt();
	int get_kind();
	void set_contianer(int conN);

	virtual ~Freighter_Ship(){}
private:
	double resistance;
	bool duck;
	bool wait_fuel;
	bool get_attackt;
	int con;
	int con_remove;


};

#endif /* Freighter_Ship_H_ */
