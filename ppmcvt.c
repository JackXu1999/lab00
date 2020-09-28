// THIS CODE IS MY OWN WORK, IT WAS WRITTEN WITHOUT CONSULTINGA  TUTOR OR CODE WRITTEN BY OTHER STUDENTS - Shengkai Xu

#include "pbm.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>


// struct PPMImage ppm;
// struct PGMImage pgm;
// struct PBMImage pbm;

// int **array_ppm;
// int **array_pgm;
// int **array_pbm;

struct Options{
    char mode[20];
    char arg[20];
    char infile_name[30];
    char outfile_name[30];
    int num;
};

extern int errno;

// struct Options option;


void bitmap(char * infilename, char * outfilename, struct Options option);
void grayscale(char * infilename, char * outfilename, struct Options option);
void sepia(char * infilename, char * outfilename, struct Options option);
void mirror(char * infilename, char * outfilename, struct Options option);
void thumbnail(char * infilename, char * outfilename, struct Options option);
void nup(char * infilename, char * outfilename, struct Options option);
void isolate(char * infilename, char * outfilename, struct Options option);
void remove_color(char * infilename, char * outfilename, struct Options option);

PPMImage * readAndCopy(char * infilename, char * outfilename);

void optionAndWrite(struct Options option, PPMImage * image_PPM);



void optionAndWrite(struct Options option, PPMImage * image_PPM) {
    // char output_name[4];
    // int arr_size = sizeof(option.outfile_name) / sizeof(option.outfile_name[0]);
    
    // file type
    // output_name[3] = '\0';
    // output_name[2] = option.outfile_name[arr_size - 2];
    // output_name[1] = option.outfile_name[arr_size - 3];
    // output_name[0] = option.outfile_name[arr_size - 4];
    
    // free the memory
    // if (strstr(option.outfile_name, "ppm") != NULL) {

        write_ppmfile(image_PPM, option.outfile_name);
        del_ppmimage(image_PPM);

    // } else if (strstr(option.outfile_name, "pgm") != NULL) {

    //     write_pgmfile(image_PPM, option.outfile_name);
    //     del_pgmimage(image_PPM);

    // } else if (strstr(option.outfile_name, "pbm") != NULL) {

    //     write_pbmfile(image_PPM, option.outfile_name);
    //     del_pbmimage(image_PPM);
    // }


}



PPMImage * readAndCopy(char * infilename, char * outfilename) {
    // reads the input file
    PPMImage *read_file = read_ppmfile(infilename); 
    
    // dynamically allocate memory
    PPMImage *new_ppm = new_ppmimage(read_file->width, read_file->height, read_file->max);
    int i, j, k;

    // copy pixel by pixel
    for (i = 0; i < 3; i++) {
        for (j = 0; j < read_file->height; j++) {
            for (k = 0; k < read_file->width; k++) {
                new_ppm->pixmap[i][j][k] = read_file->pixmap[i][j][k];
            }
        }
    }


    del_ppmimage(read_file);
    return new_ppm;
}



void bitmap(char * infilename, char * outfilename, struct Options option) {
    int i, j, k;

    PPMImage *new_ppm = readAndCopy(infilename, outfilename);

    PBMImage *new_pbm = new_pbmimage(new_ppm->width, new_ppm->height);

    // transformation

        for (j = 0; j < new_ppm->height; j++) {
            for (k = 0; k < new_ppm->width; k++) {
                float avg = (new_ppm->pixmap[1][j][k] + new_ppm->pixmap[0][j][k] + new_ppm->pixmap[2][j][k]) / 3;
                if (avg < (float)new_ppm->max / 2) {
                    new_pbm->pixmap[j][k] = 1;
                } else {
                    new_pbm->pixmap[j][k] = 0;
                }
            }
        }


    write_pbmfile(new_pbm, outfilename);
    del_pbmimage(new_pbm);
    del_ppmimage(new_ppm);


    // optionAndWrite(option, new_ppm);

}

void grayscale(char * infilename, char * outfilename, struct Options option) {
    int i, j, k;

    PPMImage *new_ppm = readAndCopy(infilename, outfilename);
    PGMImage *new_pgm = new_pgmimage(new_ppm->width, new_ppm->height, option.num);

    if (option.num >= 65536 || option.num < 1) {
        printf("Errpr: Invalid max grayscale picel value: %d; must be less than 65536\n", option.num);
        exit(0);
    }

    // transformation
        for (j = 0; j < new_ppm->height; j++) {
            for (k = 0; k < new_ppm->width; k++) {
                float avg = (new_ppm->pixmap[1][j][k] + new_ppm->pixmap[0][j][k] + new_ppm->pixmap[2][j][k]) / 3;
                new_pgm->pixmap[j][k] = (avg / (float)new_ppm->max * (float)option.num);
            }
        }
       

    write_pgmfile(new_pgm, outfilename);
    del_ppmimage(new_ppm);
    del_pgmimage(new_pgm);
    // optionAndWrite(option, new_ppm);
}


