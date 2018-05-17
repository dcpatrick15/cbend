/*
 * bender.cpp
 * Copyright (C) 2018 davidpatrick <davidpatrick@Lees-MBP.fios-router.home>
 *
 * Distributed under terms of the MIT license.
 */



#include <highfive/H5File.hpp>
#include <highfive/H5DataSet.hpp>
#include <highfive/H5DataSpace.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/io.hpp> 
#include <boost/range/algorithm.hpp>
#include <algorithm>
#include <string>



#include "bender.h"


const std::string FILE_NAME("data.h5");

//Empty Constructor
bender::bender(){}

//createMatrix(dataset, rows, cols)
boost::numeric::ublas::matrix<double> bender::createMatrix(std::string dataset, int rows,int cols){
	HighFive::File file(FILE_NAME, HighFive::File::ReadOnly);
	std::vector<std::vector<double>> m;

	boost::numeric::ublas::matrix<double> mat(rows,cols);
	HighFive::DataSet dset = file.getDataSet(dataset);
	dset.read(m);

	for(int i =0;i<rows;i++){
		for(int j = 0;j<cols;j++){
			//Copies an std vector to more useable
			//boost matrix
			mat(i,j) = m[j][i];
		}	
	}
	return mat;
}
//createVector(dataset, rows)
boost::numeric::ublas::vector<double> bender::createVector(std::string dataset, int rows){
	
	HighFive::File file(FILE_NAME, HighFive::File::ReadOnly);
	std::vector<std::vector<double>> v;

	HighFive::DataSet dset = file.getDataSet(dataset);
	dset.read(v);

	boost::numeric::ublas::vector<double> vec(rows);
	for(int i=0;i<rows;i++){
		vec(i) = v[i][0];
	}

	return vec;
}
//createZVector(size) -> zero vector
boost::numeric::ublas::zero_vector<double> bender::createZVector(int size){	
	boost::numeric::ublas::zero_vector<double> zvec(size);
	return zvec;
}
//createVector(size)
boost::numeric::ublas::vector<double> bender::createVector(int size){	
	boost::numeric::ublas::vector<double> vec(size);
	return vec;
}
//getRow(matrix, row)
boost::numeric::ublas::vector<double> bender::getRow(boost::numeric::ublas::matrix<double> mat, int row){	
	boost::numeric::ublas::vector<double> result(mat.size2());
	for(int i = 0;i<mat.size2();i++){
		result(i) = mat(row, i);	
	}
	return result;
}
//createZMatrix(row, col)
boost::numeric::ublas::zero_matrix<double> bender::createZMatrix(int row,int col){	
	boost::numeric::ublas::zero_matrix<double> zmat(row, col);
	return zmat;
}
//ismember(edge, mat)
bool bender::ismember(double edge, boost::numeric::ublas::matrix<double> mat){

	bool found = false;
	
	for(auto itr1 = mat.begin1(); itr1!=mat.end1(); ++itr1){
		for(auto itr2 = itr1.begin(); itr2!=itr1.end(); ++itr2){
			if(edge == *itr2){
				found = true;
				break;	
			}	
		}	
	}
	return found;
}
//setdiff
boost::numeric::ublas::vector<double> bender::setdiff(boost::numeric::ublas::vector<double> vec1, boost::numeric::ublas::vector<double> vec2){

	std::vector<double> tempHolder;
	boost::range::set_difference(boost::range::sort(vec1), boost::range::sort(vec2), std::back_inserter(tempHolder));
	boost::numeric::ublas::vector<double> result(tempHolder.size());

	for(int i =0;i<tempHolder.size();i++){
		result(i) = tempHolder[i];	
	}	

	return result;
}

