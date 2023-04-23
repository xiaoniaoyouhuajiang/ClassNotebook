BIN_NAME=oop2.exe
CXX ?= g++

CXXFLAGS += -D_USE_MATH_DEFINES -I$(GTEST_REPO)/googletest/include -I$(GTEST_REPO)/googlemock/include -I.

all: $(BIN_NAME)

gtest-all.o:
ifndef GTEST_REPO
	$(error GTEST_REPO is undefined)
endif
	$(CXX) $(CPPFLAGS) -I$(GTEST_REPO)/googletest $(CXXFLAGS) -c \
            $(GTEST_REPO)/googletest/src/gtest-all.cc

gmock-all.o: 
ifndef GTEST_REPO
	$(error GTEST_REPO is undefined)
endif
	$(CXX) $(CPPFLAGS) -I$(GTEST_REPO)/googlemock $(CXXFLAGS) -c \
            $(GTEST_REPO)/googlemock/src/gmock-all.cc

$(BIN_NAME): gtest-all.o gmock-all.o
	g++ main.cpp gtest-all.o gmock-all.o $(CXXFLAGS) -o $(BIN_NAME)

.PHONY: clean
clean:
	rm -f *.o $(BIN_NAME)
