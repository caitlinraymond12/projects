Project Created: Fall 2024
Class: Algorithms 

This project allows a user to input any two places in contential united states, and it will return the shortest path between the two places, written directions, and it will graphically draw it out on a map. 


This program reads in three files, intersections.txt, connections.txt, and namedplaces.txt. 


intersections.txt
```
 -80.1415   26.7097    0.75 FL Plantation Mobile Home Park  
 -80.6534   26.8142    0.40 FL Fremd Village-Padgett Island  
 -80.2008   26.7109    1.63 FL Royal Palm Beach  
```

Each intersection has an intersection number (line it is in the file), longitude, latitude, distance to nearest named place, state of named place, name of named place. 


connections.txt
```
US-41/GA-3 T-- 22471 22060 18.225   
US-27/GA-1 P-- 22192 22486 17.849  
I-85/GA-403 L-- 22381 22294 7.206  
```

Each connection has the name of road, type of road, intersection A, intersection B, length(miles)


namedplaces.txt
```
62081025KSZurich                                               126      0.172221 39.232810 -99.43481416396  7.3237  
21987690IAZwingle                                              100      0.156037 42.297837 -90.687038 9097  5.7488  
62283685LAZwolle                                              1783      3.226466 31.635134 -93.64256026884  8.6067  
```

Each named place has a numeric code, state abbreviation, name (may contain spaces), population, area (square miles), latitude, longitude, intersection number of intersection closest to center, distance from center to intersection (miles)


There is also a states.txt file that contains the full names to every state abbreivation, allowing the program to convert from a given state abbreviation to the actual name of the state. 


All of the files connect to one another. Named places has the interesection that is closest to it. Intersections have the name of the nearest place and a vector of connection * that list all the connections this intersection is apart of. Connections have pointers to two intersections, the start and end intersection of this road and the length of it. 

Using all this, I was able to implement Dikstra's algorithm to be able to find the shortest path between any two places. While the program runs through all the possible paths, it also keeps track of the path taken to get to the current position, so it is easily able to backtrack through and print out the roads taken. Some connections might be the same road, yet my program recognizes that and will only print out the road once, keeping track of the total distance taken on it, rather than printing it out multiple times in a row and saying the distance for each. 

The last part of this project is the graphical representation. I am using the library given to us by my professor, "library.h", to be able to draw the map and the correct path ontop of it. 

There are many different maps that my program can choose for any path, and it chooses the smallest one that is able to show the entire path. All of the maps are binary files, so they must be read in using:

```
fstream map(path, ios::in | ios::binary);
```

Each map is read in one byte at a time, each byte being a short int that represents an elevation. That byte is assigned a color based on the elevation, and a pixel is drawn. The map is read in one byte at a time, and drawn one pixel at a time. After the map is drawn, the red line representing the path is drawn ontop of it.

The user is prompted to enter a starting city. Then, a list of all states containing a city by that name are listed, and the user must then select a state. The same process is used to select the end city/state.


.png files have been provided to show what the graphical output of this program is, and .txt files have been provided to show what the written output of this program is. 

