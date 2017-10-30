#include <fstream>
#include <vector>
#include "Neuron.cpp"

double insertCurrent ();  
double insertTimeBirth (); 
double insertTimeStep ();
double insertTimeDeath (double tstart);
bool makeAWish();  


int main () {
	double clock_=0;
	
	///Value used by default if the user doesnt want to change it
	double t_stop (1000);


	
	Neuron FirstNeuron;
	Neuron SecondNeuron;

	
	if (makeAWish()) { ///The user decide to change or not the values
		double I (insertCurrent());
		double Step (insertTimeStep());
		double start(insertTimeBirth());
		
		FirstNeuron.setIext(I);
		SecondNeuron.setIext(I);
		FirstNeuron.setH(Step);
		SecondNeuron.setH(Step);
		FirstNeuron.setLifeTime(start);
		SecondNeuron.setLifeTime(start);
		
		t_stop = insertTimeDeath(FirstNeuron.getLifeTime());
	} 
		
	
	//OUVERTURE FICHIER ICI
	string nom_fichier ("data.txt");
	ofstream sortie (nom_fichier.c_str());
	
	
	if (sortie.fail()) {
		cerr << "Erreur d'ouverture du fichier,"
			 << "impossible d'écrire dans le fichier " << nom_fichier << endl;
			 } 
		else {
				while (clock_<t_stop) {
					clock_+= 0.1;
					
				
					
					if (FirstNeuron.Update()){
						//ECRITURE FICHIER ICI
						sortie << "Spike neuron 1 number " << FirstNeuron.getSpikes() << " at time = " << FirstNeuron.getLifeTime() << " (Potential value = " << FirstNeuron.getMembranePot() << ")"<< endl;
						   
					}
					if (SecondNeuron.Update()){
						//ECRITURE FICHIER ICI
						sortie << "Spike neuron 2 number " << SecondNeuron.getSpikes() << " at time = " << SecondNeuron.getLifeTime() << " (Potential value = " << FirstNeuron.getMembranePot() << ")"<< endl;
						   
					}
					FirstNeuron.Interact(SecondNeuron);
					SecondNeuron.Interact(FirstNeuron);
				}
				//sortie << "--> Number of Spikes: " << FirstNeuron.getSpikes() << endl;
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






