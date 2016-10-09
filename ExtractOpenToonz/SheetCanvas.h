#ifndef SHEETCANVAS_H
#define SHEETCANVAS_H


#include <QGLWidget>
#include <QWidget>
#include <qopengl.h>
#include <QMouseEvent>
#include "Skeleton.h"
#include <glut.h>

class SheetCanvas : public QGLWidget {
	
	Q_OBJECT

public:
	SheetCanvas(QWidget* parent = 0);
	~SheetCanvas();


protected:
	void initializeGL();
	void paintGL();
	void resizeGL(int width, int height);

	static void qNormalizeAngle(int &angle);

	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);

	QSize minimumSizeHint() const;
	QSize sizeHint() const;



private:
	int xRot;
	int yRot;
	int zRot;
	QPoint lastPos;
	bool drawSkel = false;
	Skeleton* m_skeleton;

	GLdouble ox = 0.0, oy = 0.0, oz = 0.0;

	void draw();
	void drawVertex(SkeletonVertex* v);
	void Mouse(double x, double y);

	public slots:
	void setXRotation(int angle);
	void setYRotation(int angle);
	void setZRotation(int angle);

signals:
	void xRotationChanged(int angle);
	void yRotationChanged(int angle);
	void zRotationChanged(int angle);

};

#endif // SHEETCANVAS_H