void sepia(char * infilename, char * outfilename, struct Options option) {
    int i, j, k;

    PPMImage *new_ppm = readAndCopy(infilename, outfilename);


    // transformation

    for (j = 0; j < new_ppm->height; j++) {
        for (k = 0; k < new_ppm->width; k++) {
            double newR = 0.393*new_ppm->pixmap[0][j][k] + 0.769*new_ppm->pixmap[1][j][k] + 0.189*new_ppm->pixmap[2][j][k];
            double newG = 0.349*new_ppm->pixmap[0][j][k] + 0.686*new_ppm->pixmap[1][j][k] + 0.168*new_ppm->pixmap[2][j][k];
            double newB = 0.272*new_ppm->pixmap[0][j][k] + 0.534*new_ppm->pixmap[1][j][k] + 0.131*new_ppm->pixmap[2][j][k];
            new_ppm->pixmap[0][j][k] = (unsigned int) newR;
            new_ppm->pixmap[1][j][k] = (unsigned int) newG;
            new_ppm->pixmap[2][j][k] = (unsigned int) newB;
        }
    }

    optionAndWrite(option, new_ppm);
    // del_ppmimage(new_ppm);
}

void mirror(char * infilename, char * outfilename, struct Options option) {
    int i, j, k;

    PPMImage *new_ppm = readAndCopy(infilename, outfilename);

    // transformation

    for (i = 0; i < 3; i++) {
        for (j = 0; j < new_ppm->height; j++) {
            for (k = 0; k < new_ppm->width / 2; k++) {
                unsigned int temp = new_ppm->pixmap[i][j][k];
                new_ppm->pixmap[i][j][k] = new_ppm->pixmap[i][j][new_ppm->width - 1 - k];
                new_ppm->pixmap[i][j][new_ppm->width - 1 - k] = temp;
            }
        }
    }

    optionAndWrite(option, new_ppm);
    // del_ppmimage(new_ppm);
}

void thumbnail(char * infilename, char * outfilename, struct Options option) {
    int i, j, k;
    int x, y;
    int arg = option.num;

    if (arg > 8 || arg < 1) {
        printf("Error: Invalid scale factor: %d; must be 1-8\n", arg);
    } else {


        PPMImage *read_file = read_ppmfile(infilename);
        PPMImage *new_ppm = new_ppmimage(read_file->width / arg, read_file->height / arg, read_file->max);


        for (i = 0; i < 3; i++) {
            for (j = 0, x = 0; j < new_ppm->height; j++, x+=arg) {
                for (k = 0, y = 0; k < new_ppm->width; k++, y+=arg) {
                    new_ppm->pixmap[i][j][k] = read_file->pixmap[i][x][y];
                }
            }
        }

        optionAndWrite(option, new_ppm);
        del_ppmimage(read_file);
    }
}

void nup(char * infilename, char * outfilename, struct Options option) {
    int i, j, k;

    int x, y;
    int arg = option.num;
    int a, b;

    if (arg > 8 || arg < 1) {
        printf("Error: Invalid scale factor: %d; must be 1-8\n", arg);
    } else {

        PPMImage *read_file = read_ppmfile(infilename);
        PPMImage *small = new_ppmimage(read_file->width / arg, read_file->height / arg, read_file->max);

        for (i = 0; i < 3; i++) {
            for (j = 0, x = 0; j < small->height; j++, x+=arg) {
                for (k = 0, y = 0; k < small->width; k++, y+=arg) {
                    small->pixmap[i][j][k] = read_file->pixmap[i][x][y];
                }
            }
        }

        PPMImage *new_ppm = new_ppmimage(read_file->width, read_file->height, read_file->max);


        for (i = 0; i < 3; i++) {
            for (j = 0, a = 0; j < new_ppm->height; j++, a++) {
                for (k = 0, b = 0; k < new_ppm->width; k++, b++) {
                    if (a == small->height) a = 0;
                    if (b == small->width) b = 0;
                    new_ppm->pixmap[i][j][k] = small->pixmap[i][a][b];
                }
            }
        }
        
        del_ppmimage(small);
        optionAndWrite(option, new_ppm);
        del_ppmimage(read_file);
    }
}

