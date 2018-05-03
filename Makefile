
# *****************************************************
# Variables to control Makefile operation

CXX = clang++
CXXFLAGS = -Wall -g -std=c++11 -L/usr/local/hdf5/lib /usr/local/hdf5/lib/libhdf5_hl_cpp.a /usr/local/hdf5/lib/libhdf5_cpp.a /usr/local/hdf5/lib/libhdf5_hl.a /usr/local/hdf5/lib/libhdf5.a -lz -ldl -lm -I/usr/local/hdf5/include -Ih5xx -IHighFive/include bender.cpp
# ****************************************************
# Targets needed to bring the executable up to date

main: main.o
	$(CXX) $(CXXFLAGS) -o main main.o 

# The main.o target can be written more simply

main.o: main.cpp 
	$(CXX) $(CXXFLAGS) -c main.cpp 


