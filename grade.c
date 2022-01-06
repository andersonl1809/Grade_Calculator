#include "grade.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAX_SIZE 20

Category *buildCategories(int numCats)
{
  Category *categories = malloc(sizeof(Category) * numCats);
  return categories;
}

GradeDoc getInputs()
{
  // get number of categories
  int numCats; // number of categories
  for (;;)
  {
    printf("\nHow many categories are there? ");
    scanf("%d", &numCats);

    if (numCats > 0 && numCats < 15)
    {
      break;
    }
    printf("Invalid input. Enter number between 1 and 14.\n");
  }

  // construct array of categories
  Category *categories = buildCategories(numCats);

  // initialize all weight types to corresponding type
  char wtType; // weight type (points or percent)

  for (;;)
  {
    printf("\nAre categories weighted by points (P) or percent (%%)? ");
    do
    {
      scanf("%c", &wtType);
    } while (wtType == '\n');

    if (wtType == Points || wtType == Percent)
      break;
    printf("Invalid Input. Enter P or %%.\n");
  }

  // sets starting excel row for categories
  int currRow = 4;

  // do for each category
  for (int catNum = 0; catNum < numCats; catNum++)
  {
    char tempCatName[MAX_SIZE];
    int sizeCatName = 0;

    // get category name
    printf("\nWhat is the name of category %d? ", catNum + 1);
    for (int i = 0; i < MAX_SIZE; i++)
    {
      if (i == 0)
      {
        do
        {
          tempCatName[i] = getc(stdin);
        } while (tempCatName[i] == '\n');
      }
      else
      {
        tempCatName[i] = getc(stdin);
      }

      if (tempCatName[i] == '\n' || tempCatName[i] == '\0')
      {
        tempCatName[i] = '\0';
        sizeCatName = i + 1;
        break;
      }
    }

    categories[catNum].catName = malloc(sizeof(char) * sizeCatName);
    for (int i = 0; i < sizeCatName; i++)
    {
      categories[catNum].catName[i] = tempCatName[i];
    }

    // get number of assignments
    do
    {
      printf("\nHow many assignments are there in %s? ", categories[catNum].catName);
      for (int i = 0; i < MAX_SIZE; i++)
      {
        if (i == 0)
        {
          do
          {
            tempCatName[i] = getc(stdin);
          } while (tempCatName[i] == '\n');
        }
        else
        {
          tempCatName[i] = getc(stdin);
        }

        if (tempCatName[i] == '\n' || tempCatName[i] == '\0')
        {
          tempCatName[i] = '\0';
          int num = 0; // number to print
          for(int j = 0; j < i; j++){
            num = 10 * num + (tempCatName[j] - '0');
          } 
          categories[catNum].numAsnmnts = num;
          break;
        }

        if(tempCatName[i] - '0' < 0 || tempCatName[i] - '0' >= 10)
        {
          categories[catNum].numAsnmnts = 0;
          char tempChar;
          do{
            tempChar = getc(stdin);
          } while(tempChar != '\n' && tempChar != '\0');
          break;
        }
      }   
      if(categories[catNum].numAsnmnts == 0) printf("Error: Please enter a valid positive integer.\n"); 
    } while (categories[catNum].numAsnmnts == 0);

    // get number of points per assignment
    categories[catNum].numPnts = 0;
    do
    { 
      printf("\nHow many points are there for each assignment? ");
      for (int i = 0; i < MAX_SIZE; i++)
      {
        if (i == 0)
        {
          do
          {
            tempCatName[i] = getc(stdin);
          } while (tempCatName[i] == '\n');
        }
        else
        {
          tempCatName[i] = getc(stdin);
        }

        if (tempCatName[i] == '\n' || tempCatName[i] == '\0')
        {
          tempCatName[i] = '\0';
          int num = 0; // number to print
          for(int j = 0; j < i; j++){
            num = 10 * num + (tempCatName[j] - '0');
          } 
          categories[catNum].numPnts = num;
          break;
        }

        if(tempCatName[i] - '0' < 0 || tempCatName[i] - '0' >= 10)
        {
          categories[catNum].numPnts = 0;
          char tempChar;
          do{
            tempChar = getc(stdin);
          } while(tempChar != '\n' && tempChar != '\0');
          break;
        }
      }
      if(categories[catNum].numPnts == 0) printf("Error: Please enter a valid positive integer.\n");   
    } while (categories[catNum].numPnts == 0);

    // get assignment names
    do
    {
      // if (checkAssName(categories[catNum].assName) == true)
      printf("\nWhat are the names of the assignments with the following format:\n  * If each assignment has a numerical value attached, it must use a # where the number should go:\n    - Example 1: HW# would display HW1, HW2, etc.\n    - Example 2: HW## would display HW01, HW02, etc.\n  * To use a space, use an _ instead\n    - Example: HW_## would display HW 01, HW 02, etc.\n  * Use a ! in place of # if no number is desired\n    - Example 1: HW! would display HW, HW, etc.\n    - Example 2: *! would allow for individual assignments to be typed out\n  * If assignments don't start at 1, append *# where # is the starting number\n    - Example: HW_#*0 would display HW 0, HW 1, etc.\n");
      scanf("%s", (categories[catNum].assName));
    } while (checkAssName(categories[catNum].assName) == false);

    // get weighting
    do
    {
      if (wtType == Points)
      {
        categories[catNum].weightVal.pnts = categories[catNum].numAsnmnts * categories[catNum].numPnts;
      }
      else
      {
        printf("\nWhat is the weight of this category (in percent)? ");
        scanf("%f", &(categories[catNum].weightVal.prcnt));
      }

    } while ((wtType == Points && !((int)categories[catNum].weightVal.pnts == categories[catNum].weightVal.pnts)) || (wtType == Percent && !((float)categories[catNum].weightVal.prcnt == categories[catNum].weightVal.prcnt)));

    // get number of drops
    categories[catNum].numDrops = -1;
    char charDrop = ' ';
    do
    {
      if (charDrop != '\0' && charDrop != '\n')
      {
        printf("\nHow many of these assignments are dropped? ");
      }
      while (true)
      {
        charDrop = getc(stdin);
        if (charDrop == '\0' || charDrop == '\n')
          break;
        categories[catNum].numDrops = charDrop - '0';
      }
    } while (categories[catNum].numDrops < 0 || categories[catNum].numDrops > 10);

    // initialize start and end rows
    categories[catNum].strtRow = currRow;
    categories[catNum].endRow = currRow + categories[catNum].numAsnmnts + 1;
    currRow = categories[catNum].endRow + 2;
  }
  GradeDoc grdDoc = {.cat = categories,
                     .numCats = numCats,
                     .wtType = wtType};

  return grdDoc;
}

