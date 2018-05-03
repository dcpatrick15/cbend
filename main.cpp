/*
 * main.cpp
 * Copyright (C) 2018 davidpatrick <davidpatrick@Lees-MBP.fios-router.home>
 *
 * Distributed under terms of the MIT license.
 */


#include <highfive/H5File.hpp>
#include <highfive/H5DataSet.hpp>
#include <highfive/H5DataSpace.hpp>
#include <iostream>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp> 

#include "bender.h"


using namespace boost::numeric::ublas;
using namespace HighFive;
int main(){
	
	
	bender bendy;
	//Initialize All variables 
	bendy.initializeData();	
	int onoff = 0;
	//Switch for L-J Repulsion; 1 = ON, 0 = OFF
	int DenseEffect = 1e0;
	//How much movement is affected due to induced viscosity	
	//SPRING = 1;
	//Determine the linear or nonlinear spring; 0:=no spring, 1:= linear
	//2:= nonlinear
	//LT = 1;
	//Determine the line tension type; 1:=sharp boundary, 2:= interface
	int STOP = 0;
	//Indication if any abnormal behavior is detected. Generally this is
	//done by checking the existence of large magnitude of movement. 
	//Normal = 0, Abnormal = 1;	
	int MAXSTEP = 1;	
	//Starting Main Loop
	bendy.printData(bendy.node);	
	
	for(int step =1;step<=MAXSTEP;step++){
		for(int i=1;i<5;i++){
			bendy.CANDIDATE = bendy.getRow(bendy.elem, bendy.edge2elem(i-1,0)-1);		
			bendy.CANDIDATE2 = bendy.getRow(bendy.elem, bendy.edge2elem(i-1,1)-1);	
			if(bendy.ismember(bendy.edge2elem(i-1,0)-1,bendy.OMEGA1) ==1 && bendy.ismember(bendy.edge2elem(i-1,1)-1,bendy.OMEGA1) ==1){
				bendy.theta0 = bendy.theta0b;			
				bendy.kb = bendy.kbp;
			}
			else if(bendy.ismember(bendy.edge2elem(i-1,0)-1,bendy.OMEGA1) ==0 && bendy.ismember(bendy.edge2elem(i-1,0)-1,bendy.OMEGA) ==1&&bendy.ismember(bendy.edge2elem(i-1,1)-1,bendy.OMEGA1) ==1){
				bendy.theta0 = (bendy.theta0b + bendy.theta0m)/2;
				bendy.kb = (bendy.kbp + bendy.kbb)/2;
			}
			else if(bendy.ismember(bendy.edge2elem(i-1,0)-1,bendy.OMEGA) ==1&&bendy.ismember(bendy.edge2elem(i-1,1)-1,bendy.OMEGA) ==0){
				bendy.theta0 = bendy.theta0m;
				bendy.kb = bendy.kbb;
			}
			else if(bendy.ismember(bendy.edge2elem(i-1,0)-1,bendy.OMEGA) ==1 && bendy.ismember(bendy.edge2elem(i-1,1)-1,bendy.OMEGA1) ==0 &&bendy.ismember(bendy.edge2elem(i-1,1)-1,bendy.OMEGA) ==0){
				bendy.theta0 = bendy.theta0m;
				bendy.kb = (bendy.kbb + bendy.kbm)/2;
			}
			else if(bendy.ismember(bendy.edge2elem(i-1,0)-1,bendy.OMEGA) ==0 && bendy.ismember(bendy.edge2elem(i-1,0)-1,bendy.OMEGA1) == 0 &&bendy.ismember(bendy.edge2elem(i-1,1)-1,bendy.OMEGA) ==1){
				bendy.theta0 = bendy.theta0m;
				bendy.kb = (bendy.kbb + bendy.kbm)/2;
			}
			else{
				bendy.theta0 = bendy.theta0m;
				bendy.kb = bendy.kbm;	
			
			}
		bendy.HEAD = bendy.setdiff(bendy.CANDIDATE, bendy.getRow(bendy.edgeinfo, i));			
		bendy.TAIL = bendy.setdiff(bendy.CANDIDATE2, bendy.getRow(bendy.edgeinfo, i));	

		//TODO: Skip bending, elas_F_liquid_ordered 

		}//ith for loop end bracket	
	}//steph for loop end bracket
	return 0;
}
