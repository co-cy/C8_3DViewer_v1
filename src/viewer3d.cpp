#include "viewer3d.h"
#include "./ui_viewer3d.h"
#include "./main.h"

#include <QFileDialog>

Viewer3D::Viewer3D(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Viewer3D)
{
    ui->setupUi(this);

    connect(ui->load_file, SIGNAL(clicked()), this, SLOT(load_file()));
}

Viewer3D::~Viewer3D()
{
    delete ui;
}

void Viewer3D::load_file() {
    QString fileName = QFileDialog::getOpenFileName(
                this, "Выбрать файл", NULL, "Object (*.obj)");
    this->ui->file_info->setText("File: " + fileName);

    object3_t* obj3 = parse_object3_from_obj_file(fileName.toStdString().c_str());
    if (obj3) {
        this->ui->vertical_info->setText("Вершин: " + QString::number(obj3->list_vertex3.size)
                                         + " Полигонов: " + QString::number(obj3->list_polygon.size));
        free_object3(obj3);
    }
}
