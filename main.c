#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>

//name:asmaa fares
//std.no:1210084
//section:2

#define MAX_CITIES 100
#define INF INT_MAX

typedef struct {//struct for city
    char name[50];//name of city
} City;

typedef struct {//struct for path info
    int distance;//distance between cities
    int previous;//previous city
} PathInfo;

City cities[MAX_CITIES];//array of cities
int graph[MAX_CITIES][MAX_CITIES];//adjacency matrix
int numCities;//number of cities

void loadCities() {
    FILE* file = fopen("cities.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    char line[100];
    numCities = 0;
    while (fgets(line, sizeof(line), file) != NULL) {//read line by line
        char source[50], destination[50];//source and destination cities
        int distance;//distance between cities
        sscanf(line, "%s %s %dkm", source, destination, &distance);

        int sourceIndex = -1, destinationIndex = -1;//source and destination city indexes
        for (int i = 0; i < numCities; i++) {//check if cities are already in the array
            if (strcmp(source, cities[i].name) == 0) {//if source city is already in the array
                sourceIndex = i;
            }
            if (strcmp(destination, cities[i].name) == 0) {//if destination city is already in the array
                destinationIndex = i;
            }
        }

        if (sourceIndex == -1) {
            strcpy(cities[numCities].name, source);//copy source city to cities array
            sourceIndex = numCities;//set source index to the index of the last city in the array
            numCities++;
        }
        if (destinationIndex == -1) {
            strcpy(cities[numCities].name, destination);//copy destination city to cities array
            destinationIndex = numCities;//set destination index to the index of the last city in the array
            numCities++;
        }

        graph[sourceIndex][destinationIndex] = distance;//add edge between source and destination cities
        graph[destinationIndex][sourceIndex] = distance;//add edge between destination and source cities
    }

    fclose(file);
}

int findCityIndex(const char* cityName) {//find city index in cities array
    for (int i = 0; i < numCities; i++) {
        if (strcmp(cityName, cities[i].name) == 0) {
            return i;
        }
    }
    return -1;
}

void constructGraph() {//construct adjacency matrix
    for (int i = 0; i < numCities; i++) {
        for (int j = 0; j < numCities; j++) {
            if (i != j && graph[i][j] == 0) {
                graph[i][j] = INF;
            }
        }
    }
}

void addEdge(int srcIndex, int destIndex, int distance) {//add edge between two cities
    graph[srcIndex][destIndex] = distance;//add edge between source and destination cities
    graph[destIndex][srcIndex] = distance;
}

void dijkstra(int sourceIndex, int destinationIndex) { //find shortest path using Dijkstra's algorithm
    bool visited[MAX_CITIES];//array of visited cities
    PathInfo pathInfo[MAX_CITIES];//array of path info

    for (int i = 0; i < numCities; i++) {//initialize arrays
        visited[i] = false;
        pathInfo[i].distance = INF;
        pathInfo[i].previous = -1;
    }

    pathInfo[sourceIndex].distance = 0;

    for (int count = 0; count < numCities - 1; count++) {//find shortest path
        int minDistance = INF;//minimum distance
        int minIndex = -1;

        for (int i = 0; i < numCities; i++) {//find unvisited city with minimum distance
            if (!visited[i] && pathInfo[i].distance <= minDistance) {
                minDistance = pathInfo[i].distance;
                minIndex = i;
            }
        }

        visited[minIndex] = true;//mark city as visited

        for (int i = 0; i < numCities; i++) {//update distance of adjacent cities
            if (!visited[i] && graph[minIndex][i] != INF &&
                pathInfo[minIndex].distance != INF &&
                pathInfo[minIndex].distance + graph[minIndex][i] < pathInfo[i].distance) {//if distance of adjacent city is greater than distance of current city + distance between current city and adjacent city
                pathInfo[i].distance = pathInfo[minIndex].distance + graph[minIndex][i];//update distance
                pathInfo[i].previous = minIndex;
            }
        }
    }

    printf("Shortest path using Dijkstra's algorithm:\n");
    int currIndex = destinationIndex;
    while (currIndex != sourceIndex) {
        int previousIndex = pathInfo[currIndex].previous;
        printf("%s <- ", cities[currIndex].name);
        printf("Distance: %d km ", graph[currIndex][previousIndex]); // Print distance between cities
        currIndex = previousIndex;
    }
    printf("%s\n", cities[sourceIndex].name);
    printf("Total distance: %d km\n", pathInfo[destinationIndex].distance);


    FILE* file = fopen("shortest_distance.txt", "w");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    fprintf(file, "Shortest path using Dijkstra's algorithm:\n");
    currIndex = destinationIndex;
    while (currIndex != sourceIndex) {
        int previousIndex = pathInfo[currIndex].previous;
        fprintf(file, "%s <- ", cities[currIndex].name);
        fprintf(file, "Distance: %d km ", graph[currIndex][previousIndex]); // Print distance between cities
        currIndex = previousIndex;
    }
    fprintf(file, "%s\n", cities[sourceIndex].name);
    fprintf(file, "Total distance: %d km\n", pathInfo[destinationIndex].distance);

    fclose(file);
}

void bfs(int sourceIndex, int destinationIndex) {//find shortest path using BFS
    bool visited[MAX_CITIES];//array of visited cities
    int parent[MAX_CITIES];//array of parent cities
    for (int i = 0; i < numCities; i++) {
        visited[i] = false;
        parent[i] = -1;
    }

    visited[sourceIndex] = true;//mark source city as visited

    int queue[MAX_CITIES];
    int front = 0;
    int rear = 0;
    queue[rear] = sourceIndex;

    while (front <= rear) {//find shortest path
        int currIndex = queue[front++];
        if (currIndex == destinationIndex) {
            break;
        }

        for (int i = 0; i < numCities; i++) {//add adjacent cities to queue
            if (!visited[i] && graph[currIndex][i] != INF) {//if city is not visited and there is an edge between current city and adjacent city
                queue[++rear] = i;
                visited[i] = true;
                parent[i] = currIndex;
            }
        }
    }

    printf("Shortest path using BFS:\n");
    int currIndex = destinationIndex;
    while (currIndex != sourceIndex) {
        int previousIndex = parent[currIndex];
        printf("%s <- ", cities[currIndex].name);
        printf("Distance: %d km ", graph[currIndex][previousIndex]); // Print distance between cities
        currIndex = previousIndex;
    }
    printf("%s\n", cities[sourceIndex].name);

    FILE* file = fopen("shortest_distance.txt", "a");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    fprintf(file, "Shortest path using BFS:\n");
    currIndex = destinationIndex;
    while (currIndex != sourceIndex) {
        int previousIndex = parent[currIndex];
        fprintf(file, "%s <- ", cities[currIndex].name);
        fprintf(file, "Distance: %d km ", graph[currIndex][previousIndex]); // Print distance between cities
        currIndex = previousIndex;
    }
    fprintf(file, "%s\n", cities[sourceIndex].name);

    fclose(file);
}

int main() {
    char fileName[100];
    int sourceIndex = -1, destinationIndex = -1;
    bool citiesLoaded = false;


    while (true) {
        int choice;
        printf("\nMenu:\n");
        printf("1. Load cities\n");
        printf("2. Enter source\n");
        printf("3. Enter destination\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                loadCities();
                constructGraph();
                citiesLoaded = true;
                printf("Cities loaded successfully.\n");
                break;
            case 2:
                if (citiesLoaded) {
                    char sourceCity[50];
                    printf("Enter the source city: ");
                    scanf("%s", sourceCity);
                    sourceIndex = findCityIndex(sourceCity);
                    if (sourceIndex == -1) {
                        printf("Source city not found.\n");
                    } else {
                        printf("Source city set to %s.\n", cities[sourceIndex].name);
                    }
                } else {
                    printf("Please load the cities first.\n");
                }
                break;
            case 3:
                if (citiesLoaded) {
                    char destinationCity[50];
                    printf("Enter the destination city: ");
                    scanf("%s", destinationCity);
                    destinationIndex = findCityIndex(destinationCity);
                    if (destinationIndex == -1) {

                        printf("Destination city set to %s.\n", cities[destinationIndex].name);
                    } else {
                        printf("Please load the cities first.\n");
                    }
                    dijkstra(sourceIndex, destinationIndex);
                    bfs(sourceIndex, destinationIndex);

                    break;

                    case 4:
                        if (citiesLoaded && sourceIndex != -1 && destinationIndex != -1) {
                            printf("\n------__printing info to the file __-----\n\n");
                            dijkstra(sourceIndex, destinationIndex);
                            bfs(sourceIndex, destinationIndex);

                        } else {
                            printf("Please load the cities and set the source and destination cities first.\n");
                        }
                    printf("Exiting the program.\n");
                    return 0;
                    default:
                        printf("Invalid choice. Please try again.\n");
                }
        }
    }
}
