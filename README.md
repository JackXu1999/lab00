# PPM Image Transformations
- Linux command lines: manual pages, Linux commands
- C Programming: structs, pointers, memory allocation, getopt

ppmcvt – convert ppm files

ppmcvt [bg:i:r:smt:n:o:] file

Description
ppmcvt manipulates input Portable Pixel Map (PPM) files and outputs a new image based
on its given options. Only one option that specifies a transformation can be used at a time.
In the synopsis, options followed by a ‘:’ expect a subsequent parameter. The options are: \
-b \
convert input file to a Portable Bitmap (PBM) file. (DEFAULT) \
-g: \
convert input file to a Portable Gray Map (PGM) file using the specified max grayscale pixel value [1-65535]. \
-i: \
isolate the specified RGB channel. Valid channels are “red”, “green”, or “blue”. \
-r: \
remove the specified RGB channel. Valid channels are “red”, “green”, or “blue”. \
-s \
apply a sepia transformation \
-m \
vertically mirror the first half of the image to the second half \
-t: \
reduce the input image to a thumbnail based on the given scaling factor [1-8]. \
-n: \
tile thumbnails of the input image based on the given scaling factor [1-8]. \
-o: \
write output image to the specified file. Existent output files will be overwritten.EXIT STATUS

ppmcvt exits 0 on success and 1 on failure.

EXAMPLES
```
ppmcvt -o out.pbm in.ppm
```
read in.ppm PPM file and write converted PBM file to out.pbm
```
ppmcvt -g 16 -o out.pgm in.ppm
```
convert the PPM image in.ppm to a PGM image in out.pgm
```
ppmcvt -s -o out.ppm in.ppm
```
apply a sepia transformation to the PPM image in in.ppm and output the new image to out.ppm
```
ppmcvt -n 4 -o out.ppm in.ppm
```
tile 4 1:4-scaled (quarter-sized) thumbnails of the image in in.ppm into a new PPPM image in out.ppm.