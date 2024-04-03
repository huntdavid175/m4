#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
    FILE *flightsFile = NULL;

    char fileName[100];
    char flightsArray[100][20];

    int flightCounter = 0;

    flightsFile = fopen(".//flights.txt", "r"); // Open flightsFile

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

        sscanf(fileName, "%[^.]", airline);

        strcpy(flightsArray[flightCounter], airline);

        printf("%s\n", airline);
        flightCounter++;
    }

    for (int i = 0; i < flightCounter; i++)
    {
        printf("Airline: %s\n", flightsArray[i]);
    }

    return 0;
}