#include "WaterRippleDemo.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	WaterRippleDemo w;
	w.show();
	return a.exec();
}
