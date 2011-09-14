#include <QtGui/QApplication>
#include "FakeEngine.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	FakeEngine w;
	w.resize(512, 512);
	w.show();

	return a.exec();
}
