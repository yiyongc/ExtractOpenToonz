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
	void mouseReleaseEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void keyPressEvent(QKeyEvent* event);

	QSize minimumSizeHint() const;
	QSize sizeHint() const;



private:
	int xRot;
	int yRot;
	int zRot;
	QPoint lastPos;
	bool drawSkel = false;
	Skeleton* m_skeleton;
	float vertexRadius = 0.020;
	int win_width, win_height;

	int idToAdd = 0;
	bool vertexMoveSelected = false;
	int selectedVertex = -1;
	bool clickCollided = false;

	bool drawKey = false;

	GLdouble objX = 0.0, objY = 0.0, objZ = 0.0;

	//drawing functions 
	//void draw();
	void drawVertex(SkeletonVertex* v);
	void drawBone(SkeletonVertex* v1);
	void highlightSelectedVertex();
	void drawMessage(int line, const char* msg);
	void drawSkeleton();

	//mouse functions
	void mouseToWorld(double x, double y);
	bool clickCollision(QVector2D pointCenter);


	void updateSelectedVertex(int id);

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