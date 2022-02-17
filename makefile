CXX ?= g++

DEBUG ?= 1
ifeq ($(DEBUG), 1)
    CXXFLAGS += -g
else
    CXXFLAGS += -O2

endif

server: main.cpp  http/httpConn.cpp 
	$(CXX) -o debug/server  $^ $(CXXFLAGS) -lpthread 

clean:
	rm  -r server