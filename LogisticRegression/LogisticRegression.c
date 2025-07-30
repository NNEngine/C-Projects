/* LogisticRegression.c | Only one feature set as input */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <float.h>

#define BIAS 0.0
#define LR 0.01
#define EPOCHS 1000

double *weights(int numberOfWeights)
{
    double min_value = -1.0;
    double max_value = 1.0;

    srand(time(0));

    double *weightsArray = (double *)malloc(numberOfWeights * sizeof(double));

    if (weightsArray == NULL)
    {
        return NULL;
    }

    for (int i = 0; i < numberOfWeights; i++)
    {
        double randomVal = ((double)rand() / RAND_MAX);                    // [0,1]
        weightsArray[i] = min_value + randomVal * (max_value - min_value); // [-1,1]
    }

    return weightsArray;
}

double LinearCombination(double *X, double *weights, int length)
{
    if (X == NULL || weights == NULL || length <= 0)
    {
        return -1.0;
    }
    double sum = 0;

    for (int i = 0; i < length; i++)
    {
        sum += (X[i] * weights[i]);
    }

    return sum + BIAS;
}

double SigmoidFunction(double LinearCombination)
{
    double predictedOutput = 1.0 / (1.0 + exp(-LinearCombination));

    return predictedOutput;
}

double Loss(double actualOutput, double predictedOutput)
{
    if (predictedOutput < DBL_EPSILON)
    {
        predictedOutput = DBL_EPSILON;
    }
    if (predictedOutput > 1.0 - DBL_EPSILON)
    {
        predictedOutput = 1.0 - DBL_EPSILON;
    }

    double loss = actualOutput * log(predictedOutput) + (1.0 - actualOutput) * log(1.0 - predictedOutput);

    return -loss;
}

double weightGradient(double actualOutput, double predictedOutput, double x)
{
    double gradient = (predictedOutput - actualOutput) * x;

    return gradient;
}

double biasGradient(double actualOutput, double predictedOutput, double x)
{
    double gradient = predictedOutput - actualOutput;

    return gradient;
}

double weightUpdate(double weight, double weightGradient)
{
    return weight - LR * weightGradient;
}

double biasUpdate(double bias, double biasGradient)
{
    return bias - LR * biasGradient;
}

int main()
{
    double X_train[4] = {0.0, 0.0, 1.0, 1.0};
    double Y_train[4] = {0.0, 1.0, 0.0, 1.0};

    int samples = 4;

    double *w = weights(1);
    double bias = BIAS;

    if (w == NULL)
    {
        return 1;
    }

    for (int epoch = 0; epoch < EPOCHS; epoch++)
    {
        double total_loss = 0.0;

        for (int i = 0; i < samples; i++)
        {
            double x = X_train[i];
            double y = Y_train[i];

            double z = LinearCombination(&x, w, 1);
            double pred = SigmoidFunction(z);
            double loss = Loss(y, pred);

            total_loss += loss;

            double w_grad = weightGradient(y, pred, x);
            double b_grad = biasGradient(y, pred, x);

            w[0] = weightUpdate(w[0], w_grad);
            bias = biasUpdate(bias, b_grad);

            if (epoch % 100 == 0)
            {
                printf("Epoch %d : Loss = %f\n", epoch, total_loss / samples);
            }
        }
    }
    printf("Final weights: %f\n", w[0]);
    printf("Final bias: %f\n", bias);

    free(w);

    return 0;
}