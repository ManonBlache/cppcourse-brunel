# cppcourse-brunel
Project SV : NeuronProject

# 1. INTRODUCTION :

In this GitHub repository are all the files needed to run the NeuronProject on your computer. 
The aim of this project is to simulate the reccurent spiking network, described in Nicolas Brunnel's paper : "Dynamics of sparsley connected networks of excitatory and inhibitory spiking neurons".

# 2. DESCRIPTION OF THE PROJECT :

First, we created only one neuron and implemented his "vital functions" : how is evolving its potential membrane, when does it spike..
Then we simulated the interaction between two neurons and thus implemented some interaction functions, taking in account the delay of each neuron interaction.
Finally, we moved to the 12500 neurons simulation, with 10% interconnection and some Poisson's background noise.

# 3. HOW TO RUN THE MAIN PROGRAM :

You need to download the github files, and create a build folder at the same time.
Then go to the terminal, in your build folder and write:

```
cmake ..

```
