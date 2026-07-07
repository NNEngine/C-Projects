#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// -------------------- Random Normal (Truncated) --------------------
double rand_normal_val() {
    double u1, u2, z0;
    do {
        u1 = (double)rand() / ((double)RAND_MAX + 1.0);
        u2 = (double)rand() / ((double)RAND_MAX + 1.0);
        z0 = sqrt(-2.0 * log(u1)) * cos(2.0 * M_PI * u2);
    } while (z0 < -1.0 || z0 > 1.0); // rejection sampling
    return z0;
}

// -------------------- Matrix Struct --------------------
typedef struct {
    int rows;
    int cols;
    double *data;
} Matrix;

// Allocate matrix
Matrix *alloc_matrix(int rows, int cols) {
    Matrix *m = (Matrix *)malloc(sizeof(Matrix));
    m->rows = rows;
    m->cols = cols;
    m->data = (double *)malloc(rows * cols * sizeof(double));

    return m;
}

// Free matrix
void free_matrix(Matrix *m) {
    if (m) {
        free(m->data);
        free(m);
    }
}

// Access element
double get(Matrix *m, int i, int j) {
    return m->data[i * m->cols + j];
}

void set(Matrix *m, int i, int j, double val) {
    m->data[i * m->cols + j] = val;
}

// -------------------- Linear Module --------------------
typedef struct {
    Matrix *weight; // (in_features x out_features)
    Matrix *bias;   // (1 x out_features)
    int in_features;
    int out_features;
} Linear;

// Initialize Linear layer
Linear *Linear_init(int in_features, int out_features) {
    Linear *layer = (Linear *)malloc(sizeof(Linear));
    layer->in_features = in_features;
    layer->out_features = out_features;

    // weights: (in_features x out_features)
    layer->weight = alloc_matrix(in_features, out_features);
    for (int i = 0; i < in_features; i++) {
        for (int j = 0; j < out_features; j++) {
            set(layer->weight, i, j, rand_normal_val());
        }
    }

    // bias: (1 x out_features)
    layer->bias = alloc_matrix(1, out_features);
    for (int j = 0; j < out_features; j++) {
        set(layer->bias, 0, j, rand_normal_val());
    }

    return layer;
}

// Forward pass: y = xW + b
Matrix *Linear_forward(Linear *layer, Matrix *input) {
    if (input->cols != layer->in_features) {
        printf("Dimension mismatch: input cols %d vs in_features %d\n",
               input->cols, layer->in_features);
        return NULL;
    }

    Matrix *output = alloc_matrix(input->rows, layer->out_features);

    for (int i = 0; i < input->rows; i++) {
        for (int j = 0; j < layer->out_features; j++) {
            double sum = 0.0;
            for (int k = 0; k < layer->in_features; k++) {
                sum += get(input, i, k) * get(layer->weight, k, j);
            }
            sum += get(layer->bias, 0, j);
            set(output, i, j, sum);
        }
    }
    return output;
}


int main() {
    srand((unsigned)time(NULL));

    int in_features = 3;
    int out_features = 2;

    // Create Linear layer
    Linear *fc = Linear_init(in_features, out_features);

    // Input: (1 x 3)
    Matrix *x = alloc_matrix(1, in_features);
    set(x, 0, 0, 1.0);
    set(x, 0, 1, 2.0);
    set(x, 0, 2, 3.0);

    // Forward pass
    Matrix *y = Linear_forward(fc, x);

    printf("Output:");
    printf("[ ");
    for (int j = 0; j < out_features; j++) {
        printf("%lf ", get(y, 0, j));
    }
    printf("]");
    printf("\n");

    printf("\nInput:");
    printf("[ ");
    for(int i = 0; i < in_features; i++){
                printf("%lf ", get(x, 0, i));
    }
    printf(" ]");

    printf("\nWeight:\n");
    printf("[ \n");
    for(int i = 0; i < in_features; i++){
                for(int j = 0; j < out_features; j++){
                        printf("%lf ", get(fc->weight, i, j));
                }
                printf("\n");
    }
    printf("]");

    printf("\nBias:");
    printf("[ ");
    for(int i = 0; i < out_features; i++){
                printf("%lf ", get(fc->bias, 0, i));
    }
    printf(" ]");

    free_matrix(x);
    free_matrix(y);
    free_matrix(fc->weight);
    free_matrix(fc->bias);
    free(fc);

    return 0;
}