//getSingleValue(dataset)
double bender::getSingleValue(std::string dataset){
	boost::numeric::ublas::vector<double> v(1);
	v = this->createVector(dataset, 1);
	return v(0);

}
//printData(mat)
void bender::printData(boost::numeric::ublas::matrix<double> mat){

	for(int i =0;i<mat.size1();i++){
		for(int j = 0;j<mat.size2();j++){
			std::cout<<mat(i,j)<<" ";	
		}	
		std::cout<<""<<std::endl;
	}
}
//elas_F_liquid_ordered
boost::numeric::ublas::matrix<double> bender::elas_F_liquid_ordered(boost::numeric::ublas::matrix<double> node, boost::numeric::ublas::matrix<double> nndata,double ksp, double ksb,double ksm, double R0b, double R0m, boost::numeric::ublas::matrix<double> OMEGA3, boost::numeric::ublas::matrix<double> LIQUID_ORDERED_NODE){
	//For now, we'll use this uncapetlized version, can't come up with
	//any unique names
	boost::numeric::ublas::matrix<double> elasf;
	boost::numeric::ublas::matrix<double> NetF;
	boost::numeric::ublas::vector<double> Rij(3);
	double mRij;
	double ks;
	double R0;
	//std::cout<<"ndata.size2(): "<<nndata.size2()<<std::endl;	
	
	//std::cout<<"getrow: "<<this->getRow(node, nndata(5,3)-1) <<std::endl;
	//std::cout<<nndata<<std::endl;
	//node.size1()
	for(int m =1;m<=5;m++){
		for(int j =1;j<=nndata.size2();j++){
			if(nndata(m-1,j-1)> 0){
				Rij = this->getRow(node, nndata(m-1,j-1)-1) - this->getRow(node, m-1);	
				mRij = boost::numeric::ublas::norm_2(Rij);
	
				if(this->ismember(m,OMEGA3)==1 && this->ismember(nndata(m-1,j-1), OMEGA3) ==1){
				ks = ksp;
				R0 = R0b;
				}
				else if(this->ismember(m,OMEGA3)==1 && this->ismember(nndata(m-1,j-1), LIQUID_ORDERED_NODE) ==1){

				ks = (ksp + ksb)/2;
				R0 = (R0b + R0b)/2;
				//Don't go any further until above is further clarified
				}
				
				
				
			}


		}	
	
	
	}

	//std::cout<<this->getRow(node, nndata(5,2)-1) <<std::endl;
	return elasf;
}
//initializeData()
void bender::initializeData(){
	//Load Matrices and Vectors here
	this->node = this->createMatrix("/node", 817, 3);
	this->AREACONSTRAINT = this->createMatrix("/AREACONSTRAINT", 817,3);
	this->neighbor = this->createMatrix("/neighbor",1536, 3);
	this->elem = this->createMatrix("/elem",1536, 3);
	this->edgeinfo = this->createMatrix("/edgeinfo",2352, 2);
	this->edge2elem = this->createMatrix("/edge2elem",2352, 2);
	this->NetRJ = this->createZVector(3);
	this->NetRK = this->createZVector(3);
	this->NetRI = this->createZVector(3);
	this->NetRL = this->createZVector(3);
	this->BendNet = this->createZMatrix(this->node.size1(),this->node.size2());
	this->CANDIDATE = this->createVector(3); 
	this->CANDIDATE2 = this->createVector(3);
	this->OMEGA = this->createMatrix("/OMEGA", 450,1);
	this->OMEGA1 = this->createMatrix("/OMEGA1", 42,1);
	this->OMEGA2 = this->createMatrix("/OMEGA2", 1,1494);
	//this->HEAD = this->createVector(3);
	//this->TAIL = this->createVector(3);
	//Load single values here
	this->theta0b = this->getSingleValue("/theta0b");
	this->theta0m = this->getSingleValue("/theta0m");
	this->kbb = this->getSingleValue("/kbb");
	this->kbp = this->getSingleValue("/kbp");
	this->kbm = this->getSingleValue("/kbm");
	this->nndata = this->createMatrix("/nndata", 817,6);
	this->OMEGA3 = this->createMatrix("/OMEGA3", 31,1);
	this->LIQUID_ORDERED_NODE = this->createMatrix("/LIQUID_ORDERED_NODE", 211,1);
	this->ksp = this->getSingleValue("/ksp");
	this->ksb = this->getSingleValue("/ksb");
	this->ksm = this->getSingleValue("/ksm");
	this->R0b = this->getSingleValue("/R0b");
	this->R0m = this->getSingleValue("/R0m");
}