bool checkAssName(char *ass)
{
  for (int charNum = 0; charNum < strlen(ass); charNum++)
  {
    if (ass[charNum] == '#' || ass[charNum] == '!')
      return true;
  }
  return false;
}

void buildExcel(GradeDoc grdDoc, char *excelFile)
{
  FILE *outFile = fopen(excelFile, "w");

  fprintf(outFile, "Assignment, Points Earned So Far, Total Points so Far, Percent, Potential Points, Max Grade, Min Grade");
  fprintf(outFile, "\n,");

  // get end rows
  int *endRows = getEndRows(grdDoc);

  // if points weighting type
  if (grdDoc.wtType == Points)
  {
    // print points earned
    fprintf(outFile, "\"=ROUND(SUM(");
    printEndRows(outFile, 'C', endRows, grdDoc.numCats);
    // get total points
    int totPnts = getTotalPnts(grdDoc);
    fprintf(outFile, "),2)&\"\"/%d\"\"\"", totPnts);

    // print total points so far
    fprintf(outFile, ",\"=SUM(");
    printEndRows(outFile, 'D', endRows, grdDoc.numCats);

    // print current percent
    fprintf(outFile, ")\",\"=if(C2=0,\"\"\"\",ROUND(SUM(");
    printEndRows(outFile, 'C', endRows, grdDoc.numCats);
    fprintf(outFile, ")/C2,4))\"");

    // print potential points
    fprintf(outFile, ",\"=SUM(");
    printEndRows(outFile, 'F', endRows, grdDoc.numCats);
    fprintf(outFile, ")&\"\"/%d\"\"\"", totPnts);

    // print max grade in percent format
    fprintf(outFile, ",\"=ROUND((SUM(");
    printEndRows(outFile, 'F', endRows, grdDoc.numCats);
    fprintf(outFile, ")+SUM(");
    printEndRows(outFile, 'C', endRows, grdDoc.numCats);
    fprintf(outFile, "))/%d,4)\"", totPnts);

    // print min grade in percent format
    fprintf(outFile, ",\"=ROUND((SUM(");
    printEndRows(outFile, 'C', endRows, grdDoc.numCats);
    fprintf(outFile, "))/%d,4)\"", totPnts);

    // print max grade in points format
    fprintf(outFile, "\n,,,,,\"=ROUND(SUM(");
    printEndRows(outFile, 'F', endRows, grdDoc.numCats);
    fprintf(outFile, ")+SUM(");
    printEndRows(outFile, 'C', endRows, grdDoc.numCats);
    fprintf(outFile, "),2)&\"\" points\"\"\"");

    // print min grade in points format
    fprintf(outFile, ",\"=ROUND(SUM(");
    printEndRows(outFile, 'C', endRows, grdDoc.numCats);
    fprintf(outFile, "),2)&\"\" points\"\"\"");
  }

  // if percent weighting type
  else
  {
    // prints points earned
    fprintf(outFile, "\"=ROUND(100 * (");
    for (int i = 0; i < grdDoc.numCats; i++)
    {
      fprintf(outFile, "(D%d/SUM(D%d,F%d))*%lf*IF(E%d=\"\"\"\",0,E%d)",
              grdDoc.cat[i].endRow, grdDoc.cat[i].endRow, grdDoc.cat[i].endRow,
              grdDoc.cat[i].weightVal.prcnt / 100,
              grdDoc.cat[i].endRow, grdDoc.cat[i].endRow);
      if (i != grdDoc.numCats - 1)
      {
        fprintf(outFile, "+");
      }
    }
    fprintf(outFile, "),2)&\"\"/100\"\"\"");

    // prints total points so far
    fprintf(outFile, ",");
    fprintf(outFile, "\"=ROUND(100*(");
    for (int i = 0; i < grdDoc.numCats; i++)
    {
      fprintf(outFile, "(D%d/SUM(D%d,F%d))*%lf",
              grdDoc.cat[i].endRow, grdDoc.cat[i].endRow,
              grdDoc.cat[i].endRow, grdDoc.cat[i].weightVal.prcnt / 100);
      if (i != grdDoc.numCats - 1)
      {
        fprintf(outFile, "+");
      }
    }
    fprintf(outFile, "),2)\"");

    // prints percent
    fprintf(outFile, ",");
    fprintf(outFile, "\"=IF(C2=0,\"\"\"\",ROUND((");
    for (int i = 0; i < grdDoc.numCats; i++)
    {
      fprintf(outFile, "(D%d/SUM(D%d,F%d))*%lf*IF(E%d=\"\"\"\",0,E%d)",
              grdDoc.cat[i].endRow, grdDoc.cat[i].endRow, grdDoc.cat[i].endRow,
              grdDoc.cat[i].weightVal.prcnt / 100,
              grdDoc.cat[i].endRow, grdDoc.cat[i].endRow);
      if (i != grdDoc.numCats - 1)
      {
        fprintf(outFile, "+");
      }
    }
    fprintf(outFile, ")/(");
    for (int i = 0; i < grdDoc.numCats; i++)
    {
      fprintf(outFile, "(D%d/SUM(D%d,F%d))*%lf",
              grdDoc.cat[i].endRow, grdDoc.cat[i].endRow, grdDoc.cat[i].endRow,
              grdDoc.cat[i].weightVal.prcnt / 100);
      if (i != grdDoc.numCats - 1)
      {
        fprintf(outFile, "+");
      }
    }
    fprintf(outFile, "),4))\"");

    // prints potential points
    fprintf(outFile, ",");
    fprintf(outFile, "\"=IF(C2<=100,ROUND(100-C2,2),\"\"\"\")\"");

    // prints max grade
    fprintf(outFile, ",");
    fprintf(outFile, "\"=ROUND(");
    for (int i = 0; i < grdDoc.numCats; i++)
    {
      fprintf(outFile, "SUM(C%d,F%d)/SUM(D%d,F%d)*%lf",
              grdDoc.cat[i].endRow, grdDoc.cat[i].endRow, grdDoc.cat[i].endRow,
              grdDoc.cat[i].endRow, grdDoc.cat[i].weightVal.prcnt / 100);
      if (i != grdDoc.numCats - 1)
      {
        fprintf(outFile, "+");
      }
    }
    fprintf(outFile, ",4)\"");

    // prints min grade
    fprintf(outFile, ",");
    fprintf(outFile, "\"=ROUND(100 * (");
    for (int i = 0; i < grdDoc.numCats; i++)
    {
      fprintf(outFile, "(D%d/SUM(D%d,F%d))*%lf*IF(E%d=\"\"\"\",0,E%d)",
              grdDoc.cat[i].endRow, grdDoc.cat[i].endRow, grdDoc.cat[i].endRow,
              grdDoc.cat[i].weightVal.prcnt / 100,
              grdDoc.cat[i].endRow, grdDoc.cat[i].endRow);
      if (i != grdDoc.numCats - 1)
      {
        fprintf(outFile, "+");
      }
    }
    fprintf(outFile, "),2)/100\"");

    fprintf(outFile, "\n");
  }

  // displays various categories
  for (int i = 0; i < grdDoc.numCats; i++)
  {
    // gets number of pound symbols (#) in assignment
    int numPnd = getNumPounds(grdDoc.cat[i].assName);

    printCat(outFile, grdDoc.cat[i], numPnd);
    fprintf(outFile, "\n");
  }
  fclose(outFile);
  for (int i = 0; i < grdDoc.numCats; i++)
  {
    free(grdDoc.cat[i].catName);
    free(grdDoc.cat[i].assName);
  }
  free(grdDoc.cat);
  free(endRows);
}

