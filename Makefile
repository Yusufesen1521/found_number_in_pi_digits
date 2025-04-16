CXX = g++
CXXFLAGS = -Wall -std=c++11
LDFLAGS = -lcurl

TARGET = pi_checker
SOURCE = pi_checker.cpp

all: $(TARGET)

$(TARGET): $(SOURCE)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCE) $(LDFLAGS)

clean:
	rm -f $(TARGET) 