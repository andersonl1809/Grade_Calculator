# Grade_Calculator
Generates a grade calculator spreadsheet as needed

![Full Sheet](https://user-images.githubusercontent.com/97125918/148138655-cf14abb9-61ad-4560-a063-5e986845975a.png)


If you want to run the code yourself, this should explain how to generate a grading excel sheet either for yourself or to share.  To begin with, the code will likely seem very poor in a lot of ways, and it definitely has consistency issues, but for the purposes of something small like this, it should serve well enough.  It also definitely has some memory issues which I will likely address at some point in the future, but it shouldn't affect anything significantly.  Without further ado, here is an overly detailed explanation of how to use this.

## Running the Code 
### Using a Makefile
To run this as intended, it will make use of a Makefile, but I will include a version that does not require this if you'd prefer that.

1. Copy the repository onto your personal device or to a location where you can run gcc and/or make.
2. In the Makefile, under the build target (line 17), change the name of the file to be whatever is desired (make sure to keep it as a .csv file).
3. Run `make build` in the command window to run the program.

### Running without Makefile
If make is not installed on your local machine, but gcc is, this should work as well.

1. Copy the repository onto your personal device or to a location where you can run gcc and/or make.
2. In your terminal, run the command `gcc -std=c99 -g -Wall -Wshadow --pedantic -Wvla -Werror main.o grade.o grade.h -o gradeCalc` which should create an executable by the name of gradeCalc.
3. Run the command `./gradeCalc [filename].csv` where filename is whatever you want the name of the file to be (keep it as a .csv file) to run the program.


### Inputs
You will be prompted for a series of inputs.
1. How many categories are there?
   - Include all unique categories (example: if homework, exams and extra credit are the only 3 types of grades used (all extra credit can fall under one category or you can separate them if you choose), there would would be 3 unique categories).
2. Are categories weighted by points (`P`) or percent (`%`)?
   - Most of the time, categories are weighted via percent, so just type `%` (example: Homework: 15%, Exams: 40%, Group Project: 10%, Final Exam: 30%, Peer Reviews: 5%).
   - Sometimes, categories are weighted via points (written as a capital `P`) (I would avoid this unless you need to use it because it may need some revisions. Example: Homework: 100 points, Exams: 200 points, Quizzes: 130 points).

#### For each unique category:
- **What is the name of category _#_?**
   - If for whatever reason, the number of characters of this name is larger than 20, you can adjust the max size by changing it in line 6 of the *grade.c* file.
- **How many assignments are there in [_category name_]?**
   - This should be relatively straight forward, but if including extra credit in one category, be sure to include total number of extra credit assignments.
   - Enter as a number.
- **How many points are there for each assignment?**
   - When a grade is put in the gradebook, it is often #/# and a percentage is also displayed.  If using `%` weighting, you can either enter the number of points each is worth or just enter 100 so the percent grade achieved can be entered directly. Example: Homeworks are each out of 5 points, so I can put 5 points for this or 100 if I just want to enter the percent earned.  2/5 would be equivalent to 40/100.
   - Enter as a number.
- **What are the names of the assignments?**
   - While the category may be something like Homework, the assignment names are more like it's written in the gradebook (Example: `HW1` or `HW01` or `HW 1`).
   - To name it, a `#` symbol must be included to represent the number for each assignment (Example: `HW_#` if the desired outputs are `HW 1`, `HW 2`, `HW 3`, etc.)
   - If a preceding 0 is used such as in `HW01`, use 2 `#` symbols (Example: `HW##` if the desired outputs are `HW01`, `HW02`, `HW03`, etc.)
   - If there is no numbering desired for this category at all, use `!` in place of a `#` symbol (Example: `HW!` would make all assignment names `HW`.  Additonally, using exclusively `!` will result in no names for any assignment in this category).
   - If you want to type out the individual names of the assignments for this given category, type `*!`
   - If the starting assignment isn't 1, you can alter the starting number by adding a `*` and then adding a number to correspond with it (Example: `HW_#*0` which will display `HW 0`, `HW 1`, `HW 2`, etc.)
- **(If % weighting) What is the weight of this category?**
   - Enter the weighting of this specific category (Example: If homework is 15% of the total grade, enter 15).
   - Be sure the categories all together add to at least 100%. For extra credit, simply enter the total additional percent possible with all extra credit combined.
   - Enter as a number.
- **How many of these assignments are dropped?**
   - If a certain number of drops are guaranteed to occur, enter that here.
   - Enter as a number.

3. (If individual assignment names) What is the name of assignment `#` of the [*category name*] category?
   - Name the individual assignment here. 
4. (If P weighting) If the total points is not #, enter the actual number now (otherwise type !).
   - Enter either as a number or just `!`
5. A .csv file as named will now be created.

## Excel File
Because what is being created is a csv file and not an actual excel file, the actual formatting needs to be done in the file itself.  How you ultimately choose to format your excel file is ultimately up to you, but I will list what I like to do here in case you want to follow it.  While this may seem needlessly tedious, I think it makes the sheet significantly more readable and aethetically pleasing.

1. If you don't have the repository saved to your actual machine, download the csv file produced onto your machine.
2. Open the .csv file and save as an excel file (.xlsx).

![Save as Excel](https://user-images.githubusercontent.com/97125918/148143762-041c11e6-f1c5-400a-841c-7adbdebbae48.png)

3. Click the top left corner of the table itself (just above row one and to the left of column A) to highlight the entire table.
4. Under the Home tab, within the "Cells" section, click Format -> `Autofit Column Width`.

![Autofit Column Width](https://user-images.githubusercontent.com/97125918/148144237-13a0c92a-00fa-4fba-8e94-9823c7aaa415.png)

5. Align everything to the center under the Home tab in the Alignment section.

![Center Alignment](https://user-images.githubusercontent.com/97125918/148144419-9458bc5f-9088-4060-9e96-3187932bfe67.png)

6. Holding ctrl (if a windows user) to select multiple cells, select D2, F2, G2 and E3. Once E3 is selected, release ctrl, hold shift and then click the bottom cell in column E.

![Percent Cells](https://user-images.githubusercontent.com/97125918/148144841-94342b95-9d79-4bdb-83c1-9e10aef0e5a9.png)

7. Once those cells are selected, click the `%` symbol under the Home tab in the Number section.

![Percent](https://user-images.githubusercontent.com/97125918/148144970-fb031b77-cb54-4017-85f7-191c4f945a46.png)

8. For each category, there should be a single cell filled in column A. Highlight all cells in column A next to this category and then click `Merge & Center` under the Home tab in the Alignment section.
 
![Category Names](https://user-images.githubusercontent.com/97125918/148145450-348a4e66-44b1-4901-a403-19e42a770886.png)

9. Highlight all of column A and rows 1 and 2 and bold all of these cells with `CTRL + B` (if windows user).

![Cells to Bold](https://user-images.githubusercontent.com/97125918/148146050-9fe97623-3de0-4f70-a96e-f898f85f8c91.png)

10. Now, highlighting just the first column, underline these cells with `CTRL + U` (if windows user).

![Cells to Underline](https://user-images.githubusercontent.com/97125918/148146173-935a03ec-f1ee-4165-9f66-85eb6fc4b007.png)

11. Highlight cell D2 using the highlighting tool under the Home tab in the Font section.

![Highlight](https://user-images.githubusercontent.com/97125918/148146405-29a8e7e3-1748-46c6-a1a2-ef4ebf96f47c.png)

12. Highlight each individual category and choose a table formatting style (I chose the first option) under the Home tab, in Styles, listed as `Format as Table`. When prompted as to whether the table has headers, this option should be selected at default so simply click `OK`.

![Create Table](https://user-images.githubusercontent.com/97125918/148146704-0c75b0aa-d728-4c11-b345-d805e832c2bd.png)

13. While each full table is still selected, change the border type to `Outside Borders` under the Home tab, in Font -> Border.

![Outer Border](https://user-images.githubusercontent.com/97125918/148147317-ade7b72f-ba54-4e62-aee7-e10fa75ff92a.png)

14. Highlight the last row of each table and add a top border by clicking `Outside Border` in the same location as step 13.  Then, bold these cells with `CTRL + B` (if windows user).  Then, highlight to a color contrasting color such as green using the same highlighting tab as described in step 11.

![Overall Row](https://user-images.githubusercontent.com/97125918/148147763-7dfade58-f338-415e-bb05-694253e3e411.png)

15. Clicking on any cell in a table should pull up the Table Design tab. Click this and then click to disable `Filter Button`.

![Disable Filter](https://user-images.githubusercontent.com/97125918/148146954-e66fb17b-a633-4db5-9e8a-2a74195a4623.png)

The final results should look something like this:

![FinalSheet](https://user-images.githubusercontent.com/97125918/148147953-354c27c9-1bae-4ac0-b614-4a5e54fc223f.png)

Simply enter your scores and the excel will do the rest of the work.

# To Do
- [x] Make question for assignment names more intuitive
- [x] Add option for inserting individual assignment names if desired (perhaps if just ! is used)
- [x] Create consistency in getting inputs (input verification)
- [ ] Add option for inserting individual assignment point values/percent if desired
- [ ] Fix memory issues
- [ ] Ensure points works properly
- [ ] Include optional drops
- [ ] Include option to reenter if number/name entered incorrectly
- [ ] Include potential example output for double checking
- [ ] Include excel file option for input
- [x] Make sure csv file is input
- [x] Break up input into individual functions
