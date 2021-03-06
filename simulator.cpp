#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <deque>
#include <iomanip>
using namespace std;

class Process{
  public:
    //Information obtained from workload file
    int processID;
    int arrivalTime;
    int lifetime;
    int memoryRequirement;
    int piecesOfMemory;

    int memoryAdmissionTime;
    int completionTime;

    Process(int pI =0,int aT=0,int l=0,int mR=0, int p=0, int mA=0, int cT=0){
    	this-> processID = pI;
    	this-> arrivalTime = aT;
    	this-> lifetime = l;
    	this-> memoryRequirement = mR;
    	this-> piecesOfMemory = p;
    	this-> memoryAdmissionTime = mA;
    	this-> completionTime=cT;
    }
};

const int MAX_MEMORY_SIZE = 30000;
const int MAX_TIME = 100000;
int memorySize=1, pageSize =1, numberOfProcesses, activeProcesses;
long clockTime;
string fileName;
vector<Process> processList;
deque<Process> inputQueue;
map<string,Process> memory;
vector<int> lower;
vector<int> upper;
vector<string> labels;

//Prototypes
void getInput();
void assignProcesses();
void mainLoop();
void enqueueArrivedProcess();
void writeToFile(string);
void inputQCount();
void addmitter(int);
void completter(int);
void labelF();

int main(){
  getInput();            //Gets user input for memory size and page size
  labelF();			         //Creates labels for memory map
  assignProcesses();     //Gets information for each process
  mainLoop();
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
			processList[i].piecesOfMemory = piecesOfMemory;
			cout<<"Memory requirement: "<<memoryRequirement<<endl;
		}
	}
	myFile.close();
}

void mainLoop(){
  clockTime=0;

  while(true){
    enqueueArrivedProcess();
    addmitter(clockTime);
    completter(clockTime);

    clockTime++;
    if(clockTime>MAX_TIME ||(memory.empty() && inputQueue.empty())){
      break;
    }
  }
}

void enqueueArrivedProcess() {
	Process proc;
	for (int x = 0; x < numberOfProcesses; x++) {
		proc = processList[x];
		if (proc.arrivalTime == clockTime) {
		    string message = "t = " + to_string(clockTime) + ": Process " + to_string(proc.processID) + " arrives";
		    cout<<endl<<message<<endl;

		    writeToFile(message);
			  inputQueue.push_back(proc);
			  inputQCount();

		}

	}
}

void writeToFile(string output){
  ofstream outputFile;
  outputFile.open("out.txt",std::ios_base::app);
  outputFile<<output<<endl;
  outputFile.close();
}

void inputQCount(){  //prints current processes on the inputQueue
  string output = "  Input Queue: [";
	if (inputQueue.size() > 0){
		//cout<< "	"<< "Input Queue: [";
			for (int i =0 ; i < inputQueue.size(); i++){
				if(inputQueue[i].processID !=0){
          output = output + " " + to_string(inputQueue[i].processID);
					//cout<<" " << inputQueue[i].processID;
				}
			}
		//cout<< "]" <<endl;
    output = output + "]";
    cout<<output<<endl;
    writeToFile(output);
	}
}

void addmitter(int clockTime){ //admits if there is enough memory and there is a process in the queue
	Process proc;
  string output;
	if(inputQueue.size() > 0 ){
		if(inputQueue.front().memoryRequirement <= memorySize){
			proc = inputQueue.front();

			memorySize -= proc.memoryRequirement;
			proc.memoryAdmissionTime = clockTime;
			proc.completionTime = proc.memoryAdmissionTime + proc.lifetime;
			// if (proc.memoryRequirement>pageSize){
			// 	for (int i=0 ; i<pr; i++){
			// 	memory.insert(std::pair<string,Process>(labels[i], proc));
			// 	}
			// }
			// else{
			// 	memory.insert(std::pair<string,Process>(labels., proc));
			// }
			memory.insert(std::pair<string,Process>(to_string(proc.processID), proc));

      output = "  MM moves Process " + to_string(proc.processID) + " to memory";
      cout<<output<<endl;
      writeToFile(output);
			//cout << "	"<< "MM moves Process "<< proc.processID << " to memory" << endl;
			inputQueue.pop_front();
			inputQCount();

		}
	}
}

void completter(int clockTime){
  string output;
	for(map<string,Process>::const_iterator it= memory.begin(); it != memory.end(); it++){
		if(it->second.completionTime == clockTime){
			//cout << "  Process " <<it->second.processID << " completes" << endl;
      output="  Process ";
      output = output + to_string(it->second.processID) + " completes";
      cout<<output<<endl;

			memorySize += it->second.memoryRequirement;


		}
	}
}

void labelF(){
	int ltemp = 0;
	int utemp = pageSize-1;
	double l = memorySize/pageSize;
	string label = " ";
	for(int i = 0;i<l; i ++){
		lower.push_back(ltemp);
		upper.push_back(utemp);
		label = to_string(lower[i]) + "-" + to_string(upper[i]);
		labels.push_back(label);
		label = " ";
		ltemp += pageSize;
		utemp += pageSize;
	}
}
