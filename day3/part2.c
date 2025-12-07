#include "stdio.h"
#include "stdlib.h"
#include "stdint.h"
#include "stdbool.h"
#include "string.h"

#include "assert.h"

static uint64_t poors_man_pow( uint64_t x, uint64_t p ){
    uint64_t result = 1;

    for(uint32_t i = 0; i < p; i++){
        result *= x;
    }

    return result;
};

/**
 * @brief Battery definition
 */
typedef struct battery{
    uint8_t value; /* Value of the battery */
    bool is_on; /* Used to indicate battery is on in the pack */
}battery;

int32_t main(int32_t argc, char* argv[]) {
    char line[256] = { 0 };
    battery battery_pack[256] = { 0 };

    uint64_t battery_sum = 0;

    /* Open input file */
    FILE* input = fopen("input.txt", "r");
    assert(input != NULL);

    /* Read the file entirely, line by line */
    while( fgets(line, sizeof(line), input) != NULL ){
        uint32_t battery_left_to_find = 12;
        uint32_t last_highest_battery_index = 0;
        uint32_t battery_pack_size = strlen(line);

        /* Remove carriage return if it exists */
        if( line[battery_pack_size - 1] == 10 ){
            battery_pack_size--;
        }

        /* Parse line to get cells in the battery pack */
        for( uint32_t idx = 0; idx < battery_pack_size; idx++ ){
            battery_pack[idx].is_on = false;
            battery_pack[idx].value = line[idx] - '0';
        }

        /* 
         * Find the twelve highest value batteries, and set them to on.
         * Batteries positionned at the left most in the pack must be set on first!
         **/
        do{
            uint32_t highest_battery_value = 0;
            uint32_t highest_battery_index = 0;

            /* Find the next highest value battery, starting from the last found index, till the last index (to let enough batteries to compose the pack) */
            for( uint32_t idx = last_highest_battery_index; idx < battery_pack_size - (battery_left_to_find - 1); idx++ ){
                /* Found a candidate ! */
                if( battery_pack[idx].value > highest_battery_value ){
                    highest_battery_value = battery_pack[idx].value;
                    highest_battery_index = idx;
                }
            }

            /* For the next iteration, start the search after the found battery */
            last_highest_battery_index = highest_battery_index + 1;
            
            /* Accumulate value */
            battery_sum += highest_battery_value * poors_man_pow(10, battery_left_to_find - 1);
            battery_left_to_find--;
        }while( battery_left_to_find > 0 );
    }

  	printf("Battery sum %llu! \r\n", battery_sum);

    return 0;
}