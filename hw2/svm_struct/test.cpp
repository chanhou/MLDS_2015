#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
#include <sstream>
#include <map>
// #include "stopWatch.h"
#include <stdio.h>
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

typedef struct word {
  int    wnum;	               /* word number */
  float    weight;              /* word weight */
} WORD;

typedef struct svector {
  WORD    *words;              /* The features/values in the vector by
				  increasing feature-number. Feature
				  numbers that are skipped are
				  interpreted as having value zero. */
  
  struct svector *next;        /* Let's you set up a list of SVECTOR's
				  for linear constraints which are a
				  sum of multiple feature
				  vectors. List is terminated by
				  NULL. */
  
} SVECTOR;


typedef struct pattern {
  /* this defines the x-part of a training example, e.g. the structure
     for storing a natural language sentence in NLP parsing */
  
  // int add_your_variables_here;
  
  //  dimension
   std::vector< std::vector <double> >  x_part;
  // std::vector<string> x_part;

} PATTERN;

typedef struct label {
  /* this defines the y-part (the label) of a training example,
     e.g. the parse tree of the corresponding sentence. */
  
  // int add_your_variables_here;

  // dynamic dimension
  std::vector<std::string> y_part;

} LABEL;


typedef struct example {  /* an example is a pair of pattern and label */
  PATTERN x;
  LABEL y;
} EXAMPLE;

typedef struct sample { /* a sample is a set of examples */
  int     n;            /* n is the total number of examples */
  EXAMPLE *examples;
} SAMPLE;


