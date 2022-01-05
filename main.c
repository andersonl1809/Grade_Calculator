#include <stdio.h>
#include <stdlib.h>
#include "grade.h"

int main(int argc, char **argv){
  GradeDoc grdDoc = getInputs(); 
  buildExcel(grdDoc,argv[1]);
}