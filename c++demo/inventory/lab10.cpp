#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>

using namespace std;

class Inventory
{
	public:
		string getName(){return name;}
		float getPrice(){return price;}
		int getQty(){return qty;}
		void setName(string name){this->name = name;}
		void setPrice(float price){this->price = price;}
		void setQty(int qty){this->qty = qty;}
		static void updateMax(int qty){
			if (qty > maxItem)
				maxItem = qty;}
		static int getMax(){return maxItem;}
		friend void applyDiscount(Inventory &foo, float dis);
		Inventory(){name = ""; price = 0; qty = 0;}
		Inventory(string name, float price, int qty){this->name = name; this->price = price; this->qty = qty;}
	private:
	        string name;
		float price;
		int qty;
		static int maxItem;

};

int Inventory::maxItem = 0;
void applyDiscount(Inventory &foo, float dis);
int main()
{
	ifstream inFile;
	ofstream outFile;
	outFile.open("results.txt");
	inFile.open("Inventory_worksheet.txt");
	string readBuffer;
	getline(inFile, readBuffer);
	outFile << setw(10) << "Name" << setw(10) << "Price" << setw(10) << "Quantity" << "\n";


	Inventory foo;
	vector<Inventory> stock;
	string name;
	float price;
	int qty;
	float dis = 0.20;
	while (inFile >> name)
	{
		inFile >> price >> qty;

		foo.setName(name);
		foo.setPrice(price);
		foo.setQty(qty);
		
		Inventory::updateMax(qty);
		applyDiscount(foo, dis); 
		stock.push_back(foo);
	}
	
	for (int i=0;i<stock.size();i++)
	{
		outFile << setw(10) << stock[i].getName() << setw(10) << stock[i].getPrice() << setw(10) << stock[i].getQty() << "\n";
	}


	cout << "The current maximum item quantity is: " << Inventory::getMax() << endl;

	return 0;
}

void applyDiscount(Inventory &foo, float dis)
{
	
	foo.price = foo.price - (foo.price * dis) ;
}
