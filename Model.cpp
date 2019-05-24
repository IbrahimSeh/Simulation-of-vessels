#include "Model.h"
Model* Model::model = 0;
/*TODO realese the model*/
/* model destroyer */
class  Model_destroyer {

public:
	~Model_destroyer() {
	delete Model:: model;
	}
};

// create the object if it doesn't already exist
Model* Model::get_Instance() {
	if (!model){
		model=new Model();
	}
	return model;
}

//c'tor
Model:: Model():time(0){

	listPort.push_back(makePort("Nagoya",50,5,1000000,1000));//creat the first port

}

//d'tor
Model:: ~Model(){

	listPort.clear();
	listShips.clear();
}

void Model::course(string nameShip,double angle,double speed)
{
	Point p(0,0);
	list<shared_ptr<Basic_Ship>>::iterator it;
	for(it =listShips.begin(); it != listShips.end(); ++it)
	{
		if((*it)->getName()==nameShip){
			(*it)->Course(angle,speed);
			break;
		}
	}
}

//sets position
void Model::position(string nameShip,double xCor,double yCor,double speed)
{
	Point point(xCor,yCor);
	list<shared_ptr<Basic_Ship>>::iterator it;
	for(it =listShips.begin(); it != listShips.end(); ++it)
	{
		if((*it)->getName()==nameShip){
			(*it)->Position(point,speed);
			break;
		}
	}
}

//read another ports from argv[1]
void Model:: read_from_file(char * file)throw(InvalidModelInput){
	string line;
	string msg=file;
	string port_name="";
	string coordinates1="",coordinates2="",fuelAmount="",createFuel="";
	ifstream File( file, ios::in );


	/* exit program if file could not be opened*/
	if (!File) {
		File.close();// close file
		throw InvalidModelInput(msg+" invalid");
	}

	while(!File.eof()){
		port_name="",coordinates1="",coordinates2="",fuelAmount="",createFuel="";
		getline(File,line);
		istringstream instr(line);
		instr>>port_name>>coordinates1>>coordinates2 >> fuelAmount>>createFuel;
		if(port_name==""||coordinates1==""||createFuel==""|| fuelAmount==""){
			File.close();
			throw InvalidModelInput(msg+" invalid");
		}

		if(!check_name(port_name)||!port_is_exist(port_name)){
			File.close();
			throw InvalidModelInput(msg+" invalid");
		}

		string tmp(coordinates1+coordinates2);
		if(is_valid_coordinates(coordinates2)){
			File.close();
			throw InvalidModelInput(msg+" invalid");
		}

		if(!isOnlyDouble(fuelAmount.c_str()) || !isOnlyDouble(createFuel.c_str())){
			File.close();
			throw InvalidModelInput(msg+" invalid");
		}

		double x=stod(fixString(coordinates1));
		double y=stod(fixString(coordinates2));
		double fuel=stod(fuelAmount);
		double create=stod(createFuel);

		add_to_list_port(makePort(port_name,x,y,fuel,create));

	}
}

bool Model:: isOnlyDouble(const char* str)
{
    char* endptr = 0;
    strtod(str, &endptr);

    if(*endptr != '\0' || endptr == str)
        return false;
    return true;
}