int *getEndRows(GradeDoc grdDoc)
{
  int *endRows = malloc((sizeof(int) * grdDoc.numCats) + 1);
  for (int i = 0; i < grdDoc.numCats; i++)
  {
    endRows[i] = grdDoc.cat[i].endRow;
  }
  return endRows;
}

int getTotalPnts(GradeDoc grdDoc)
{
  int totPnts = 0;
  for (int i = 0; i < grdDoc.numCats; i++)
  {
    totPnts += grdDoc.cat[i].numPnts * grdDoc.cat[i].numAsnmnts;
  }
  char totPoints[6];
  char charDrop = ' ';
  printf("\nIf the total points is not %d, enter the actual number now (otherwise type !). ", totPnts);
  for (int i = 0; i < 6; i++)
  {
    charDrop = getc(stdin);
    totPoints[i] = charDrop;
    if (charDrop == '!')
      return totPnts;
    if (charDrop == '\0' || charDrop == '\n')
      break;
  }
  totPnts = atoi(totPoints);

  return totPnts;
}

void printEndRows(FILE *outFile, char col, int *endRows, int size)
{
  for (int i = 0; i < size; i++)
  {
    fprintf(outFile, "%c%d", col, endRows[i]);
    if (i != size - 1)
      fprintf(outFile, ",");
  }
}

