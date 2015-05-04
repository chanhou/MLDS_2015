/***********************************************************************/
/*                                                                     */
/*   svm_struct_api.c                                                  */
/*                                                                     */
/*   Definition of API for attaching implementing SVM learning of      */
/*   structures (e.g. parsing, multi-label classification, HMM)        */ 
/*                                                                     */
/*   Author: Thorsten Joachims                                         */
/*   Date: 03.07.04                                                    */
/*                                                                     */
/*   Copyright (c) 2004  Thorsten Joachims - All rights reserved       */
/*                                                                     */
/*   This software is available for non-commercial use only. It must   */
/*   not be modified and distributed without prior permission of the   */
/*   author. The author is not responsible for implications from the   */
/*   use of this software.                                             */
/*                                                                     */
/***********************************************************************/

#include <stdio.h>
#include <string.h>
#include "svm_struct/svm_struct_common.h"
#include "svm_struct_api.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <map>

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

void        svm_struct_learn_api_init(int argc, char* argv[])
{
  /* Called in learning part before anything else is done to allow
     any initializations that might be necessary. */
}

void        svm_struct_learn_api_exit()
{
  /* Called in learning part at the very end to allow any clean-up
     that might be necessary. */
}

void        svm_struct_classify_api_init(int argc, char* argv[])
{
  /* Called in prediction part before anything else is done to allow
     any initializations that might be necessary. */
}

void        svm_struct_classify_api_exit()
{
  /* Called in prediction part at the very end to allow any clean-up
     that might be necessary. */
}

SAMPLE      read_struct_examples(char *file, STRUCT_LEARN_PARM *sparm)
{
  /* Reads struct examples and returns them in sample. The number of
     examples must be written into sample.n */
  SAMPLE   sample;  /* sample */
  EXAMPLE  *examples;
  long     n;       /* number of examples */

  n= 3695; /* replace by appropriate number of examples */
  examples=(EXAMPLE *)my_malloc(sizeof(EXAMPLE)*n);

  /* fill in your code here */

  // input label y, create a mapper to map y to the data
  vector<string> v;
  string line; 
  map<string,string> mapp_label;  
  ifstream train_lab;
  train_lab.open("../../hw1/MLDS_HW1_RELEASE_v1/label/train.lab");
  while(getline(train_lab,line)){

    v.clear();
    split(line,',',v);
    
    mapp_label[v[0]] = v[1];
  }

  // using label map file to map the chr to index
  map<string,int> mapp_int;  
  ifstream lab_int;
  lab_int.open("../48_idx_chr.map_b");
  string forget;
  string temp1;
  double temp2;
  while(getline(lab_int,line)){
    istringstream iss(line);
    iss >>temp1 >> temp2 >> forget;
    mapp_int[ temp1 ] = (temp2+1); // index start from 1 in psi for featurenum
  }


  // input data of x:
  // string temp1;
  // double temp2;
  // int name_rec = 0;
  ifstream train_data;
  string previous_ppl = "0";
  string ppl_name;
  long count=0;
  vector<double> x_value;
  // vector<vector<vector<double>>> record (n);

  train_data.open("../../hw1/MLDS_HW1_RELEASE_v1/fbank/train.ark");
  while(getline(train_data,line)){
    istringstream iss(line);
    v.clear();

    iss >>temp1;
    
    // split the unique speaker
    split(temp1,'_',v);

    // record the data
    while(!iss.eof()){
      iss >> temp2;
      // cout<<temp2<<endl;
      x_value.push_back(temp2);
    }

    // cout<<v[0]<<","<<v[1];
    ppl_name = v[0]+"_"+v[1];
    // cout<<ppl_name;
    // if this is the first one
    if(previous_ppl == "0") {
      previous_ppl = ppl_name;
    }
    // if this speaker is the same with the previous data speaker
    if(previous_ppl == ppl_name){
      // record[count].push_back(x_value);
      // push the data to this speaker
      examples[count].y.y_part.push_back( mapp_int[ mapp_label[temp1] ]);
      // push the data to this speaker
      examples[count].x.x_part.push_back(x_value);
      // cout<<"ff"<<record[count].size()<<endl;
      x_value.clear();
    }
    else{ // this speaker is not the same with previous on
      count++; // count for the unique speaker
      // record[count].push_back(x_value);
      // push this speaker data to its own y
      examples[count].y.y_part.push_back( mapp_int[ mapp_label[temp1] ] );
      // push this speaker data to its own x
      examples[count].x.x_part.push_back(x_value);
      // if (count==2) break;
      previous_ppl = ppl_name;
      x_value.clear();
    }

  }

  sample.n=n;
  sample.examples=examples;
  return(sample);
}

