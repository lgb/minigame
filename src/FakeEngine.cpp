#include <QtGui>
#include <QtOpenGL>

#include "FakeEngine.h"

FakeEngine::FakeEngine(QWidget *parent)
	: QGLWidget(parent)
{
}

FakeEngine::~FakeEngine()
{
	unloadTextures();
}

void FakeEngine::initializeGL()
{
//	glShadeModel(GL_SMOOTH);
//	glClearColor(0, 0, 0, 0);

	preloadTextures();
	glEnable(GL_TEXTURE_2D);

//	glEnable(GL_DEPTH_TEST);
//	glDepthFunc(GL_LEQUAL);
//	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
//	glClearDepth(1.0);
}

void FakeEngine::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT/* | GL_DEPTH_BUFFER_BIT*/);
	glLoadIdentity();

	glBindTexture(GL_TEXTURE_2D, textureIDs[0]);
	glBegin(GL_QUADS);
		 glTexCoord2f(0.0f, 0.0f);
		 glVertex2f(0.0f, 0.0f);

		 glTexCoord2f(1.0f, 0.0f);
		 glVertex2f(1.0f, 0.0f);

		 glTexCoord2f(1.0f, 1.0f);
		 glVertex2f(1.0f, 1.0f);

		 glTexCoord2f(0.0f, 1.0f);
		 glVertex2f(0.0f, 1.0f);
	glEnd();
}

void FakeEngine::resizeGL(int width, int height)
{
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
//	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1, 100.0);
	glOrtho(0, 1, 0, 1, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void FakeEngine::mousePressEvent(QMouseEvent *event)
{
	QPoint mousePos = event->pos();
}

///////////////////////////////////////////////////////////////////////////////////

const size_t FakeEngine::numTextures = 1;
const char* FakeEngine::textureNames[numTextures] = { ":/res/image.png" };
unsigned int FakeEngine::textureIDs[numTextures] = { 0 };

void FakeEngine::preloadTextures()
{
	QImage image, texture;

	for (size_t textureIndex = 0; textureIndex < numTextures; ++textureIndex)
	{
		if (!image.load(textureNames[textureIndex]))
		{
			assert(false);
		}

		texture = QGLWidget::convertToGLFormat(image);
		glGenTextures(1, &textureIDs[textureIndex]);
		glBindTexture(GL_TEXTURE_2D, textureIDs[textureIndex]);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, texture.width(), texture.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, texture.bits());
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
}

void FakeEngine::unloadTextures()
{
	glDeleteTextures(numTextures, textureIDs);
}
