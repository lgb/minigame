#include <QtGui>
#include <QtOpenGL>

#include "FakeEngine.h"
#include "Game.h"

FakeEngine::FakeEngine(QWidget *parent)
	: QGLWidget(parent)
{
	miniGame = new Game();
	miniGame->Initialize();
}

FakeEngine::~FakeEngine()
{
	unloadTextures();
	delete miniGame;
}

void FakeEngine::initializeGL()
{
	preloadTextures();
	glEnable(GL_TEXTURE_2D);
}

void FakeEngine::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

	miniGame->Render();
}

void FakeEngine::resizeGL(int width, int height)
{
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 1, 0, 1, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void FakeEngine::mousePressEvent(QMouseEvent *event)
{
	if (!miniGame->IsComplete())
	{
		miniGame->Click(event->posF().x(), event->posF().y());
	}
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
		glTexImage2D(GL_TEXTURE_2D, 0, 3, texture.width(), texture.height(),
						 0, GL_RGBA, GL_UNSIGNED_BYTE, texture.bits());
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
}

void FakeEngine::unloadTextures()
{
	glDeleteTextures(numTextures, textureIDs);
}

void Render(const Rect& screenCoords, int textureId, const Rect& textureCoord)
{
	glBindTexture(GL_TEXTURE_2D, FakeEngine::textureIDs[textureId - 1]);
	glBegin(GL_QUADS);
		 glTexCoord2f(textureCoord.left, textureCoord.top);
		 glVertex2f(screenCoords.left, screenCoords.top);

		 glTexCoord2f(textureCoord.right, textureCoord.top);
		 glVertex2f(screenCoords.right, screenCoords.top);

		 glTexCoord2f(textureCoord.right, textureCoord.bottom);
		 glVertex2f(screenCoords.right, screenCoords.bottom);

		 glTexCoord2f(textureCoord.left, textureCoord.bottom);
		 glVertex2f(screenCoords.left, screenCoords.bottom);
	glEnd();
}
