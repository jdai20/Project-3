//Code written by Alex J. Dai
//CS 107
//13 November 2018

//This program will create a 0 potential array of user defined size, left and 
//right potential values, and then insert a user defined number of charges within
//the array. Then the array will iterate until the field of array values achieves
//equilibrium.

#include <stdio.h>
#include <stdbool.h>
#include <math.h>

//Charge struct declaration
typedef struct Charge_struct{
	int indRow;
	int indCol;
	double strength;
}Charge;

//----------------------------------------------------------------------------------------------------

// printData2D: prints to screen 2D array
// *Note: sizeR is the #rows of useable data (the first index of data[][])
//        sizeC is the #cols of useable data (the second index of data[][])
// [in]: data[sizeR][sizeC]: array to be printed
// [out]: returns void: nothing returned, array is printed to screen
void printData2D(double data[100][100],int sizeR, int sizeC){
    int i, j;
	for(i = 0; i < sizeR; ++i){
		for(j = 0; j < sizeC; ++j){
			printf("%7.1lf ", data[i][j]);
		}
		printf("\n");
	}
}

// evolveField: adds values of set charges to the position input by the user
// *Note: sizeR is the #rows of useable data (the first index of data[][])
//        sizeC is the #cols of useable data (the second index of data[][])
//[in]: data[100][100]: array of potential values
//[in]: someCharges[sizeCharge]: 1D array of Charge type
//[out]: returns double: maximum difference between a point in the old array and evolved array
double evolveField(double data[100][100],int sizeR, int sizeC, Charge someCharges[], int sizeCharge){
    int i, j;
	double dataCopy[100][100] = {0.0};
	double maxDiff = 0.0;
	
	//creates copy of potential array before evolving
	for(i = 0; i < sizeR; ++i){
		for(j = 0; j < sizeC; ++j){
			dataCopy[i][j] = data[i][j];
		}
	}
	//evolving  top and bottom rows
	for(i = 0; i < sizeR; ++i){
		for(j = 1; j < sizeC-1; ++j){
			data[0][j] = (dataCopy[0][j-1] + dataCopy[1][j] + dataCopy[0][j+1]) / 3;
			data[sizeR-1][j] = (dataCopy[sizeR-1][j-1] + dataCopy[sizeR-2][j] + dataCopy[sizeR-1][j+1]) / 3; 
		}
	}
	//evolving middle rows
	for(i = 1; i < sizeR-1; ++i){
		for(j = 1; j<sizeC-1; ++j){
			data[i][j] = (dataCopy[i-1][j] + dataCopy[i+1][j] + dataCopy[i][j-1] + dataCopy[i][j+1]) / 4;
		}
	}
	//resets the input charges
	for(i = 0; i < sizeCharge; ++i){
		data[someCharges[i].indRow][someCharges[i].indCol] = someCharges[i].strength;
	}
	//compares new array to old array and finds max difference
	for(i = 0; i < sizeR; ++i){
		for(j = 1; j < sizeC-1; ++j){
			if(fabs(data[i][j] - dataCopy[i][j]) > maxDiff){
				maxDiff = fabs(data[i][j] - dataCopy[i][j]);
			}
		}
	}
	
	return maxDiff;
}

//calcAvg: calculates the average value of array
// *Note: sizeR is the #rows of useable data (the first index of data[][])
//        sizeC is the #cols of useable data (the second index of data[][])
//[in]: data[sizeR][sizeC]: array of potential values
//[out]: returns double: the average potential of all values in the array
double calcAvg(double data[100][100],int sizeR, int sizeC){
    int i,j;
	double sum = 0.0;
	
	for(i = 0; i < sizeR; ++i){
		for(j = 0; j < sizeC; ++j){
			sum += data[i][j];
		}
	}
	
	return sum / (sizeR*sizeC);
}

//findMaxCharge: reads Charge array and returns Charge element with max absolute strength
//[in]: SomeCharges[sizeCharge]: array of Charge to be checked
//[out]: returns Charge: the element within the struct array with the greates absolute strength
Charge findMaxCharge(Charge someCharges[], int sizeCharge){
   Charge max;
	int i;
	double maxStren;
	
	maxStren = fabs(someCharges[0].strength);
	max = someCharges[0];
	
	for(i = 0; i < sizeCharge; ++i){
		if(fabs(someCharges[i].strength) > maxStren){
			maxStren = fabs(someCharges[i].strength);
			max = someCharges[i];
		}
	}
	return max;
}

