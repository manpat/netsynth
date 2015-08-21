#ifndef KEYBOARDMAP_H
#define KEYBOARDMAP_H

#include "common.h"

#include <map>
#include <QtCore/QString>

class KeyboardMap{
public:
	KeyboardMap();
	
	std::pair<s8, s8> FindNote(quint32 scancode);

private:
	std::map<quint32, std::pair<s8, s8>> map;
};

#endif//KEYBOARDMAP_H