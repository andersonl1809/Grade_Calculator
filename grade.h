#ifndef GRADE_H
#define GRADE_H

#include <stdbool.h>
#include <stdio.h>

// Type of weighting present
typedef enum WeightType
{
  Points = 'P',
  Percent = '%'
} WeightType;

// Actual weight values themselves
typedef union Weighting
{
  int pnts;
  float prcnt;
} Weighting;

// Category of grading
typedef struct Category
{
  char *catName;       // category name
  int numAsnmnts;      // number of assignments
  int numPnts;         // number of points per assignment
  char *assName;       // assignment name
  int strtRow;         // starting row in excel
  int endRow;          // ending row in excel
  Weighting weightVal; // value based on weight type
  int numDrops;        // number of assignments dropped
} Category;

// Struct to hold categories
typedef struct GradeDoc
{
  Category *cat;     // categories held
  int numCats;       // number of categories
  WeightType wtType; // type of weighting
} GradeDoc;

// builds an individual category
Category *buildCategories(int numCats);

// calculates a power if power is an integer
long double powrInt(float x, int y);

// gets all inputs necessary to generate excel
GradeDoc getInputs();

// general input function
void inputFunc(void (*f) (GradeDoc*,int));
/*



*/
// individual input functions

// gets number of categories
void getNumCats(GradeDoc *grdDoc);

// gets type of weighting present
void getWtType(GradeDoc *grdDoc);

// gets name of category
void getCatName(GradeDoc *grdDoc, int catNum);

// gets number of assignments
void getAssNum(GradeDoc *grdDoc, int catNum);

// gets number of points per assignment
void getNumPnts(GradeDoc *grdDoc, int catNum);

// gets assignment names
void getAssName(GradeDoc *grdDoc, int catNum);

// gets weighting value
void getWeightVal(GradeDoc *grdDoc, int catNum);

// gets number of assignment drops
void getDrops(GradeDoc *grdDoc, int catNum);
/*



*/
// checks whether assignment names is valid
bool checkAssName(char *ass);

// constructs excel file
void buildExcel(GradeDoc grdDoc, char *excelFile);

// gets integer array of end rows
int *getEndRows(GradeDoc grdDoc);

// gets total points when points are weight
int getTotalPnts(GradeDoc grdDoc);

// prints end rows with specified column
void printEndRows(FILE *outFile, char col, int *endRows, int size);

// gets number of pound symbols
int getNumPounds(char *assName);

// prints entire categories
void printCat(FILE *outFile, Category cat, int numPnd);

// prints category row
void printRow(FILE *outFile, int assNum, Category cat, int numPnd);

// gets starting number for category
int getStrtNum(char *assName);

// prints all parts of drop code
void printDrop(FILE *outFile, Category cat, int numDrop, int rowNum);

// frees entire GradeDoc struct
void freeGrdDoc(GradeDoc * grdDoc);

#endif