void isolate(char * infilename, char * outfilename, struct Options option) {
    int i, j, k;

    char green[6] = {'g', 'r', 'e', 'e', 'n', '\0'};
    char red[4] = {'r', 'e', 'd', '\0'};
    char blue[5] = {'b', 'l', 'u', 'e', '\0'};

    PPMImage *new_ppm = readAndCopy(infilename, outfilename);


    if (strcmp(option.arg, red) == 0) {

        for (i = 0; i < 3; i++) {
            for (j = 0; j < new_ppm->height; j++) {
                for (k = 0; k < new_ppm->width; k++) {
                    if (i == 1 || i == 2) {
                        new_ppm->pixmap[i][j][k] = 0;
                    }
                }
            }
        }

    } else if (strcmp(option.arg, green) == 0) {

        for (i = 0; i < 3; i++) {
            for (j = 0; j < new_ppm->height; j++) {
                for (k = 0; k < new_ppm->width; k++) {
                    if (i == 0 || i == 2) {
                        new_ppm->pixmap[i][j][k] = 0;
                    }
                }
            }
        }
        
    } else if (strcmp(option.arg, blue) == 0){

        for (i = 0; i < 3; i++) {
            for (j = 0; j < new_ppm->height; j++) {
                for (k = 0; k < new_ppm->width; k++) {
                    if (i == 0 || i == 1) {
                        new_ppm->pixmap[i][j][k] = 0;
                    }
                }
            }
        } 
        
    } else {
        printf("Error: Invalid chanel specification: %s; should be 'red, 'green or 'blue'\n", option.arg);
    }

    optionAndWrite(option, new_ppm);
    // del_ppmimage(new_ppm);
}

void remove_color(char * infilename, char * outfilename, struct Options option) {
    int i, j, k;
    char green[6] = {'g', 'r', 'e', 'e', 'n', '\0'};
    char red[4] = {'r', 'e', 'd', '\0'};
    char blue[5] = {'b', 'l', 'u', 'e', '\0'};

    PPMImage *new_ppm = readAndCopy(infilename, outfilename);


    if (strcmp(option.arg, red) == 0) {

        for (i = 0; i < 3; i++) {
            for (j = 0; j < new_ppm->height; j++) {
                for (k = 0; k < new_ppm->width; k++) {
                    if (i == 0) {
                        new_ppm->pixmap[i][j][k] = 0;
                    }
                }
            }
        }

    } else if (strcmp(option.arg, green) == 0) {
        
        for (i = 0; i < 3; i++) {
            for (j = 0; j < new_ppm->height; j++) {
                for (k = 0; k < new_ppm->width; k++) {
                    if (i == 1) {
                        new_ppm->pixmap[i][j][k] = 0;
                    }
                }
            }
        }
        
    } else if (strcmp(option.arg, blue) == 0) {

        for (i = 0; i < 3; i++) {
            for (j = 0; j < new_ppm->height; j++) {
                for (k = 0; k < new_ppm->width; k++) {
                    if (i == 2) {
                        new_ppm->pixmap[i][j][k] = 0;
                    }
                }
            }
        }

    } else {
        printf("Error: Invalid chanel specification: %s; should be 'red, 'green or 'blue'\n", option.arg);
    }

    optionAndWrite(option, new_ppm);
    // del_ppmimage(new_ppm);
}


// TODO FINISH the switch statement

