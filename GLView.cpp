#include "GLView.h"

GLView::GLView(QWidget *parent, const char * /*name*/ ) : QGLWidget(parent, 0)
{
    xRot = -45.0;
    yRot = 0.0;
    zRot = -45.0;

    tScale = 1.0;

    modelNum = 6;
    opacity = 1.0f;
    ambiLight[0] = 0.3;
    ambiLight[1] = 0.3;
    ambiLight[2] = 0.3;
    ambiLight[3] = 1.0;

    diffLight[0] = 0.7f;
    diffLight[1] = 0.7f;
    diffLight[2] = 0.7f;
    diffLight[3] = 1.0f;

    specLight[0] = 1.0f;
    specLight[1] = 1.0f;
    specLight[2] = 1.0f;
    specLight[3] = 1.0f;

    ambiMat[0] = 0.2;
    ambiMat[1] = 0.5;
    ambiMat[2] = 0.7;
    ambiMat[3] = opacity;

    diffMat[0] = 0.7f;
    diffMat[1] = 0.7f;
    diffMat[2] = 0.7f;
    diffMat[3] = opacity;

    specMat[0] = 1.0f;
    specMat[1] = 1.0f;
    specMat[2] = 1.0f;
    specMat[3] = opacity;

    specRef[0] =  1.0f;
    specRef[1] =  1.0f;
    specRef[2] =  1.0f;
    specRef[3] =  1.0f;

    shine = 128;

    hasTexture = true;
}

GLView::~GLView()
{
}

void GLView::updateView()
{
    updateGL();
}

void GLView::topView()
{
    xRot = 0;
    yRot = 0;
    zRot = 0;
}

void GLView::bottomView()
{
    xRot = -180;
    yRot = 0;
    zRot = 0;

}

void GLView::frontView()
{
    xRot = -90;
    yRot = 0;
    zRot = 0;
}

void GLView::backView()
{
    xRot = -90;
    yRot = 0;
    zRot = -180;
}

void GLView::leftView()
{
    xRot = -90;
    yRot = 0;
    zRot = -90;
}

void GLView::rightView()
{
    xRot = -90;
    yRot = 0;
    zRot = 90;
}

void GLView::axonoView()
{
    xRot = -45;
    yRot = 0;
    zRot = -45;

}

void GLView::toggleAnim()
{
}

void GLView::initializeGL ()
{
    // Set up the rendering context, define display lists etc.:
    /* Insert your OpenGL initialization code here */
    // Set background color
    qglClearColor(QColor("gray"));

    // Set drawing color to
    glColor3ub(255, 255, 255);

    //top
    if ( !buf.load( "textures/Top.bmp" ) )
    {	// Load first image from file
        qWarning( "Could not read image file, using single-color instead." );
        QImage dummy( 128, 128, (QImage::Format)5 );
        dummy.fill( Qt::white );
        buf = dummy;
    }
    topTex = QGLWidget::convertToGLFormat( buf );  // flipped 32bit RGBA

    if ( !buf.load( "textures/Bottom.bmp" ) )
    {	// Load first image from file
        qWarning( "Could not read image file, using single-color instead." );
        QImage dummy( 128, 128, (QImage::Format)5 );
        dummy.fill( Qt::white );
        buf = dummy;
    }
    botTex = QGLWidget::convertToGLFormat( buf );  // flipped 32bit RGBA

    if ( !buf.load( "textures/Front.bmp" ) )
    {	// Load first image from file
        qWarning( "Could not read image file, using single-color instead." );
        QImage dummy( 128, 128, (QImage::Format)5 );
        dummy.fill( Qt::white );
        buf = dummy;
    }
    frTex = QGLWidget::convertToGLFormat( buf );  // flipped 32bit RGBA

    if ( !buf.load( "textures/Back.bmp" ) )
    {	// Load first image from file
        qWarning( "Could not read image file, using single-color instead." );
        QImage dummy( 128, 128, (QImage::Format)5 );
        dummy.fill( Qt::white );
        buf = dummy;
    }
    bkTex = QGLWidget::convertToGLFormat( buf );  // flipped 32bit RGBA

    if ( !buf.load( "textures/Side.bmp" ) )
    {	// Load first image from file
        qWarning( "Could not read image file, using single-color instead." );
        QImage dummy( 128, 128, (QImage::Format)5 );
        dummy.fill( Qt::white );
        buf = dummy;
    }
    lefTex = QGLWidget::convertToGLFormat( buf );  // flipped 32bit RGBA

    if ( !buf.load( "textures/Side.bmp" ) )
    {	// Load first image from file
        qWarning( "Could not read image file, using single-color instead." );
        QImage dummy( 128, 128, (QImage::Format)5 );
        dummy.fill( Qt::white );
        buf = dummy;
    }
    rhtTex = QGLWidget::convertToGLFormat( buf );  // flipped 32bit RGBA

    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glEnable( GL_TEXTURE_2D );
}

