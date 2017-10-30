//#include "Neuron.h"
#include <fstream>
#include "Neuron.cpp"

double insertCurrent ();  
double insertTimeBirth (); 
double insertTimeStep ();
double insertTimeDeath (double tstart);
bool makeAWish();  

int main () {
	
	///Value used by default if the user doesnt want to change it
	double t_stop (1000);
	
	Neuron FirstNeuron;
	
	if (makeAWish()) { ///The user decide to change or not the values
		FirstNeuron.setIext(insertCurrent());
		FirstNeuron.setH(insertTimeStep ());
		FirstNeuron.setLifeTime(insertTimeBirth());
		t_stop = insertTimeDeath(insertTimeBirth());
	} 
		
	
	//OUVERTURE FICHIER ICI
	string nom_fichier ("data.txt");
	ofstream sortie (nom_fichier.c_str());
	
	
	if (sortie.fail()) {
		cerr << "Erreur d'ouverture du fichier,"
			 << "impossible d'écrire dans le fichier " << nom_fichier << endl;
			 } 
		else {
				while (FirstNeuron.getLifeTime()<t_stop) {
					if (FirstNeuron.Update()){
						//ECRITURE FICHIER ICI
						sortie << "Spike number " << FirstNeuron.getSpikes() << " at time = " << FirstNeuron.getLifeTime() << " (Potential value = " << FirstNeuron.getMembranePot() << ")"<< endl;
						     
					}
				}
				sortie << "--> Number of Spikes: " << FirstNeuron.getSpikes() << endl;
		}
	
	//FERMETURE FICHIER ICI
	sortie.close ();
	
	
	return 0;
}

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
	/** In this function, the user choose to change the values for Iext and h or not
	 * **/
	char choix ('O');
	cout << "Voulez-vous choisir des valeurs pour Iext, t_start, t_stop et h?  (O/N) ";
		cin >> choix;
		if (choix == 'O') { return true;} else {return false;}
}





