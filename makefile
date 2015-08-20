PREFIX ?= 
INCLUDES  := -I/usr/include/qt4 -I/home/patrick/Development/libraries/fmodstudio/api/lowlevel/inc
SRCFLAGS  := -std=c++11 -Wall $(INCLUDES) -I$(PREFIX) -I.
LINKFLAGS := 
LIBS := -Wl,--rpath=lib -lQtGui -lQtCore lib/libfmod.so.6

MOC := $(shell find $(PREFIX) -name "moc_*.h")
SRC := $(shell find $(PREFIX) -name "*.cpp") $(MOC:%.h=%.cpp)
OBJ := $(SRC:%.cpp=%.o) $(PREFIX)/main.o

ifeq ($(PREFIX), server)
SRCFLAGS += -DSERVER
endif

.PHONY: build all
.SUFFIXES:

default: checkdirs
	@# @make -j4 build -r --silent PREFIX=server
	@make -j4 build -r --silent PREFIX=client

build: $(OBJ)
	@echo "-- Building $(PREFIX) --"
	@g++ $(LINKFLAGS) $^ $(LIBS) -o$(PREFIX)/build

checkdirs:
	@if [ ! -d server ]; then mkdir server; fi
	@if [ ! -d client ]; then mkdir client; fi

$(PREFIX)/main.o: main.cpp app.h
	@echo "-- Generating $(PREFIX) main --"
	@g++ $(SRCFLAGS) -c main.cpp -o $@

moc_%.cpp: moc_%.h
	@echo "-- Generating $@ --"
	@moc-qt4 $(INCLUDES) $^ -o$@

%.o: %.cpp %.h
	@echo "-- Generating $@ --"
	@g++ $(SRCFLAGS) -c $< -o $@

%.o: %.cpp
	@echo "-- Generating $@ --"
	@g++ $(SRCFLAGS) -c $< -o $@

clean:
	@echo "-- Cleaning --"
	@rm -r */*.o
	@rm -r */build

run: default
	@echo "-- Running --"
	# @server/build
	@client/build