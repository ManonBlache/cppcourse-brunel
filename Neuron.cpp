#include "Neuron.h"
#include <cmath>
#include <random>

//Constructeur et constructeur de copie
	Neuron::Neuron(double J)
	//!<The default constructor initializes all the parameters used by default.
	:membrane_pot_(0),
	 num_spikes_(0),
	 tau_(20), //!<membrane time constant
	 tau_ref_(2),
	 membrane_resistance_(20),//!<membrane resistance
	 threshold_(20), //!<spike threshold
	 life_time_(0),
	 h_(0.1), //!<integration time step
	 ref_(0),
	 Iext_(1.01), //est ce qu'on voudrait pas avoir un constructeur qui cree les neurones inhibiteurs et excitateurs?
	 J_(J),//!<PSP (spike response) amplitude for excitatory connection
	 D_(1.5), //!<Synaptic delay
	 buffer_((D_/h_)+1, 0),
	 targets_(0,0)
	 {}

	Neuron::Neuron(double J,double const& birth) 
	//!< This constructor allows the user to run the simulation from a t_start!=0
	: membrane_pot_(0),
	 num_spikes_(0),
	 tau_(20), //!<membrane time constant
	 tau_ref_(2),
	 membrane_resistance_(20),//!<membrane resistance
	 threshold_(20), //!<spike threshold
	 life_time_(birth),
	 h_(0.1), //!<integration time step
	 ref_(0),
	 Iext_(1.01),
	 J_(0.1),//!<PSP (spike response) amplitude 
	 D_(1.5), //!<Synaptic delay
	 buffer_((D_/h_)+1, 0),
	 targets_(0,0)
	{} 

	
	Neuron::~Neuron (){}
	
//Getters and setters
	double Neuron::getMembranePot () const { return membrane_pot_; }
    unsigned int Neuron::getSpikes () const { return num_spikes_; }
    bool Neuron::getIfSpike() const {return spike_;}
    double Neuron::getLifeTime() const {return life_time_*h_;}
    double Neuron::getH() const {return h_;}
    double Neuron::getD() const {return D_;}
    double Neuron::getJ() const {return J_;}
    vector<int> Neuron::getTargets() const {return targets_;}
    
    void Neuron::setLifeTime(int time) {life_time_=life_time_+time;}
    void Neuron::setH(double h) {h_=h;}
    void Neuron::setJ(double j) {J_=j;}
    void Neuron::setIext(double I) {Iext_=I;}

//Method that updates the neuron state from time t+T, where T=n*h
bool Neuron::Update (double const& Iext, bool poisson)
{
	/** Before everything else, we have to initialize the boolean attribute
	 * spikes_ which keep in memory if there was a spike during last update
	 **/
	spike_ =false;
	
	/** We have now to check if the neuron is refractory.
	 * 	-->If it is (ref_>0), then the membrane potential stays at 0 and 
	 * the neuron doesnt interact with others.
	 * We have to make sure that even if the neuron doesnt interact, 
	 * his buffer is cleared (imput is lost), or the imput will be 
	 * reported later in time.
	 * -->If not, then we have to update the membrane potential and check
	 * the spike condition.
	 **/
	if (ref_>0){
		/**We clear the neuron buffer to make sure the imput during 
		 * refratory time is lost.
		 **/
		clearBuffer((life_time_+1)%buffer_.size()); 
		/**ref_ counts the remaining steps until neuron is no more 
		 * refractory, so ref_-=1
		 **/
		ref_ -=1;
		
	} else {
	
	/**The following 'if' allows us to run the test/simulation with(bool=true) or 
	 * without (bool=false) Poisson's background noise
	 * 
	 * For both cases, the membrane potential at time t is given by the 
	 * formula given in the course slides + what is in the buffer at time t.
	**/
	if (poisson){ 
		membrane_pot_= getBuffer(life_time_+1) 
		/**We have to add+1 because neuron clock is not yet incremented**/
						+(exp(-h_/tau_)*membrane_pot_) 
						+( Iext*membrane_resistance_*(1-exp(-h_/tau_)) ) 
						/**Here we're in the Poisson'case, so have to
						 * take in acount the amplitude delivered by the 
						 * spiking neurons of the rest of the brain.
						 * -->add 0.1*Poisson_noise()
						 **/
						+0.1*Poisson_noise(); //does the poisson spikes have 0.1(excitatory) or 0.5(inhibatory) J value?
	//cout << membrane_pot_ << "/";
	//if(getBuffer(life_time_+1)!=0){cout<<" buffer "<< getBuffer(life_time_+1)<<" at time "<<life_time_+1<<endl;}
	} else {
		
		
		membrane_pot_= getBuffer(life_time_+1) 
		/**We have to add+1 because neuron clock is not yet incremented**/
						+(exp(-h_/tau_)*membrane_pot_) 
						+( Iext*membrane_resistance_*(1-exp(-h_/tau_)));
	if(getBuffer(life_time_+1)!=0){cout<<" buffer "<< getBuffer(life_time_+1)<<" at time "<<life_time_+1<<endl;}
	}
		/**We make sure that buffer is cleared**/
		clearBuffer((life_time_+1)%buffer_.size());
		
	}
	
	/**We just updated the membrane potential.
	 * Now we have to check the thresolhd condition
	 **/
	if (membrane_pot_>=threshold_) {
		/**Condition is satisfayed so there was a spike
		 * -->initialize ref_ as the number of refractory steps
		 * -->set the membrane potential to 0
		 * -->add a spike in the neuron global spikes count
		 * -->set the boolean=true=the neuron spiked during this update
		 **/
		ref_= tau_ref_/h_;
		membrane_pot_=0;
		num_spikes_+=1;
		spike_=true;
		}
		
		/**Increment the neuron clock**/
		life_time_+=1;
		
	/**Return the spike information**/
	return spike_;
}


void Neuron::ImplementBuffer(double j, int time) {
	/**Increment the buffer with the amplitude J transmitted, 
	 * at the t time the neuron receives it (after delay)
	 **/
	
	size_t position = (time+15)%buffer_.size();
	buffer_[position]+=j;
}

double Neuron::getBuffer(int time) {
	/** Return what is in the buffer at a certain possition**/
	size_t position = (time)%buffer_.size();
	return buffer_[position];
}

void Neuron::clearBuffer(size_t position){
	/**clear the buffer after use**/
	buffer_[position]=0;
	}

double Neuron::Poisson_noise(){
	/**Generate a number of spikes comming from the rest of the brain, 
	 *for each update, and return it
	 **/
	random_device rd;
	mt19937 gen(rd());
	poisson_distribution<> d(2);

	return d(gen);
}

void Neuron::setConnections(int target){
	targets_.push_back(target);
	/**The excitatory and inhibitatory neurons are ordoned in the 
	 * neurons_ list, so with their numbers, we know if the connection
	 * is exct or inhb.
	 * Same for the targets_ list.
	 **/
}
