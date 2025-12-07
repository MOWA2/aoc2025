#include "stdio.h"
#include "stdlib.h"
#include "stdint.h"
#include "string.h"

#include "assert.h"

/**
 * @brief Battery definition
 */
typedef struct battery{
    uint8_t value; /* Value of the battery */
    uint16_t position_in_pack; /* Position of the battery in the pack */
}battery;

int32_t main(int32_t argc, char* argv[]) {
    char line[256] = { 0 };
    battery battery_pack[256] = { 0 };

    uint32_t battery_sum = 0;

    /* Open input file */
    FILE* input = fopen("input.txt", "r");
    assert(input != NULL);

    /* Read the file entirely, line by line */
    while( fgets(line, sizeof(line), input) != NULL ){
        battery highest_value_battery = { 0 };
        uint32_t battery_max_combination = 0;
        uint32_t battery_pack_size = strlen(line);

        /* Remove carriage return if it exists */
        if( line[battery_pack_size - 1] == 10 ){
            battery_pack_size--;
        }

        /* Parse line to get cells in the battery pack */
        for(uint32_t idx = 0; idx < battery_pack_size; idx++ ){
            battery_pack[idx].position_in_pack = idx;
            battery_pack[idx].value = line[idx] - '0';
        }

        /* Sort batteries in the pack in descending order using bubble sort */
        for (int i = 0; i < battery_pack_size - 1; i++) {
            for (int j = 0; j < battery_pack_size - i - 1; j++) {
                if (battery_pack[j].value < battery_pack[j + 1].value) {
                    battery temp = battery_pack[j];
                    battery_pack[j] = battery_pack[j + 1];
                    battery_pack[j + 1] = temp;
                }
            }
        }
        
        /* Take the first available highest value battery (can't be at the last position in the pack) */
        highest_value_battery = battery_pack[0];
        if( highest_value_battery.position_in_pack == battery_pack_size - 1 ){
            highest_value_battery = battery_pack[1];
        }

        /* Find the next highest value battery that is positioned AFTER the first one in the pack */
        for(uint32_t idx = 0; idx < battery_pack_size; idx++ ){
            if( battery_pack[idx].position_in_pack > highest_value_battery.position_in_pack ){
                battery_max_combination = highest_value_battery.value * 10 + battery_pack[idx].value;
                break;
            }
        }

        battery_sum += battery_max_combination;
    }

  	printf("Battery sum %d! \r\n", battery_sum);

    return 0;
}