int getNumPounds(char *assName)
{
  int numPounds = 0;
  for (int i = 0; i < strlen(assName); i++)
  {
    if (assName[i] == '#')
      numPounds += 1;
  }
  return numPounds;
}

void printCat(FILE *outFile, Category cat, int numPnd)
{
  // print headers
  fprintf(outFile, "\n");
  fprintf(outFile, "%s", cat.catName);

  fprintf(outFile, ",Assignments");
  fprintf(outFile, ",Scores");
  fprintf(outFile, ",Total Points");
  fprintf(outFile, ",Percent");
  fprintf(outFile, ",Points Left");
  if (cat.numDrops > 0)
    fprintf(outFile, "/Drops");
  fprintf(outFile, "\n");

  // print rows
  for (int i = 1; i <= cat.numAsnmnts; i++)
  {
    printRow(outFile, i, cat, numPnd);
    fprintf(outFile, "\n");
  }

  // print total row
  fprintf(outFile, ",");
  fprintf(outFile, "Overall");

  fprintf(outFile, ",");
  fprintf(outFile, "\"=SUMIF(F%d:F%d,\"\"<>\"\"&\"\"Dropped\"\",C%d:C%d)\"",
          cat.strtRow + 1, cat.endRow - 1, cat.strtRow + 1, cat.endRow - 1);

  fprintf(outFile, ",");
  fprintf(outFile, "\"=SUMIFS(D%d:D%d,F%d:F%d,\"\"<>\"\"&\"\"Dropped\"\",C%d:C%d,\"\">=0\"\")\"",
          cat.strtRow + 1, cat.endRow - 1, cat.strtRow + 1, cat.endRow - 1,
          cat.strtRow + 1, cat.endRow - 1);

  fprintf(outFile, ",");
  fprintf(outFile, "\"=IF(D%d=0,\"\"\"\",C%d/D%d)\"", cat.endRow, cat.endRow, cat.endRow);

  fprintf(outFile, ",");
  fprintf(outFile, "=COUNT(D%d:D%d)*D%d-D%d-%d*D%d", cat.strtRow + 1, cat.endRow - 1, cat.strtRow + 1, cat.endRow, cat.numDrops, cat.strtRow + 1);
}

