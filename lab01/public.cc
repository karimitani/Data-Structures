#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern void private_array_check (const int *array);
extern void private_copy_init ();
extern void private_copy_check (const char *string);
extern void private_sort_check (const int *array);

void initialize_array ();
void copy_string ();
void bubble_sort ();


int main (int argc, char *argv[])
{
  printf ("Starting tests.\n");
  fflush (stdout);
  initialize_array ();
  copy_string ();
  bubble_sort ();
  return (0);
}

/*
 * Iinitializes the array numbers[] to contain the
 * digits 1-20. 
 */
void initialize_array () {
  int i, numbers[20];

  while (i < 20) {
    numbers[i] = i + 1;
    i++;
  }
  private_array_check (numbers);
}

/*
 * Copies a C string into an allocated buffer called
 * copy.
 */
void copy_string () {
  char string[] = "String that I will copy.";
  char *copy;
  int i;
  
  private_copy_init ();
  
  copy = malloc (strlen (string) + 1);
  for (i = 0; i < strlen (string); i++) {
    copy[i] = string[i];
  }
  
  printf ("Copied string: %s\n", copy);
  private_copy_check (copy);
  free (copy);
}

/*
 * Takes an unsorted array of integers and
 * bubble sorts it.
 */
void bubble_sort () {
  int array[12] = { 5, 7, 99, 12, 42, 31, 1, 45, 9, 21, 22, 23 };
  int i, j, temp;
  
  for (i = 12 - 2; i > 0; i--) {
    for (j = i; j < 12 - 1; j++) {
      if (array[j] > array[j + 1]) {
        temp = array[j];
        array[j] = array[j + 1];
        array[j + 1] = temp;
      } else {
        break;
      }
    }
  } 
  private_sort_check (array);
}
