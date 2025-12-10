#include "stdio.h"
#include "stdlib.h"
#include "stdint.h"
#include "string.h"
#include "stdbool.h"

#include "assert.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct Range {
    uint64_t min;
    uint64_t max;
} Range;

int32_t main(int32_t argc, char* argv[]) {
    char line[256] = { 0 };

    Range ranges[256] = { 0 };
    uint32_t range_count = 0;

    uint64_t valid_ingredient_count = 0;
    
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


    /* Sort ranges in ascending order using bubble sort (by maximum) to gain some time */
    for( uint32_t i = 0; i < range_count - 1; i++ ){
        for( uint32_t j = 0; j < range_count - i - 1; j++ ){
            if (ranges[j].max >= ranges[j + 1].max) {
                Range temp = ranges[j];
                ranges[j] = ranges[j + 1];
                ranges[j + 1] = temp;
            }
        }
    }

    /* Merge ranges that overlaps */
    for( int32_t i = 0; i < range_count - 1; i++ ){
        /* If range max is equal or greater than the range +1 min, then it can be merged */
        if( ranges[i].max >= ranges[i + 1].min ){
            ranges[i].min = (ranges[i + 1].min > ranges[i].min) ? ranges[i].min : ranges[i + 1].min;
            ranges[i].max = ranges[i + 1].max;

            /* Start from +1 index and move back the range list */
            for( uint32_t j = i + 1; j < range_count; j++ ){
                if( j == range_count ){
                    ranges[j].min = 0;
                    ranges[j].max = 0;
                }
                else{
                    ranges[j].min = ranges[j + 1].min;
                    ranges[j].max = ranges[j + 1].max; 
                }
                
            }

            /* Stay at the same index for the next iteration */
            i--;

            /* Decrement range count */
            range_count--;
        }
    }

    /* Go through every ranges and sum the ranges delta to get valid ingredients count */
    for( uint32_t idx = 0; idx < range_count; idx++ ){
        valid_ingredient_count += (ranges[idx].max - ranges[idx].min) + 1;
    }

    printf("Valid ingredients %llu!\r\n", valid_ingredient_count);

    return 0;
}