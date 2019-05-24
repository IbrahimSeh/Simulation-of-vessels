/*
 *  Tel Hai College
 *
 *  @Date: 	17 June 2018
 *  @Author:   	Ibrahim Seh & noor bakriya
 *  @Id:	316237031 & 318586302
 *  @email:	abrahem-seh@hotmail.com & noor.bakrieh@yahoo.com
 */

 #include "Controller.h"

int main (int argc , char **argv) {  
if(argc>2)
{
cout << "invalid number of argument " << endl;
exit(1);
}

Controller controller;
controller.set_up_objects(argv[1]);
controller.run();
return 0;
}