void printRow(FILE *outFile, int assNum, Category cat, int numPnd)
{
  fprintf(outFile, ",");

  // get starting number for hw
  int newStrt = getStrtNum(cat.assName);

  // prints assignment
  // for individual assignment inputs
  if (strlen(cat.assName) == 2 && cat.assName[0] == '*' && cat.assName[1] == '!')
  {
    char assNameIn[MAX_SIZE];
    printf("\nWhat is the name of assignment %d of the %s category? ", assNum, cat.catName);
    scanf("%s", assNameIn);
    for (int i = 0; i < strlen(assNameIn); i++)
    {
      if (assNameIn[i] == '_')
        assNameIn[i] = ' ';
    }
    fprintf(outFile, "%s", assNameIn);
  }

  // for general assignment inputs
  else
  {
    for (int i = 0; i < strlen(cat.assName); i++)
    {
      if (cat.assName[i] == '#' || cat.assName[i] == '!')
      {
        break;
      }
      if (cat.assName[i] == '_')
      {
        fprintf(outFile, " ");
      }
      else
      {
        fprintf(outFile, "%c", cat.assName[i]);
      }
    }

    if (numPnd > 0)
      fprintf(outFile, "%0*d", numPnd, assNum - 1 + newStrt);
  }
  // prints blank score column
  fprintf(outFile, ",,");

  // print total points
  fprintf(outFile, "%d", cat.numPnts);

  // prints percentage
  int rowNum = cat.strtRow + assNum;
  fprintf(outFile, ",\"=IF(ISBLANK(C%d),\"\"\"\",C%d/D%d)\"", rowNum, rowNum, rowNum);

  // prints whether dropped or not
  if (cat.numDrops > 0)
  {
    // prints if >= number of drops
    fprintf(outFile, ",\"=IF(COUNT(C%d:C%d)>=%d,", cat.strtRow + 1, cat.endRow - 1, cat.numDrops);

    // prints if cell isn't empty
    fprintf(outFile, "IF(NOT(ISBLANK(C%d)),", cat.strtRow + assNum);

    // prints if smallest value information
    for (int numDrop = 1; numDrop <= cat.numDrops; numDrop++)
    {
      printDrop(outFile, cat, numDrop, rowNum);
    }
    fprintf(outFile, "\"\"\"\"");
    for (int numDrop = 1; numDrop <= cat.numDrops; numDrop++)
    {
      fprintf(outFile, ")");
    }
    fprintf(outFile, ",\"\"\"\"),IF(COUNTBLANK(C%d:C%d)+COUNTA(C%d:C%d)<=%d",
            cat.strtRow + 1, cat.strtRow + assNum, cat.strtRow + 1, cat.strtRow + assNum, cat.numDrops);
    fprintf(outFile, ",\"\"Dropped\"\",\"\"\"\"))\"");
  }
}

