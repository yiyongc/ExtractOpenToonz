#include "SheetCanvas.h"


SheetCanvas::SheetCanvas(QWidget* parent) {
	xRot = 0;
	yRot = 0;
	zRot = 0;
	m_skeleton = NULL;
}

SheetCanvas::~SheetCanvas() {

}

void SheetCanvas::qNormalizeAngle(int &angle)
{
	while (angle < 0)
		angle += 360 * 16;
	while (angle > 360)
		angle -= 360 * 16;
}

void SheetCanvas::setXRotation(int angle)
{
	qNormalizeAngle(angle);
	if (angle != xRot) {
		xRot = angle;
		emit xRotationChanged(angle);
		updateGL();
	}
}

void SheetCanvas::setYRotation(int angle)
{
	qNormalizeAngle(angle);
	if (angle != yRot) {
		yRot = angle;
		emit yRotationChanged(angle);
		updateGL();
	}
}

void SheetCanvas::setZRotation(int angle)
{
	qNormalizeAngle(angle);
	if (angle != zRot) {
		zRot = angle;
		emit zRotationChanged(angle);
		updateGL();
	}
}



void SheetCanvas::initializeGL() {
	float  light0_position[] = { 10.0, 10.0, 10.0, 1.0 };
	float  light0_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
	float  light0_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	float  light0_ambient[] = { 0.1, 0.1, 0.1, 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
	glEnable(GL_LIGHT0);

	//
	glEnable(GL_LIGHTING);

	// 
	glEnable(GL_COLOR_MATERIAL);

	// 
	glEnable(GL_DEPTH_TEST);

	// 
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);



	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//BackGround color
	glClearColor(0.98, 0.98, 0.98, 0.0);

}

void SheetCanvas::paintGL() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -10.0);
	glRotatef(xRot / 16.0, 1.0, 0.0, 0.0);
	glRotatef(yRot / 16.0, 0.0, 1.0, 0.0);
	glRotatef(zRot / 16.0, 0.0, 0.0, 1.0);
	//draw();

	if (drawSkel == false)
		draw();
	else {
		for (int i = 0; i < m_skeleton->getVertexCount(); i++) {
			drawVertex(m_skeleton->getVertices()[i]);
		}
	}
}

void SheetCanvas::resizeGL(int width, int height) {
	int side = qMin(width, height);
	glViewport((width - side) / 2, (height - side) / 2, side, side);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
#ifdef QT_OPENGL_ES_1
	glOrthof(-2, +2, -2, +2, 1.0, 15.0);
#else
	glOrtho(-2, +2, -2, +2, 1.0, 15.0);
#endif
	glMatrixMode(GL_MODELVIEW);
}

QSize SheetCanvas::minimumSizeHint() const
{
	return QSize(50, 50);
}

QSize SheetCanvas::sizeHint() const
{
	return QSize(400, 400);
}

void SheetCanvas::mousePressEvent(QMouseEvent *event) {
	lastPos = event->pos();

	if (m_skeleton == NULL) {
		m_skeleton = new Skeleton();
		drawSkel = true;
	}
	Mouse(lastPos.x(), lastPos.y());
	SkeletonVertex* vertexToAdd = new SkeletonVertex(ox, oy);
	vertexToAdd->setID(m_skeleton->getVertexCount());
	m_skeleton->addVertex(vertexToAdd);
	m_skeleton->setSelectedVertex(vertexToAdd->getID());

}

void SheetCanvas::mouseMoveEvent(QMouseEvent *event) {
	int dx = event->x() - lastPos.x();
	int dy = event->y() - lastPos.y();

	if (event->buttons() & Qt::LeftButton) {
		setXRotation(xRot + 8 * dy);
		setYRotation(yRot + 8 * dx);
	}
	else if (event->buttons() & Qt::RightButton) {
		setXRotation(xRot + 8 * dy);
		setZRotation(zRot + 8 * dx);
	}

	lastPos = event->pos();
}



void SheetCanvas::draw() {
	//Draws a pyramid

	qglColor(Qt::red);
	glBegin(GL_QUADS);
	glNormal3f(0, 0, -1);
	glVertex3f(-1, -1, 0);
	glVertex3f(-1, 1, 0);
	glVertex3f(1, 1, 0);
	glVertex3f(1, -1, 0);

	glEnd();
	glBegin(GL_TRIANGLES);
	glNormal3f(0, -1, 0.707);
	glVertex3f(-1, -1, 0);
	glVertex3f(1, -1, 0);
	glVertex3f(0, 0, 1.2);
	glEnd();
	glBegin(GL_TRIANGLES);
	glNormal3f(1, 0, 0.707);
	glVertex3f(1, -1, 0);
	glVertex3f(1, 1, 0);
	glVertex3f(0, 0, 1.2);
	glEnd();
	glBegin(GL_TRIANGLES);
	glNormal3f(0, 1, 0.707);
	glVertex3f(1, 1, 0);
	glVertex3f(-1, 1, 0);
	glVertex3f(0, 0, 1.2);
	glEnd();
	glBegin(GL_TRIANGLES);
	glNormal3f(-1, 0, 0.707);
	glVertex3f(-1, 1, 0);
	glVertex3f(-1, -1, 0);
	glVertex3f(0, 0, 1.2);
	glEnd();
}

void SheetCanvas::drawVertex(SkeletonVertex* v) {
	double x = v->getXPos();
	double y = v->getYPos();

	

	glBegin(GL_LINE_LOOP);
	glVertex2d(x - 0.015, y - 0.015);
	glVertex2d(x + 0.015, y - 0.015);
	glVertex2d(x + 0.015, y + 0.015);
	glVertex2d(x - 0.015, y + 0.015);
	glEnd();
	update();
}


void SheetCanvas::Mouse(double x, double y) {
	GLint viewport[4];
	GLdouble modelview[16], projection[16];
	GLfloat wx = x, wy, wz;

	glGetIntegerv(GL_VIEWPORT, viewport);
	y = viewport[3] - y;
	wy = y;
	glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
	glGetDoublev(GL_PROJECTION_MATRIX, projection);
	glReadPixels(x, y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &wz);
	gluUnProject(wx, wy, wz, modelview, projection, viewport, &ox, &oy, &oz);
	//glutPostRedisplay();
}