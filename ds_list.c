/*Name: Kartik Patel
  Email: kpatel15@uoguelph.ca
  Student ID: 1052085
*/

#include "ds_list.h"
#include "ds_memory.h"

/*This function creates a list bin where the memory is tracked*/
void ds_create_list() {

    long local = -1;
    ds_init("list.bin");
    ds_malloc(sizeof(local));
    ds_finish();

}

/*initializes the file*/
int ds_init_list(){

    ds_init("list.bin");

return 0;
}

/*inserts a value into the given index*/
int ds_insert(int value, long index){

    struct ds_list_item_struct previous;
    struct ds_list_item_struct newStruct;
    long first;
    long previous_loc = 0;
    long i;

    ds_read(&first, 0, sizeof(first));
    previous.next = first;

    for(i=index;0<=i;i=i-1) {
        if(previous.next == -1) {
            return -1;
        }

        else{
            previous_loc = previous.next;
            ds_read(&previous, previous.next, sizeof(previous));

        }
    }

    newStruct.item = value;
    newStruct.next = previous.next;
    ds_malloc(sizeof(newStruct));
    ds_write(newStruct.next, &newStruct.item, sizeof(newStruct.item));
    if (previous_loc == 0){
        return -1;
    }
    else {
        ds_write(previous_loc, &previous, sizeof(previous));
    }

return 0;

}

int ds_finish_list() {

    int finish = ds_finish();
    if (finish == 1) {
        return 0;
    }
    else {
        return 1;
    }

}

