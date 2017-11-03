#include <iostream>
#include <cmath>
#include "Network.h"
#include "gtest/gtest.h"


TEST(NetworkTest, Creation){
	Network Brain;
	EXPECT_EQ(12500, Brain.getNeurons().size());
	
	for (auto& neuron : Brain.getNeurons()){
		EXPECT_EQ(1250, neuron->getTargets().size());
		EXPECT_EQ(0.0, neuron->getMembranePot());
		EXPECT_EQ(0,neuron->getLifeTime()/0.1);
		EXPECT_EQ(0,neuron->getSpikes());
		EXPECT_TRUE (0.1 == neuron->getJ() || -0.5 == neuron->getJ());
		}
	
} 

TEST(NetworkTest,Connections){
	
	Network Brain;
	int test_clock(0);
	
	///Jump to the step just before first spike, without poisson.
	while (test_clock<923) {
		Brain.update(false);
		++test_clock;
	}
	for (auto& neuron : Brain.getNeurons()){
		EXPECT_EQ(0,neuron->getSpikes());
		}
		
	Brain.update(false);
	for (auto& neuron : Brain.getNeurons()){
		EXPECT_EQ(1,neuron->getSpikes());
		EXPECT_EQ(0.0, neuron->getMembranePot());
		}
	
	while (test_clock <938) {
		Brain.update(false);
		++test_clock;
		}
	for (auto& neuron : Brain.getNeurons()){
		EXPECT_EQ(1,neuron->getSpikes());
		//EXPECT_EQ(-25, neuron->getBuffer(test_clock+1+15));
		}
	
	Brain.update(false);
	++test_clock;
	for (auto& neuron : Brain.getNeurons()){
		//EXPECT_EQ(2,neuron->getSpikes());
		//EXPECT_EQ(0.0, neuron->getMembranePot());
		}
	
	
	
}
