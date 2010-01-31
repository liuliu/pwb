CXX=g++
COMPFLAG=-O3 -mmmx -msse2 -msse3 -fopenmp --fast-math
LINKFLAG=-lcxcore -lcv -lhighgui -lgsl -lgslcblas -lm
OPENCV=/opt/opencv
LINKLIB=-L"$(OPENCV)/lib"
CXXFLAGS=-I"$(OPENCV)/include/opencv" -I"/usr/local/include"

all: pwbcreate

pwbcreate: pwbcreate.o
	$(CXX) $(CXXFLAGS) $(LINKLIB) -o $@ $^ $(LINKFLAG)

clean:
	rm *.o

.c.o:
	$(CXX) $(CXXFLAGS) $< -o $@ -c $(COMPFLAG)

.cpp.o:
	$(CXX) $(CXXFLAGS) $< -o $@ -c $(COMPFLAG)

.cc.o:
	$(CXX) $(CXXFLAGS) $< -o $@ -c $(COMPFLAG)

