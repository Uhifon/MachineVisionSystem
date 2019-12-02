#include "MachineVisionSystem.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv); 
	MachineVisionSystem w;
	w.show();

	
	return a.exec();
}
