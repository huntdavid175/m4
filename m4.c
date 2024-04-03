#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void displayLeastFareDetails();

struct AirlineFlights
{
    char airlineName[50];
    char flightSource[50];
    char flightDestination[50];
    double flightFee;
};

int main(void)
{
    FILE *flightsFile = NULL;

    FILE *airlineFile = NULL;

    char fileName[100];
    char flightsArray[100][50];

    struct AirlineFlights flightsData[100];

    int flightCounter = 0;

    flightsFile = fopen("flights.txt", "r"); // Open flightsFile

    if (flightsFile == NULL) // Check if file opened
    {
        printf("Error: Couldn't open file");
        return -1;
    }

    // Read file
    while (fgets(fileName, 50, flightsFile) != NULL)
    {
        char airline[100];
        fileName[strcspn(fileName, "\n")] = '\0';

        sscanf(fileName, "%[^.]", airline); // Extract airline name without extension

        strcpy(flightsArray[flightCounter], airline);

        printf("%s\n", airline);
        flightCounter++;
    }

    int flightsFileClose = fclose(flightsFile);
    if (flightsFileClose != 0)
    {
        printf("File couldn't close");
        return -1;
    }

    // Code to create files (Not related to assignment tho)
    // for (int i = 0; i < flightCounter; i++)
    // {
    //     strcat(flightsArray[i], ".txt");
    //     airlineFile = fopen(flightsArray[i], "w");
    //     int writeFile = fprintf(airlineFile, "%s", flightsArray[i]);

    //     if (writeFile < 0)
    //     {
    //         printf("Counldn't write to file");
    //         return -1;
    //     }

    //     int closeFile = fclose(airlineFile);
    //     if (closeFile != 0)
    //     {
    //         printf("Couldn't close file");
    //         return -1;
    //     }

    //     printf("Airline: %s\n", flightsArray[i]);
    // }

    return 0;
}