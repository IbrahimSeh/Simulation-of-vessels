#include "View.h"

View::View():size(DEFAULTSIZE),scale(DEFAULTSCALE),xOrigin(-10.0),yOrigin(-10.0)
{}

bool View:: is_number(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

//function handles vie commands
void View::run_commands(string input)throw(InvalidViewInput){

	string command;
	istringstream in(input);
	in>>command;


	if(command=="default"){
		set_size(DEFAULTSIZE);
	    set_x(-10);
	    set_y(-10);
	}

	if(command=="show")
		show_map();

	if(command=="size"){

		if(in.rdbuf()->in_avail()==0){
			throw InvalidViewInput("invalid number of arguments");
		}
		string temp;
		in>>temp;
		if(!is_number(temp)){
			throw InvalidViewInput("illegal argument: size not an integer");
		}
		int size=stoi(temp);

		if(size <6)
			throw InvalidViewInput("size entered is too small");

		if(size >30)
			throw InvalidViewInput("size entered is too large");


		set_size(size);
	}

	if(command=="zoom"){

		if(in.rdbuf()->in_avail()==0){
			throw InvalidViewInput("invalid number of arguments");
		}
		string temp;
		in>>temp;
		if(!isOnlyDouble(temp.c_str())){
			throw InvalidViewInput("illegal argument: scale not type double");
		}

		double scale=stod(temp);
		if(scale<0){
			throw InvalidViewInput("illegal argument: scale not positive");
		}

		set_scale(scale);
	}

	if(command=="pan"){

		if(in.rdbuf()->in_avail()==0){
			cout << "invalid number of arguments" <<endl;
			return;
		}

		string temp;
		in>>temp;
		if(!isOnlyDouble(temp.c_str())){
			cout << "illegal argument: scale not type double" <<endl;
			return;
		}
		if(in.rdbuf()->in_avail()==0){
			cout << "invalid number of arguments" <<endl;
			return;
		}
		string temp2;
		in>>temp2;
		if(!isOnlyDouble(temp.c_str())){
			cout << "illegal argument: scale not type double" <<endl;
			return;
		}
		double x=stod(temp);
		set_x(x);
		double y=stod(temp2);
		set_y(y);

	}

}

//function displays map to client
void View::show_map(){

	shared_ptr<Port> s1;
	shared_ptr<Basic_Ship> s2;
  cout << "Display: " << "size: " << size << " scale: " <<scale;
	cout << " origin: ( " << xOrigin<< ", " <<yOrigin<< " ) "<<endl;
	bool flag=false;

	int y=(int)(yOrigin+(size*scale-scale));
	int x1=(int)(xOrigin);

	for(int i=0;i<size;i++){
		x1=xOrigin;
		flag=false;
		if(i%3==0){
       if(y<-10)
				 cout <<" "<< y <<" ";
       else if(y>10 || y<0)
        cout <<" "<< y <<"  ";
       else
        cout<<" "<< y <<"   ";
	   }
	   else 
			cout<<"     ";
		
    for(int j=0;j<size;j++){
			s2=exist_in_cords_ship(x1,y);
      s1=exist_in_cords_port(x1,y);
      if(s2!=nullptr){
			x1+=scale;
			if(s2!=nullptr && flag==false){
				string name=s2->getName();
				cout<<name[0]<<name[1];
				flag=true;

			}else{
				cout<<". ";
			}
   }else
   {
     	x1+=scale;
			if(s1!=nullptr && flag==false){
				string name=s1->getName();
				cout<<name[0]<<name[1];
				flag=true;

			}else{
				cout<<". ";
			}
   }
   
	}
		y-=scale;

		cout <<endl;
	}


	int x=(int)xOrigin;
	cout<<"    ";
	for(int i=0;i<size;i++){

		if((i%3)==0)
			cout << x<< " ";
		cout<<" ";
		x+=scale;
	}
	cout<<endl;
	cout.precision(2);

}

bool View:: isOnlyDouble(const char* str)
{
    char* endptr = 0;
    strtod(str, &endptr);

    if(*endptr != '\0' || endptr == str)
        return false;
    return true;
}
//function checks if an object exist in certain corrdinates
shared_ptr<Port> View::exist_in_cords_port(double x,double y){

	list<shared_ptr<Port> > ports=Model::get_Instance()->get_portList();
	double xcor,ycor;

	list<shared_ptr<Port>>::iterator it;
	for(it =ports.begin(); it != ports.end(); ++it){

		xcor=(*it)->get_x();
		ycor=(*it)->get_y();

		if((round(xcor)>=x && round(xcor)<=x+scale) && (round(ycor)>y && round(ycor)<=y+scale))
			return (*it);
	}

	return nullptr;
}

shared_ptr<Basic_Ship> View::exist_in_cords_ship(double x,double y){

	list<shared_ptr<Basic_Ship> > ships=Model::get_Instance()->get_shipList();
	double xcor,ycor;

	list<shared_ptr<Basic_Ship>>::iterator it2;
	for(it2 =ships.begin(); it2 != ships.end(); ++it2){

		xcor=(*it2)->returnX();
		ycor=(*it2)->returnY();

		if((round(xcor)>=x && round(xcor)<x+scale) && (round(ycor)>=y && round(ycor)<y+scale))
			return (*it2);
	}

	return nullptr;
}