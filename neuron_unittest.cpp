#include <iostream>
#include <cmath>
#include "Network.h"
#include "gtest/gtest.h"

TEST (NeuronTest, MembranePotential){
	Neuron neuron(0.1);
	//!< Here we want to test without Poisson's background noise,
	//!<so we test with updtate(iext, poisson=false)

	//First Update
	neuron.Update(1.0,false);
	EXPECT_EQ(20.0*(1.0-exp(-0.1/20.0)), neuron.getMembranePot());
	
	//Test after numerous updates
	for ( int i(0); i<10000; ++i) {neuron.Update(1.0,false);}
	///The membrane potential should tend to 20 but never reach the 
	///threshold, thus the neuron will never spike
	EXPECT_EQ(0, neuron.getSpikes());
	EXPECT_NEAR(20, neuron.getMembranePot(), 1e-3);

	//After numerous updates w/o imput current
	///The membrane should tend naturally towards 0 
	///Should be enough to wait 10*tau_ ms
	for (int i(0); i<2000 ; ++i) {neuron.Update(0.0,false);}
	EXPECT_NEAR(0, neuron.getMembranePot(), 1e-3);
	
}

TEST (NeuronTest, SpikeTime){
	Neuron neuron(0.1);
	
	//With an imput current of 1.01, we know that the spikes should occur
	//at 92.4 ms , 186,8 ms , 281,2 ms and 375,6 ms.
	
	///Jump to the step just before first spike
	///Number of spikes should be 0
	for (int i (1); i<924; ++i) {neuron.Update(1.01,false);}
	EXPECT_EQ(0, neuron.getSpikes());
	///Update to first spike
	///Number of spike should be 1
	neuron.Update(1.01,false);
	EXPECT_EQ(1, neuron.getSpikes());
	///Check if the membrane potential is reset to 0 after spike
	EXPECT_EQ(0.0, neuron.getMembranePot());

	///Jumping to second spike
	for (int i(0); i<943 ;++i ){neuron.Update(1.01,false);}
	EXPECT_EQ(1, neuron.getSpikes());
	neuron.Update(1.01,false);
	EXPECT_EQ(2, neuron.getSpikes());
	
	//We assume that if the first 2 spikes are corrects, the others too
}

TEST(NeuronTest, PoissonNoise){
	Neuron neuron(0.1);
	EXPECT_EQ(0.0, neuron.getMembranePot());
	neuron.Update(0.0,true);
	EXPECT_FALSE(neuron.getMembranePot()==0.0);
}

TEST (TwoNeurons, TransmitionAndDelay){
	Neuron n1(0.1); //!<Will send spike to n2, Iext=1.01
	Neuron n2(0.1); //!<Will receive only imput from n1, Iext=0
	int global_clock =0;
	
	/*At time 92.4, n1 is supposed to spike,
	 * then it should implement n2's buffer for time 92.4+1.5(delay)=939*/
	///Jump to the step just before first spike
	while (global_clock<923) {
		n1.Update(1.01,false);
		n2.Update(0,false);
		++global_clock;
	}
	EXPECT_EQ(0, n1.getSpikes());
	EXPECT_EQ(0,n2.getMembranePot());
	
	///Update to first spike
	n1.Update(1.01,false);
	EXPECT_EQ(1, n1.getSpikes());
	n2.Update(0,false);
	EXPECT_EQ(0, n2.getSpikes());
	EXPECT_EQ(0,n2.getMembranePot());
	++global_clock;
	
	/**Check if all the clocks are equal**/
	EXPECT_EQ(924,global_clock);
	EXPECT_EQ(924,n1.getLifeTime()/0.1);
	EXPECT_EQ(924,n2.getLifeTime()/0.1);
	
	/**Check if the buffer is well implemented**/
	n2.ImplementBuffer(n1.getJ(),global_clock);
	EXPECT_EQ(0.1, n2.getBuffer((n2.getLifeTime()/0.1)+15));
	
	///Update to step before input is transmitted
	while (global_clock <938) {
		n1.Update(1.01,false);
		n2.Update(0.0,false);
		++global_clock;
		}
	EXPECT_EQ(1, n1.getSpikes());
	EXPECT_EQ(0, n2.getSpikes());
	EXPECT_EQ(0,n2.getMembranePot());
	
	EXPECT_EQ(938,global_clock);
	EXPECT_NEAR(938, n1.getLifeTime()/0.1, 1e-3);
	EXPECT_NEAR(938, n2.getLifeTime()/0.1, 1e-3);
	
	n1.Update(1.01,false);
	n2.Update(0.0,false);
	++global_clock;
	
	EXPECT_EQ(0.1,n2.getMembranePot());
	
}

