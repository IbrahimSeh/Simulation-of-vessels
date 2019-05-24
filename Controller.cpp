#include "Controller.h"

// c'tor
Controller::Controller():view_ptr(0) {
  cout.setf(ios::fixed, ios::floatfield);
  cout.precision(2);
  view_ptr=make_shared<View>();
}

// run function
void Controller:: run(){
	run_commands();
}

// checks if command is a model command
bool Controller:: check_if_leggal_command(string c){

	if(c=="status")
		return true;
	if(c=="go")
		return true;
	if(c=="create")
		return true;
	return false;
}

void Controller:: set_up_objects(char * file)throw(InvalidFile){
	try{
		Model::get_Instance()->read_from_file(file);
	}
	catch(Model::InvalidModelInput &in){
		in.print();
		exit(1);
	}
}

bool Controller:: check_if_view_command(string command){

	if(command=="default"|| command=="zoom" || command=="pan"|| command=="size" || command=="show")
		return true;
	return false;
}

int Controller:: check_if_legal_ship_command(string c){//replace c to cmd

	if(c=="course")
		return 1;
	if(c=="position")
		return 2;
	if(c=="destination")
		return 3;
	if(c=="load_at")
		return 4;
	if(c=="unload_at")
		return 5;
	if(c=="dock_at")
		return 6;
	if(c=="attack")
		return 7;
	if(c=="refuel")
		return 8;
	if(c=="stop")
		return 9;
	return -1;
	

}

void Controller::run_commands(){

	string input="";
	string command="";


	while(command != "exit"){


		cout << "TIME " << Model::get_Instance()->get_time() << ": " << "Enter Command: "<<endl;
		getline(cin,input);
		istringstream instr(input);
		instr>>command;


		if(check_if_leggal_command(command)){
			try{
				Model::get_Instance()->Control_unit_commands(command,input);
			}
			catch(Model:: InvalidModelInput & in){
				in.print();
			}
		}
		else{

			if(!(Model::get_Instance()->check_if_exist_ship(command)))
			{
				string n_command;
				instr>>n_command;
          
				int num_command=(check_if_legal_ship_command(n_command));
				if( num_command != -1){
					try{
						Model::get_Instance()->run_command_ship(command,num_command,instr);

					}
					catch(Model:: InvalidModelInput & in){
						in.print();
					}
				}
				else{
					cout<< "ilegal command entered : "<<n_command<<endl;
				}
			}
			else{

				if(check_if_view_command(command)){

					try{
						view_ptr->run_commands(input);
					}
					catch(View:: InvalidViewInput & in){
						in.print();
					}

				}
				else{
					if(command != "exit")
						cout<< "ilegal command entered : " << command  <<endl;
				}

			}
		}
	}

}