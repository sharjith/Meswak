#ifndef ABOUTDIALOGIMPL_H
#define ABOUTDIALOGIMPL_H
//
#include "ui_About.h"
//
class AboutDialogImpl : public QDialog, public Ui::AboutDialog
{
Q_OBJECT
public:
    AboutDialogImpl( QWidget * parent = 0, Qt::WindowFlags f = 0 );
private slots:
};
#endif





