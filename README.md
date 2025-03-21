# Shortest Path Finder

## Overview
This program implements a shortest path finder using  Dijkstra's Algorithm  and  Breadth-First Search (BFS)  to determine the shortest route between cities. The program reads city data from a file and constructs an adjacency matrix to represent the distances between cities.

## Features
- Loads cities and distances from a file ( cities.txt ).
- Constructs an adjacency matrix for graph representation.
- Finds the shortest path using  Dijkstra's Algorithm .
- Finds the shortest path using  BFS .
- Outputs the shortest path and distance.
- Saves the results to  shortest_distance.txt .

## Files
-  main.c  - The main C program.
-  cities.txt  - The input file containing city data (source, destination, and distance).
-  shortest_distance.txt  - The output file containing shortest path results.

## Compilation and Execution
### Compilation
To compile the program, use:
   sh
gcc main.c -o shortest_path
   

### Execution
To run the program:
   sh
./shortest_path
   

## Input File Format ( cities.txt )
Each line should contain:
   
[City1] [City2] [Distance]km
   
Example:
   
NewYork Boston 300km
Boston Chicago 500km
   

## How to Use
1.  Run the program .
2.  Select an option from the menu :
   -  1  Load cities from cities.txt.
   -  2  Enter the source city.
   -  3  Enter the destination city.
   -  4  Exit the program.
3.  View shortest path results :
   - Shortest path is displayed in the terminal.
   - Results are also saved in  shortest_distance.txt .

## Example Output
   
Menu:
1. Load cities
2. Enter source
3. Enter destination
4. Exit
Enter your choice: 1
Cities loaded successfully.
Enter the source city: NewYork
Enter the destination city: Chicago

Shortest path using Dijkstra's algorithm:
Chicago <- Boston <- NewYork
Total distance: 800 km

Shortest path using BFS:
Chicago <- Boston <- NewYork
Total distance: 800 km
   

## Notes
- The program assumes a bidirectional graph where distances are symmetrical.
- If a city is not found, the program prompts the user to enter a valid city.
- The adjacency matrix is initialized with  INF  (infinity) for non-connected cities.

## Author
-  Name : Asmaa Fares
-  Student Number : 1210084
- Section: 2
