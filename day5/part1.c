#include "stdio.h"
#include "stdlib.h"
#include "stdint.h"
#include "string.h"
#include "stdbool.h"

#include "assert.h"

typedef struct Range {
    uint64_t min;
    uint64_t max;
} Range;

int32_t main(int32_t argc, char* argv[]) {
    char line[256] = { 0 };

    Range ranges[256] = { 0 };
    uint32_t range_count = 0;

    uint64_t valid_ingredient = 0;
    
    /* Open input file */
    FILE* input = fopen("input.txt", "r");
    assert(input != NULL);

    /* Read the file entirely, line by line */
    /* Start by parsing ranges */
    while( fgets(line, sizeof(line), input) != NULL ){
        /* Remove carriage return if it exists */
        if( line[strlen(line) - 1] == 10 ){
            line[strlen(line) - 1] = '\0';
        }

        /* If this is the empty line, break the loop */
        if( strlen(line) == 0 ){
            break;
        }
        
        /* Parse range */
        assert(sscanf(line, "%llu-%llu", &ranges[range_count].min, &ranges[range_count].max) == 2);

        /* Increment count */
        range_count++;
    }

    /* Then parse ingredients */
    while( fgets(line, sizeof(line), input) != NULL ){
        uint64_t ingredient_id = atoll(line);

        /* Go through every ranges to check if ingredient id is in a range */
        for( uint32_t idx = 0; idx < range_count; idx++ ){
            /**
             * If ingredient id is lesser than the max of the range, then it can be checked.
             * As soon as the max of a range is lesser, ingredient id can't be in a range (as it has been sorted)
             **/
            if( ingredient_id <= ranges[idx].max ){
                if( ingredient_id >= ranges[idx].min ){
                    valid_ingredient++;
                    break;
                }
            }
        }
    }

    printf("Valid ingredients %llu!\r\n", valid_ingredient);

    return 0;
}