void        init_struct_model(SAMPLE sample, STRUCTMODEL *sm, 
			      STRUCT_LEARN_PARM *sparm, LEARN_PARM *lparm, 
			      KERNEL_PARM *kparm)
{
  /* Initialize structmodel sm. The weight vector w does not need to be
     initialized, but you need to provide the maximum size of the
     feature space in sizePsi. This is the maximum number of different
     weights that can be learned. Later, the weight vector w will
     contain the learned weights for the model. */

  // 48 phones + 1 dummy + 1 transition

  // sm->sizePsi=50; /* replace by appropriate number of features */

  // 48 phones + 1 transition

  sm->sizePsi=49; /* replace by appropriate number of features */
}

CONSTSET    init_struct_constraints(SAMPLE sample, STRUCTMODEL *sm, 
				    STRUCT_LEARN_PARM *sparm)
{
  /* Initializes the optimization problem. Typically, you do not need
     to change this function, since you want to start with an empty
     set of constraints. However, if for example you have constraints
     that certain weights need to be positive, you might put that in
     here. The constraints are represented as lhs[i]*w >= rhs[i]. lhs
     is an array of feature vectors, rhs is an array of doubles. m is
     the number of constraints. The function returns the initial
     set of constraints. */
  CONSTSET c;
  long     sizePsi=sm->sizePsi;
  long     i;
  WORD     words[2];

  if(1) { /* normal case: start with empty set of constraints */
    c.lhs=NULL;
    c.rhs=NULL;
    c.m=0;
  }
  else { /* add constraints so that all learned weights are
            positive. WARNING: Currently, they are positive only up to
            precision epsilon set by -e. */
    c.lhs=my_malloc(sizeof(DOC *)*sizePsi);
    c.rhs=my_malloc(sizeof(double)*sizePsi);
    for(i=0; i<sizePsi; i++) {
      words[0].wnum=i+1;
      words[0].weight=1.0;
      words[1].wnum=0;
      /* the following slackid is a hack. we will run into problems,
         if we have move than 1000000 slack sets (ie examples) */
      c.lhs[i]=create_example(i,0,1000000+i,1,create_svector(words,"",1.0));
      c.rhs[i]=0.0;
    }
  }
  return(c);
}

LABEL       classify_struct_example(PATTERN x, STRUCTMODEL *sm, 
				    STRUCT_LEARN_PARM *sparm)
{
  /* Finds the label yhat for pattern x that scores the highest
     according to the linear evaluation function in sm, especially the
     weights sm.w. The returned label is taken as the prediction of sm
     for the pattern x. The weights correspond to the features defined
     by psi() and range from index 1 to index sm->sizePsi. If the
     function cannot find a label, it shall return an empty label as
     recognized by the function empty_label(y). */
  LABEL y;

  /* insert your code for computing the predicted label y here */

  return(y);
}

LABEL       find_most_violated_constraint_slackrescaling(PATTERN x, LABEL y, 
						     STRUCTMODEL *sm, 
						     STRUCT_LEARN_PARM *sparm)
{
  /* Finds the label ybar for pattern x that that is responsible for
     the most violated constraint for the slack rescaling
     formulation. For linear slack variables, this is that label ybar
     that maximizes

            argmax_{ybar} loss(y,ybar)*(1-psi(x,y)+psi(x,ybar)) 

     Note that ybar may be equal to y (i.e. the max is 0), which is
     different from the algorithms described in
     [Tschantaridis/05]. Note that this argmax has to take into
     account the scoring function in sm, especially the weights sm.w,
     as well as the loss function, and whether linear or quadratic
     slacks are used. The weights in sm.w correspond to the features
     defined by psi() and range from index 1 to index
     sm->sizePsi. Most simple is the case of the zero/one loss
     function. For the zero/one loss, this function should return the
     highest scoring label ybar (which may be equal to the correct
     label y), or the second highest scoring label ybar, if
     Psi(x,ybar)>Psi(x,y)-1. If the function cannot find a label, it
     shall return an empty label as recognized by the function
     empty_label(y). */
  LABEL ybar;

  /* insert your code for computing the label ybar here */

  return(ybar);
}

