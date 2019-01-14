#include <iostream>
#include "unistd.h"
#include "pipeline.h"
#include <stdlib.h>
#include <stdio.h>

using namespace std;

int main(int argc, char *argv[]) {

	int opt;
	bool forwarding = false;
	string fileName = "instruction.txt";
	int forwarding_width = 0;
	while ((opt = getopt(argc,argv,"fi:")) != EOF)
        switch(opt)
        {
            case 'f': forwarding = true; break;
            case 'i': fileName.assign(optarg); break;
            case '?': fprintf(stderr, "usuage is \n -i fileName : to run input file fileName \n -f : for enabling forwarding ");
            default: cout<<endl; abort();
        }
	if(forwarding == true)
	{
		forwarding_width = std::stoi(argv[4]);
		/*switch(forwarding_width){
			case 0: cout << " Forwarding is disabled"<<endl;
			break;
			case 1: cout << "Forwarding for EXEC/MEM pipeline register to EXEC Stage is enabled"<<endl;
			break;
			case 2: cout << "Forwarding for EXEC/MEM to EXEC Stage and MEM/WB to EXEC Stage is enabled"<< endl;
			break;
			default: cout<<endl; abort();
		}*/
		if(forwarding_width==0){
			cout << "Forwarding is disabled"<<endl;
		}
		else if(forwarding_width == 1){
			cout << "Forwarding for EXEC/MEM pipeline register to EXEC Stage is enabled"<< endl;
		}
		else if(forwarding_width == 2){
			cout << "Forwarding for EXEC/MEM to EXEC Stage and MEM/WB to EXEC Stage is enabled"<<endl;
		}
		else{
			cout << endl; abort();
		}
	}

	cout << "Loading application..." << fileName << endl;
	Application application;
	application.loadApplication(fileName);
	cout << "Initializing pipeline..." << endl;
	Pipeline pipeline(&application);
	pipeline.forwarding = forwarding;
	pipeline.forwarding_width = forwarding_width;

	do {
		pipeline.cycle();
		pipeline.printPipeline();

	} while(!pipeline.done());

	cout << "Completed in " << pipeline.cycleTime - 1 << " cycles" << endl;
	return 0;
}
