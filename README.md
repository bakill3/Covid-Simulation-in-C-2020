# Simulation of Vı́rus Propagation
## 1. Introduction
It is intended to implement a program that simulates, in a simplified way, the spread of a virus among a population. The individuals of the population are in a space made up of places, interconnected with each other. The implementation of the programme consists of 2 sequential phases:
- **Preparation**: At the beginning of the execution, the application loads all the necessary data from files: Space configuration and size and characteristics of the initial population.
- **Simulation**: When the preparation phase ends, an iterative simulation process begins that represents the spread of the virus over time (1 iteration at a time, each of these iterations corresponding to 1 day). At the end of the simulation, the program presents a summary of the results and records relevant information in files.

## 2.	Space
The space in which the simulation takes place consists of a set of interconnected places, for example, several rooms of the same building.

It consists of 4 sites, and there are some bidirectional connections between them. Each site has   a positive (unique) numeric id, a maximum capacity, and some direct links to other locations. At most, each location can have 3 links.
The possible spaces to perform the simulation are stored in binary files (1 file per space). Each of these files contains several structures  of the local type, one for each of the locations in that space:
```C
typedef struct sala local, *plocal; room struct{
 int id;	Numeric location id int capacity; maximum capacity
 int league[3];	Binding ID (-1 in unused cases)
};
```

At the beginning of the execution, the user indicates the name of the file where the information of the space to be used is located. Before starting the simulation phase, this information is necessarily transferred to a **dynamic vector of structures**.
The program must validate the organization of the space: all locations must have  unique positive ids and the links must be correct (for example, if site A has a link to site B, then B must also link to A). If there is an error detected in the validation, an appropriate message should be displayed and the program ends without starting the simulation phase.
Along with the statement are available 3 binary files with possible spaces for simulation. They are only examples and during the defense other files may be used, as long as they follow the same organization indicated in this statement.

# 3.	People

There is an initial set of people that must be distributed to the places where the simulation will be performed. Each of the people in this initial set has the following characteristics:
-	Unique alphanumeric identifier (1 word)
-	Age
-	Status: can be **Healthy**, **Sick**, **Immune**
-	If you are sick, there is information on how many days ago you were infected

Text files store information about populations of people. Each text file must have the information stored in the format described below.
A line has all the information of a person, according to the following order: identifier, age, state (S, D or I). If the state is D, there is still an integer indicating how many days ago it was infected. The information on a line is separated by one or more blanks. The data on the various people appear in consecutive rows. 

During the preparation phase, the user indicates the name of the text file where the information of the people with whom the simulation will start is found. Each of these people should be placed in one of the existing locations. The selection of the location for each person must be made randomly, satisfying the capacity restriction. If there are more people than the total capacity of space, some of these people do not participate in the simulation.
During execution, information about the people who are participating in the simulation is stored in **dynamic structures of the linked list type**. It is at the discretion of the student to choose the best organization for the dynamic structures, subject only to the constraints of the statement.
The program must validate the information read from the people file. If it is in an invalid format, an appropriate message should be displayed and the program ends without starting the simulation phase.
Along with the statement are available 2 text files with possible populations for simulation.

# 4.	Virus Spread Model Configuration

In order for the virus spread model to be simulated over time (details are given in section 5), some parameters need to be defined. This template has the following parameters, whose values are fixed:
 - *Spread rate*: Number of people a patient infects in each iteration of the simulation. In this model, the value corresponds to 5% of the number of people who are in the same place (value rounded down). For example, in a room with 75 people, one patient transmits the virus to 3 other people in each iteration of the simulation. The affected people are chosen at random, from among all those who are on site. It can happen that the virus is transmitted to another person who is already sick. In this case, the infection has no effect.
 - *Probability of recovery*: The probability that a patient has to recover in each iteration of the simulation. In this model, the probability is 1/age, that is, for a 50-year-old patient, the probability of recovering in each iteration is 1/50 = 0.02.
 - *Maximum duration of infection*: Number of days a person is sick. At the end of this period, anyone gets healthy again. In this model, the value is 5 + 1 day for every ten years of life (rounded down). For example, an infected person who is 45 years old is cured after 9 days.
 - *Immunity rate*: When an infected person is cured (by recovery or by having exceeded the maximum duration of infection), there is a likelihood that they will stay immune to disease. If this happens, even if you become infected again in the future, you do not contract the disease again. In this model, the immunity rate is 20%.

# 5.	Simulation of the Virus Propagation Model

The simulation phase begins after finishing reading information from the space and the group of people to consider. The simulation takes place over several successive iterations, each corresponding to a day. During the simulation phase, the application must provide a menu with at least the following options:

 - **Advance 1 iteration in the simulation**: the application applies the propagation model to the population and updates the state of the people.
 - **Present statistics**:  the application presents statistical data of the current state of the simulation. Among other results, it should show: distribution of people by room, rate of healthy, rate of infected, rate of immune, ...
 - **Add sick**: 1 new sick person is added to a location. The user specifies the location id  and identifier, age, and number of days of infection of the new person.
 - **Transfer people**: N people are moved from one location to another within the space, as long as these locations have a direct connection. The ids of the source and destination locations and the value N are indicated by the user (for example, moving 3 people from location 1 to location 3). The program chooses N people randomly, from among those who are in the place of origin.
 - **End Simulation**: When you finish the simulation, the application generates a final report. It is up to the student to decide what information should be included, but it should be complete. This report is saved in a text file named report.txt. In addition, the existing population in the last iteration must be saved in a text file. The name of this file is provided by the user.







