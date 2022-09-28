#include "viewer3d.h"
#include "./ui_viewer3d.h"

Viewer3D::Viewer3D(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Viewer3D)
{
    ui->setupUi(this);
}

Viewer3D::~Viewer3D()
{
    delete ui;
}

