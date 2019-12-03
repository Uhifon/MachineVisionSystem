#include "MachineVisionSystem.h"

#include <QtWidgets>
#include <QDialog>
#include <QtWidgets/QApplication>
#include "FormBinaryzation.h"
#include "FormMorphological.h"

using namespace std;


MachineVisionSystem::MachineVisionSystem(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	connect(ui.btnBinarizeTool, SIGNAL(clicked()), this, SLOT(ThresholdFormShow()));
	connect(ui.btnMorphologicalTool, SIGNAL(clicked()), this, SLOT(MorphologicalFormShow()));
}
 
void MachineVisionSystem::ThresholdFormShow()
{
	FormBinaryzation *form = new FormBinaryzation();
	form->show();
}

void MachineVisionSystem::MorphologicalFormShow()
{
	FormMorphological *form = new FormMorphological();
	form->show();
}