LABEL       find_most_violated_constraint_marginrescaling(PATTERN x, LABEL y, 
						     STRUCTMODEL *sm, 
						     STRUCT_LEARN_PARM *sparm)
{
  /* Finds the label ybar for pattern x that that is responsible for
     the most violated constraint for the margin rescaling
     formulation. For linear slack variables, this is that label ybar
     that maximizes

            argmax_{ybar} loss(y,ybar)+psi(x,ybar)

     Note that ybar may be equal to y (i.e. the max is 0), which is
     different from the algorithms described in
     [Tschantaridis/05]. Note that this argmax has to take into
     account the scoring function in sm, especially the weights sm.w,
     as well as the loss function, and whether linear or quadratic
     slacks are used. The weights in sm.w correspond to the features
     defined by psi() and range from index 1 to index
     sm->sizePsi. Most simple is the case of the zero/one loss
     function. For the zero/one loss, this function should return the
     highest scoring label ybar (which may be equal to the correct
     label y), or the second highest scoring label ybar, if
     Psi(x,ybar)>Psi(x,y)-1. If the function cannot find a label, it
     shall return an empty label as recognized by the function
     empty_label(y). */
  LABEL ybar;

  /* insert your code for computing the label ybar here */

  // use viterbi to find what the ybar is

  // then check argmax_{ybar} sprod_ns(sm->w, psi(x, ybar, sm, sparm))
  // will be same as what viterbi calculate



  return(ybar);
}

int         empty_label(LABEL y)
{
  /* Returns true, if y is an empty label. An empty label might be
     returned by find_most_violated_constraint_???(x, y, sm) if there
     is no incorrect label that can be found for x, or if it is unable
     to label x at all */
  return(0);
}

