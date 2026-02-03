#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

struct Image{
	int rows;
	int cols;

	uint8_t *img;
};

struct Image *createImage(int rows, int cols)
{
	struct Image *newImage = malloc(sizeof(struct Image));
	if(!newImage) return NULL;

	newImage->rows = rows;
	newImage->cols = cols;

	newImage->img = malloc(rows * cols * sizeof(uint8_t));

	if(!newImage->img){
		free(newImage);
		return NULL;
	}


	int min = 0, max = 255;

	for (int i = 0; i < newImage->rows; i++){
		for(int j = 0;j < newImage->cols; j++){
			int num = min + rand() % (max - min + 1);
			newImage->img[i * newImage->cols + j] = (uint8_t)num;
		}
	}

	return newImage;
}

void freeImage(struct Image *image)
{
	if (image){
		free(image->img);
		free(image);
	}
}

void printImage(struct Image *image)
{
	if(!image || !image->img) return;

	int rows = image->rows;
	int cols = image->cols;

	for(int i = 0; i < rows; i++){
		for(int j = 0; j < cols; j++){
			printf("%3u ", image->img[i * cols + j]);
		}
		printf("\n");
	}
}
double sizeOfImageKB(struct Image *image)
{
	if (!image || !image->img) return 0.0;

    size_t bytes = (size_t)image->rows * image->cols * sizeof(uint8_t);
    return (double)bytes / 1024.0;
}

int saveImagePGM(const char *filename, struct Image *image)
{
	// Binary PGM (P5)
    FILE *fp = fopen(filename, "wb");
    if (!fp) {
        perror("Failed to open file");
        return -1;
    }

    fprintf(fp, "P5\n");
    fprintf(fp, "%d %d\n", image->cols, image->rows);
    fprintf(fp, "255\n");

    fwrite(image->img, sizeof(uint8_t),
           image->rows * image->cols, fp);

    fclose(fp);
    return 0;
}

// ==============================================================================
//  generateSmoothField
// ==============================================================================

uint8_t clamp(int v) {
    if (v < 0) return 0;
    if (v > 255) return 255;
    return (uint8_t)v;
}

void generateSmoothField(struct Image *img, int noise_strength)
{
    for (int i = 0; i < img->rows; i++) {
        for (int j = 0; j < img->cols; j++) {

            int value;

            if (i == 0 && j == 0)
                value = rand() % 256;
            else if (i == 0)
                value = img->img[j - 1];
            else if (j == 0)
                value = img->img[(i - 1) * img->cols];
            else
                value = (
                    img->img[i * img->cols + j - 1] +
                    img->img[(i - 1) * img->cols + j] +
                    img->img[(i - 1) * img->cols + j - 1]
                ) / 3;

            value += (rand() % (2 * noise_strength + 1)) - noise_strength;
            img->img[i * img->cols + j] = clamp(value);
        }
    }
}

int main(int argc, char *argv[])
{
	srand((unsigned)time(NULL));
	struct Image *img1  = createImage(1050, 1050);
	// printImage(img1);
	printf("%f KB", sizeOfImageKB(img1));

	// generateSmoothField
	generateSmoothField(img1, 10);

	saveImagePGM("output.pgm", img1);


	freeImage(img1);

	return 0;
}
