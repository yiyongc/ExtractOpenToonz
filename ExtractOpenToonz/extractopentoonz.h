#ifndef EXTRACTOPENTOONZ_H
#define EXTRACTOPENTOONZ_H

#include <QtWidgets/QMainWindow>
#include "ui_extractopentoonz.h"
#include <QVBoxLayout>

class ExtractOpenToonz : public QMainWindow
{
	Q_OBJECT

public:
	ExtractOpenToonz(QWidget *parent = 0);
	~ExtractOpenToonz();

private:
	Ui::ExtractOpenToonzClass ui;
};

#endif // EXTRACTOPENTOONZ_H
