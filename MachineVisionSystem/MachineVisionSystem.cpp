#include "MachineVisionSystem.h"

#include <QtWidgets>
#include <QDialog>
#include <QtWidgets/QApplication>
#include "FormBinaryzation.h"
#include "FormMorphological.h"
#include "FormFiltering.h"
#include "FormColorExtraction.h"
#include "FormCheckScratch.h"


using namespace std;


MachineVisionSystem::MachineVisionSystem(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
 

}
 
void MachineVisionSystem::btnBinarizeToolClick()
{
	FormBinaryzation *form = new FormBinaryzation();
	form->show();
}

void MachineVisionSystem::btnMorphologicalToolClick()
{
	FormMorphological *form = new FormMorphological();
	form->show();
}
void MachineVisionSystem::btnFilteringToolClick()
{
	FormFiltering *form = new FormFiltering();
	form->show();

}

void MachineVisionSystem::btnColorExtractionToolClick()
{
	FormColorExtraction *form = new FormColorExtraction();
	form->show();

}

void MachineVisionSystem::btnCheckScratchClick()
{
	FormCheckScratch *form = new FormCheckScratch();
	form->show();

}
