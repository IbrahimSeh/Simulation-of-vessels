/*
 *  Tel Hai College
 *
 *  @Date: 	17 June 2018
 *  @Author:   	Ibrahim Seh & noor bakriya
 *  @Id:	316237031 & 318586302
 *  @email:	abrahem-seh@hotmail.com & noor.bakrieh@yahoo.com
 */

#ifndef VIEW_H_
#define VIEW_H_
using namespace std;
#include <iostream>
#include <sstream>
#include <cctype>
#include <math.h>
#include "Model.h"
#include "Port.h"
#include "Basic_Ship.h"
const int DEFAULTSIZE=25;
const double DEFAULTSCALE=2.0;


class View {
public:

	class InvalidViewInput{

	private:
		string msg;
	public:
		InvalidViewInput(string m):msg(m){}
		void print(){ cout<<"Wrong input : " << msg<< endl;}
	};

	View();
	void set_size(int s){size=s;}
	void set_scale(int s){scale=s;}
	void set_x(double num){xOrigin=num;}
	void set_y(double num){yOrigin=num;}
	int get_size(){return size;}
	double get_scale(){return scale;}
	double get_xorigin(){return xOrigin;}
	double get_yorigin(){return yOrigin;}
	void run_commands(string command)throw(InvalidViewInput);
	void show_map();
	bool is_number(const std::string& s);
	bool isOnlyDouble(const char* str);
	shared_ptr<Basic_Ship> exist_in_cords_ship(double x,double y);
	shared_ptr<Port> exist_in_cords_port(double x,double y);

private:
	int size;
	double scale;
	double xOrigin;
	double yOrigin;
};

#endif /* VIEW_H_ */
