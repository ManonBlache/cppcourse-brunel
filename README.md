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
23 const double g =/*your g constant*/;
...
30 const double eta_= /*your vext/vthr constant*/;
```

If you need to change the title of the file you are writing in (to not overwrite in your previous results) you need to go into the Network.cpp file and make a change as below:

```
11 	string nom_fichier ("new_name_of_your_file.gdf");
```


### 4. HOW TO PLOT THE RESULTS ###
Here I will explain how to transform the data.gdf file into the "Brunnel's plot".
--> You need to go to https://try.jupyter.org/ and download the output files (such as data_network_A/B/C/D.gdf)
Then you go to "new" and chose "python 3". In the box, you need to write :

```
import numpy as np
import matplotlib.pyplot as pl

data = np.genfromtxt('data_network_C.gdf')

select= np.array([d for d in data if d[1] < 80])
data1= select.transpose()
pl.scatter(0.1*data1[0],data1[1],alpha=0.8, edgecolors='none');
pl.show();

n, bins, patches = pl.hist(0.1*data1[0], 50, normed=0, alpha=0.75)
pl.show();

```
and then you can run the test, and it will give you the plots.


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

### 6. HOW TO GENERATE THE DOXYGEN DOCUMENTATION ###
Through the terminal, you need to go in your project file, where should be all the .h and .cpp files, plus the CMakeLists.txt, and then write

```
doxygen Doxyfile.in
cd buil
cmake ..
make
make doc
```

Now you can go to the html folder, which should contain an "annoted.html" document. You can click on it to generate a web page with all the doxygen documentation of my project.

### 7. ABOUT THE OTHER TEST.CPP FILES ###
You could have noticed some test.cpp (from 1 to 4) in my github repository. They are files that I used during the semester to run my program when it was not finished. 
They are all included in my CMakeLists, they have been modified to run with the last version of my classes, thus you can execute them by writing ./test1 or ./test3, etc...

#### Test1.cpp ###
Test1 creates only one neuron, and updates it while writing in a files the time and membrane potential when a spike is registered.
When executing Test1, you will be asked wether or not you want to modify the values for Iext, t_start and t_stop of the simulation, or even the time step h. If the values are not within the expected range, the program will tell you to enter a new number. If you do not want to change values, the parameters given in the Brunel's simulation will be applied by default.

#### Test2.cpp ####
Test2 is like Test1, but this time simulates two neurons and their interactions. Here again, you can change some values if you want to, and spiking results are writen in a file.
Both neurons have an imput current of 1.01 mV, that is to say that the simulation is symetrical : the two neurons are spiking a the same time during the whole simulation.

#### Test3.cpp ####
Test3 is some vartient of Test2. We still have two neurons, but this time neuron2 receive as only imput current what neuron1 send to him.

#### Test4.cpp ####
Test4 is the one simulating the whole network, composed of 12500 neurons interconnected to each other. 
(It does almost the same than network_main.cpp)


