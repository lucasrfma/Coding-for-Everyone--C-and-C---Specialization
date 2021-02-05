/*
  Calculate the average weight for a population of elephants. The data has to be passed
  as parameter at startup like: "average_elephant elephant_seal_data"
*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  // Long to prevent overflow for large arrays
  long total_weight = 0;
  int weight;
  int elephants = 0;

  // Open passed file for reading
  FILE * file = fopen(argv[1], "r");

  // Loop until the end of the file
  while (1 == fscanf(file, "%d", &weight)) {
    elephants++;
    total_weight += weight;
    printf("\nWeight: %d Number: %d",weight,elephants);
  }

  printf("Average weight: %ld\n", (total_weight/elephants));

  return 0;
}
