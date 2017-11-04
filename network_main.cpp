#include <iostream>
#include <cmath>
#include "Network.h"

int main(){
	
	Network Brain;
	int simulation_clock (0);
	int t_stop(1000);

	
	while(simulation_clock<t_stop){
		Brain.update(true);
		++simulation_clock;
		}
	

	
	
	
	
	
	cout <<"done" <<endl;
	
return 0;	
}
