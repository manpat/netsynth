#include <iostream>
#include <fstream>
#include <string>
#include "app.h"

#include <QtGui/QApplication>
#include <QtGui/QWidget>
#include <QtGui/QFont>

#include "stylesheet.h"

int main(int ac, char** av){
	try{
		std::cout << "NetSynth" << std::endl;
		QApplication a(ac, av);
		App w;

		a.setStyleSheet(stylesheet);
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
		std::cout << "Some Unknown Exception Happened!" << std::endl;
		return 1;
	}

	return 0;
}