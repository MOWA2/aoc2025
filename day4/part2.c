#include "stdio.h"
#include "stdlib.h"
#include "stdint.h"
#include "string.h"

#include "assert.h"

int32_t main(int32_t argc, char* argv[]) {
    char line[256] = { 0 };
    char map[256][256] = { 0 };
    uint32_t current_y_parsing_index = 0;

    uint32_t map_x_max = 0;
    uint32_t map_y_max = 0;

    uint32_t accessible_rolls = 0;

    /* Open input file */
    FILE* input = fopen("input.txt", "r");
    assert(input != NULL);

    /* Read the file entirely, line by line */
    while( fgets(map[current_y_parsing_index], sizeof(map[current_y_parsing_index]), input) != NULL ){
        map_x_max = strlen(map[current_y_parsing_index]);

        /* Remove carriage return if it exists */
        if( map[current_y_parsing_index][map_x_max - 1] == 10 ){
            map_x_max--;
        }

        current_y_parsing_index++;
    }
    map_y_max = current_y_parsing_index;

    /*
     * For every place in the map, check if this is a paper roll.
     * If this is a paper roll, check if it can be accessed by a forklift
     * If it can be accessed sum it, then remove it
     * Repeat this operation till there is no more paper rolls to remove
     **/
    uint32_t removed_rolls = 0;
    do{
        /* Reset removed rolls count */
        removed_rolls = 0;

        for( uint32_t idx_y = 0; idx_y < map_y_max; idx_y++ ){
            for( uint32_t idx_x = 0; idx_x < map_x_max; idx_x++ ){
                if( map[idx_y][idx_x] == '@' ){
                    uint32_t adjacent_paper_rolls = 0;

                    /* Check the upper row */
                    if( idx_y > 0 ){
                        if( idx_x > 0 && map[idx_y - 1][idx_x - 1] == '@' ) adjacent_paper_rolls++; /* x.. */
                        if( map[idx_y - 1][idx_x] == '@' ) adjacent_paper_rolls++; /* .x. */
                        if( idx_x < map_x_max && map[idx_y - 1][idx_x + 1] == '@' ) adjacent_paper_rolls++; /* ..x */
                    }

                    /* Check the middle row */
                    if( idx_x > 0 && map[idx_y][idx_x - 1] == '@' ) adjacent_paper_rolls++; /* x.. */
                    if( idx_x < map_x_max && map[idx_y][idx_x + 1] == '@' ) adjacent_paper_rolls++; /* ..x */

                    /* Check the lower row  */
                    if( idx_y < map_y_max ){
                        if( idx_x > 0 && map[idx_y + 1][idx_x - 1] == '@' ) adjacent_paper_rolls++; /* x.. */
                        if( map[idx_y + 1][idx_x] == '@' ) adjacent_paper_rolls++; /* .x. */
                        if( idx_x < map_x_max && map[idx_y + 1][idx_x + 1] == '@' ) adjacent_paper_rolls++; /* ..x */
                    }
                    
                    /* If there is less than 4 adjacent paper roll, mark it as accessible and remove it */
                    if( adjacent_paper_rolls < 4 ){
                        removed_rolls++;
                        map[idx_y][idx_x] = 'x';
                    }
                }
            }
        }

        accessible_rolls += removed_rolls;
    }while(removed_rolls > 0);

    printf("accessibles rolls %d!\r\n", accessible_rolls);

    return 0;
}