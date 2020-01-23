/*
Name: Kartik Patel
Email: kpatel15@uoguelph.ca
Student ID: 1052085
*/

#include "ds_memory.h"

/*
Declaring the global variables here
*/
struct ds_file_struct ds_file;
struct ds_counts_struct ds_counts;

/*
ds_create creates a file and writes the block array in it
*/
int ds_create(char *filename, long size){
    /*
    declaring variables and creating the file
    */
    int i;
    FILE *fp;
    char bytes = 0;

    /*
    placing the values for the first value in the block array
    */
    ds_file.block[0].start = 0;
    ds_file.block[0].length = size;
    ds_file.block[0].alloced = 0;

    /*
    making the other values 0 in the block array
    */
    for (i = 1;i<4096;i++){
        ds_file.block[i].start = 0;
        ds_file.block[i].length = 0;
        ds_file.block[i].alloced = 0;
    }

    /*
    opening the file and writing the array and "size" bytes in the file
    */
    fp = fopen(filename, "wb");

    if(fp == NULL){
        return 1;
    }

    fwrite(ds_file.block, sizeof(ds_file.block), 1, fp);

    for(i=1;i<=size;i++){
        fwrite(&bytes, sizeof(bytes), 1, fp);
    }

    /*
    closing the file
    */

    if(fclose(fp) != 0) {
        return 1;
    }

return 0;
}

/*
opens a file in read and write binary mode and reads the block array
*/
int ds_init(char *filename) {

    /*
    Opening the file in the global variable
    */
    ds_file.fp = fopen(filename, "rb+");

    /*
    read the block array
    */
    fread(ds_file.block, sizeof(ds_file.block), 1, ds_file.fp);

    /*
    set counts reads and writes to 0
    */
    ds_counts.reads = 0;
    ds_counts.writes = 0;

return 0;
}


void ds_test_init() {

    int i;
    printf("Block#     start     length     alloced\n");
    for(i = 0; i<4096; i++){
        printf("%d          %ld         %ld          %d\n", i, ds_file.block[i].start, ds_file.block[i].length, ds_file.block[i].alloced); 
    }

    printf("reads = %d\n", ds_counts.reads);
    printf("writes = %d\n", ds_counts.writes);

return;
}

/*
Used to allocate memory in the block array
*/
long ds_malloc(long amount) {
    /*
    declare variables
    */
    int i;
    int j;
    long tempLength = 0;
    /*
    first this loop finds the first value where amount is less than length
    then it makes that length to amount and alloced to 1
    the second loop sees if there is a length after with the value of 0
    it then inputs the new start and length values and makes alloced to 0
    */ 
    for(i=0; i<4096; i++) {
        if((amount<=ds_file.block[i].length) && (ds_file.block[i].alloced == 0)) {
            tempLength = ds_file.block[i].length;
            ds_file.block[i].length = amount;
            ds_file.block[i].alloced = 1;
            for(j=0; j<4096; j++){
                if(ds_file.block[j].length == 0){
                    ds_file.block[j].start = ds_file.block[i].start + amount;
                    ds_file.block[j].length = tempLength - amount;
                    ds_file.block[j].alloced = 0;
                    break;
                }
            }
            return (ds_file.block[i].start);
        }
    }

return (-1);
}
/*
this function frees the array by making the alloced value 1 to 0
*/
void ds_free(long start) {
    /*
    declare variables
    */
    int i;
    /*
    Loops through the start in the block array until it finds a value same as parameter
    start and then makes alloced to 0 at that point in the block array
    */
    for(i=0; i<MAX_BLOCKS; i++) {
        if(ds_file.block[i].start == start) {
            ds_file.block[i].alloced = 0;
            break;
        }
    }
return;
}

/*
This function reads the number of bytes in ptr from the start value
*/
void *ds_read(void *ptr, long start, long bytes) {
    /*
    declare variables
    */
    long test=0;
    long add = 0;
    /*
    fseeks to the location of where to read
    */
    fseek(ds_file.fp, sizeof(ds_file.block), SEEK_SET);
    test=ftell(ds_file.fp);
    add = start + test;
    fseek(ds_file.fp, add, SEEK_SET);
    fread(ptr, bytes, 1, ds_file.fp);
    ds_counts.reads = ds_counts.reads + 1;
    /*
    error checking
    */
    if(ferror(ds_file.fp)) {
       return (NULL);
    }
    else {
        return (ptr);
    }
}

/*
This function writes the number of bytes in ptr at the start location
*/
long ds_write(long start, void *ptr, long bytes) {
    /*
    Declare variables
    */
    long test = 0;
    long add = 0;
    /*
    fseeks to the location of where to write
    */
    fseek(ds_file.fp, sizeof(ds_file.block), SEEK_SET);
    test=ftell(ds_file.fp);
    add = start + test;
    fseek(ds_file.fp, add, SEEK_SET);
    fwrite(ptr, bytes, 1, ds_file.fp);
    ds_counts.writes = ds_counts.writes + 1;
    /*
    error checking
    */
    if(ferror(ds_file.fp)) {
       return (-1);
    }
    else {
        return (start);
    }


}
/*
This function writes the block array and closes the fle
*/
int ds_finish() {

    /*
    sets the file to the beginning
    */
    fseek(ds_file.fp, 0, SEEK_SET);
    /*
    writing the block array
    */
    fwrite(ds_file.block, sizeof(ds_file.block), 1, ds_file.fp);
    /*
    printing out the read and writes from the counts structure
    */
    printf("reads: %d\n", ds_counts.reads);
    printf("writes: %d\n", ds_counts.writes);

    /*
    closing the file
    */
    fclose(ds_file.fp);

return 1;
}

