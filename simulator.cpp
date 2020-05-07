#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class Process{
public:
    //Information obtained from workload file
    int processID;
    int arrivalTime;
    int lifetime;
    int memoryRequirement;

    int memoryAdmissionTime;
    int completionTime;
};

const int MAX_MEMORY_SIZE = 30000;
int memorySize, pageSize, numberOfProcesses;
string fileName;
vector<Process> processList;

//Gets user input for memory size and page size
void getInput(){
  cout << "Enter memory size(0-30000): ";
  cin >> memorySize;
  cout << "Enter page size: ";
  cin >> pageSize;

  if(memorySize<0 || memorySize>MAX_MEMORY_SIZE )
  {
    cout<<"Error: Invalid input for memory size"<<endl;
    getInput();
  }
  else if(pageSize<=0){
    cout<<"Error: Invalid input for page size"<<endl;
    getInput();
  }
  else if(memorySize % pageSize != 0){
    cout<<"Error: Invalid input. Given page size does not evenly divide given memory size"<<endl;
    getInput();
  }
}

//Obtains information from a workload file for each process
void assignProcesses() {
	cout << "Enter the name of the workload file: ";
	cin >> fileName;

	ifstream myFile;
	myFile.open(fileName);

	if(!myFile){
		perror("Failed to open file. Please try again.");
		assignProcesses();
	}

	if (myFile.is_open()) {
		//Get number of processes
		myFile >> numberOfProcesses;

		processList.resize(numberOfProcesses);

		for (int i = 0; i < numberOfProcesses; i++) {
			//Get process ID
			myFile >> processList[i].processID;

			//Get arriving time and life time
			myFile >> processList[i].arrivalTime >> processList[i].lifetime;

			//Get memory requirement
			int piecesOfMemory = 0;          //Number of memory pieces; we need to sum those piecces
			int temp;                        //Holds the value of a memory piece
			int memoryRequirement = 0;       //Equal to the sum of our memory pieces

			myFile >> piecesOfMemory;
			for (int j = 0; j < piecesOfMemory; j++) {
				myFile >> temp;
				memoryRequirement += temp;    //Adds the value of a piece to the memory requirement
			}
			processList[i].memoryRequirement = memoryRequirement;
		}
	}
	myFile.close();
}

int main(){
  getInput();            //Gets user input for memory size and page size
  assignProcesses();     //Gets information for each process
}
