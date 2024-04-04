#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct AirlineFlights
{
    char airlineName[50];
    char flightSource[50];
    char flightDestination[50];
    double flightFee;
};

void displayLeastFareDetails();

int processFlight(char *fileName, struct AirlineFlights *flightData, int *totalCount);

int parseLine(char *line, char *source, char *destination, double *fare);

int main(void)
{
    FILE *flightsFile = NULL;

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

    // Read indivial airline files implementation
    int totalCount = 0;

    for (int i = 0; i < 3; i++)
    {
        printf("%s ", flightsArray[i]);
        processFlight(flightsArray[i], flightsData, &totalCount);
    }

    printf("%d\n", totalCount);
    return 0;
}

// processFlight function
int processFlight(char *fileName, struct AirlineFlights *flightData, int *totalCount)
{
    FILE *airlineFIle = NULL;
    char currentLine[50] = "";
    char source[20] = "";
    char destination[20] = "";
    double fare = 0;
    char filePath[50] = "";

    strcpy(filePath, fileName);

    strcat(filePath, ".txt");

    airlineFIle = fopen(filePath, "r");

    if (airlineFIle == NULL)
    {
        printf("Couldn't open file");
        return -1;
    }

    while (fgets(currentLine, 50, airlineFIle) != NULL && *totalCount < 100)
    {
        currentLine[strcspn(currentLine, "\n")] = '\0';

        parseLine(currentLine, source, destination, &fare);

        (*totalCount)++;
    }

    int fileClose = fclose(airlineFIle);
    if (fileClose != 0)
    {
        printf("Coulnd't close file");
    }

    return 0;
}

// parseLine function
int parseLine(char *line, char *source, char *destination, double *fare)
{
    sscanf(line, "%[^-] - %[^,], %lf", source, destination, fare);

    printf("Source:%s, Destination: %s, Fare: %lf \n", source, destination, *fare);
    return 0;
}