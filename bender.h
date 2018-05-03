/*
 * bender.h
 * Copyright (C) 2018 davidpatrick <davidpatrick@Lees-MBP.fios-router.home>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef BENDER_H
#define BENDER_H

class bender{

	private: 	
				
	public: 
		//This constructor will temporarily remain empy
		bender();	
		//Used purely for testing data
		void printData(boost::numeric::ublas::matrix<double> node);
		//Ran at the beginning, similar to 'load' in matlab
		void initializeData();
		//TODO: Create a save function saveData(); to export back to hdf5.
		//Function that converts Hdf5 -> stl vector(using the high five wrapper),
		//then converts stl vector -> boost matrix. If necessary, I will make 
		//a vector equivelant. 
		boost::numeric::ublas::matrix<double> createMatrix(std::string, int,int);
		//Creates a vector, however it cannot differentiate mx1 vs 1xm
		//so it's safer to just pull everything in as a matrix
		boost::numeric::ublas::vector<double> createVector(std::string, int);
		//Setters for our struct
		boost::numeric::ublas::zero_vector<double> createZVector(int);
		boost::numeric::ublas::vector<double> createVector(int);
		boost::numeric::ublas::zero_matrix<double> createZMatrix(int,int);
		//Returns a single row from a matrix, similar to matrix(m,:) in matlab
		boost::numeric::ublas::vector<double> getRow(boost::numeric::ublas::matrix<double>,int);
		//Reads in a single value from our hdf5 data
		double getSingleValue(std::string);
		/*
		 *Converted matlab helper functions
		 */
		//ismember
		bool ismember(double, boost::numeric::ublas::matrix<double>);
		//setdiff
		boost::numeric::ublas::vector<double> setdiff(boost::numeric::ublas::vector<double>, boost::numeric::ublas::vector<double>);


	struct {
		//Copying in hdf5 structured data when needed
		//as I convert over	
		boost::numeric::ublas::matrix<double> AREACONSTRAINT;
		boost::numeric::ublas::matrix<double> node;
		boost::numeric::ublas::matrix<double> neighbor;
		boost::numeric::ublas::matrix<double> elem;
		boost::numeric::ublas::matrix<double> edgeinfo;	
		boost::numeric::ublas::matrix<double> edge2elem;
		boost::numeric::ublas::vector<double> NetRJ;	
		boost::numeric::ublas::zero_vector<double> NetRK;
		boost::numeric::ublas::zero_vector<double> NetRI;
		boost::numeric::ublas::zero_vector<double> NetRL;
		boost::numeric::ublas::zero_matrix<double> BendNet;
		boost::numeric::ublas::vector<double> CANDIDATE;
		boost::numeric::ublas::vector<double> CANDIDATE2;	
		boost::numeric::ublas::matrix<double> OMEGA;
		boost::numeric::ublas::matrix<double> OMEGA1;
		boost::numeric::ublas::matrix<double> OMEGA2;
		boost::numeric::ublas::vector<double> HEAD;
		boost::numeric::ublas::vector<double> TAIL;
		double theta0;
		double theta0b;
		double theta0m;
		double kb;
		double kbb;
		double kbp;
		double kbm;	
	};

};

#endif /* !BENDER_H */
