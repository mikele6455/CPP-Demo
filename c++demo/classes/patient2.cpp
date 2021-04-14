#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Patient //class to organize varibles and information
{
	private: string name;
		 int    days;
		 float  medication;
		 float  procedure;
		 float  consult;
	
	public:  void   setName(string n)          {name = n;} //function to access private variables
		 string getName()                  {return name;} //function to return private variables

		 void   setDays(int d)             {days = d;}
		 int    getDays()                  {return days;}
		 
		 void   setMedicationCost(float m) {medication = m;}
		 float  getMedicationCost()        {return medication;}
		 
		 void   setProcedureCost(float p)  {procedure = p;}
		 float  getProcedureCost()         {return procedure;}
		 
		 void   setConsultCost(float c)    {consult = c;}
		 float  getConsultCost()           {return consult;}
		
		 Patient() {name = ""; days = 0; medication = 0; procedure = 0; consult = 0;} //default constructor to initialize varible values

		 Patient(string n, int d, float m, float p, float c) 
		 {name = n; days = d; m = medication; p = procedure; c = consult;} //non-default constructor to set varible values
		 
		 float calculateFinalBill() //function to calculate final bill using class variables
		 {return medication + consult + procedure + (days * 50);} 
		 
		 ~Patient() {cout << "I'm deallocated" << endl;} //deconstructor
};


int main()
{
	string name;
	int days;
	float medication, consult, procedure;
	Patient foo; //temporary varible used to store information into vecotr
	vector<Patient> bills; //vector to store information
	int i, size;
	
	cout << "How many patients today?: " << endl;
	cin >> size; //loop duration input
	cin.ignore();

	for (i=0;i<size;i++) //loop to accquire input for information
	{
		cout << "Enter patient name: " << endl;
		getline(cin, name); 
		cout << "Enter patient days: " << endl;
		cin >> days;
		cout << "Enter patient medication cost: " << endl;
		cin >> medication;
		cout << "Enter patient procedural cost: " << endl;
		cin >> procedure;
		cout << "Enter patient consulting cost: " << endl;
		cin >> consult;
		cin.ignore();

		foo.setName(name); //appending class information into temporary variables
		foo.setDays(days);
		foo.setMedicationCost(medication);
		foo.setProcedureCost(procedure);
		foo.setConsultCost(consult);

		bills.push_back(foo); //pushing information stored on variable into vector
		cout << "The vector is currently: " << bills.size() << endl;//displays current vector size
	}

	for(i=0;i<bills.size();i++) //print out information of all stored variables
	{
		cout    << bills[i].getMedicationCost() << "\n" 
			<< bills[i].getProcedureCost()  << "\n"
		       	<< bills[i].getConsultCost()    << "\n"
			<< bills[i].getDays()           << "\n";

		cout    << "The final bill for " << bills[i].getName() << " is: " << bills[i].calculateFinalBill() << endl; //calculate final bill for each patient in vector
	}
	return 0;
}

