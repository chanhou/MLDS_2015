# Makefile for empty SVM-struct API, 03.10.06

#Call 'make' using the following line to make CYGWIN produce stand-alone Windows executables
#		make 'SFLAGS=-mno-cygwin'

#Use the following to compile under unix or cygwin
CC = g++
LD = g++

CPPFLAGS = -O2 -std=c++11 -Wall

CFLAGS =   $(SFLAGS) -O3 -fomit-frame-pointer -ffast-math -Wall -std=c++11 -fopenmp
LDFLAGS =  $(SFLAGS) -O3 -Wall -fopenmp
#CFLAGS =  $(SFLAGS) -pg -Wall
#LDFLAGS = $(SFLAGS) -pg -lm -Wall 

all: svm_empty_learn svm_empty_classify

.PHONY: clean
clean: svm_light_clean svm_struct_clean
	rm -f *.o *.tcov *.d core gmon.out *.stackdump 

#-----------------------#
#----   SVM-light   ----#
#-----------------------#
svm_light_hideo_noexe: 
	cd svm_light; make svm_learn_hideo_noexe

svm_light_clean: 
	cd svm_light; make clean

#----------------------#
#----  STRUCT SVM  ----#
#----------------------#

svm_struct_noexe: 
	cd svm_struct; make svm_struct_noexe

svm_struct_clean: 
	cd svm_struct; make clean


#-------------------------#
#----  SVM empty API  ----#
#-------------------------#

svm_empty_classify: svm_light_hideo_noexe svm_struct_noexe svm_struct_api.o svm_struct/svm_struct_classify.o svm_struct/svm_struct_common.o svm_struct/svm_struct_main.o 
	$(LD) $(LDFLAGS) svm_struct_api.o svm_struct/svm_struct_classify.o svm_light/svm_common.o svm_struct/svm_struct_common.o -o svm_empty_classify $(LIBS) -lm

svm_empty_learn: svm_light_hideo_noexe svm_struct_noexe svm_struct_api.o svm_struct_learn_custom.o svm_struct/svm_struct_learn.o svm_struct/svm_struct_common.o svm_struct/svm_struct_main.o
	$(LD) $(LDFLAGS) svm_struct/svm_struct_learn.o svm_struct_learn_custom.o svm_struct_api.o svm_light/svm_hideo.o svm_light/svm_learn.o svm_light/svm_common.o svm_struct/svm_struct_common.o svm_struct/svm_struct_main.o -o svm_empty_learn $(LIBS) -lm


svm_struct_api.o: svm_struct_api.cpp svm_struct_api.h svm_struct_api_types.h svm_struct/svm_struct_common.h
	# $(CC) -c $(CFLAGS) svm_struct_api.cpp -o svm_struct_api.o
	$(CC) -c $(CFLAGS) svm_struct_api.cpp -o svm_struct_api.o

svm_struct_learn_custom.o: svm_struct_learn_custom.c svm_struct_api.h svm_light/svm_common.h svm_struct_api_types.h svm_struct/svm_struct_common.h
	$(CC) -c $(CFLAGS) svm_struct_learn_custom.c -o svm_struct_learn_custom.o


test: test.cpp
	g++ $(CPPFLAGS) $^ -o $@

run_train:
	./svm_empty_learn -c 1 -w 3 -v 2 -a ./result/check_pre_label.dat ../../hw1/MLDS_HW1_RELEASE_v1/fbank/train.ark ./result/model.dat
	# ./svm_empty_learn -c 1 -w 2  ../hwb_normalize.dat

run_test:
	./svm_empty_classify -v 2 ../../hw1/MLDS_HW1_RELEASE_v1/fbank/test.ark ./result/model.dat ./result/result.csv