void GLView::resizeGL ( int w, int h )
{
    GLdouble modelMatrix[16];
    GLdouble projMatrix[16];
    GLint viewport[4];

    // setup viewport, projection etc.:
    /* Prevent a divide by zero*/
    if(h == 0)
        h = 1;

    glViewport (0, 0, w, h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    if (w <= h)
        glOrtho (-125.0f, 125.0f, -125.0f*h/w, 125.0f*h/w, -1250.0f, 1250.0f);
    else
        glOrtho (-125.0f*w/h, 125.0f*w/h, -125.0f, 125.0f, -1250.0f, 1250.0f);
    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity ();

    /* store limits for gradient background */
    glGetDoublev(GL_PROJECTION_MATRIX, projMatrix);
    glGetDoublev(GL_MODELVIEW_MATRIX, modelMatrix);
    glGetIntegerv(GL_VIEWPORT, viewport);
    gluUnProject(0, 0, 1, modelMatrix, projMatrix, viewport,
                 &win_xmin, &win_ymin, &winz);
    gluUnProject(w, h, 1, modelMatrix, projMatrix, viewport,
                 &win_xmax, &win_ymax, &winz);

}

void GLView::paintGL ()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glShadeModel(GL_SMOOTH);
    glBegin(GL_POLYGON);

    glColor3ub(51, 51, 101);
    glVertex3f (win_xmin, win_ymax, 1250.0f);
    glVertex3f (win_xmax, win_ymax, 1250.0f);

    glColor3ub(171, 172, 193);
    glVertex3f (win_xmax, win_ymin, 1250.0f);
    glVertex3f (win_xmin, win_ymin, 1250.0f);

    glEnd();


    // Enable Depth Testing
    glEnable(GL_DEPTH_TEST);
    // Enable lighting
    glEnable(GL_LIGHTING);

    GLfloat position[] = {0.0, 0.0, 3.0, 0.0};
    GLfloat lmodel_ambient[] = {0.2, 0.2, 0.2, 1.0};
    GLfloat local_view[] = {0.0};

    // Setup and enable light 0
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambiLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specLight);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
    glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);
    glEnable(GL_LIGHT0);

    glEnable(GL_AUTO_NORMAL);
    glEnable(GL_NORMALIZE);
    glDepthFunc(GL_LESS);

    // required for two side lighting in case of open objects

    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);


    //Setup Material
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambiMat);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffMat);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specMat);


    // All materials hereafter have full specular reflectivity
    // with a high shine
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,specRef);
    glMateriali(GL_FRONT_AND_BACK,GL_SHININESS, shine);

    glShadeModel(GL_FLAT);

    if(hasTexture)
        glEnable( GL_TEXTURE_2D );
    else
        glDisable( GL_TEXTURE_2D );

    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glPushMatrix();
    glRotatef(xRot, 1.0f, 0.0f, 0.0f);
    glRotatef(yRot, 0.0f, 1.0f, 0.0f);
    glRotatef(zRot, 0.0f, 0.0f, 1.0f);

    glScalef(tScale, tScale, tScale);


    drawBox();

    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glColor3f(1.0, 1.0, 1.0);
    renderText(5, 15,  "Meswak");
    glEnable(GL_LIGHTING);
    if(hasTexture)
        glEnable(GL_TEXTURE_2D);

    glDisable(GL_BLEND);
    glPopMatrix();
}

void GLView::slotXRotation(int rotX)
{
    xRot = (GLfloat)rotX;
    updateGL();
}

void GLView::slotYRotation(int rotY)
{
    yRot = (GLfloat)rotY;
    updateGL();
}

void GLView::slotZRotation(int rotZ)
{
    zRot = (GLfloat)rotZ;
    updateGL();
}

void GLView::slotZoom(int val)
{
    tScale = (GLfloat)val/50.0;
    updateGL();
}

