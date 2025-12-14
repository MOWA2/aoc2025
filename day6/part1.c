#include "stdio.h"
#include "stdlib.h"
#include "stdint.h"
#include "string.h"
#include "stdbool.h"

#include "assert.h"

int32_t main(int32_t argc, char* argv[]) {
    char line[5000] = { 0 };

    uint64_t num[5][2000] = { 0 };
    uint32_t row_index = 0;

    bool numbers_parsed = false;

    uint64_t operation_sum = 0;
    
    /* Open input file */
    FILE* input = fopen("input.txt", "r");
    assert(input != NULL);

    /* Read the file entirely, line by line */
    while( fgets(line, sizeof(line), input) != NULL ){
        uint32_t col_index = 0;

        /* Remove carriage return if it exists */
        if( line[strlen(line) - 1] == 10 ){
            line[strlen(line) - 1] = '\0';
        }

        /* Split read line by space, and parse numbers */
        char* split = strtok ( line, " " );
        while ( split != NULL ) {
            /* Check if numbers parsing is finished and if its now operand turn */
            if( split[0] == '*' || split[0] == '+' ) numbers_parsed = true;

            /* If numbers needs to be parsed */
            if( numbers_parsed == false ){
                num[row_index][col_index] = atoll(split);
            }
            /* Else this is an operand, so execute calculations and sum it up ! */
            else{
                uint64_t result = split[0] == '*' ? 1 : 0;

                for( uint32_t idx = 0; idx < row_index; idx++ ){
                    if( split[0] == '*' ){
                        result *= num[idx][col_index];
                    }
                    else if( split[0] == '+' ){
                        result += num[idx][col_index];
                    }
                }

                operation_sum += result;
            }

            /* Increment column index */
            col_index++;

            split = strtok( NULL, " " );
        }

        /* Increment row index */
        row_index++;
    }

    printf("Total sum %llu !\r\n", operation_sum);

    return 0;
}