
#ifndef __MESWAK_H__
#define __MESWAK_H__

#ifdef __APPLE__
#include <OpenGl/gl.h>
#include <OpenGl/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>

#endif

#include "ui_Meswak.h"
#include "GLView.h"

class Meswak : public QMainWindow, private Ui::Meswak
{
    Q_OBJECT
    public:
	Meswak(QWidget* parent);
	~Meswak();

    private slots:

	void on_sliderXRot_valueChanged(int value);
	void on_sliderYRot_valueChanged(int value);
	void on_sliderZRot_valueChanged(int value);
	void on_sliderZoom_valueChanged(int value);

	void on_actionTop_triggered(bool checked);
    	void on_actionBottom_triggered(bool checked);
	void on_actionFront_triggered(bool checked);
	void on_actionBack_triggered(bool checked);
	void on_actionLeft_triggered(bool checked);
	void on_actionRight_triggered(bool checked);
	void on_actionAxonometric_triggered(bool checked);
	void on_actionAnimStop_triggered(bool checked);
	void on_actionExit_triggered(bool checked);

	void rotateOneStep();

    private:
    GLView* theView;
	bool animStopped;
    
    private slots:
	void on_actionAbout_activated();
	
	
	
};

#endif //__MESWAK_H__

