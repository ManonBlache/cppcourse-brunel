#include <fstream>
#include <vector>
#include "Neuron.h"

double insertCurrent ();  
double insertTimeBirth (); 
double insertTimeStep ();
double insertTimeDeath (double tstart);
bool makeAWish();  


int main () {
	int clock_=0;
	
	///Value used by default if the user doesnt want to change it
	int t_stop (1000);


	
	Neuron FirstNeuron;
	Neuron SecondNeuron;

	
	if (makeAWish()) { ///The user decide to change or not the values
		double I (insertCurrent());
		double Step (insertTimeStep());
		double start(insertTimeBirth());
		
		FirstNeuron.setIext(I);
		SecondNeuron.setIext(0);
		FirstNeuron.setH(Step);
		SecondNeuron.setH(Step);
		FirstNeuron.setLifeTime(start/Step);
		SecondNeuron.setLifeTime(start/Step);
		
		t_stop = insertTimeDeath(FirstNeuron.getLifeTime());
	} 
		
	
	//OUVERTURE FICHIER ICI
	string nom_fichier ("data_01.txt");
	ofstream sortie (nom_fichier.c_str());
	
	string nom_fichier_02 ("data_02.txt");
	ofstream sortie_02 (nom_fichier_02.c_str());
	
	
	if (sortie.fail() or sortie_02.fail()) {
		cerr << "Erreur d'ouverture du fichier,"
			 << "impossible d'écrire dans le fichier " << nom_fichier << endl;
			 } 
		else {
				while (clock_*0.1<t_stop) {
					
 					if (FirstNeuron.Update(1.01)){
						SecondNeuron.ImplementBuffer(FirstNeuron.getJ(),FirstNeuron.getD());
						
						//ECRITURE FICHIER ICI
						sortie << "Spike neuron 1 number " << FirstNeuron.getSpikes() 
							   << " at time = " << FirstNeuron.getLifeTime()
							   << " (Potential value = " << FirstNeuron.getMembranePot() << ")"<< endl;   
					}
					if (SecondNeuron.Update(0)){
						//ECRITURE FICHIER ICI
						sortie_02 << "Spike neuron 2 number " << SecondNeuron.getSpikes() 
							   << " at time = " << SecondNeuron.getLifeTime() 
							   << " (Potential value = " << FirstNeuron.getMembranePot() << ")"<< endl;   
					}
					
					
					clock_+=1;
				}

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
	/** In this function, the user choose to change the values for Iext, h, tstart and tstop
	 * @return : true if the user want to change values, false if not.
	 * **/
	char choix ('O');
	cout << "Voulez-vous choisir des valeurs pour Iext, t_start, t_stop et h?  (O/N) ";
		cin >> choix;
		if (choix == 'O') { return true;} else {return false;}
}







