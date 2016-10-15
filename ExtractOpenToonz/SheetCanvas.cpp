#include "SheetCanvas.h"
#include <qtimer.h>
#include <qvector3d.h>

SheetCanvas::SheetCanvas(QWidget* parent) {
	xRot = 0;
	yRot = 0;
	zRot = 0;
	m_skeleton = NULL;

	//Auto-updates widget every 10ms
	QTimer* timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(update()));
	timer->start(10);

	setFocusPolicy(Qt::StrongFocus);
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
	char message1[50];
	sprintf(message1, "Currently Selected Vertex: %d", selectedVertex);
	drawMessage(0, message1);


	char debug[50];
	if (drawKey) {
		sprintf(debug, "Delete Key is Pressed");
	}
	else {
		sprintf(debug, "No key/random key pressed");
	}
	drawMessage(1, debug);

	if (drawSkel != false)
		drawSkeleton();

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

	win_width = width;
	win_height = height;
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
	
	//Get position of mouse click
	mouseToWorld(lastPos.x(), lastPos.y());

	if (event->button() == Qt::LeftButton) {
		if (m_skeleton != NULL) {
			for (int i = 0; i < m_skeleton->getVertexCount(); i++) {
				SkeletonVertex* v1 = m_skeleton->getVertices()[i];

				QVector2D vertexCenter(v1->getXPos(), v1->getYPos());

				//Check for collision
				clickCollided = clickCollision(vertexCenter);

				//Update selected vertex if click collides
				if (clickCollided) {
					updateSelectedVertex(v1->getID());

					//Allow vertex to be moved
					vertexMoveSelected = true;
					break;
				}
			}
		}
	}
}

void SheetCanvas::mouseReleaseEvent(QMouseEvent* event) {
	lastPos = event->pos();
	
	//Update no movement state on mouse release
	vertexMoveSelected = false;

	if (event->button() == Qt::LeftButton) {
		if (!clickCollided) {
			//Check if skeleton exists
			if (m_skeleton == NULL) {
				m_skeleton = new Skeleton();
				drawSkel = true;
			}

			//Get position of mouse release point
			mouseToWorld(lastPos.x(), lastPos.y());

			//Add vertex into skeleton structure
			SkeletonVertex* vertexToAdd = new SkeletonVertex(objX, objY);
			vertexToAdd->setID(idToAdd++);
			m_skeleton->addVertex(vertexToAdd);

			//Update selection vertex
			updateSelectedVertex(vertexToAdd->getID());
			//m_skeleton->setSelectedVertex(vertexToAdd->getID());
			//selectedVertex = vertexToAdd->getID();
		}
	}

}


void SheetCanvas::mouseMoveEvent(QMouseEvent *event) {
	//int dx = event->x() - lastPos.x();
	//int dy = event->y() - lastPos.y();

	//if (event->buttons() & Qt::LeftButton) {
	//	setXRotation(xRot + 8 * dy);
	//	setYRotation(yRot + 8 * dx);
	//}
	//else if (event->buttons() & Qt::RightButton) {
	//	setXRotation(xRot + 8 * dy);
	//	setZRotation(zRot + 8 * dx);
	//}

	lastPos = event->pos();

	if (vertexMoveSelected) {
		if (m_skeleton != NULL) {
			//Get position of mouse in world coordinates
			mouseToWorld(lastPos.x(), lastPos.y());
			SkeletonVertex* v0 = m_skeleton->getVertex(selectedVertex);
			v0->setXPos(objX);
			v0->setYPos(objY);
		}
	}
}

void SheetCanvas::keyPressEvent(QKeyEvent* event) {
	if (event->key() == Qt::Key_Delete) {
		drawKey = true;
		
		if (m_skeleton != NULL) {
			if (m_skeleton->getVertexCount() != 0) {
				//Get vertex to delete and parentId
				int idToDelete = selectedVertex;
				int vertexParent = m_skeleton->getVertex(selectedVertex)->getParent();

				//Update new selected vertex to parent and reconnect children to parent
				if (vertexParent != -1) {
					updateSelectedVertex(vertexParent);
					m_skeleton->removeVertex(idToDelete);
				}
			}
		}

	}
	else
		drawKey = false;
}

//
//
//void SheetCanvas::draw() {
//	//Draws a pyramid
//
//	qglColor(Qt::red);
//	glBegin(GL_QUADS);
//	glNormal3f(0, 0, -1);
//	glVertex3f(-1, -1, 0);
//	glVertex3f(-1, 1, 0);
//	glVertex3f(1, 1, 0);
//	glVertex3f(1, -1, 0);
//
//	glEnd();
//	glBegin(GL_TRIANGLES);
//	glNormal3f(0, -1, 0.707);
//	glVertex3f(-1, -1, 0);
//	glVertex3f(1, -1, 0);
//	glVertex3f(0, 0, 1.2);
//	glEnd();
//	glBegin(GL_TRIANGLES);
//	glNormal3f(1, 0, 0.707);
//	glVertex3f(1, -1, 0);
//	glVertex3f(1, 1, 0);
//	glVertex3f(0, 0, 1.2);
//	glEnd();
//	glBegin(GL_TRIANGLES);
//	glNormal3f(0, 1, 0.707);
//	glVertex3f(1, 1, 0);
//	glVertex3f(-1, 1, 0);
//	glVertex3f(0, 0, 1.2);
//	glEnd();
//	glBegin(GL_TRIANGLES);
//	glNormal3f(-1, 0, 0.707);
//	glVertex3f(-1, 1, 0);
//	glVertex3f(-1, -1, 0);
//	glVertex3f(0, 0, 1.2);
//	glEnd();
//}

