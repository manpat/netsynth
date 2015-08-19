INCLUDES  := -I/usr/include/qt4 -I/home/patrick/Development/libraries/fmodstudio/api/lowlevel/inc
CXXFLAGS  := -std=c++11 -Wall $(INCLUDES)
LINKFLAGS := 
LIBS := -Wl,--rpath=lib -lQtGui -lQtCore lib/libfmod.so.6

CXXFLAGS += -DSERVER

MOC := $(shell find . -name "moc_*")
SRC := $(shell find . -name "*.cpp") $(MOC:%.h=%.cpp)
OBJ := $(SRC:%.cpp=%.o)

.PHONY: build

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