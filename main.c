#include <stdio.h>
#include <stdlib.h>
#include "grade.h"
#include <string.h>

int main(int argc, char **argv)
{
  if (argc != 2)
    return EXIT_FAILURE;
  for (int i; i <= strlen(argv[1]); i++)
  {
    if (argv[1][i] == '.')
    {
      if (strlen(argv[1]) == i + 4 && argv[1][i + 1] == 'c')
      {
        if (argv[1][i + 2] == 's')
        {
          if (argv[1][i + 3] == 'v')
          {
            if (argv[1][i + 4] == '\0')
            {
              break;
            }
          }
        }
      }
    }
    if (i == strlen(argv[1])){
      printf("\nError: csv file must be input.\n");
      return EXIT_FAILURE;
    }
  }

  GradeDoc grdDoc = getInputs();
  buildExcel(grdDoc, argv[1]);
}