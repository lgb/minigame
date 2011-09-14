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

};

#endif // WIDGET_H
