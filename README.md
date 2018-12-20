# Project-3

Electric Potential Fields

Introduction and Motivation
This project focuses on creating two-dimensional electric potential fields (also called voltages) from a user inputted set of electric charges, which are sources of electric potential. You may have some experience with the physics of electricity already, or perhaps you are looking forward to your introduction to electromagnetism physics class in the near future. Whereas knowledge about the physics of electric potential fields will not be required to complete the tasks of this project, you may find that a short investigation on subject may spur your interest and provide inspiration for the coding tasks that follow. A quick internet search or perusal through a physics textbook will provide much of the nitty-gritty details, so instead you are directed to the following interactive simulation, Phet Simulations, where you can place your own charges in space and visualize the electric potential fields. We will use the simulation in-class to make a few fields that we can reproduce with our C code.

Program Objective
The main purpose of the project is to create a two dimensional electric potential field based on a configuration of electric charges inputted by the user. The electric potential field should be stored in a 2D array, where each element represents a point in 2D space that has an electric potential (or voltage) value associated with it. The user will specify the following:

the size of the electric potential field (i.e. number of rows and columns for the 2D array)
the value of the potential field on the left and right edges of the domain (i.e. first and last columns of the array), which represent electrically charged plates
the number of internal sources of electric potential, also called electric charges. For each source, the user also must specify the following:
the row and column of the array where the source is located, and
the value of the electric potential for the source (which fixes the value of the electric potential at the specified location in the array)
From all of this user-specified information, the full 2D electric potential field (i.e. the value of the potential at all array locations) must be determined through an iterative process, which is described as follows:

Begin with an electric potential field that is zero everywhere.
Set the value of the electric potential at locations in the array that are fixed, which include the following:
the first and last columns (left and right edges of the domain) are set by the user
the internal sources of electric potential also set by the user
Now it is time to evolve the field, where elements of the array are updated using the information stored in the neighboring elements [NOTE: Make sure to use the old (i.e. not-yet-updated) potential values when calculating the the average of the neighbors, which is most easily done by creating a copy of the array before updating.]:
the potential at interior points (not on an edge or corner) is updated as the average potential value of its four neighbors (up, down, left, and right).
the points on the top and bottom edge of the domain (first and last row) are updated as the average potential value of only three of its neighbors (left, right, and up OR down), since one of its neighbors is outside of the array.
all points where the potential is fixed by user specifications in #2 should not be updated.
Finally, repeat the evolution step #3 until the potential field is converged, which means that it stops changing from one iteration to the next. In practice, the field never fully stops changing, but, instead, the changes get smaller and smaller as the iterations continue. For the purposes of this project, a converged potential field is defined as one where the maximum absolute difference between the old and new potential field during the previous evolve step is less than 0.0001.
Programming Tasks
Level 0
[50 pts - all test cases visible]

Properly format all output printed to the screen, as shown below. Even if you are not able to produce the correct numbers for the later tasks, at this stage you should focus on proper formatting of the printf() statements. This should give a nice overall structure to you main() function, to which you will add more functionality as you move forward with the coding tasks. Note: beyond this Level 0 task, the remainder of the output of your code must be variables printed with proper formatting as a result of your programming; that is, OUTPUT BEYOND THESE BASIC PRINT STATEMENTS CANNOT BE HARDCODED just to pass test cases.
Enter # rows: 
Enter # columns: 
Enter left plate potential value: 
Enter right plate potential value: 

Enter # of internal charges (sources of electric potential):

For source #
Enter row index: 
Enter column index: 
Enter source strength: 

Initial Potential Field:

Iteration step #
Max Diff =

The potential field converged after
The average potential is: 
Level 1
[25 pts - all test cases visible or show as much detail as possible]

All of the following should be done in main() unless otherwise specified:

Read in the user input for the Level 0 prompts, including number of rows and columns for the array, left and right edge potential values, number of internal charges, and row, column, and strength for EACH internal charge.

Define a new struct type called Charge. The subitems include two integers, indRow and indCol, which represent the row and column index in the array where the charge is located, and a double strength, which represents the fixed potential value associated with the charge.

Create a 1D array of elements, where each element is of type Charge . The number of Charge elements in the 1D array is set by the user when they enter the number of internal charges. The subitems for each element of the 1D Charge array should be assigned with the user input.