void Model::run_command_ship(string shipName,int num_command,istringstream & in)
{
	switch(num_command){
	case COURSE:
	{
		int angle=0,speed=0;
		string a,s;
		if(in.rdbuf()->in_avail()==0 ){
			throw InvalidModelInput("insufficient arguments for Course ");
		}
		in>>a;
		if(!is_number(a)||in.rdbuf()->in_avail()==0 ){
			throw InvalidModelInput("invalid arguments for Course ");
		}

		angle=stoi(a);
		in>>s;
		if(!is_number(s)){
			throw InvalidModelInput("insufficient arguments for Course ");
			break;
		}

		speed=stoi(s);
		if(speed>get_ship(shipName)->get_speed()){
			throw InvalidModelInput("invalid speed arguments for Course  ");
			break;
		}
		course(shipName,angle,speed);
		break;
	}
	case POSITION:{
		double xCor=0,yCor=0,speed=0;
		string s,x,y;
		if(in.rdbuf()->in_avail()==0 ){
			throw InvalidModelInput("insufficient arguments for POSITION command1 ");
		}
		in>>x;
		if(in.rdbuf()->in_avail()==0)
			throw InvalidModelInput("invalid arguments for POSITION command2 ");

		in>>y;
		if(in.rdbuf()->in_avail()==0)
			throw InvalidModelInput("invalid arguments for POSITION command3 ");

		if(!is_valid_coordinates(x)||!is_valid_coordinates(y))//*******
			throw InvalidModelInput("invalid arguments for POSITION command4 ");

		in>>s;
		if(!isOnlyDouble(s.c_str()))
			throw InvalidModelInput("invalid arguments for POSITION command5 ");

		speed=stod(s);


		if(speed>get_ship(shipName)->get_speed()){
			throw InvalidModelInput("invalid speed arguments for Position  ");
			break;
		}
		xCor=stod(x);
		yCor=stod(y);
		position(shipName,xCor,yCor,speed);
		break;

	}
	case DESTINATION:{
		string port,speedP;
		double speed=0;
		if(in.rdbuf()->in_avail()==0 ){
			throw InvalidModelInput("insufficient arguments for DESTINATION command ");
			break;
		}
		in>>port;
		if(port_is_exist(port)||in.rdbuf()->in_avail()==0){
			throw InvalidModelInput("invalid arguments for DESTINATION command ");
			break;
		}

		in>>speedP;
		if(!isOnlyDouble(speedP.c_str())){
			throw InvalidModelInput("invalid arguments for DESTINATION command ");
			break;
		}
		if(speed>get_ship(shipName)->get_speed()){
			throw InvalidModelInput("invalid speed arguments for Course  ");
			break;
		}
		speed=stod(speedP);
		speed=stod(speedP);
		destination(shipName, port,speed);
		break;
	}
	case LOAD_AT:{
		string port;
		if(in.rdbuf()->in_avail()==0 ){
			throw InvalidModelInput("insufficient arguments for LOAD_AT command ");
		}
		in>>port;
		if(port_is_exist(port)){
			throw InvalidModelInput("invalid arguments for LOAD_AT command2 ");
			break;
		}
		if(get_ship(shipName)->get_kind()!=Basic_Ship::Freighter){
			throw InvalidModelInput("invalid arguments for LOAD_AT command kind of ship innvalid");
			break;
		}

		load_at(shipName,port);
		break;

	}
	case UNLOAD_AT:{
		int containers;
		string port,cont;
		if(in.rdbuf()->in_avail()==0 ){
			throw InvalidModelInput("insufficient arguments for UNLOAD_AT command ");
			break;
		}
		in>>port;
		if(port_is_exist(port)||in.rdbuf()->in_avail()==0){
			throw InvalidModelInput("invalid arguments for UNLOAD_AT command ");
			break;
		}
		in>>cont;
		if(!is_number(cont)){
			throw InvalidModelInput("invalid arguments for UNLOAD_AT command ");
			break;
		}
		if(get_ship(shipName)->get_kind()!=Basic_Ship::Freighter){
			throw InvalidModelInput("invalid arguments for UNLOAD_AT command kind of ship unvalid");
			break;
		}

		containers=stoi(cont);
		unload_at(shipName,port,containers);

		break;

	}
	case DOCK_AT:{
		string port;
		if(in.rdbuf()->in_avail()==0 ){
			throw InvalidModelInput("insufficient arguments for DOC_AT command ");
			break;
		}
		in>>port;
		if(port_is_exist(port)){
			throw InvalidModelInput("invalid arguments for DOC_AT command ");
			break;
		}

		dock_at(shipName,port);
		break;

	}
	case ATTACK:{
		string ship;
		if(in.rdbuf()->in_avail()==0 ){
			throw InvalidModelInput("insufficient arguments for ATTACK command ");
		}
		in>>ship;
		if(check_if_exist_ship(ship)){
			throw InvalidModelInput("invalid arguments for ATTACK command ");
			break;
		}
		Point shipBeingAttack=get_ship(ship)->get_current();
		Point shipAttack=get_ship(shipName)->get_current();
		double dist = distanceCalculate(shipBeingAttack.get_x(),shipBeingAttack.get_y(), shipAttack.get_x(), shipAttack.get_y());
		if(dist > MaxDockingRange) {
			cout<<dist;
			throw InvalidModelInput("invalid arguments for ATTACK command out of range");
			break;
		}
		if(get_ship(shipName)->get_kind()!=Basic_Ship::Pirate_ship){
			throw InvalidModelInput("invalid arguments for ATTACK command kind of ship unvalid");
			break;
		}
		int resistance=get_ship(ship)->attack();
		int force=get_ship(shipName)->attack();
		if(resistance!=-1)
		{
			shared_ptr<Freighter_Ship> shipF=make_shared<Freighter_Ship>();
			shared_ptr<Pirate_ship> shipP=make_shared<Pirate_ship>();
			shipF= std::dynamic_pointer_cast<Freighter_Ship>(get_ship(ship));
			shipP=std::dynamic_pointer_cast<Pirate_ship>(get_ship(shipName));
			if(resistance<force)
			{

				shipF->being_attackt();
				shipP->add_force(1);
			}
			else{
				shipP->add_force(-1);
			}
		}
		break;
	}
	case REFUEL:{
		handle_refuel(shipName);
		break;

	}
	case STOP:{
		handle_stop(shipName);
		break;
	 }
	}
}

