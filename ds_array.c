/*
Name: Kartik Patel
Email: kpatel15@uoguelph.ca
Student ID: 1052085
*/

#include "ds_array.h"
#include "ds_memory.h"

/*
Declaring global variables here
*/
long elements;

/*This function creates the array by allocating space*/
int ds_create_array() {

    int init;
    long malloc;
    long malloc2;
    int numElements;
    int finish = 0;
    numElements = sizeof(MAX_ELEMENTS)*MAX_ELEMENTS;
    init= ds_init("array.bin");
    malloc = ds_malloc(sizeof(elements));
    elements = 0;
    malloc2= ds_malloc(numElements);
    finish = ds_finish();

    if(init == 1 || malloc == (-1) || malloc2 == (-1) || finish == 0) {
        return 1;
    }
    else{
        return 0;
    }
}

/*This function initailizes the array for the amount of bytes*/
int ds_init_array() {

    long init;
    long memory = 0;

    init = ds_init("array.bin");

    if(init == 1) {
        return 1;
    }

    ds_read(&init, memory, sizeof(init));
    elements = init;


return 0;
}

/*This function replaces an object in a specific index*/
int ds_replace(int value, long index) {

    index = (index *sizeof(int)) + sizeof(elements);
    ds_write(index,&value, sizeof(value));

    if(index > MAX_ELEMENTS || index<0) {
        return 1;
    }
    else {
       return 0;
    }
}

/*This function inserts the values in the area*/
int ds_insert(int value, long index) {


    int oldVal;
    int newVal = value;
    long i;
    long index2 = (index *sizeof(int)) + sizeof(elements);
    if(index > MAX_ELEMENTS || index<0){
        return 1;
    }
    for(i=index; i<=elements; i++) {
        ds_read(&oldVal, index2, sizeof(oldVal));
        ds_write(index2,&newVal, sizeof(newVal));
        newVal= oldVal;
        if(index <elements){
            index2 =index2 + sizeof(int);
        }
    }

    elements = elements + 1;

return 0;
}

/*This function deletes a value at the index location*/
int ds_delete(long index) {

    int value;
    long i;
    long index2 = (index *sizeof(int)) + sizeof(elements) +sizeof(int);
    long index3 = (index *sizeof(int)) + sizeof(elements);
    if(index > MAX_ELEMENTS || index<0){
        return 1;
    }
    for(i=index; i<=elements; i++) {
        ds_read(&value, index2, sizeof(value));
        ds_write(index3,&value, sizeof(value));
        index2 =index2 + sizeof(int);
        index3 =index3 + sizeof(int);
    }

    elements = elements - 1;


return 0;
}

/*This function swaps two values at their given index*/
int ds_swap(long index1, long index2) {

    int val1;
    int val2;

    if(index1 > MAX_ELEMENTS || index1<0 || index2 > MAX_ELEMENTS || index2<0){
        return 1;
    }


    index1 = (index1 *sizeof(int)) + sizeof(elements);
    index2 = (index2 *sizeof(int)) + sizeof(elements);

    ds_read(&val1, index1, sizeof(val1));
    ds_read(&val2, index2, sizeof(val2));
    ds_write(index2,&val1, sizeof(val1));
    ds_write(index1,&val2, sizeof(val2));

return 0;
}

/*This function finds a value in the array*/
long ds_find(int target) {

    long index = sizeof(elements);
    int value;
    long i;

    for(i=0; i<elements; i++){
        ds_read(&value, index, sizeof(value));
        if(value == target){
            return(i);
        }
        index = index + sizeof(int);
    }

return -1;
}

/*This function reads elements from a txt file*/
int ds_read_elements(char *filename) {
    long i = 0;
    int num=0;
    FILE *fp;

    fp = fopen(filename, "r");
    if(fp == NULL){
        return 1;
    }
    while(fscanf(fp, "%d\n", &num) != EOF){
        if(i >MAX_ELEMENTS){
            return 1;
        }

        ds_insert(num, i);
        i=i+1;
    }
    fclose(fp);

return 0;
}

int ds_finish_array() {

    int finish;
    long memory = 0;
    long check;

    check = ds_write(memory,&elements, sizeof(elements));


    finish = ds_finish();

    if (finish == 0 || check == -1){
        return 1;
    }
    else{
        return 0;
    }

}

