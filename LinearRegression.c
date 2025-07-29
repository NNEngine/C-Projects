#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int Min(int x, int y)
{
    if (x > y)
    {
        return y;
    }
    else
    {
        return x;
    }
}

double Mean(double X[], int size)
{
    double sum = 0;

    for (int i = 0; i < size; i++)
    {
        sum += X[i];
    }

    return sum / size;
}

double Covariance(double X[], int sizeX, double Y[], int sizeY)
{
    double meanX = Mean(X, sizeX);
    double meanY = Mean(Y, sizeY);

    double sum = 0;
    int size = Min(sizeX, sizeY);

    for (int i = 0; i < size; i++)
    {
        sum += (X[i] - meanX) * (Y[i] - meanY);
    }
    return sum / size;
}

double DifferenceFromMean(double X[], int size, int power)
{
    double mean = Mean(X, size);

    double differenceSum = 0;

    for (int i = 0; i < size; i++)
    {
        differenceSum += pow((X[i] - mean), power);
    }
    return differenceSum;
}

double *LinearRegression(double X[], int sizeX, double Y[], int sizeY)
{
    double *parameters = (double *)malloc(2 * sizeof(double));
    double slope = (Covariance(X, sizeX, Y, sizeY)) / (DifferenceFromMean(X, sizeX, 2));

    double intercept = Mean(Y, sizeY) - slope * Mean(X, sizeX);

    parameters[0] = slope;
    parameters[1] = intercept;

    return parameters;
}

int main()
{
    printf("Enter the number of elements in X: ");
    int sizeX;
    scanf("%d", &sizeX);
    double *X = (double *)malloc(sizeX * sizeof(double));
    if (X == NULL)
    {
        printf("Memory Allocation Failed");
        return 1;
    }
    printf("Enter the Elements of X:\n ");
    for (int i = 0; i < sizeX; i++)
    {
        scanf("%lf", &X[i]);
    }

    printf("Enter the number of elements in Y: ");
    int sizeY;
    scanf("%d", &sizeY);
    double *Y = (double *)malloc(sizeY * sizeof(double));
    if (Y == NULL)
    {
        printf("Memory Allocation Failed");
        return 1;
    }

    printf("Enter the Elements of Y:\n ");
    for (int i = 0; i < sizeY; i++)
    {
        scanf("%lf", &Y[i]);
    }

    double *parameters = LinearRegression(X, sizeX, Y, sizeY);

    printf("y = %lf * x + %lf", parameters[0], parameters[1]);

    free(X);
    free(Y);

    return 0;
}