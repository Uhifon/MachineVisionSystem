#include "MachineVisionSystem.h"

#include <QtWidgets>
#include <QDialog>
#include <QtWidgets/QApplication>
#include "FormBinaryzation.h"

using namespace std;


MachineVisionSystem::MachineVisionSystem(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	connect(ui.btnBinarizeTool, SIGNAL(clicked()), this, SLOT(BinarizeDialogShow()));
}

void MachineVisionSystem::BinarizeDialogShow()
{
	FormBinaryzation *form = new FormBinaryzation();
	form->show();
}