int getStrtNum(char *assName)
{
  for (int i = 0; i < strlen(assName); i++)
  {
    if (assName[i] == '#')
    {
      for (int j = i + 1; i < strlen(assName); j++)
      {
        if (assName[j] != '*' && assName[j] != '#')
          return 1;
        if (assName[j] == '*')
        {
          if (j != strlen(assName) - 1 && assName[j + 1] == (int)assName[j + 1])
          {

            return atoi(&assName[j + 1]);
          }
        }
      }
    }
  }
  return 1;
}

void printDrop(FILE *outFile, Category cat, int numDrop, int rowNum)
{
  // prints if value equal to numDrop (1st, 2nd, etc) smallest value
  fprintf(outFile, "IF(C%d=SMALL(C%d:C%d,%d),", rowNum, cat.strtRow + 1,
          cat.endRow - 1, numDrop);

  // prints if total cells equal to numDrop smallest are below total drops left
  fprintf(outFile, "IF(COUNTIF(C%d:C%d,\"\"=\"\"&SMALL(C%d:C%d,%d)) < %d",
          cat.strtRow + 1, cat.endRow - 1, cat.strtRow + 1, cat.endRow - 1, numDrop, cat.numDrops);

  // adds if not smallest value
  for (int i = 1; i < numDrop; i++)
  {
    fprintf(outFile, "-COUNTIF(C%d:C%d,", cat.strtRow + 1, cat.endRow - 1);
    if (i > 1)
    {
      fprintf(outFile, "AND(");
      fprintf(outFile, "\"\"=\"\"&SMALL(C%d:C%d,%d),", cat.strtRow + 1, cat.endRow - 1, i);
      for (int j = 1; j < i; j++)
      {
        fprintf(outFile, "\"\"<>\"\"&SMALL(C%d:C%d,%d)", cat.strtRow + 1, cat.endRow - 1, j);
        if (j != i - 1)
          fprintf(outFile, ",");
      }
      fprintf(outFile, "))");
    }
    else
      fprintf(outFile, "\"\"=\"\"&SMALL(C%d:C%d,%d))", cat.strtRow + 1, cat.endRow - 1, i);
  }
  // dropped
  fprintf(outFile, ",\"\"Dropped\"\",");

  // prints if cells up to less than/equal to number of drops
  fprintf(outFile, "IF(COUNTIF(C%d:C%d,\"\"=\"\"&SMALL(C%d:C%d,%d)) <= %d",
          cat.strtRow + 1, rowNum, cat.strtRow + 1, cat.endRow - 1, numDrop, cat.numDrops);

  // adds if not smallest value
  for (int i = 1; i < numDrop; i++)
  {
    fprintf(outFile, "-COUNTIFS(C%d:C%d,", cat.strtRow + 1, cat.endRow - 1);
    if (i > 1)
    {
      fprintf(outFile, "\"\"=\"\"&SMALL(C%d:C%d,%d),", cat.strtRow + 1, cat.endRow - 1, i);
      for (int j = 1; j < i; j++)
      {
        fprintf(outFile, "C%d:C%d,", cat.strtRow + 1, cat.endRow - 1);
        fprintf(outFile, "\"\"<>\"\"&SMALL(C%d:C%d,%d)", cat.strtRow + 1, cat.endRow - 1, j);
        if (j != i - 1)
          fprintf(outFile, ",");
      }
      fprintf(outFile, ")");
    }
    else
      fprintf(outFile, "\"\"=\"\"&SMALL(C%d:C%d,%d))", cat.strtRow + 1, cat.endRow - 1, i);
  }

  // dropped
  fprintf(outFile, ",\"\"Dropped\"\",\"\"\"\")),");
}
