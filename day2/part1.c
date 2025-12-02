#include "stdio.h"
#include "stdlib.h"
#include "stdint.h"
#include "string.h"

#include "assert.h"

int32_t main(int32_t argc, char* argv[]) {
    char read_char = 0;

    char range_str[256] = { 0 };
    uint32_t range_str_idx = 0;
    uint32_t range_min = 0;
    uint32_t range_max = 0;

    uint64_t invalid_id_sum = 0;

    /* Open input file */
    FILE* input = fopen("input.txt", "r");
    assert(input != NULL);

    /* Read file char by char, stopping at each comma or EOF */
    do{
        read_char = fgetc(input);

        /* If comma or end of file reached, a range is complete and can be processed */
        if( read_char == ',' || read_char == EOF ){
            range_str[range_str_idx] = '\0';
            
            /* Get range min and max */
            assert(sscanf(range_str, "%u-%u", &range_min, &range_max) == 2);

            /* For every number in the range, check if this is an invalid id */
            for( uint32_t candidate = range_min; candidate <= range_max; candidate++ ){
                char candidate_str[256] = { 0 };
                char candidate_left_str[256] = { 0 };
                char candidate_right_str[256] = { 0 };
                uint32_t candidate_digit_count = 0;
                uint32_t candidate_half_index = 0;
                uint32_t candidate_left = 0;
                uint32_t candidate_right = 0;

                /* First, convert it to a string */
                snprintf(candidate_str, sizeof(candidate_str) - 1, "%u", candidate);
                
                /* Get the number of digit the candidate number is composed of */
                candidate_digit_count = strlen(candidate_str);

                /* If number of digit is not even, do not even go further as candidate can't be splitted
                 * in perfect halves.. */
                if( (candidate_digit_count % 2) != 0 ) continue;

                /* Get the left, and right part of the candidate number by splitting it in 2 */
                candidate_half_index = candidate_digit_count / 2;
                candidate_right = strtoul(candidate_str + candidate_half_index, NULL, 10);
                candidate_str[candidate_half_index] = '\0';
                candidate_left = strtoul(candidate_str, NULL, 10);
                
                /* If left and right part are identical, candidate is a invalid id */
                if( candidate_left == candidate_right ){
                    invalid_id_sum += candidate;
                }
            }

            /* Reset parsing variables */
            range_str_idx = 0;
        }
        /* Add char to range string */
        else{
            range_str[range_str_idx] = read_char;
            range_str_idx++;
        }
    }while(read_char != EOF);

    printf("%llu is the sum of all invalid ids!\r\n", invalid_id_sum);

    return 0;
}