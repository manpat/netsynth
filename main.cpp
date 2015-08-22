#include <iostream>
#include <fstream>
#include <string>
#include "app.h"

#include <QtGui/QApplication>
#include <QtGui/QWidget>
#include <QtGui/QFont>

int main(int ac, char** av){
	try{
		std::cout << "NetSynth" << std::endl;
		QApplication a(ac, av);

		std::ifstream f("stylesheet.css");
		if(!f) throw "Stylesheet open failed";

		f.seekg(0, f.end);
		std::string css(f.tellg(), '\0');
		f.seekg(0, f.beg);
		f.read(&css[0], css.size());
		f.close();

		a.setStyleSheet(css.data());
		
		App w;

		return a.exec();
		
	}catch(const char* e){
		std::cout << "Exception!\n" << e << std::endl;
		return 1;

	}catch(const std::string& e){
		std::cout << "Exception!\n" << e << std::endl;
		return 1;

	}catch(const std::exception& e){
		std::cout << "Exception!\n" << e.what() << std::endl;
		return 1;

	}catch(...){
		std::cout << "Some Exception Happened!" << std::endl;
		std::cout << "Add good exceptions now!" << std::endl;
		return 1;
	}

	return 0;
}