int main( int argc, char * argv[] ) {
    int opt;
    int index;
    // -o always comes with two arguments
    struct Options option;
    

    while ((opt = getopt(argc, argv, "bg:i:r:smt:n:o")) != -1) {
        
        // if (strstr(argv[argc - 2], ".ppm") == NULL || strstr(argv[argc - 2], ".pbm") == NULL || strstr(argv[argc - 2], ".pgm")== NULL) {
        //     printf("Error: No output file specified\n");
        //     exit(0);
        // }

        // if (strstr(argv[argc - 1], ".ppm") == NULL || strstr(argv[argc - 1], ".pbm") == NULL || strstr(argv[argc - 1], ".pgm") == NULL ) {
        //     printf("Error: No input file specified\n");
        //     exit(0);
        // }

        
        strcpy(option.outfile_name, argv[argc - 2]);
        strcpy(option.infile_name, argv[argc - 1]);

        if (argc > 6) {
            printf("Error: Mutiple transformation specified\n");
            exit(0);
        }
                
        switch (opt) {
            case 'b':
                strcpy(option.mode, "b");
                break;

            case 'g':
                strcpy(option.mode, "g");
                option.num = atoi(optarg);
                break;

            case 'i':
                strcpy(option.mode, "i");
                strcpy(option.arg, optarg);
                break;

            case 'r':
                strcpy(option.mode, "r");
                strcpy(option.arg, optarg);
                break;

            case 's':
                strcpy(option.mode, "s");
                break;

            case 'm':
                strcpy(option.mode, "m");
                break;

            case 't':
                strcpy(option.mode, "t");
                option.num = atoi(optarg);
                break;
   
            case 'n':
                strcpy(option.mode, "n");
                option.num = atoi(optarg);
                break;

            case 'o':
                
                break;

            default:

                printf("Usage: ppmcvt [-btgismtno] [FILE]\n:");
                break;
        }
    }
    // call the suitable function for transformation
    if (strcmp(option.mode, "b") == 0) {
        bitmap(option.infile_name, option.outfile_name, option);

    } else if (strcmp(option.mode, "g") == 0) {
        grayscale(option.infile_name, option.outfile_name, option);

    } else if (strcmp(option.mode, "i") == 0) {
        isolate(option.infile_name, option.outfile_name, option);

    } else if (strcmp(option.mode, "r") == 0) {
        remove_color(option.infile_name, option.outfile_name, option);

    } else if (strcmp(option.mode, "s") == 0) {
        sepia(option.infile_name, option.outfile_name, option);

    } else if (strcmp(option.mode, "m") == 0) {
        mirror(option.infile_name, option.outfile_name, option);

    } else if (strcmp(option.mode, "t") == 0) {
        thumbnail(option.infile_name, option.outfile_name, option);

    } else if (strcmp(option.mode, "n") == 0) {
        nup(option.infile_name, option.outfile_name, option);

    }

}

PPMImage * new_ppmimage( unsigned int width, unsigned int height, unsigned int max) {
    
    int i, j;
    // array_ppm = (int ***) malloc(sizeof(int **) * 3);
    PPMImage *array_ppm = (PPMImage*)malloc(sizeof(PPMImage));

    for (j = 0; j < 3; j++) {
        array_ppm->pixmap[j] = (unsigned int **) malloc(sizeof(unsigned int *) * height);
        for (i = 0; i < height; i++) {
            array_ppm->pixmap[j][i] = (unsigned int *) malloc (sizeof (unsigned int) * width);
        }
    }
    array_ppm->max = max;
    array_ppm->height = height;
    array_ppm->width = width;
    // PPMImage ppm = {array_ppm, width, height, max};

    return array_ppm;
}

PGMImage * new_pgmimage( unsigned int width, unsigned int height, unsigned int max) {
    
    int i;
    PGMImage *array_pgm = (PGMImage*)malloc(sizeof(PGMImage));

    array_pgm ->pixmap = (unsigned int **) malloc(sizeof(unsigned int *) * height);
    for (i = 0; i < height; i++) {
        array_pgm->pixmap[i] = (unsigned int *) malloc (sizeof (unsigned int) * width);
    }
    array_pgm->width = width;
    array_pgm->max = max;
    array_pgm->height = height;

    // PGMImage pgm = {array_pgm, width, height, max};
    return array_pgm;
}

PBMImage * new_pbmimage( unsigned int width, unsigned int height ) {
    // what does it mean?

    int i;

    PBMImage *array_pbm = (PBMImage*)malloc(sizeof(PBMImage));
    array_pbm->pixmap = (unsigned int **) malloc(sizeof(unsigned int *) * height);
    for (i = 0; i < height; i++) {
        array_pbm->pixmap[i] = (unsigned int *) malloc (sizeof (unsigned int) * width);
    }
    array_pbm->width = width;
    array_pbm->height = height;

    // PBMImage pbm = {array_pbm, width, height};
    return array_pbm;
}


void del_ppmimage( PPMImage * ppm) {
    int i, j;
    for (j = 0; j < 3; j++) {
        for (i = 0; i < ppm->height; i++) {
            free(ppm->pixmap[j][i]);
        }
        free(ppm->pixmap[j]);
    }
    // free(ppm->pixmap);
    free(ppm);
}

void del_pgmimage( PGMImage * pgm) {
    int i;
    for (i = 0; i < pgm->height; i++) {
        free(pgm->pixmap[i]);
    }
    free(pgm->pixmap);
    free(pgm);
}

void del_pbmimage( PBMImage * pbm) {
    int i;
    for (i = 0; i < pbm->height; i++) {
        free(pbm->pixmap[i]);
    }
    free(pbm->pixmap);
    free(pbm);
}


