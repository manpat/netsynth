#ifndef MOC_SERVERGUI_H
#define MOC_SERVERGUI_H

#include <map>
#include <QtGui/QWidget>
#include <QtGui/QHBoxLayout>
#include "common.h"

class VisualizationSlider;

class ServerGUI : public QWidget {
	Q_OBJECT
public:
	std::map<u32, VisualizationSlider*> sliders;
	QHBoxLayout* layout;

	ServerGUI(QWidget* = nullptr);

	void UpdateSlider(u32 id, u32 val);

private slots:
	void AddSlider(u32 id);
	void RemoveSlider(u32 id);

};

#endif//MOC_SERVERGUI_H