Create the initial 2D electric potential array. Initialize all elements to zero. Then, assign the appropriate elements to their fixed values based on user input (see #2 in the Programming Objectives list above).

Write the printData2D() function, which takes in a 2D double array and two integer size parameters that represent the number of rows and columns of the array that store usable values. The function should print the values of the array using the format "%7.1lf " (this reserves 7 spaces for a floating point number, with one space after the decimal point), which makes it easier to interpret patterns in the printed potential field. An example for a 5x5 array is given:

    0.0    16.7    25.6    16.7     0.0 
    0.0    24.4    43.6    24.4     0.0 
    0.0    37.2   100.0    37.2     0.0 
    0.0    24.4    43.6    24.4     0.0 
    0.0    16.7    25.6    16.7     0.0 
Call printData2D() in main() to print the initial potential array with the nice, easy-to-interpret formatting.

Write the evolveField() function, which takes in a 2D double array data[][] and its two integer size parameters AND a 1D Charge array along with an integer for its size. The function should evolve data based on the rules detailed in #3 of the Programming Objectives list above. The function should implicitly return the evolved data array (remember that arrays are passed by pointer). The function should explicitly return the absolute maximum difference between the old (input) and updated (evolved) data arrays.

Call evolveField() in main() to evolve the potential field one step. Print the returned quantity from evolveField() to the screen, for example "Max Diff = 0.746742". Then, print the updated potential array to screen using printData2D().

write the calcAvg() function, which takes in a 2D double array data[][] and its two integer size parameters. The function should calculate and return the average value over all array elements.

Modify printData2D() to also print out the average value of the array by calling your calcAvg() function. A sample output is:

   10.0    20.9    27.2    10.9   -10.0 
   10.0    25.4    50.0    15.4   -10.0 
   10.0    20.9    27.2    10.9   -10.0 
The average potential is: 13.925127
Level 2
[15 points, some test cases visible]

Iterate the process of updating the potential field exactly 100 times [by repeatedly calling evolveField() from main()]. Print the potential field after 100 iterations (i.e. 100 evolve update steps).
Write the findMaxCharge() function, which takes in a 1D array of elements with Charge type and an integer for the size of the array. The function should find the Charge in the array with the greatest absolute strength and return that entire Charge element.
In main(), after the user has entered all input quantities and the array of Charges has been filled, call findMaxCharge() and print the returned Charge using the following format: "Charge at row = 5 and column = 4 has potential strength = 100.0".
Level 3
[10 points, all test cases hidden]

Instead of iterating a fixed number of evolve steps, continue iterating until a converged field is achieved as described in #4 of the Programming Objectives list above. [Note: make sure to iterate at least 100 steps so that the Level 2 Tasks are still passed.]
Print the converged potential field, the average potential value of the converged field, and the number of iterations required to achieve the converged field. Here is a sample output:
Iteration step #129:
Max Diff = 0.000091
  100.0    83.5    68.3    56.8    52.9    51.7    48.7    39.5    27.3    13.8     0.0 
  100.0    82.2    64.6    49.2    50.3    53.5    55.0    42.6    28.5    14.2     0.0 
  100.0    80.8    58.8    25.0    45.6    56.9    75.0    47.5    29.7    14.5     0.0 
  100.0    82.2    64.6    49.2    50.3    53.5    55.0    42.6    28.5    14.2     0.0 
  100.0    83.5    68.3    56.8    52.9    51.7    48.7    39.5    27.3    13.8     0.0 
The average potential is: 49.079746
The potential field converged after 129 iterations
Do not allow the user to enter charge locations that are not in the array. If the user enters an invalid row or column index number, continue requesting another input until a valid number is entered.
Level 3+
[up to 10 extra credit points]

Choose a set of inputs to your liking with many internal charges, but uncharged plates (I think it looks best with both left and right plates set to zero potential), and create a visualization of the converged electric potential field using shades of blue and red to represent potential values less than and greater than zero, respectively, where the higher magnitude potential values have a deeper color. This requires you to take the final potential field printed out at the end of your program and process the data outside of zyBooks or any other C programming environment. I was able to make the pictures shown in class in Excel, using conditional formatting. To receive the full extra credit points, you need to submit your work to Blackboard (look for Project 3 Extra Credit) as a single .pdf document with the following:
the potential field array from your program output
the colored visualization of your potential field using external software
a screenshot of a comparable charge configuration using the Phet Simulations with the electric potential (voltage) field shown and a nice collection of equipotential (green) lines.
Grading
[200 points total]

100 points: auto graded test cases (110 points possible with Extra Credit)

50 points: closer inspection of program functionality.
these points will be awarded for significant progress at developing code that ended up non-functional (i.e. not passing the test cases). Your code must compile, run, and pass lower-level tasks, but any unsuccessful efforts at achieving higher-level tasks will be rewarded here.

hardcoding output to match test case output for Levels 1, 2, or 3 is not allowed and will result in -50 points for this grade component.

50 points: formatting and style, 10 points for each of the following (see piazza post @10 for more details):
meaningful identifier names (variables and functions): you must define and call at least one additional function beyond what is provided in the template

comments: short description stating the purpose of each block of code in main() and each function (reword the provided comments in your own words)

variable declaration & initialization: valid types, proper initializing, no additional global variables beyond those provided in the template, etc.

code layout: nested levels with proper indentation

program header: must include overall goal of program, author, class, and date
