#ifndef WIDGET_H
#define WIDGET_H

#include <QGLWidget>

class FakeEngine : public QGLWidget
{
	Q_OBJECT

public:
	FakeEngine(QWidget *parent = 0);
	~FakeEngine();

protected:
	void initializeGL();
	void paintGL();
	void resizeGL(int width, int height);
	void mousePressEvent(QMouseEvent *event);

public:
	static void preloadTextures();
	static void unloadTextures();

	static const size_t numTextures;
	static const char* textureNames[];
	static unsigned int textureIDs[];

};

#endif // WIDGET_H
