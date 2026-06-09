# Turkey Route Optimizer in C

## Project Overview

Turkey Route Optimizer is a graph-based route planning system developed in C. The project represents 81 Turkish cities as nodes and road connections as weighted edges. It calculates optimal routes between multiple stops using graph algorithms and dynamic programming techniques.

The system loads city and road information from external files and determines the shortest route between selected locations.

---

## Features

* Graph representation using adjacency lists
* Loading city and road data from external files
* Dijkstra's shortest path algorithm
* Multi-stop route optimization
* Dynamic Programming based route planning
* Real route reconstruction and visualization
* Distance calculation between Turkish cities

---

## Algorithms Used

### Dijkstra Algorithm

Used to calculate the shortest path between cities in the graph.

### Dynamic Programming

Used to optimize routes containing multiple stops.

### Graph Data Structures

The map of Turkey is represented as a weighted graph using adjacency lists.

---

## Project Structure

```text
main.c
cities.txt
roads.txt
```

* `main.c` : Main application and algorithms
* `cities.txt` : Turkish city information
* `roads.txt` : Road and distance data

---

## Example Usage

1. Enter the number of stops.
2. Enter city plate numbers.
3. The program calculates the optimal route.
4. The complete route and total distance are displayed.

Example:

```text
Stops:
Izmir -> Ankara -> Konya -> Istanbul

Total Distance: XXXX km
```

---

## Technologies

* C Programming Language
* Graph Data Structures
* Dijkstra Algorithm
* Dynamic Programming
* File Handling
* Adjacency Lists

---



