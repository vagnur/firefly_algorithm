TARGET=fa

CXX=g++
CXXFLAGS=-std=c++14 -g -ggdb -Wall -O3
INCLUDE=-I./include
OBJS=obj/enviroment.o obj/firefly.o obj/firefly_algorithm.o

all:
	 make $(TARGET)

$(TARGET):$(OBJS)
		    $(CXX) $^ -o $@ $(CXXFLAGS) $(INCLUDE) 

obj/enviroment.o:src/enviroment.cc include/enviroment.hh
				$(CXX) $< -c -o $@ $(CXXFLAGS) $(INCLUDE)
obj/firefly.o:src/firefly.cc include/firefly.hh
				$(CXX) $< -c -o $@ $(CXXFLAGS) $(INCLUDE)
obj/firefly_algorithm.o:src/fireflyalgorithm.cc
				$(CXX) $< -c -o $@ $(CXXFLAGS) $(INCLUDE)
				
clean:
	${RM} $(OBJS) $(TARGET) 