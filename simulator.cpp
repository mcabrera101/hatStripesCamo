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

struct processQueue {
	int capacity;
	int size;
	int front;
	int rear;
	vector<PROCESS> contents;
};

const int MAX_MEMORY_SIZE = 30000;
int memorySize, pageSize, numberOfProcesses;
long clock;
string fileName;
vector<Process> processList;
processQueue waitQueue;

void getInput();
void assignProcesses();
void writeToFile();

int main(){
  getInput();            //Gets user input for memory size and page size
  assignProcesses();     //Gets information for each process
  inputQueue = createProcessQueue(numberOfProcesses);

  mainLoop();
  writeToFile();
}

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
		cout<<"Number of processes: "<<numberOfProcesses<<endl;
		for (int i = 0; i < numberOfProcesses; i++) {
			//Get process ID
			myFile >> processList[i].processID;
			cout<<"process ID: "<<processList[i].processID<<endl;
			//Get arriving time and life time
			myFile >> processList[i].arrivalTime >> processList[i].lifetime;
			cout<<"Arrival time: "<<processList[i].arrivalTime<<endl;
			cout<<"Lifetime: "<<processList[i].lifetime<<endl;
			//Get memory requirement
			int piecesOfMemory = 0;          //Number of memory pieces; we need to sum those piecces
			int temp;                        //Holds the value of a memory piece
			int memoryRequirement = 0;       //Equal to the sum of our memory pieces

			myFile >> piecesOfMemory;
			cout<<"piecesOfMemory: "<<piecesOfMemory<<endl;
			for (int j = 0; j < piecesOfMemory; j++) {
				myFile >> temp;
				memoryRequirement += temp;    //Adds the value of a piece to the memory requirement
			}
			processList[i].memoryRequirement = memoryRequirement;
			cout<<"Memory requirement: "<<memoryRequirement<<endl;
		}
	}
	myFile.close();
}

processQueue createProcessQueue(int length) {
	processQueue q;
	q.size=0;
	q.capacity=length;
	q.front=0;
	q.rear=-1;
  q.elements.resize(length);
	return q;
}

void writeToFile(){
  ofstream outputFile;
  outputFile.open("out.txt");
  for(int x=0; x<numberOfProcesses;x++){
    outputFile<<processList[x].processID;
  }
}
