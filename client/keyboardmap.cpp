#include "keyboardmap.h"

KeyboardMap::KeyboardMap() {
	map.insert(std::make_pair(Qt::Key_Q, std::make_pair(0, 1))); // Q
	map.insert(std::make_pair(Qt::Key_W, std::make_pair(1, 1))); // W
	map.insert(std::make_pair(Qt::Key_E, std::make_pair(2, 1))); // E
	map.insert(std::make_pair(Qt::Key_R, std::make_pair(3, 1))); // R
	map.insert(std::make_pair(Qt::Key_T, std::make_pair(4, 1))); // T
	map.insert(std::make_pair(Qt::Key_Y, std::make_pair(5, 1))); // Y
	map.insert(std::make_pair(Qt::Key_U, std::make_pair(6, 1))); // U
	map.insert(std::make_pair(Qt::Key_I, std::make_pair(7, 1))); // I
	map.insert(std::make_pair(Qt::Key_O, std::make_pair(8, 1))); // O
	map.insert(std::make_pair(Qt::Key_P, std::make_pair(9, 1))); // P

	map.insert(std::make_pair(Qt::Key_A, std::make_pair(0, 0))); // A
	map.insert(std::make_pair(Qt::Key_S, std::make_pair(1, 0))); // S
	map.insert(std::make_pair(Qt::Key_D, std::make_pair(2, 0))); // D
	map.insert(std::make_pair(Qt::Key_F, std::make_pair(3, 0))); // F
	map.insert(std::make_pair(Qt::Key_G, std::make_pair(4, 0))); // G
	map.insert(std::make_pair(Qt::Key_H, std::make_pair(5, 0))); // H
	map.insert(std::make_pair(Qt::Key_J, std::make_pair(6, 0))); // J
	map.insert(std::make_pair(Qt::Key_K, std::make_pair(7, 0))); // K
	map.insert(std::make_pair(Qt::Key_L, std::make_pair(8, 0))); // L

	map.insert(std::make_pair(Qt::Key_Z, std::make_pair(0, -1))); // Z
	map.insert(std::make_pair(Qt::Key_X, std::make_pair(1, -1))); // X
	map.insert(std::make_pair(Qt::Key_C, std::make_pair(2, -1))); // C
	map.insert(std::make_pair(Qt::Key_V, std::make_pair(3, -1))); // V
	map.insert(std::make_pair(Qt::Key_B, std::make_pair(4, -1))); // B
	map.insert(std::make_pair(Qt::Key_N, std::make_pair(5, -1))); // N
	map.insert(std::make_pair(Qt::Key_M, std::make_pair(6, -1))); // M
}

std::pair<s8, s8> KeyboardMap::FindNote(quint32 scancode) {
	auto it = map.find(scancode);
	if (it != map.end()) {
		return it->second;
	}

	return { -100, -100 };
}