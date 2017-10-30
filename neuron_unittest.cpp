#include <iostream>
#include <cmath>
#include "Neuron.h"
#include "gtest/gtest.h"

TEST (NeuronTest, MembranePotential){
	Neuron neuron;

	//First Update
	neuron.Update(1.0);
	EXPECT_EQ(20.0*(1.0-exp(-0.1/20.0)), neuron.getMembranePot());
	
	//Test after numerous updates
	for ( int i(0); i<10000; ++i) {neuron.Update(1.0);}
	///The membrane potential should tend to 20 but never reach the 
	///threshold, thus the neuron will never spike
	EXPECT_EQ(0, neuron.getSpikes());
	EXPECT_NEAR(20, neuron.getMembranePot(), 1e-3);

	//After numerous updates w/o imput current
	///The membrane should tend naturally towards 0 
	///Should be enough to wait 10*tau_ ms
	for (int i(0); i<2000 ; ++i) {neuron.Update(0.0);}
	EXPECT_NEAR(0, neuron.getMembranePot(), 1e-3);
	
}

TEST (NeuronTest, SpikeTime){
	Neuron neuron;
	
	//With an imput current of 1.01, we know that the spikes should occur
	//at 92.4 ms , 186,8 ms , 281,2 ms and 375,6 ms.
	
	///Jump to the step just before first spike
	///Number of spikes should be 0
	for (int i (1); i<924; ++i) {neuron.Update(1.01);}
	EXPECT_EQ(0, neuron.getSpikes());
	///Update to first spike
	///Number of spike should be 1
	neuron.Update(1.01);
	EXPECT_EQ(1, neuron.getSpikes());
	///Check if the membrane potential is reset to 0 after spike
	EXPECT_EQ(0.0, neuron.getMembranePot());

	///Jumping to second spike
	for (int i(0); i<943 ;++i ){neuron.Update(1.01);}
	EXPECT_EQ(1, neuron.getSpikes());
	neuron.Update(1.01);
	EXPECT_EQ(2, neuron.getSpikes());
	
	//We assume that if the first 2 spikes are corrects, the others too
}

