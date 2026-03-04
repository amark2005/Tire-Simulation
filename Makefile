CXX = g++
CXXFLAGS = -std=c++20 -O3 -flto -funroll-loops -ffast-math -fomit-frame-pointer \
           -finline-functions -fno-signed-zeros -fno-trapping-math \
           -fipa-pta -fipa-cp -fipa-bit-cp -fdevirtualize -fdevirtualize-at-ltrans \
           -Wall -Wextra

TARGET = tire
SRC = tire.cpp

all: $(TARGET)
	./$(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)