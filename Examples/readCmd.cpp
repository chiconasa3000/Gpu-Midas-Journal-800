#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

string GetStdoutFromCommand(string cmd){

	string data;
	FILE * stream;
	const int max_buffer = 256;
	char buffer[max_buffer];
	cmd.append(" 2>&1");

	stream = popen(cmd.c_str(),"r");
	if(stream){
		while(!feof(stream))
			if(fgets(buffer, max_buffer, stream) != NULL)
				data.append(buffer);				
			pclose(stream);
	}
	return data;
}

int main(){
	string ls = GetStdoutFromCommand("./MultiImageRegistration ../bestData/pelvisSegmIntensity.mha 2 ../bestData/pelvisDRRG0LspCenter.mha 0 1990 0 ../bestData/pelvisDRRG90PsrCenter.mha -1990 0 0 0.08 8.0 4 6 4 2 1 ../bestData/outDirNewUmbral");
	ofstream out("LogRegisterIterations.txt");
	out << ls << endl;
	out.close();
	return 0;
}
