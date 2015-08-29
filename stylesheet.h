static const char* stylesheet = R"(
* {
	border: none;
	background-color: #222;
	color: #aaa;
	show-decoration-selected: 0;
}

QTabBar::tab {
	padding: 8px 20px;
}

QTabBar::tab:!selected {
	background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, 
		stop: 0 #222, stop: 0.949999 #222, stop: 0.95 #444)
}
QTabBar::tab:hover {
	background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,
		stop: 0 #222, stop: 0.899 #222, stop: 0.9 #454545)
}
QTabBar::tab:selected {
	background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,
		stop: 0 #222, stop: 0.9 #222, stop: 0.91 #555)
}
)";