SVECTOR     *psi(PATTERN x, LABEL y, STRUCTMODEL *sm,
		 STRUCT_LEARN_PARM *sparm)
{
  /* Returns a feature vector describing the match between pattern x
     and label y. The feature vector is returned as a list of
     SVECTOR's. Each SVECTOR is in a sparse representation of pairs
     <featurenumber:featurevalue>, where the last pair has
     featurenumber 0 as a terminator. Featurenumbers start with 1 and
     end with sizePsi. Featuresnumbers that are not specified default
     to value 0. As mentioned before, psi() actually returns a list of
     SVECTOR's. Each SVECTOR has a field 'factor' and 'next'. 'next'
     specifies the next element in the list, terminated by a NULL
     pointer. The list can be though of as a linear combination of
     vectors, where each vector is weighted by its 'factor'. This
     linear combination of feature vectors is multiplied with the
     learned (kernelized) weight vector to score label y for pattern
     x. Without kernels, there will be one weight in sm.w for each
     feature. Note that psi has to match
     find_most_violated_constraint_???(x, y, sm) and vice versa. In
     particular, find_most_violated_constraint_???(x, y, sm) finds
     that ybar!=y that maximizes psi(x,ybar,sm)*sm.w (where * is the
     inner vector product) and the appropriate function of the
     loss + margin/slack rescaling method. See that paper for details. */
  SVECTOR *fvec=NULL;

  /* insert code for computing the feature vector for x and y here */
  int nn = 48*69+48*48+1;

  WORD* my_word = (WORD *) my_malloc( sizeof(WORD)*nn);

  // using label map file to map the chr to index
  // map<string,int> mapp_int;  
  // ifstream lab_int;
  // lab_int.open("../48_idx_chr.map_b");
  // string forget;
  // while(getline(lab_int,line)){
  //   istringstream iss(line);
  //   iss >>temp1 >> temp2 >> forget;
  //   mapp_int[ temp1 ] = (temp2+1); // index start from 1 in psi for featurenum
  // }

  int now;
  int count_p = 0;
  int count_sparse = 0;

  vector<int> record_appear (49,-1);
  vector<int> record_sparse (49,-1);
  for(auto &y: y.y_part){
    // record the label which have appear
    // record_sparse[ mapp_int[y] ] = 1;
    record_sparse[ y ] = 1;
  }
  for(int ee=0; ee< (int)record_sparse.size(); ++ee){
    // record the order and position for fixed featurenum
    if( record_sparse[ee] != -1){
      record_appear[ee] = count_p;
      count_p ++;
      count_sparse ++;
    }
  }
  ///////
  // for dummy state
  // count_sparse ++; 
  ///////

  // for observation part
  for (int cc=0; cc< (int) x.x_part.size() ; ++cc){ // 474
    // the feature num
    // now = mapp_int[ y.y_part[cc] ];
    now =  y.y_part[cc];

    for(int ww=0; ww< (int) x.x_part[cc].size(); ++ww ){
      // record_appear[now]*69 specify the position of feature num
      my_word[ record_appear[now]*69 + ww ].wnum = now;
      my_word[ record_appear[now]*69 + ww ].weight += x.x_part[cc][ww];

      ///////
      // dummy state
      ///////
      // my_word[ 49*69 + ww ].wnum = 49;
      // my_word[ 49*69 + ww ].weight += x.x_part[cc][ww];
    }
  }

  // for transition part
  int previous_transition = -1;

  // initialization of wnum
  // since we no need to do sparse here
  // then we need to initialize a 48*48 matrix
  for(int trans = 0; trans< (48*48); ++trans){
    if(trans != (48*48-1) ){
      my_word[ count_sparse*69 + trans ].wnum = sm->sizePsi; // sm->sizePsi
    }
    else{ // last element
      // psi format
      my_word[ count_sparse*69 + trans ].wnum = 0;
    }
  }

  for (int cc=0; cc< (int) y.y_part.size() ; ++cc){ 
        
    // now = mapp_int[ y.y_part[cc] ] -1 ;
    now =  y.y_part[cc]  - 1 ;
    if (previous_transition == -1){
      previous_transition = now;
      continue;
    }

    // my_word[ count_sparse*69 + previous_transition*48 + now ].wnum = sm->sizePsi;
    my_word[ count_sparse*69 + previous_transition*48 + now ].weight += 1;

    previous_transition = now;
  }

  fvec = create_svector(my_word, false, 1); // userdefined set as false, factor set as 1, don't know set what


  return(fvec);
}

double      loss(LABEL y, LABEL ybar, STRUCT_LEARN_PARM *sparm)
{
  /* loss for correct label y and predicted label ybar. The loss for
     y==ybar has to be zero. sparm->loss_function is set with the -l option. */
  if(sparm->loss_function == 0) { /* type 0 loss: 0/1 loss */
                                  /* return 0, if y==ybar. return 1 else */

    // if y size and ybar size different? 
    // how to calculate ?
    // if i pass the same size of ybar then no need t oconsider this question
    double error = 0;
    for(int i=0;i< y.y_part.size() ; ++i){
      if ( y.y_part[i] != ybar.y_part[i] ){
        error ++;
        // return 1;
      }
    }
    // return 0;
    return (double) error/y.y_part.size();
  }
  else {
    /* Put your code for different loss functions here. But then
       find_most_violated_constraint_???(x, y, sm) has to return the
       highest scoring label with the largest loss. */
    // for(int i=0;i< y.y_part.size() ; ++i){
    //   if ( y.y_part[i] != ybar.y_part[i] ){
    //     error ++;
    //   }
    // }
    // return (double) error/y.y_part.size();    

  }
}

int         finalize_iteration(double ceps, int cached_constraint,
			       SAMPLE sample, STRUCTMODEL *sm,
			       CONSTSET cset, double *alpha, 
			       STRUCT_LEARN_PARM *sparm)
{
  /* This function is called just before the end of each cutting plane iteration. ceps is the amount by which the most violated constraint found in the current iteration was violated. cached_constraint is true if the added constraint was constructed from the cache. If the return value is FALSE, then the algorithm is allowed to terminate. If it is TRUE, the algorithm will keep iterating even if the desired precision sparm->epsilon is already reached. */
  return(0);
}

void        print_struct_learning_stats(SAMPLE sample, STRUCTMODEL *sm,
					CONSTSET cset, double *alpha, 
					STRUCT_LEARN_PARM *sparm)
{
  /* This function is called after training and allows final touches to
     the model sm. But primarly it allows computing and printing any
     kind of statistic (e.g. training error) you might want. */
}

