
#include "Meswak.h"
#include <QtGui>
#include <QApplication>

Meswak::Meswak(QWidget* parent) : QMainWindow(parent)
{
    setupUi(this);
    animStopped = false;
    theView = new GLView(glframe, "glview");
    // Put the GL widget inside the frame
    QHBoxLayout* flayout = new QHBoxLayout(glframe);
    flayout->addWidget( theView, 1 );

    
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(rotateOneStep()));
    timer->start(100);
    
}

Meswak::~Meswak()
{
    if(theView)
	delete theView;
}

void Meswak::rotateOneStep()
{
    if (!animStopped)
	theView->rotateBy(2 , 2 , -1 );
}


void Meswak::on_sliderXRot_valueChanged(int value)
{
    theView->slotXRotation(value);
}

void Meswak::on_sliderYRot_valueChanged(int value)
{
    theView->slotYRotation(value);
}

void Meswak::on_sliderZRot_valueChanged(int value)
{
    theView->slotZRotation(value);
}

void Meswak::on_sliderZoom_valueChanged(int value)
{
    theView->slotZoom(value);
}

void Meswak::on_actionTop_triggered(bool /*checked*/)
{
    theView->topView();
    
    sliderXRot->setSliderPosition(0);
    sliderYRot->setSliderPosition(0);
    sliderZRot->setSliderPosition(0);

    /*
    sliderXRot->setValue(0);
    sliderYRot->setValue(0);
    sliderZRot->setValue(0);*/
}

void Meswak::on_actionBottom_triggered(bool /*checked*/)
{
    theView->bottomView();

    sliderXRot->setSliderPosition(-180);
    sliderYRot->setSliderPosition(0);
    sliderZRot->setSliderPosition(0);

    /*
    sliderXRot->setValue(-180);
    sliderYRot->setValue(0);
    sliderZRot->setValue(0);*/
}

void Meswak::on_actionFront_triggered(bool /*checked*/)
{
    theView->frontView();

    sliderXRot->setSliderPosition(-90);
    sliderYRot->setSliderPosition(0);
    sliderZRot->setSliderPosition(0);

    /*
    sliderXRot->setValue(-90);
    sliderYRot->setValue(0);
    sliderZRot->setValue(0);*/
}

void Meswak::on_actionBack_triggered(bool /*checked*/)
{
    theView->backView();

    sliderXRot->setSliderPosition(-90);
    sliderYRot->setSliderPosition(0);
    sliderZRot->setSliderPosition(-180);

    /*
    sliderXRot->setValue(-90);
    sliderYRot->setValue(0);
    sliderZRot->setValue(-180);*/
}

void Meswak::on_actionLeft_triggered(bool /*checked*/)
{
    theView->leftView();

    sliderXRot->setSliderPosition(-90);
    sliderYRot->setSliderPosition(0);
    sliderZRot->setSliderPosition(-90);

    /*
    sliderXRot->setValue(-90);
    sliderYRot->setValue(0);
    sliderZRot->setValue(-90);*/
}

void Meswak::on_actionRight_triggered(bool /*checked*/)
{
    theView->rightView();

    sliderXRot->setSliderPosition(-90);
    sliderYRot->setSliderPosition(0);
    sliderZRot->setSliderPosition(90);

    /*
    sliderXRot->setValue(-90);
    sliderYRot->setValue(0);
    sliderZRot->setValue(90);*/
}

void Meswak::on_actionAxonometric_triggered(bool /*checked*/)
{
    theView->axonoView();

    sliderXRot->setSliderPosition(-45);
    sliderYRot->setSliderPosition(0);
    sliderZRot->setSliderPosition(-45);

    /*
    sliderXRot->setValue(-45);
    sliderYRot->setValue(0);
    sliderZRot->setValue(-45);*/
}

void Meswak::on_actionAnimStop_triggered(bool /*checked*/)
{
    animStopped = !animStopped;
    theView->toggleAnim();
    actionAnimStop->setText((animStopped) ? "Start": "Stop");
}

void Meswak::on_actionExit_triggered(bool /*checked*/)
{
    qApp->quit();
}

#include "aboutdialogimpl.h"
void Meswak::on_actionAbout_activated()
{
	AboutDialogImpl* ab = new AboutDialogImpl(this);
	ab->exec();
}

