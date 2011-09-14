#include <QtGui>
#include <QtOpenGL>

#include "widget.h"

FakeEngine::FakeEngine(QWidget *parent)
	: QGLWidget(parent)
{
}

FakeEngine::~FakeEngine()
{
}

void FakeEngine::initializeGL()
{
//	qglClearColor(qtPurple.dark());

//	logo = new QtLogo(this, 64);
//	logo->setColor(qtGreen.dark());

//	glEnable(GL_DEPTH_TEST);
//	glEnable(GL_CULL_FACE);
//	glShadeModel(GL_SMOOTH);
//	glEnable(GL_LIGHTING);
//	glEnable(GL_LIGHT0);
//	glEnable(GL_MULTISAMPLE);
//	static GLfloat lightPosition[4] = { 0.5, 5.0, 7.0, 1.0 };
//	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
}

void FakeEngine::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
//	glTranslatef(0.0, 0.0, -10.0);
//	glRotatef(xRot / 16.0, 1.0, 0.0, 0.0);
//	glRotatef(yRot / 16.0, 0.0, 1.0, 0.0);
//	glRotatef(zRot / 16.0, 0.0, 0.0, 1.0);
//	logo->draw();
}

void FakeEngine::resizeGL(int width, int height)
{
	int side = qMin(width, height);
	glViewport((width - side) / 2, (height - side) / 2, side, side);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-0.5, +0.5, -0.5, +0.5, 4.0, 15.0);
	glMatrixMode(GL_MODELVIEW);
}

void FakeEngine::mousePressEvent(QMouseEvent *event)
{
	QPoint mousePos = event->pos();
}

