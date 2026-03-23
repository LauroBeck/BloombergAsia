CXX = g++
CXXFLAGS = -I./ta-lib/include -pthread -O3
LDFLAGS = -L./ta-lib/src/.libs -lcurl -lta_lib

all: quant_engine

quant_engine: quant_engine.cpp
	$(CXX) quant_engine.cpp -o quant_engine $(CXXFLAGS) $(LDFLAGS)

clean:
	rm -f quant_engine