int main(int argc, char **argv) {

	// map<string,string> mapp_label;	

	// ifstream train_lab;
	// train_lab.open("../../hw1/MLDS_HW1_RELEASE_v1/label/train.lab");
	// string line; // each line ;
	// vector<string> v;
	// while(getline(train_lab,line)){
	// 	// istringstream iss(line);

	// 	// cout<<line<<endl;
	// 	// string temp1, temp2;
	// 	// iss >> temp1 >> comma1 >>temp2;
	// 	// cout<<temp1<<" "<<temp2;

	// 	v.clear();
	// 	split(line,',',v);
	// 	// cout<<v[0]<<" "<<v[1];
	// 	mapp_label[v[0] ] = v[1];
	// 	// cout<<mapp_label[v[0]];
	// 	// break;
	// 	// string mission;
	// 	// // int model_parameter;
	// 	// iss >> mission ;
	// }

	// ifstream train_data;
	// train_data.open("../../hw1/MLDS_HW1_RELEASE_v1/fbank/train.ark");
	// string temp1;
	// double temp2;

	// string previous_ppl = "0";
	// string ppl_name;
	// long count=0;
	// vector<double> x_value;
	// vector<vector<vector<double>>> record (3695);
	
	// while(getline(train_data,line)){

	// 	istringstream iss(line);
	// 	v.clear();

	// 	iss >> temp1; // name space
	// 	// cout<<mapp_label[temp1];
	// 	split(temp1,'_',v);

	// 	while(!iss.eof()){
	// 		iss >> temp2;
	// 		// cout<<temp2<<endl;
	// 		x_value.push_back(temp2);
	// 	}

	// 	// cout<<v[0]<<","<<v[1];
	// 	ppl_name = v[0]+"_"+v[1];
	// 	// cout<<ppl_name;
	// 	if(previous_ppl == "0") previous_ppl = ppl_name;
	// 	if(previous_ppl == ppl_name){
	// 		record[count].push_back(x_value);
	// 		// cout<<"ff"<<record[count].size()<<endl;
	// 		x_value.clear();
	// 	}
	// 	else{
	// 		if(previous_ppl != "0"){
	// 			cout<<"ff"<<record[count].size()<<endl;
	// 			// for(auto & x : record[count]){
	// 			// 	cout<<x[0];
	// 			// 	// break;
	// 			// }
	// 			cout<<record[count][222][68]<<endl;
	// 			count++;
	// 			record[count].push_back(x_value);
	// 			if (count==2)
	// 			{break;	}
	// 		}
	// 		previous_ppl = ppl_name;
	// 		x_value.clear();
	// 	}
	// 	// break;
		
	// }

	// SAMPLE   sample;  /* sample */
	// EXAMPLE  *examples;
	// long     n;       /* number of examples */

	// n= 3695; /* replace by appropriate number of examples */
	// examples=(EXAMPLE *)malloc(sizeof(EXAMPLE)*n);

	// /* fill in your code here */

	// // input label y, create a mapper to map y to the data
	// vector<string> v;
	// string line; 
	// map<string,string> mapp_label;  
	// ifstream train_lab;
	// train_lab.open("../../hw1/MLDS_HW1_RELEASE_v1/label/train.lab");
	// while(getline(train_lab,line)){

	// 	v.clear();
	// 	split(line,',',v);

	// 	mapp_label[v[0]] = v[1];
	// }

	// // input data of x:

	// string temp1;
	// double temp2;
	// // long count = 0;
	// // int name_rec = 0;
	// ifstream train_data;
	// string previous_ppl = "0";
	// string ppl_name;
	// long count=0;
	// vector<double> x_value;
	// // vector<vector<vector<double>>> record (n);

	// train_data.open("../../hw1/MLDS_HW1_RELEASE_v1/fbank/train.ark");
	// while(getline(train_data,line)){
	// 	istringstream iss(line);
	// 	v.clear();

	// 	iss >>temp1;

	// 	// split the unique speaker
	// 	split(temp1,'_',v);

	// 	// record the data
	// 	while(!iss.eof()){
	// 		iss >> temp2;
	// 		// cout<<temp2<<endl;
	// 		x_value.push_back(temp2);
	// 	}

	// 	// cout<<v[0]<<","<<v[1];
	// 	ppl_name = v[0]+"_"+v[1];
	// 	// cout<<ppl_name;
	// 	// if this is the first one
	// 	if(previous_ppl == "0") {
	// 		previous_ppl = ppl_name;
	// 	}
	// 	// if this speaker is the same with the previous data speaker
	// 	if(previous_ppl == ppl_name){
	// 		// record[count].push_back(x_value);
	// 		// push the data to this speaker
	// 		examples[count].y.y_part.push_back(mapp_label[temp1]);
	// 		// push the data to this speaker
	// 		examples[count].x.x_part.push_back(x_value);
	// 		// cout<<"ff"<<record[count].size()<<endl;
	// 		x_value.clear();
	// 	}
	// 	else{ // this speaker is not the same with previous on
	// 		count++; // count for the unique speaker
	// 		// record[count].push_back(x_value);
	// 		// push this speaker data to its own y

	// 		break;
	// 		examples[count].y.y_part.push_back(mapp_label[temp1]);
	// 		// push this speaker data to its own x
	// 		examples[count].x.x_part.push_back(x_value);
	// 		// if (count==2) break;
	// 		previous_ppl = ppl_name;
	// 		x_value.clear();
	// 	}

	// }

	// // cout<<examples[0].y.y_part[0]<<endl;
	// cout<<examples[0].x.x_part.size()<<endl;
	// cout<<examples[0].x.x_part[0].size()<<endl;



	// // SVECTOR *fvec=NULL;
	// int nn = 48*69+48*48+1;

	// // fvec = (SVECTOR *) malloc( sizeof(SVECTOR) );
	// // fvec->words = (WORD *) malloc( sizeof(WORD)*nn);
	// WORD* my_word = (WORD *) malloc( sizeof(WORD)*nn);

	// map<string,int> mapp_int;  
	// ifstream lab_int;
	// lab_int.open("../48_idx_chr.map_b");
	// string forget;
	// while(getline(lab_int,line)){
	// 	istringstream iss(line);
	// 	iss >>temp1 >> temp2 >> forget;
	// 	mapp_int[ temp1 ] = (temp2+1); // index start from 1
	// }
	// // cout<<mapp_int["aa"]<<endl;

	// int now;
	// int count_p = 0;
	// int count_sparse = 0;

	// vector<int> record_appear (49,-1);
	// vector<int> record_sparse (49,-1);
	// for(auto &y: examples[0].y.y_part){
	// 	record_sparse[ mapp_int[y] ] = 1;
	// }
	// for(int ee=0; ee< (int)record_sparse.size(); ++ee){
	// 	if( record_sparse[ee] != -1){
	// 		record_appear[ee] = count_p;
	// 		count_p ++;
	// 		count_sparse ++;
	// 	}
	// }

	// // for(auto &x: record_appear) cout<<x<<",";

	// // for observation part
	// for (int cc=0; cc< (int) examples[0].x.x_part.size() ; ++cc){ // 474
		
	// 	now = mapp_int[examples[0].y.y_part[cc]];
	// 	// cout<<now<<endl;
	// 	// cout<<examples[0].y.y_part[cc]<<endl;
	// 	for(int ww=0; ww< (int)examples[0].x.x_part[cc].size(); ++ww ){
	// 		// fvec->words[ record_appear[now] + ww ].wnum = now;
	// 		// fvec->words[ record_appear[now] + ww ].weight += examples[0].x.x_part[cc][ww];
	// 		// cout << my_word[ record_appear[now]*69 + ww ].weight<<endl;
			
	// 		my_word[ record_appear[now]*69 + ww ].wnum = now;
	// 		my_word[ record_appear[now]*69 + ww ].weight += examples[0].x.x_part[cc][ww];
	// 	}
	// 	// break;
	// }

	// // for(auto &x: record_appear) cout<<x<<","<<endl;
	// // for(auto &x: record_appear) cout<<x<<","<<endl;

	// // cout<<my_word[138].weight<<endl;
	
	// cout<<count_sparse<<endl;

	// // for transition part
	// int previous_transition = -1;
	// // vector< vector< int > > transition(48,48);

	// // initialization of wnum
	// for(int trans = 0; trans< (48*48); ++trans){
	// 	if(trans != (48*48-1) ){
	// 		my_word[ count_sparse*69 + trans ].wnum = 49;
	// 	}
	// 	else{ // last element
	// 		my_word[ count_sparse*69 + trans ].wnum = 0;
	// 	}
	// }

	// for (int cc=0; cc< (int)examples[0].y.y_part.size() ; ++cc){ 
				
	// 	now = mapp_int[ examples[0].y.y_part[cc] ] -1 ;

	// 	if (previous_transition == -1){
	// 		previous_transition = now;
	// 		continue;
	// 	}

	// 	my_word[ count_sparse*69 + previous_transition*48 + now ].wnum = 49;
	// 	my_word[ count_sparse*69 + previous_transition*48 + now ].weight += 1;

	// 	previous_transition = now;
	// }

	FILE *abc;
	abc = fopen ("test.csv", "w");

	fprintf(abc, "SVM 1,2,3,4,5,4\n");
	fprintf(abc, "SVM 2,3,1,4\n");
	fprintf(abc, "SVM 0000\n");

	fclose(abc);
	// FILE *def;
	// def = fopen("test.csv", "r");
	// char ggg[100];
	// fscanf(def,"SVM %s\n", ggg);
	// cout<<ggg[0]<<ggg[1]<<endl;
	// printf ("I have read: %s \n",ggg);
	// cout<<strlen(ggg)<<endl;

	// ifstream lab_int;
	// lab_int.open("test.csv");
	// string line;
	// string result1;
	// string result2;
	// cout<<"??"<<endl;
	// while(getline(lab_int,line)){
	// 	istringstream iss(line);
	// 	iss >> result1 >> result2;
	// 	cout<<result1<<"\n"<<result2;
	// }

    std::ifstream f;
    std::string line;
    std::stringstream ss;
    int i=0;
    f.open("test.csv");
    if(f.is_open()){
        while(getline(f,line)){
            std::cout<<line<<std::endl;
            i++;
            if(i==1)break;
        }
        ss<<"sed -i -e 1,"<<i<<"d test.csv";
        system(ss.str().c_str());
        // while(getline(f,line)){
        //     std::cout<<line<<std::endl;
        // }
    }



	return 0;
}