void        print_struct_testing_stats(SAMPLE sample, STRUCTMODEL *sm,
				       STRUCT_LEARN_PARM *sparm, 
				       STRUCT_TEST_STATS *teststats)
{
  /* This function is called after making all test predictions in
     svm_struct_classify and allows computing and printing any kind of
     evaluation (e.g. precision/recall) you might want. You can use
     the function eval_prediction to accumulate the necessary
     statistics for each prediction. */
}

void        eval_prediction(long exnum, EXAMPLE ex, LABEL ypred, 
			    STRUCTMODEL *sm, STRUCT_LEARN_PARM *sparm, 
			    STRUCT_TEST_STATS *teststats)
{
  /* This function allows you to accumlate statistic for how well the
     predicition matches the labeled example. It is called from
     svm_struct_classify. See also the function
     print_struct_testing_stats. */
  if(exnum == 0) { /* this is the first time the function is
		      called. So initialize the teststats */
  }
}

void        write_struct_model(char *file, STRUCTMODEL *sm, 
			       STRUCT_LEARN_PARM *sparm)
{
  /* Writes structural model sm to file file. */
}

STRUCTMODEL read_struct_model(char *file, STRUCT_LEARN_PARM *sparm)
{
  /* Reads structural model sm from file file. This function is used
     only in the prediction module, not in the learning module. */
}

void        write_label(FILE *fp, LABEL y)
{
  /* Writes label y to file handle fp. */
} 

void        free_pattern(PATTERN x) {
  /* Frees the memory of x. */
}

void        free_label(LABEL y) {
  /* Frees the memory of y. */
}

void        free_struct_model(STRUCTMODEL sm) 
{
  /* Frees the memory of model. */
  /* if(sm.w) free(sm.w); */ /* this is free'd in free_model */
  if(sm.svm_model) free_model(sm.svm_model,1);
  /* add free calls for user defined data here */
}

void        free_struct_sample(SAMPLE s)
{
  /* Frees the memory of sample s. */
  int i;
  for(i=0;i<s.n;i++) { 
    free_pattern(s.examples[i].x);
    free_label(s.examples[i].y);
  }
  free(s.examples);
}

void        print_struct_help()
{
  /* Prints a help text that is appended to the common help text of
     svm_struct_learn. */
  printf("         --* string  -> custom parameters that can be adapted for struct\n");
  printf("                        learning. The * can be replaced by any character\n");
  printf("                        and there can be multiple options starting with --.\n");
}

void         parse_struct_parameters(STRUCT_LEARN_PARM *sparm)
{
  /* Parses the command line parameters that start with -- */
  int i;

  for(i=0;(i<sparm->custom_argc) && ((sparm->custom_argv[i])[0] == '-');i++) {
    switch ((sparm->custom_argv[i])[2]) 
      { 
      case 'a': i++; /* strcpy(learn_parm->alphafile,argv[i]); */ break;
      case 'e': i++; /* sparm->epsilon=atof(sparm->custom_argv[i]); */ break;
      case 'k': i++; /* sparm->newconstretrain=atol(sparm->custom_argv[i]); */ break;
      default: printf("\nUnrecognized option %s!\n\n",sparm->custom_argv[i]);
	       exit(0);
      }
  }
}

void        print_struct_help_classify()
{
  /* Prints a help text that is appended to the common help text of
     svm_struct_classify. */
  printf("         --* string -> custom parameters that can be adapted for struct\n");
  printf("                       learning. The * can be replaced by any character\n");
  printf("                       and there can be multiple options starting with --.\n");
}

void         parse_struct_parameters_classify(STRUCT_LEARN_PARM *sparm)
{
  /* Parses the command line parameters that start with -- for the
     classification module */
  int i;

  for(i=0;(i<sparm->custom_argc) && ((sparm->custom_argv[i])[0] == '-');i++) {
    switch ((sparm->custom_argv[i])[2]) 
      { 
      /* case 'x': i++; strcpy(xvalue,sparm->custom_argv[i]); break; */
      default: printf("\nUnrecognized option %s!\n\n",sparm->custom_argv[i]);
	       exit(0);
      }
  }
}

