#include "stdio.h"
#include "stdlib.h"
#include "stdint.h"
#include "stdbool.h"
#include "assert.h"

int32_t main(int32_t argc, char* argv[]) {
    char line[256] = { 0 };
    int32_t dial_position = 50;
    uint32_t reached_O_count = 0;

    /* Open input file */
    FILE* input = fopen("input.txt", "r");
    assert(input != NULL);

    /* Read the file entirely */
    while( fgets(line, sizeof(line), input) != NULL ){
        bool dial_was_zero = dial_position == 0;

        /* Fetch rotation tick count */
        int32_t rotation_count = atoi(line + 1);

        /* Get the count of complete rotation */
        int32_t complete_rotation_count = rotation_count / 100;
        reached_O_count += complete_rotation_count;

        /* Remove complete rotation to rotation tick count */
        rotation_count = rotation_count % 100;

        /* Check the first character to know which direction to rotate */
        if( line[0] == 'R' ){
            dial_position += rotation_count;
        }
        else{
            dial_position -= rotation_count;
        }

        /* Dial is circular (0 to 99), so make sure to handle over and underflow */
        if( dial_position > 99 ){
            dial_position = dial_position % 100;
            reached_O_count++;
        } 
        else if( dial_position < 0 ){
            dial_position = 100 - ((-1) * dial_position % 100);
            if( !dial_was_zero ) reached_O_count++;
        }
        else if( dial_position == 0 ) reached_O_count++;
    }

  	printf("Dial reached 0 position %d times! \r\n", reached_O_count);

    return 0;
}