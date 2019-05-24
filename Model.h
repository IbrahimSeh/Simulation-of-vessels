/*
 *  Tel Hai College
 *
 *  @Date: 	17 June 2018
 *  @Author:   	Ibrahim Seh & noor bakriya
 *  @Id:	316237031 & 318586302
 *  @email:	abrahem-seh@hotmail.com & noor.bakrieh@yahoo.com
 */

#ifndef MODEL_H_
#define MODEL_H_

#include <algorithm>
#include <list>
#include <string>
#include <sstream>
#include <fstream>
#include "Port.h"
class Model {

public:

	class InvalidModelInput{

	private:
		string msg;
	public:
		InvalidModelInput(string m):msg(m){}
		void print(){ cout<<"Invalid input : " << msg<< endl;}
	};

	static  Model* get_Instance();
	
	~Model();
	Model(const Model&) = delete;
	Model& operator= (const Model&) = delete;
	Model(const Model&&) = delete;
	Model& operator= (const Model&&) = delete;
	void add_to_list_port(shared_ptr<Port> p){listPort.push_back(p);}
	void add_to_list_Basic_Ship(shared_ptr<Basic_Ship> p){listShips.push_back(p);}
	void read_from_file(char * file)throw(InvalidModelInput);
	void Control_unit_commands(string command,string input)throw(InvalidModelInput);
	void create_ship(istringstream &in)throw(InvalidModelInput);
	void show_status();
	void update_ports_and_ships();
	void set_time(int t){time=t;}//
	int get_time(){return time;}//
	bool check_name(string name);
	bool port_is_exist(string p);
	bool is_valid_coordinates(string coord);
	bool is_number(const std::string& s);
	bool check_if_exist_ship(string s);
	int  check_if_legal_ship_kind(string k);
	void set_container_F(string ship_name,int containerF);
	void set_resistence_F(string ship_name,double resistenceF);
	shared_ptr<Basic_Ship> get_ship(string shipName);
	void course(string nameShip,double angle,double speed);
	bool isOnlyDouble(const char* str);
	void position(string nameShip,double xCor,double yCor,double speed);
	void destination(string nameShip, string portName,double speed);
	void load_at(string nameShip,string portName);
	void run_command_ship(string ship,int num_command,istringstream & in);
	void unload_at(string nameShip,string portName,int contianer);
	void dock_at(string nameShip,string portName);
	int check_if_legal_ship_command(string c);
	shared_ptr<Port> get_port(string portName);
	double distanceCalculate(double x1, double y1, double x2, double y2);
	shared_ptr<Port> makePort(string name, double x, double y,double gas,double fuelCreate)
  { shared_ptr<Port> a(new Port(name,x,y,gas,fuelCreate)); return a;}
	shared_ptr<Basic_Ship> makeShip(Basic_Ship::ShipKind shipk,string shipName,double xCor,double yCor);
	void handle_stop(string shipName);
	void handle_refuel(string shipName);
	list<shared_ptr<Basic_Ship> > get_shipList(){return listShips;}
	list<shared_ptr<Port>> get_portList(){return listPort;}
	string fixString(string s);
	void set_forceP(string ship_name,double forceP);
	
	friend class Model_destroyer;

private:
	Model();
	enum Choice{COURSE = 1,POSITION = 2,DESTINATION = 3,LOAD_AT = 4,UNLOAD_AT = 5,DOCK_AT = 6,ATTACK = 7,REFUEL = 8,STOP = 9};
	static Model* model;
	list<shared_ptr<Basic_Ship> > listShips;
	list<shared_ptr<Port> > listPort;
	int time;

};

#endif /* MODEL_H_ */
