#include <iomanip>
#include <iostream>
#include <fstream>
#include <cmath>

//array size is dependent on the question being answered

using namespace std;

typedef double baking[11][11]; //defining array type

//function prototypes
void init_block(baking &block); //function to initialize 2d array to zero
void set_boundary(baking &block, int temp); //function to set boundary of 2d array to temperature
void print_block(baking &block, float avg); //function to print out current iteration of the heat flow sim
double average_temp(baking &block); //finding the average of all cells
void update_cells(baking &block); //updating cell temperatures 
bool zero(baking &block); //finding the iteration that the center cell is zero

int main()
{
	int sides, temp; //heat sink size variable and temperature varible
	bool zeroGot = false; //variable to confirm finding the zero
	int zeroit, above = 0; //varible to store interation that found zero and iteration that is above required temperature
	long long int iteration = 0; //interation counter
	double average = 0.0; 

	cout << "Enter the size: " << endl;
	cin >> sides;
	
	baking oven;

	cout << "Enter temperature: " << endl;
	cin >> temp;

	init_block(oven);
	set_boundary(oven, temp);
	
	average = average_temp(oven);
	print_block(oven, average);

	for (iteration = 0; average < temp; iteration++) //loop to check and store all required information for test
	{
		update_cells(oven);
		average = average_temp(oven);
		if (!zeroGot){
			zeroGot = zero(oven);
			if (zeroGot)
				zeroit = iteration;
		}
		if (above == 0 && average > 60)
			above = iteration;
		if (sides <= 11)
			print_block(oven, average);
	}
	//displaying results on console
	cout << "Completed in: " << iteration << " iterations" << endl;
        cout << "Zero got in: " << zeroit << endl;
	cout << "Above temp in: " << above << endl;	
			
	return 0;
}

//functions declarations

void init_block(baking &block) //loop to set all array values to zero
{
	for (int i=0;i<11;i++){
		for (int j=0;j<11;j++){
			block[i][j] = 0;
		}
	}
}

void set_boundary(baking &block, int temp) //algorithm to set all boundary cells to the desired temperature
{
	for (int i=0;i<11;i++){
		for (int j=0;j<11;j++){
			if (i==0||j==0||i==11-1||j==11-1)
				block[i][j] = temp;
		}
	}
}

void print_block(baking &block, float avg) //printing and appending the simulation to a new text file
{

	//int append = 0;
	ofstream outFile;
	//if (append == 0)
	//	outFile.open("simulation_results.txt");
	//else
	outFile.open("simulation_results.txt", fstream::app);
	
	outFile << fixed << setprecision(2) << "\n\n";

	for (int i = 0; i < 11; i++) {
		for (int j = 0; j < 11; j++) {
			outFile << setw(10) << block[i][j];
		}
		outFile << "\n\n";
	}
	outFile << "Average temperature: " << avg << endl; //appending the current average temperature of the whole sink
	//append++;
	outFile.close();
}

double average_temp(baking &block) //calculating the current average temperature
{
	double avg = 0;
	for (int i=0;i<11;i++){
		for (int j=0;j<11;j++){
			avg += block[i][j];
		}
	}
	
	avg /= pow(11,2);
	return avg;
}	

void update_cells(baking &block) //coping array values into a temporary array in order to calculate temperature then coping it back into original array
{
	baking tempoary;
	for (int i=0;i<11;i++){
		for (int j=0;j<11;j++){
			tempoary[i][j] = block[i][j];
		}
	}
	
	double fourAvg = 0.0;

	//Set to 1 to ignore boundary cells this took way too long to figure out
	for (int i=1;i<11-1;i++){
		for (int j=1;j<11-1;j++){
			fourAvg = (block[i-1][j] + block[i+1][j] + block[i][j-1] + block[i][j+1]) /4.0;
			tempoary[i][j] = fourAvg;
		}
	}

	for (int i=0;i<11;i++){
		for (int j=0;j<11;j++){
			block[i][j] = tempoary[i][j];
		}
	}
}


bool zero(baking &block) //returning boolean value to determine if zero has been found or not
{
	float zeroBlock = block[11/2][11/2];
	if (zeroBlock == 0.0){
		if (block[11/2 - 1][11/2] !=0.0){
			return true;
		}
	}
	return false;
}
