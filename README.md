# cppcourse-brunel #
Project SV : NeuronProject

### 1. INTRODUCTION : ###

In this GitHub repository are all the files needed to run the NeuronProject on your computer. 
The aim of this project is to simulate the reccurent spiking network, described in Nicolas Brunnel's paper : "Dynamics of sparsley connected networks of excitatory and inhibitory spiking neurons".

### 2. DESCRIPTION OF THE PROJECT : ###

First, we created only one neuron and implemented his "vital functions" : how is evolving its potential membrane, when does it spike..
Then we simulated the interaction between two neurons and thus implemented some interaction functions, taking in account the delay of each neuron interaction.
Finally, we moved to the 12500 neurons simulation, with 10% interconnection and some Poisson's background noise.

### 3. HOW TO RUN THE MAIN PROGRAM : ###
 
You need to download the github files, and create a build folder at the same time.
Then go to the terminal, in your build folder and write:

```
cmake ..
make
./network_main
```

***What does ./network_main ? :***
This network_main.cpp is writen to simulate the network model with 12500 neurons, during 1000 steps (=100ms).
It write down in a text file (data_network.gdf) the time and the ID of each neuron that is spiking at time t.
***Change the initial conditions :***
The program is set to simulate the Brunnel's C plot : g=5 and vext/vthr=2.
If you want to change this values, you need to modify the Network.h file as below:


```
TO WRITEEEEE!!!!
```

If you need to change the title of the file you are writing in (to not overwrite in your previous results) you need to go into the Network.cpp file and make a change as below:

```
TO WRITEEEEE!!!!
```


### 4. HOW TO PLOT THE RESULTS ###
Here I will explain how to transform the data.gdf file into the "Brunnel's plot"


### 5. HOW TO RUN THE GOOGLE TESTS ###
There are two test files in the github repository: one is testing in details the Neuron Class and its methods (neuron_unittest), the other tests the Network Class (network_unittest).
If you want to run these tests, you need to do, in your build folder

```
cmake ..
make
./neuron_unittest 
```
or 
```
cmake ..
make
./network_unittest 
```
depending on what you want to test.

***More about the network tests***
As the random generation of numbers takes an important role in the network simulation, i did not know how to write more tests, because all the spiking values depend on the backgroung noise. So I tested that my 12500 neurons network was well created at the beginning of the simulation. (i.e. Verify that I have the right number of neurons and connections between them)



