#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct AirlineFlight
{

    char flightSource[50];
    char flightDestination[50];
    double flightFee;
};

void displayLeastFareDetails();

int processFlight(char fileName[40], struct AirlineFlight *flightDataArray, int *totalCount);

int parseLine(char *line, char *source, char *destination, double *fare);

int checkTextForCharacter(char text[], char character);

int checkTextForComma(char text[]);

int main(void)
{
    FILE *flightsFile = NULL;

    char fileName[100];
    char flightsArray[100][50];

    struct AirlineFlight flightsDataArray[100];

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

        // printf("%s\n", airline);
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
        // printf("%s ", flightsArray[i]);
        processFlight(flightsArray[i], flightsDataArray, &totalCount);
    }

    return 0;
}

// processFlight function
int processFlight(char fileName[40], struct AirlineFlight *flightDataArray, int *totalCount)
{
    FILE *airlineFile = NULL;
    char currentLine[50] = "";
    char source[50] = "";
    char destination[50] = "";
    double fare = 0.00;
    char filePath[50] = "";

    strcpy(filePath, fileName);

    strcat(filePath, ".txt");

    airlineFile = fopen(filePath, "r");

    if (airlineFile == NULL)
    {
        printf("Couldn't open file");
        return -1;
    }

    while (fgets(currentLine, 50, airlineFile) != NULL && *totalCount < 100)
    {
        currentLine[strcspn(currentLine, "\n")] = '\0';

        /* Check for dash in text*/
        if (checkTextForCharacter(currentLine, '-') < 1)
        {
            printf("Missing dash in %s\n", currentLine);
            continue;
        }

        /*Check for comma in text*/

        if (checkTextForCharacter(currentLine, ',') < 1)
        {
            printf("Missing comma in %s\n", currentLine);
            continue;
        }

        /*Parse line*/
        parseLine(currentLine, source, destination, &fare);

        // Add to struct array the name of the source, destination and  fare
        strcpy(flightDataArray[*totalCount].flightSource, source);
        strcpy(flightDataArray[*totalCount].flightDestination, destination);
        flightDataArray[*totalCount].flightFee = fare;

        printf("Struct Source: %s, Struct Destination: %s, Struct fare: %.2lf\n", flightDataArray[*totalCount].flightSource, flightDataArray[*totalCount].flightDestination, flightDataArray[*totalCount].flightFee);
        // printf("Source:%s, Destination: %s, Fare: %lf \n", source, destination, fare);
        (*totalCount)++;
    }

    int fileClose = fclose(airlineFile);
    if (fileClose != 0)
    {
        printf("Couldn't close file");
    }

    return 0;
}

// parseLine function
int parseLine(char *line, char *source, char *destination, double *fare)
{
    sscanf(line, "%[^-] - %[^,], %lf", source, destination, fare);

    // printf("Source:%s, Destination: %s, Fare: %lf \n", source, destination, *fare);

    return 0;
}

int checkTextForCharacter(char text[], char character)
{
    int characterCount = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if (text[i] == character)
        {
            characterCount++;
        }
    }
    return characterCount;
}
