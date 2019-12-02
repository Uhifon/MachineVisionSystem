#pragma once

#include <QtWidgets/QMainWindow>

#include "ui_MachineVisionSystem.h"


class MachineVisionSystem : public QMainWindow
{
	Q_OBJECT

public:
	MachineVisionSystem(QWidget *parent = Q_NULLPTR);

private:
	Ui::MachineVisionSystemClass ui;
	 

signals:


private slots:
     void BinarizeDialogShow();
};
