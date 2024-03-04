#ifndef GLVIEW_H
#define GLVIEW_H

#include <QtGui>
#include <QtOpenGL>
#include <QImage>
#include <QColor>

#ifdef __APPLE__
#include <OpenGl/gl.h>
#include <OpenGl/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif


#include <math.h>

#ifndef M_PI
#define M_PI 3.14285714285714285714 
#endif
/* Custom OpenGL Viewer Widget */

class GLView : public QGLWidget
{
   Q_OBJECT
public: 
	GLView(QWidget *parent=0, const char *name=0);
	~GLView();	

	void updateView();

	void topView();
	void bottomView();
	void frontView();
	void backView();
	void leftView();
	void rightView();
	void axonoView();

	void toggleAnim();

public:
	GLfloat ambiLight[4];
	GLfloat diffLight[4];
	GLfloat specLight[4];
	
	GLfloat ambiMat[4];
	GLfloat diffMat[4];
	GLfloat specMat[4];
	
	GLfloat specRef[4];
	GLfloat opacity;
	GLint shine;
	
	GLfloat xRot;
	GLfloat yRot;
	GLfloat zRot;
	GLfloat tScale;
	
	bool hasTexture;
	
public slots:
	void slotXRotation(int rotX);
	void slotYRotation(int rotY);
	void slotZRotation(int rotZ);
	void slotZoom(int val);
	void rotateBy(int xAngle, int yAngle, int zAngle);

protected:
	void initializeGL();
	void resizeGL( int width, int height );
	void paintGL();
	
private:
	int modelNum;
	GLdouble win_xmax, win_xmin, win_ymax, win_ymin, winz;
	QImage frTex, bkTex, topTex, botTex, lefTex, rhtTex;
	QImage buf;

private:
	void drawBox();
};

#endif