void Model::handle_refuel(string shipName){

	shared_ptr<Basic_Ship> ship=get_ship(shipName);
	if(ship->refuel()){
		string port_name=ship->get_docket_port_name();
		get_port(port_name)->add_to_queue(ship);

	}
}

shared_ptr<Port> Model::get_port(string portName){

	list<shared_ptr<Port>>::iterator it;
	for(it =listPort.begin(); it != listPort.end(); ++it){
		if((*it)->getName()==portName)
			return(*it);
	}
	return nullptr;
}

void Model::handle_stop(string shipName){
	(get_ship(shipName))->Stopping();
}

int Model:: check_if_legal_ship_command(string c){

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

double Model:: distanceCalculate(double x1, double y1, double x2, double y2)
{
	double x = x1 - x2; //calculating number to square in next step
	double y = y1 - y2;
	double dist;

	dist = pow(x, 2) + pow(y, 2);       //calculating Euclidean distance
	dist = sqrt(dist);                  

	return dist;
}

void  Model::dock_at(string nameShip,string portName)
{
	int xP,yP;
	list<shared_ptr<Port>>::iterator it;
	for(it =listPort.begin(); it != listPort.end(); ++it)
	{
		if((*it)->getName()==portName){
			xP=(*it)->get_x();
			yP=(*it)->get_y();
		}
	}
	Point portP(xP,yP);
	Point shipP=get_ship(nameShip)->get_current();
	double dist = distanceCalculate(portP.get_x(),portP.get_y(), shipP.get_x(), shipP.get_y());
	if(dist > MaxDockingRange) {
		cout<<dist;
		throw InvalidModelInput("invalid arguments for Dock command out of range");
		return;
	}
	get_ship(nameShip)->anchoring(portP,portName);
}

void Model::unload_at(string nameShip,string portName,int contianer)
{
	int xCor=-1,yCor=-1;
	list<shared_ptr<Port>>::iterator it;
	for(it =listPort.begin(); it != listPort.end(); ++it)
	{
		if((*it)->getName()==portName){
			xCor=(*it)->get_x();
			yCor=(*it)->get_y();
		}
	}
	if(xCor==-1 && yCor==-1)
	{
		throw InvalidModelInput("invalid arguments for UNLOAD ");
		return;
	}
	if(get_ship(nameShip)->get_kind()!=Basic_Ship::Freighter)
	{
		throw InvalidModelInput("invalid arguments for UNLOAD ");
		return;
	}
	Point portP(xCor,yCor);
	Point shipP=get_ship(nameShip)->get_current();
	double dist = distanceCalculate(portP.get_x(),portP.get_y(), shipP.get_x(), shipP.get_y());
	if(dist > MaxDockingRange) {
		cout<<dist;
		throw InvalidModelInput("invalid arguments for UNLOAD command out of range");
		return;
	}

	shared_ptr<Freighter_Ship> ship=make_shared<Freighter_Ship>();
	list<shared_ptr<Basic_Ship>>::iterator it_ship;
	for(it_ship =listShips.begin(); it_ship != listShips.end(); ++it_ship){
		if((*it_ship)->getName()==nameShip)
		{
			ship= std::dynamic_pointer_cast<Freighter_Ship>(*it_ship);
			ship->unloading(contianer);
		}
	}
}

void Model::load_at(string nameShip,string portName)
{
	int xCor=-1,yCor=-1;
	list<shared_ptr<Port>>::iterator it;
	for(it =listPort.begin(); it != listPort.end(); ++it)
	{
		if((*it)->getName()==portName){
			xCor=(*it)->get_x();
			yCor=(*it)->get_y();
		}
	}
	if(xCor==-1 && yCor==-1)
	{
		throw InvalidModelInput("invalid arguments for LOAD ");
		return;
	}
	Point portP(xCor,yCor);
	Point shipP=get_ship(nameShip)->get_current();
	double dist = distanceCalculate(portP.get_x(),portP.get_y(), shipP.get_x(), shipP.get_y());
	if(dist > MaxDockingRange) {
		throw InvalidModelInput("invalid arguments for LOAD command out of range");
		return;
	}

	shared_ptr<Freighter_Ship> ship=make_shared<Freighter_Ship>();
	list<shared_ptr<Basic_Ship>>::iterator it_ship;
	for(it_ship =listShips.begin(); it_ship != listShips.end(); ++it_ship){
		if((*it_ship)->getName()==nameShip)
		{
			ship= std::dynamic_pointer_cast<Freighter_Ship>(*it_ship);
			ship->loading();
		}
	}
}

void Model::destination(string nameShip, string portName,double speed)
{
	int xCor=-1,yCor=-1;
	list<shared_ptr<Port>>::iterator it;
	for(it =listPort.begin(); it != listPort.end(); ++it)
	{
		if((*it)->getName()==portName){
			xCor=(*it)->get_x();
			yCor=(*it)->get_y();
		}
	}
	if(xCor==-1 && yCor==-1)
	{
		throw InvalidModelInput("invalid arguments for DESTINATION ");
		return;
	}
	Point point(xCor,yCor);

	list<shared_ptr<Basic_Ship>>::iterator it_ship;
	for(it_ship =listShips.begin(); it_ship != listShips.end(); ++it_ship){
		if((*it_ship)->getName()==nameShip)
			(*it_ship)->destination(point,speed,portName);
	}
}

shared_ptr<Basic_Ship> Model::get_ship(string shipName){

	list<shared_ptr<Basic_Ship>>::iterator it;
	for(it =listShips.begin(); it != listShips.end(); ++it){
		if((*it)->getName()==shipName)
			return(*it);
	}
	return nullptr;
}

bool Model:: is_number(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    if(it==s.end())
      return true;
    return !s.empty() && it == s.end();
}

bool Model:: is_valid_coordinates(string coords){

	int dotFlag=0;
	bool commaFlag=false;
 
	for(unsigned int i=0;i<coords.length();i++){

		if(i==0){
			if(coords[i]!='(')
				return false;
		}
		else{
			if(i==coords.length()-1 ){
				if(coords[i]!=')')
					return false;
			}
			else{
				if(!isdigit(coords[i])){
					if(coords[i]=='.')
					{
						dotFlag++;
						if((dotFlag> 1 && commaFlag==false) || dotFlag>2)
              return false;
					}else{
						if(coords[i]==',')
						{
							if(commaFlag==true){
								return false;
							commaFlag=true;
						}
						else{
              printf("err I=%d",i);
							return false;
						}
					}
				}
			}
		}
	}
	return true;
 }
}

bool Model:: check_name(string name){

	if(name.length() > 12)
		return false;
int i=0;
 while (name[i])
  {
    if (!isalpha(name[i])) 
      return false;
      i++;
  }
  return true;
}

bool Model:: port_is_exist(string p){

	list<shared_ptr<Port>>::iterator it;
	for(it =listPort.begin(); it != listPort.end(); ++it){
		if((*it)->getName()==p)
			return false;
	}
	return true;
}

void Model:: Control_unit_commands(string command, string input)throw(InvalidModelInput){

	istringstream in(input);
	in>>command;

	if(command=="go"){

		if(in.rdbuf()->in_avail()!=0){
			throw InvalidModelInput("invalid number of arguments");
		}
		set_time(++time);
		update_ports_and_ships();
	}

	if(command=="status"){
		if(in.rdbuf()->in_avail()!=0){
			throw InvalidModelInput("invalid number of arguments");
		}
		show_status();
	}

	if(command=="create"){
		if(in.rdbuf()->in_avail()==0){
			throw InvalidModelInput("invalid number of arguments");
		}
		try{
			create_ship(in);
		}
		catch(InvalidModelInput &in){
			throw(in);
		}
	}

}

void Model:: show_status(){

	list<shared_ptr<Port>>::iterator it;
	for(it =listPort.begin(); it != listPort.end(); ++it){
		(*it)->show_status();
	}

	list<shared_ptr<Basic_Ship>>::iterator it2;
	for(it2 =listShips.begin(); it2 != listShips.end(); ++it2){
		(*it2)->show_status();
	}
}

void Model::create_ship(istringstream &in)throw(InvalidModelInput){

	string ship_name,shipKind,coordinatesX,coordinatesY;
	Basic_Ship::ShipKind shipk;//bug
	in>>ship_name;

	if(!check_if_exist_ship(ship_name)||in.rdbuf()->in_avail()==0 ){ //ok
		throw InvalidModelInput("invalid input");
	}

	if(!check_name(ship_name)){  //ok
		throw InvalidModelInput("invalid ship name");
	}

	in>>shipKind;
	int kind=check_if_legal_ship_kind(shipKind);
	if(kind==-1||in.rdbuf()->in_avail()==0 ){  //ok
		throw InvalidModelInput("invalid ship kind");
	}

	switch(kind)
	{
	case 1:{
		shipk=Basic_Ship::ShipKind::Patrol; //Patrol boat
		in>>coordinatesX>>coordinatesY;
		string temp(coordinatesX+coordinatesY);
		if(!is_valid_coordinates(temp)){//BUG
			throw InvalidModelInput("invalid input");
		}
		double x=stod(fixString(coordinatesX));
		double y=stod(fixString(coordinatesY));
   
		add_to_list_Basic_Ship(makeShip(shipk,ship_name,x,y));
		shared_ptr<Patrol_ship> shipC=make_shared<Patrol_ship>();
		shipC= std::dynamic_pointer_cast<Patrol_ship>(get_ship(ship_name));//get_ship not found
   
		list<shared_ptr<Port>>::iterator it;
		for(it =listPort.begin(); it != listPort.end(); ++it){
			shipC->add_port((*it)->get_point(),(*it)->getName());//add implimntation to add_port
		}
   
		break;
	}
	case 2:{
		shipk=Basic_Ship::ShipKind::Pirate;
		in>>coordinatesX>>coordinatesY;
		string temp(coordinatesX);
		if(!is_valid_coordinates(temp)){//BUG
			throw InvalidModelInput("invalid input");
		}
		double x=stod(fixString(coordinatesX));
		double y=stod(fixString(coordinatesY));

		string force;
		if(in.rdbuf()->in_avail()==0 ){
			throw InvalidModelInput("insufficient arguments for Pirate ship ");
		}
		in>>force;

		if(!is_number(force))
			throw InvalidModelInput("invalid arguments for Pirate ship ");

		int forceP=stoi(force);
		add_to_list_Basic_Ship(makeShip(shipk,ship_name,x,y));
		set_forceP(ship_name,forceP);
   
		break;
	}

	case 3:{
		shipk=Basic_Ship::ShipKind::Freighter;
		in>>coordinatesX>>coordinatesY;
		string temp(coordinatesX+coordinatesY);
		if(!is_valid_coordinates(temp)){//BUG
			throw InvalidModelInput("invalid input");
		}
		double x=stod(fixString(coordinatesX));
		double y=stod(fixString(coordinatesY));

		string container,resistence;
		if(in.rdbuf()->in_avail()==0 ){
			throw InvalidModelInput("insufficient arguments for Freighter ship ");
		}
		in>>container;
		if(in.rdbuf()->in_avail()==0 ){
			throw InvalidModelInput("insufficient arguments for Freighter ship ");
		}
		in>>resistence;
		if(!is_number(container)||!is_number(resistence))
			throw InvalidModelInput("invalid arguments for Freighter ship ");

		int containerF=stoi(container);
		int resistenceF=stoi(resistence);
		add_to_list_Basic_Ship(makeShip(shipk,ship_name,x,y));
		set_container_F(ship_name,containerF);
		set_resistence_F(ship_name,resistenceF);

		break;
	}
 }
}

void Model::set_resistence_F(string ship_name,double resistenceF)
{
	shared_ptr<Freighter_Ship> ship=make_shared<Freighter_Ship>();
	list<shared_ptr<Basic_Ship>>::iterator it_ship;
	for(it_ship =listShips.begin(); it_ship != listShips.end(); ++it_ship){
		if((*it_ship)->getName()==ship_name)
		{
			ship= std::dynamic_pointer_cast<Freighter_Ship>(*it_ship);
			ship->set_resistance(resistenceF);
		}
	}
}

void Model::set_container_F(string ship_name,int containerF)
{
	shared_ptr<Freighter_Ship> ship=make_shared<Freighter_Ship>();
	list<shared_ptr<Basic_Ship>>::iterator it_ship;
	for(it_ship =listShips.begin(); it_ship != listShips.end(); ++it_ship){
		if((*it_ship)->getName()==ship_name)
		{
			ship= std::dynamic_pointer_cast<Freighter_Ship>(*it_ship);
			ship->set_contianer(containerF);
		}
	}
}

string Model:: fixString(string s){

	string temp;
	for(unsigned int i=0;i<s.length();i++){
		if(isdigit(s[i]) || s[i]=='.')
			temp+=s[i];
	}
	return temp;
}

void Model::set_forceP(string ship_name,double forceP)
{
	shared_ptr<Pirate_ship> ship=make_shared<Pirate_ship>();
	list<shared_ptr<Basic_Ship>>::iterator it_ship;
	for(it_ship =listShips.begin(); it_ship != listShips.end(); ++it_ship){
		if((*it_ship)->getName()==ship_name)
		{
			ship= std::dynamic_pointer_cast<Pirate_ship>(*it_ship);
			ship->set_force(forceP);
		}
	}
}

int  Model:: check_if_legal_ship_kind(string k){

	if(k=="Freighter")
		return 3;
 	if(k=="Cruiser")
		return 2;
 	if(k== "Patrol_boat")
		return 1;
	return -1;
}

bool Model:: check_if_exist_ship(string s){

	list<shared_ptr<Basic_Ship>>::iterator it;
	for(it =listShips.begin(); it != listShips.end(); ++it){
		if((*it)->getName()==s)
			return false;
	}
	return true;
}


void Model:: update_ports_and_ships(){

	list<shared_ptr<Port>>::iterator it;
	for(it =listPort.begin(); it != listPort.end(); ++it){
		(*it)->update();
	}
	list<shared_ptr<Basic_Ship>>::iterator it2;
	for(it2 =listShips.begin(); it2 != listShips.end(); ++it2){
		(*it2)->update();
	}
}

shared_ptr<Basic_Ship> Model::makeShip(Basic_Ship::ShipKind shipk,string shipName,double xCor,double yCor)
{
	switch(shipk)
	{
	case Basic_Ship::ShipKind::Patrol:{
		shared_ptr<Basic_Ship> a(new Patrol_ship(shipName,xCor,yCor));
		return a;
		break;
	}
	case Basic_Ship::ShipKind::Pirate:{
		shared_ptr<Basic_Ship> b(new Pirate_ship(shipName,xCor,yCor));
		return b;
		break;
	}

	case Basic_Ship::ShipKind::Freighter:{
		shared_ptr<Basic_Ship> c(new Freighter_Ship(shipName,xCor, yCor));
		return c;
		break;
	}
	}
	return nullptr;
}