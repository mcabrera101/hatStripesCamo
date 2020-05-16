#include<iostream>
#include<string>
using namespace std;


void enterData();

int main()
{
	int num = -1;
	cout<<"Starting Up..."<<endl;
	while(num != 0)
	{
		if(num != -1){enterData();}
		cout<<"Enter an option:\n0:End\n1:Input Data\n->";
		cin>>num;
	}	
	cout<<"Adios!"<<endl;
	return 0;
}

void enterData()
{
	long mSize = 0;
	cout<<"Memory size> ";
	cin>>mSize;
	long pSize = 0;
	cout<<"Page Size (1: 100, 2: 200, 3: 400)> ";
	cin>>pSize;
	cout<<"Processing..."<<endl;			//THIS STEP needs to be modified.	
}