void GLView::rotateBy(int xAngle, int yAngle, int zAngle)
{
    xRot += xAngle;
    yRot += yAngle;
    zRot += zAngle;
    updateGL();
}


void GLView::drawBox()
{
    static float x = 210;
    static float y = 35;
    static float z = 60;

    // Top
    glTexImage2D( GL_TEXTURE_2D, 0, 3, topTex.width(), topTex.height(), 0,
                  GL_RGBA, GL_UNSIGNED_BYTE, topTex.bits() );

    glBegin(GL_QUADS);

    glNormal3f(0,0,1);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-x/2, -y/2, z/2);

    glTexCoord2f(1.0, 0.0);
    glVertex3f(x/2, -y/2, z/2);

    glTexCoord2f(1.0, 1.0);
    glVertex3f(x/2, y/2, z/2);

    glTexCoord2f(0.0, 1.0);
    glVertex3f(-x/2, y/2, z/2);

    glEnd();

    // Bottom
    glTexImage2D( GL_TEXTURE_2D, 0, 3, botTex.width(), botTex.height(), 0,
                  GL_RGBA, GL_UNSIGNED_BYTE, botTex.bits() );

    glBegin(GL_QUADS);

    glTexCoord2f(0.0, 0.0);
    glVertex3f(-x/2, -y/2, -z/2);

    glTexCoord2f(1.0, 0.0);
    glVertex3f(x/2, -y/2, -z/2);

    glTexCoord2f(1.0, 1.0);
    glVertex3f(x/2, y/2, -z/2);

    glTexCoord2f(0.0, 1.0);
    glVertex3f(-x/2, y/2, -z/2);

    glEnd();

    // Front
    glTexImage2D( GL_TEXTURE_2D, 0, 3, frTex.width(), frTex.height(), 0,
                  GL_RGBA, GL_UNSIGNED_BYTE, frTex.bits() );

    glBegin(GL_QUADS);

    glNormal3f(0,-1,0);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-x/2, -y/2, -z/2);

    glTexCoord2f(1.0, 0.0);
    glVertex3f(x/2, -y/2, -z/2);

    glTexCoord2f(1.0, 1.0);
    glVertex3f(x/2, -y/2, z/2);

    glTexCoord2f(0.0, 1.0);
    glVertex3f(-x/2, -y/2, z/2);

    glEnd();

    // Back
    glTexImage2D( GL_TEXTURE_2D, 0, 3, bkTex.width(), bkTex.height(), 0,
                  GL_RGBA, GL_UNSIGNED_BYTE, bkTex.bits() );

    glBegin(GL_QUADS);

    glTexCoord2f(0.0, 0.0);
    glVertex3f(-x/2, y/2, -z/2);

    glTexCoord2f(1.0, 0.0);
    glVertex3f(x/2, y/2, -z/2);

    glTexCoord2f(1.0, 1.0);
    glVertex3f(x/2, y/2, z/2);

    glTexCoord2f(0.0, 1.0);
    glVertex3f(-x/2, y/2, z/2);

    glEnd();

    // Left
    glTexImage2D( GL_TEXTURE_2D, 0, 3, lefTex.width(), lefTex.height(), 0,
                  GL_RGBA, GL_UNSIGNED_BYTE, lefTex.bits() );

    glBegin(GL_QUADS);

    glNormal3f(-1,0,0);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-x/2, y/2, -z/2);

    glTexCoord2f(1.0, 0.0);
    glVertex3f(-x/2, -y/2, -z/2);

    glTexCoord2f(1.0, 1.0);
    glVertex3f(-x/2, -y/2, z/2);

    glTexCoord2f(0.0, 1.0);
    glVertex3f(-x/2, y/2, z/2);

    glEnd();

    // Right
    glTexImage2D( GL_TEXTURE_2D, 0, 3, rhtTex.width(), rhtTex.height(), 0,
                  GL_RGBA, GL_UNSIGNED_BYTE, rhtTex.bits() );

    glBegin(GL_QUADS);

    glTexCoord2f(0.0, 0.0);
    glVertex3f(x/2, y/2, -z/2);

    glTexCoord2f(1.0, 0.0);
    glVertex3f(x/2, -y/2, -z/2);

    glTexCoord2f(1.0, 1.0);
    glVertex3f(x/2, -y/2, z/2);

    glTexCoord2f(0.0, 1.0);
    glVertex3f(x/2, y/2, z/2);

    glEnd();
}

