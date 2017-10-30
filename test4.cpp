#include <fstream>
#include <vector>
#include "Network.h"

double insertCurrent ();  
double insertTimeBirth (); 
double insertTimeStep ();
double insertTimeDeath (double tstart);
bool makeAWish();  


int main(){
	
	int clock_=0;
	int t_stop (1000);
	
	
	Network Brain;
	
	while (clock_<t_stop){
		Brain.update();
		++clock_;
	}
	
	
	
	
	
}


//______________________________________________________________________
//_________Functions to change the values for iext or time______________
//______________________________________________________________________

double insertCurrent () {
	/**This function allows the user to choose a specific value for the external current Iext
	 * **/
	double current;
	cout << "Specify an external current Iext [0;400] : ";
	cin >> current;
	if((current<0)or (current>400)) {
		cerr << "Wrong value, try again : ";
		cin >> current;
	}
	return current;
}
double insertTimeBirth () {
	/**This function allows the user to choose a specific value for the start time
	 * **/
	double start;
	cout << "Specify a start time: ";
	cin >> start;
	if(start<0) {
		cerr << "Wrong value, time must be positive or zero : ";
		cin >> start;
	}
	return start;
}
double insertTimeStep () {
	/**This function allows the user to choose a specific value for the time interval h
	 * **/
	double step;
	cout << "Specify a time interval: ";
	cin >> step;
	if(step<=0) {
		cerr << "Wrong value, step must be positive : ";
		cin >> step;
	}
	return step;
}
double insertTimeDeath (double tstart) {
	/**This function allows the user to choose a specific value for the stop time
	 * **/
	double stop;
	cout << "Specify a stop time: ";
	cin >> stop;
	if((stop<0) or (stop<=tstart)) {
		cerr << "Wrong value, tstop > tstart : ";
		cin >> stop;
		}
	return stop;
}

bool makeAWish() {
	/** In this function, the user choose to change the values for Iext, h, tstart and tstop
	 * @return : true if the user want to change values, false if not.
	 * **/
	char choix ('O');
	cout << "Voulez-vous choisir des valeurs pour Iext, t_start, t_stop et h?  (O/N) ";
		cin >> choix;
		if (choix == 'O') { return true;} else {return false;}
}








