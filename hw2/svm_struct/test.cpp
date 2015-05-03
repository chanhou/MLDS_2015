#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>

#include <string>
#include <vector>
#include <sstream>
#include <map>
// #include "stopWatch.h"

using namespace std;

void split(const string& s, char c, vector<string>& v) {
	string::size_type i = 0;
	string::size_type j = s.find(c);

	if (j != string::npos){
		while (j != string::npos) {
			//if(j==(s.length())) break;
			//if(s.substr(i, j-i).find_first_not_of(' ') == string::npos) break;
			//cout<<"hh"<<endl;
			v.push_back(s.substr(i, j-i));
			i = ++j;
			j = s.find(c, j);
			//cout<<"s length"<<s.length()<<endl;
			//cout<<"j"<<j<<endl;
			
			if(j==(s.length()-1)) {
				v.push_back(s.substr(i, j-i));
				break;
			}
			

			if (j == string::npos)
				v.push_back(s.substr(i, s.length()));
			
		}	
	}
	else {
		// cout<<"hh"<<endl;
		v.push_back(s.substr(0, s.length()));
	}
}

int main(int argc, char **argv) {

	map<string,string> mapp_label;	

	ifstream train_lab;
	train_lab.open("../../hw1/MLDS_HW1_RELEASE_v1/label/train.lab");
	string line; // each line ;
	vector<string> v;
	while(getline(train_lab,line)){
		// istringstream iss(line);

		// cout<<line<<endl;
		// string temp1, temp2;
		// iss >> temp1 >> comma1 >>temp2;
		// cout<<temp1<<" "<<temp2;

		v.clear();
		split(line,',',v);
		// cout<<v[0]<<" "<<v[1];
		mapp_label[v[0] ] = v[1];
		// cout<<mapp_label[v[0]];
		// break;
		// string mission;
		// // int model_parameter;
		// iss >> mission ;
	}

	ifstream train_data;
	train_data.open("../../hw1/MLDS_HW1_RELEASE_v1/fbank/train.ark");
	string temp1;
	double temp2;

	string previous_ppl = "0";
	string ppl_name;
	long count=0;
	vector<double> x_value;
	vector<vector<vector<double>>> record (3695);
	
	while(getline(train_data,line)){

		istringstream iss(line);
		v.clear();

		iss >> temp1; // name space
		// cout<<mapp_label[temp1];
		split(temp1,'_',v);

		while(!iss.eof()){
			iss >> temp2;
			// cout<<temp2<<endl;
			x_value.push_back(temp2);
		}

		// cout<<v[0]<<","<<v[1];
		ppl_name = v[0]+"_"+v[1];
		// cout<<ppl_name;
		if(previous_ppl == "0") previous_ppl = ppl_name;
		if(previous_ppl == ppl_name){
			record[count].push_back(x_value);
			// cout<<"ff"<<record[count].size()<<endl;
			x_value.clear();
		}
		else{
			if(previous_ppl != "0"){
				cout<<"ff"<<record[count].size()<<endl;
				// for(auto & x : record[count]){
				// 	cout<<x[0];
				// 	// break;
				// }
				cout<<record[count][222][68]<<endl;
				count++;
				record[count].push_back(x_value);
				if (count==2)
				{break;	}
			}
			previous_ppl = ppl_name;
			x_value.clear();
		}
		// break;
		
	}


	return 0;
}
