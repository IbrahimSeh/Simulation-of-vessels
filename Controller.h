/* Controller
This class is responsible for controlling the Model and View according to interactions
with the user.
*/
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cctype>
#include "View.h"
#include <string>
class Controller {
public:	

	class InvalidFile{

	private:
		string fileName;
	public:
		InvalidFile(string fn):fileName(fn){}
		void print(){ cout << "invalid input in file " << fileName << endl;}
	};

	Controller();
	~Controller(){}
	void  set_up_objects(char * file)throw(InvalidFile);
	void run_commands();
	bool check_if_leggal_command(string c);
	int check_if_legal_ship_command(string c);
	bool check_if_view_command(string command);
	// creates View object, runs the program by accepting user commands, then destroys View object
	void run();
private:
	shared_ptr<View> view_ptr;
};