//----- Drawing Functions -----//

void SheetCanvas::drawVertex(SkeletonVertex* v) {
	double x = v->getXPos();
	double y = v->getYPos();
	qglColor(Qt::blue);
	glBegin(GL_POLYGON);
	glVertex2d(x - vertexRadius, y - vertexRadius);
	glVertex2d(x + vertexRadius, y - vertexRadius);
	glVertex2d(x + vertexRadius, y + vertexRadius);
	glVertex2d(x - vertexRadius, y + vertexRadius);
	glEnd();
	update();
}

void SheetCanvas::drawBone(SkeletonVertex* v1) {
	int parentID = v1->getParent();

	//Check if parent from vertex exists
	if (parentID != -1) {
		SkeletonVertex* v2 = NULL;
		v2 = m_skeleton->getVertex(parentID);

		if (v2 == NULL)
			return;

		glDisable(GL_LIGHTING);
		qglColor(QColor(250, 184, 70));
		glLineWidth(2.0f);  // Yellow/Orange-ish line center

		glBegin(GL_LINES);
		glVertex2d(v1->getXPos(), v1->getYPos());
		glVertex2d(v2->getXPos(), v2->getYPos());
		glEnd();


		qglColor(Qt::black);
		glLineWidth(4.0f);  // Black border

		glBegin(GL_LINES);
		glVertex2d(v1->getXPos(), v1->getYPos());
		glVertex2d(v2->getXPos(), v2->getYPos());
		glEnd();
	}
}

void SheetCanvas::drawSkeleton() {
	for (int i = 0; i < m_skeleton->getVertexCount(); i++) {
		
		drawVertex(m_skeleton->getVertices()[i]);
		drawBone(m_skeleton->getVertices()[i]);
	}

	highlightSelectedVertex();
}


void SheetCanvas::highlightSelectedVertex() {
	if (selectedVertex < 0)
		return;

	SkeletonVertex* vertexSelected;
	for (int i = 0; i < m_skeleton->getVertexCount(); i++) {
		if (m_skeleton->getVertices().at(i)->getID() == selectedVertex)
			vertexSelected = m_skeleton->getVertices().at(i);
	}


	float highlightBorder = vertexRadius + 0.005;


	qglColor(Qt::red);
	glLineWidth(2.0f);
	glBegin(GL_LINE_LOOP);
	glVertex2d(vertexSelected->getXPos() - highlightBorder, vertexSelected->getYPos() - highlightBorder);
	glVertex2d(vertexSelected->getXPos() + highlightBorder, vertexSelected->getYPos() - highlightBorder);
	glVertex2d(vertexSelected->getXPos() + highlightBorder, vertexSelected->getYPos() + highlightBorder);
	glVertex2d(vertexSelected->getXPos() - highlightBorder, vertexSelected->getYPos() + highlightBorder);
	glEnd();
	update();
}

void  SheetCanvas::drawMessage(int line_no, const char * message)
{
	int   i;
	if (message == NULL)
		return;

	// 
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0.0, win_width, win_height, 0.0);

	// 
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	// 
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);

	//
	glColor3f(1.0, 0.0, 0.0);
	glRasterPos2i(8, 24 + 18 * line_no);
	for (i = 0; message[i] != '\0'; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, message[i]);

	// ?
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

//----- Mouse related functions -----//

void SheetCanvas::mouseToWorld(double x, double y) {
	//Use of QT to determine x, y position on the widget
	x = this->mapFromGlobal(QCursor::pos()).x();
	y = this->mapFromGlobal(QCursor::pos()).y();
	
	//Setting up of view, model, projection matrices
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);

	GLdouble modelview[16];
	glGetDoublev(GL_MODELVIEW_MATRIX, modelview);

	GLdouble projection[16];
	glGetDoublev(GL_PROJECTION_MATRIX, projection);

	GLfloat winX, winY, winZ;


	winX = (float)x;
	//Convert normal coordinate to OpenGL-format coordinate
	winY = (float)viewport[3] - y;

	//Obtain depth
	glReadPixels(winX, winY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);

	//Obtain values for world coordinates
	gluUnProject(winX, winY, winZ, modelview, projection, viewport, &objX, &objY, &objZ);
}


bool SheetCanvas::clickCollision(QVector2D pointCenter) {
	QVector2D mouseClickPos(objX, objY);

	float distance = pointCenter.distanceToPoint(mouseClickPos);

	if (distance <= vertexRadius * 2)
		return true;
	else
		return false;
}

void SheetCanvas::updateSelectedVertex(int id) {
	selectedVertex = id;
	m_skeleton->setSelectedVertex(id);
}