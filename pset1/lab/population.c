#include <cs50.h>
#include <stdio.h>

int main(void) {

    // TODO: Prompt for start size
    int start_size;
    do {
        start_size = get_int("Start size: ");
    } while (start_size < 9);

    // TODO: Prompt for end size
    int end_size;
    do {
        end_size = get_int("End size: ");
    } while (end_size < start_size);
    // TODO: Calculate number of years until we reach threshold
    int n_years = 0;
    int cur_pop = start_size;
    while (cur_pop < end_size) {
        cur_pop = cur_pop + (int)(cur_pop / 3) - (int)(cur_pop / 4);
        n_years++;
    }
    // TODO: Print number of years
    printf("Years: %i\n", n_years);
}
