#include <cs50.h>
#include <stdio.h>

int main(void) {

    // TODO: Prompt for start size
    int start_size;
    do {
        start_size =
            get_int("Enter starting population size(9 is the minimum): ");
    } while (start_size < 9);

    // TODO: Prompt for end size
    int end_size;
    do {
      end_size = get_int("Enter ending population size: ");
    }
    while (end_size < start_size)
    // TODO: Calculate number of years until we reach threshold
    
    // TODO: Print number of years
}
