
# *****************************************************
# Variables to control Makefile operation

CXX = clang++
CXXFLAGS = -Wall -g -L/Users/davidpatrick/anaconda/lib -L/usr/local/hdf5/lib -lhdf5_hl_cpp -lhdf5_cpp -lhdf5_hl -lhdf5 -lpthread -lz -ldl -lm -I/usr/local/hdf5/include -lstdc++ 

# ****************************************************
# Targets needed to bring the executable up to date

main: main.o
	$(CXX) $(CXXFLAGS) -o main main.o 

# The main.o target can be written more simply

main.o: main.cpp 
	$(CXX) $(CXXFLAGS) -c main.cpp 


