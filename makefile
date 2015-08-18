INCLUDES  := -I/usr/include/qt4
CXXFLAGS  := -std=c++11 -Wall -DSERVER $(INCLUDES)
LINKFLAGS := 
LIBS := -lQtGui -lQtCore

MOC := $(shell find . -name "moc_*")
SRC := $(shell find . -name "*.cpp") $(MOC:%.h=%.cpp)
OBJ := $(SRC:%.cpp=%.o)

build: $(OBJ)
	@g++ $(LINKFLAGS) $^ $(LIBS) -obuild

moc_%.cpp: moc_%.h
	@echo "-- Generating $@ --"
	@moc-qt4 $(INCLUDES) $^ -o$@

moc_%.cpp: moc_%.h %.cpp
	@echo "-- Generating $@ --"
	@moc-qt4 $(INCLUDES) $^ -o$@

%.o: %.cpp %.h
	@echo "-- Generating $@ --"
	@g++ $(CXXFLAGS) -c $< -o $@
	
%.o: %.cpp
	@echo "-- Generating $@ --"
	@g++ $(CXXFLAGS) -c $< -o $@


clean:
	@echo "-- Cleaning --"
	@rm *.o

run: build
	@echo "-- Running --"
	@./build