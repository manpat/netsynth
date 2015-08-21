#include "keyboardmap.h"

KeyboardMap::KeyboardMap() {
	map.insert(std::make_pair(16, std::make_pair(0, 1))); // Q
	map.insert(std::make_pair(17, std::make_pair(1, 1))); // W
	map.insert(std::make_pair(18, std::make_pair(2, 1))); // E
	map.insert(std::make_pair(19, std::make_pair(3, 1))); // R
	map.insert(std::make_pair(20, std::make_pair(4, 1))); // T
	map.insert(std::make_pair(21, std::make_pair(5, 1))); // Y
	map.insert(std::make_pair(22, std::make_pair(6, 1))); // U
	map.insert(std::make_pair(23, std::make_pair(7, 1))); // I
	map.insert(std::make_pair(24, std::make_pair(8, 1))); // O
	map.insert(std::make_pair(25, std::make_pair(9, 1))); // P

	map.insert(std::make_pair(30, std::make_pair(0, 0))); // A
	map.insert(std::make_pair(31, std::make_pair(1, 0))); // S
	map.insert(std::make_pair(32, std::make_pair(2, 0))); // D
	map.insert(std::make_pair(33, std::make_pair(3, 0))); // F
	map.insert(std::make_pair(34, std::make_pair(4, 0))); // G
	map.insert(std::make_pair(35, std::make_pair(5, 0))); // H
	map.insert(std::make_pair(36, std::make_pair(6, 0))); // J
	map.insert(std::make_pair(37, std::make_pair(7, 0))); // K
	map.insert(std::make_pair(38, std::make_pair(8, 0))); // L

	map.insert(std::make_pair(44, std::make_pair(0, -1))); // Z
	map.insert(std::make_pair(45, std::make_pair(1, -1))); // X
	map.insert(std::make_pair(46, std::make_pair(2, -1))); // C
	map.insert(std::make_pair(47, std::make_pair(3, -1))); // V
	map.insert(std::make_pair(48, std::make_pair(4, -1))); // B
	map.insert(std::make_pair(49, std::make_pair(5, -1))); // N
	map.insert(std::make_pair(50, std::make_pair(6, -1))); // M
}

std::pair<s8, s8> KeyboardMap::FindNote(quint32 scancode) {
	auto it = map.find(scancode);
	if (it != map.end()) {
		return it->second;
	}

	return { -100, -100 };
}