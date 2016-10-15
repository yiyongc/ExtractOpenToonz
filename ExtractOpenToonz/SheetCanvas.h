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
	float vertexRadius = 0.015;
	int win_width, win_height;


	int selectedVertex = -1;




	GLdouble startX = 0.0, startY = 0.0, startZ = 0.0;
	GLdouble objX = 0.0, objY = 0.0, objZ = 0.0;

	//void draw();
	void drawVertex(SkeletonVertex* v);
	void drawBone(SkeletonVertex* v1, SkeletonVertex* v2);
	void mouseToWorld(double x, double y);
	void highlightSelectedVertex();
	void drawMessage(int line, const char* msg);
	//bool rayCollision(QVector3D pointCenter);
	bool clickCollision(QVector2D pointCenter);

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