//----------------------------------------------------------------------------------------------------
int main() {
	
    int rows, cols;
    double leftP, rightP;
    int numIntQ;
    int i;
    double diff;
    //declares 1D charge array
    Charge intQ[1000];
    //Declares array of electrical potentials and initializes all values to 0
    double potentArr[100][100] = {0.0};
    Charge maxCharge;
    int counter = 1;
	
	//asks user for input
    printf("Enter # rows: ");
    scanf("%d", &rows);
    printf("Enter # columns: ");
    scanf("%d", &cols);
    printf("Enter left plate potential value: ");
    scanf("%lf", &leftP);
    printf("Enter right plate potential value: ");
    scanf("%lf", &rightP);
	
	//sets left and right columns to the user input values
	for(i = 0; i < rows; ++i){
		potentArr[i][0] = leftP;
		potentArr[i][cols - 1] = rightP;
	}
	
	//Sets the charges
    printf("\nEnter # of internal charges (sources of electric potential): ");
    scanf("%d", &numIntQ);
    
    //sets the points and values for each internal charge
    for(i = 0; i < numIntQ; ++i){
		//internal charge index number
		printf("\nFor source #%d\n", i+1);
		
		//charge position
		printf("Enter row index: ");
		scanf("%d", &intQ[i].indRow);
		//checks if charge location is within the array
		while(intQ[i].indRow > rows-1 || intQ[i].indRow < 0){
			printf("Enter row index: ");
			scanf("%d", &intQ[i].indRow);
		}
		
		printf("Enter column index: ");
		//checks if charge location is within the array and not on either end
		scanf("%d", &intQ[i].indCol);
		while(intQ[i].indCol >= cols-1 || intQ[i].indCol <= 0){
			printf("Enter column index: ");
			scanf("%d", &intQ[i].indCol);
		}
		//charge polarity and strength
		printf("Enter source strength: ");
		scanf("%lf", &intQ[i].strength);
	}
	//calling findMaxCharge
	maxCharge = findMaxCharge(intQ, numIntQ);
	printf("Charge at row = %d and column = %d has potential strength = %0.1lf\n", maxCharge.indRow, maxCharge.indCol, maxCharge.strength);
	
	//sets charges in their respective postitions
	for(i = 0; i < numIntQ; ++i){
		potentArr[intQ[i].indRow][intQ[i].indCol] = intQ[i].strength;
	}
	//2D array of electric potentials
	printf("Initial Potential Field: \n");
	//printing initial array of potentials
	printData2D(potentArr, rows, cols);
	//prints average potential of initial array
	printf("The average potential is: %lf\n\n", calcAvg(potentArr, rows, cols));
	
	//iterating array once
	printf("Iteration step #%d:\n", counter);
	diff = evolveField(potentArr, rows, cols, intQ, numIntQ);
	printf("Max Diff = %lf\n", diff);
	//printing evolved array
	printData2D(potentArr, rows, cols);
	//printing average potential
	printf("The average potential is: %lf\n\n", calcAvg(potentArr, rows, cols));
	
	//iterating until 100 iterations or convergence
	while(diff > 0.0001){
		diff = evolveField(potentArr, rows, cols, intQ, numIntQ);
		++counter;
		if(counter == 100){
			printf("Iteration step #%d:\n", counter);
			printf("Max Diff = %lf\n", diff);
			//printing evolved array
			printData2D(potentArr, rows, cols);
			//printing average potential
			printf("The average potential is: %lf\n\n", calcAvg(potentArr, rows, cols));
		}
	}
	if(counter < 100){
		for(i = counter; i <= 100; ++i){
			diff = evolveField(potentArr, rows, cols, intQ, numIntQ);
		}
		printf("Iteration step #%d:\n", i-1);
		printf("Max Diff = %lf\n", diff);
		//printing evolved array
		printData2D(potentArr, rows, cols);
		//printing average potential
		printf("The average potential is: %lf\n\n", calcAvg(potentArr, rows, cols));
	}
	printf("Iteration step #%d:\n", counter);
	printf("Max Diff = %lf\n", diff);
	//printing evolved array
	printData2D(potentArr, rows, cols);
	//printing average potential
	printf("The average potential is: %lf\n\n", calcAvg(potentArr, rows, cols));
	printf("The potential field converged after %d iterations\n", counter);
	
	for(i = 0; i < numIntQ; ++i){
		printf("%d, %d, %0.1lf\n", intQ[i].indRow, intQ[i].indCol, intQ[i].strength);
	}
	
	return 0;
}
