#include <QtGui/QApplication>
#include "FakeEngine.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	FakeEngine w;
	w.resize(FakeEngine::width, FakeEngine::height);
	w.show();

	return a.exec();
}