TEST(TwoNeurons, CleanedBuffer){
	Neuron n1(0.1); //!<Will send spike to n2, Iext=1.01
	Neuron n2(0.1); //!<Will receive only imput from n1, Iext=0
	int global_clock =0;
	
	/*At time 92.4, n1 is supposed to spike,
	 * then it should implement n2's buffer for time 92.4+1.5(delay)=939*/
	///Jump to the step just before first spike
	while (global_clock<924) {
		n1.Update(1.01,false);
		n2.Update(0,false);
		++global_clock;
		EXPECT_EQ(0.0, n1.getBuffer(n2.getLifeTime()/0.1));
		EXPECT_EQ(0.0, n2.getBuffer(n2.getLifeTime()/0.1));
	}

	
	/**Check if the buffer is well implemented**/
	n2.ImplementBuffer(n1.getJ(),global_clock);
	EXPECT_EQ(0.1, n2.getBuffer(((n2.getLifeTime()/0.1)+15)));
	
	///Update to step before input is transmitted
	while (global_clock <938) {
		n1.Update(1.01,false);
		n2.Update(0.0,false);
		++global_clock;
		EXPECT_EQ(0.0, n1.getBuffer(n2.getLifeTime()/0.1));
		EXPECT_EQ(0.0, n2.getBuffer(n2.getLifeTime()/0.1));
		}
	
	///At this step, the imput is integrated in membrane potential
	EXPECT_EQ(0.1, n2.getBuffer((n2.getLifeTime()/0.1)+1));
	n1.Update(1.01,false);
	n2.Update(0.0,false);
	++global_clock;
	
	EXPECT_EQ(0.1,n2.getMembranePot());
	EXPECT_EQ(0.0, n1.getBuffer(n2.getLifeTime()/0.1));
	EXPECT_EQ(0.0, n2.getBuffer(n2.getLifeTime()/0.1));
	
}

TEST(TwoNeurons, Spiking){
	Neuron n1(0.1); //!<Will send spike to n2, Iext=1.01
	Neuron n2(0.1); //!<Will receive only imput from n1, Iext=0
	int global_clock =0;
	
	n1.setJ(19.999); /*We want n2 spiking after 2 spikes of n1*/
	
	///Jump to the step just before second spike
	while (global_clock<1867) {
		if (n1.Update(1.01,false)){
			n2.ImplementBuffer(n1.getJ(),global_clock);
			EXPECT_EQ(19.999, n2.getBuffer(((n2.getLifeTime()/0.1)+15)));
			};
		n2.Update(0,false);
		++global_clock;
	}
	EXPECT_EQ(1, n1.getSpikes());
	EXPECT_EQ(0, n2.getSpikes());
	
	///Update to second spike
	n1.Update(1.01,false);
	EXPECT_EQ(2, n1.getSpikes());
	n2.Update(0,false);
	EXPECT_EQ(0, n2.getSpikes());
	++global_clock;
	
	EXPECT_EQ(1868,global_clock);
	EXPECT_NEAR(1868, n1.getLifeTime()/0.1, 1e-3);
	EXPECT_NEAR(1868, n2.getLifeTime()/0.1, 1e-3);
	
	/**Check if the buffer is well implemented**/
	n2.ImplementBuffer(n1.getJ(),global_clock);
	EXPECT_EQ(19.999, n2.getBuffer(((n2.getLifeTime()/0.1)+15)));
	
	///Update to step before input is transmitted
	while (global_clock <1882) {

		n1.Update(1.01,false);
		n2.Update(0.0,false);
		++global_clock;
		}
	EXPECT_EQ(2, n1.getSpikes());
	EXPECT_EQ(0, n2.getSpikes());

	
	n1.Update(1.01,false);
	n2.Update(0.0,false);
	++global_clock;
	EXPECT_EQ(1, n2.getSpikes());
	EXPECT_EQ(0,n2.getMembranePot());
	
}
