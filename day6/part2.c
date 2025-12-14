#include "stdio.h"
#include "stdlib.h"
#include "stdint.h"
#include "string.h"
#include "stdbool.h"

#include "assert.h"

int32_t main(int32_t argc, char* argv[]) {
    char line[5][5000] = { 0 };

    uint32_t num[1000] = { 0 };
    uint32_t num_index = 0;

    uint32_t row_index = 0;
    uint32_t col_index = 0;
    uint32_t operand_row = 0;

    uint64_t operation_sum = 0;
    
    /* Open input file */
    FILE* input = fopen("input.txt", "r");
    assert(input != NULL);

    /* Read the file entirely, line by line */
    while( fgets(line[row_index], sizeof(line[row_index]), input) != NULL ){
        /* Increment row index */
        row_index++;
    }
    operand_row = row_index - 1;

    /** 
     * Input must be read in column, from right to left. For every cols, get a number. If all chars
     * of a col are blanks (or \n), then, list of numbers is complete, and a result can be computed.
     **/
    bool operand_fetched = false;
    char operand = '*';
    do{
        uint32_t col_number = 0;
        bool is_blank = true;

        for( uint32_t i = 0; i < operand_row; i++ ){
            /* Check if char is blank/return or not */
            if( line[i][col_index] != ' ' && line[i][col_index] != '\n' ){
                is_blank = false;

                col_number *= 10;
                col_number += line[i][col_index] - '0';
            }
        }

        if( !operand_fetched ){
            if( line[operand_row][col_index] == '*'
                || line[operand_row][col_index] == '+' ){
                operand_fetched = true;
                operand = line[operand_row][col_index];
            }
        }        

        /* If blank for all lines has been reached, read numbers in column from right to left and execute operation */
        if( is_blank ){
            uint64_t operation_result = (operand == '*') ? 1 : 0;
            
            for( int32_t idx = num_index - 1; idx >= 0; idx-- ){
                if( operand == '*' ){
                    operation_result *= num[idx];
                }
                else{
                    operation_result += num[idx];
                }
            }

            operand_fetched = false;
            num_index = 0;

            /* Accumulate operation result */
            operation_sum += operation_result;
        }
        /* Else, just had the acquired number in the list */
        else{
            num[num_index] = col_number;
            num_index++;
        }

        col_index++;
    }while(line[0][col_index] != '\0');

    printf("Total sum %llu !\r\n", operation_sum);

    return 0;
}