#include "viewer3d.h"
#include "./ui_viewer3d.h"

#include <QFileDialog>

Viewer3D::Viewer3D(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Viewer3D)
{
    ui->setupUi(this);

    connect(ui->load_file, SIGNAL(clicked()), this, SLOT(load_file()));
    connect(ui->load_file_2, SIGNAL(clicked()), this, SLOT(load_file()));
}

Viewer3D::~Viewer3D()
{
    delete ui;
}

void Viewer3D::load_file() {
    QString fileName = QFileDialog::getOpenFileName(
                this, "Выбрать файл", NULL, "Object (*.obj)");
    this->ui->file_info->setText("File: " + fileName);
}
