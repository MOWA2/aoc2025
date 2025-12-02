#include "stdio.h"
#include "stdlib.h"
#include "stdint.h"
#include "string.h"
#include "stdbool.h"

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
                assert(strlen(candidate_str) > 0);

                /* Split candidate string in equal length parts, starting at 1 char, to the half number of digit */
                for( uint32_t offset = 1; offset <= strlen(candidate_str) / 2; offset++ ){
                    bool all_splits_are_identical = true;
                    char previous_split[256] = { 0 };
                    
                    /* Candidate must be splittable in equal length parts */
                    if( strlen(candidate_str) % offset != 0 ) continue;

                    /* Check if every split of the candidate has the same value. If yes, id is invalid */
                    for( uint32_t idx = 0; idx < strlen(candidate_str); idx += offset ){
                        char split[256] = { 0 };
                        strncpy(split, candidate_str + idx, offset);
                        
                        /* If the is the first iteration, simply copy split for next comparison */
                        if( idx == 0 ){
                            strncpy(previous_split, split, offset);
                        }
                        /* If current split is different from the previous split, then mark split as not identical */
                        else if( strncmp(split, previous_split, strlen(split)) != 0 ){
                            all_splits_are_identical = false;
                            break;
                        }
                    }

                    /* If all splits are identical, candidate is a valid id, add it to the sum */
                    if( all_splits_are_identical == true ){
                        invalid_id_sum += candidate;
                        break;
                    }
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