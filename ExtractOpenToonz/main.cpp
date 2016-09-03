#include "extractopentoonz.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	ExtractOpenToonz w;
	w.show();
	return a.exec();
}
