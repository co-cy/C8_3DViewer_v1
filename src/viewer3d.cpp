#include "viewer3d.h"

#include <QFileDialog>

#include "./ui_viewer3d.h"

Viewer3D::Viewer3D(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::Viewer3D) {
  ui->setupUi(this);

  connect(ui->load_file, SIGNAL(clicked()), this, SLOT(load_file()));

  this->setEnableTools(this->current_obj3);

  connect(ui->move_x_spin, SIGNAL(valueChanged(double)), this,
          SLOT(obj3_move_x(double)));
  connect(ui->move_y_spin, SIGNAL(valueChanged(double)), this,
          SLOT(obj3_move_y(double)));
  connect(ui->move_z_spin, SIGNAL(valueChanged(double)), this,
          SLOT(obj3_move_z(double)));

  connect(ui->rotate_x_spin, SIGNAL(valueChanged(double)), this,
          SLOT(obj3_rotate_x(double)));
  connect(ui->rotate_y_spin, SIGNAL(valueChanged(double)), this,
          SLOT(obj3_rotate_y(double)));
  connect(ui->rotate_z_spin, SIGNAL(valueChanged(double)), this,
          SLOT(obj3_rotate_z(double)));

  connect(ui->scale_x_spin, SIGNAL(valueChanged(double)), this,
          SLOT(obj3_scale_x(double)));
  connect(ui->scale_y_spin, SIGNAL(valueChanged(double)), this,
          SLOT(obj3_scale_y(double)));
  connect(ui->scale_z_spin, SIGNAL(valueChanged(double)), this,
          SLOT(obj3_scale_z(double)));
}

Viewer3D::~Viewer3D() {
  qDebug() << "FREE";
  free_object3(current_obj3);

  delete ui;
}

void Viewer3D::obj3_move_x(double new_x) {
  if (this->current_obj3) {
    double shift = this->current_obj3->shift.x - new_x;
    if (shift > 0.0001) {
      vertex3_t tmp = {shift, 0, 0};
      object3_move(tmp, this->current_obj3);
    }
  }
}

void Viewer3D::obj3_move_y(double new_y) {
  if (this->current_obj3) {
    double shift = this->current_obj3->shift.y - new_y;
    if (shift > 0.0001) object3_move({0, shift, 0}, this->current_obj3);
  }
}

void Viewer3D::obj3_move_z(double new_z) {
  if (this->current_obj3) {
    double shift = this->current_obj3->shift.z - new_z;
    if (shift > 0.0001) object3_move({0, 0, shift}, this->current_obj3);
  }
}

void Viewer3D::obj3_rotate_x(double new_x) {
  if (this->current_obj3) {
    double shift = this->current_obj3->rotate.x - new_x;
    if (shift > 0.0001) object3_rotate({shift, 0, 0}, this->current_obj3);
  }
}

void Viewer3D::obj3_rotate_y(double new_y) {
  if (this->current_obj3) {
    double shift = this->current_obj3->rotate.y - new_y;
    if (shift > 0.0001) object3_rotate({0, shift, 0}, this->current_obj3);
  }
}

void Viewer3D::obj3_rotate_z(double new_z) {
  if (this->current_obj3) {
    double shift = this->current_obj3->rotate.z - new_z;
    if (shift > 0.0001) object3_rotate({0, 0, shift}, this->current_obj3);
  }
}

void Viewer3D::obj3_scale_x(double new_x) {
  if (this->current_obj3) {
    double shift = new_x / this->current_obj3->scale.x;
    if (shift > 0.0001) object3_scale({shift, 0, 0}, this->current_obj3);
  }
}

void Viewer3D::obj3_scale_y(double new_y) {
  if (this->current_obj3) {
    double shift = new_y / this->current_obj3->scale.y;
    if (shift > 0.0001) object3_scale({0, shift, 0}, this->current_obj3);
  }
}

void Viewer3D::obj3_scale_z(double new_z) {
  if (this->current_obj3) {
    double shift = new_z / this->current_obj3->scale.z;
    if (shift > 0.0001) object3_scale({0, 0, shift}, this->current_obj3);
  }
}

void Viewer3D::load_file() {
  QString fileName =
      QFileDialog::getOpenFileName(this, "Выбрать файл", NULL, "Object(*.obj)");
  this->ui->file_info->setText("File: " + fileName);

  if (this->current_obj3) free_object3(this->current_obj3);

  this->current_obj3 =
      parse_object3_from_obj_file(fileName.toStdString().c_str());
  if (this->current_obj3) {
    QString vertexes =
        "Вершин: " + QString::number(this->current_obj3->list_vertex3.size);
    QString polygon =
        " Полигонов: " + QString::number(this->current_obj3->list_polygon.size);
    this->ui->vertical_info->setText(vertexes + polygon);
  }

  this->setEnableTools(this->current_obj3);
}

void Viewer3D::setEnableTools(bool state) {
  this->ui->move_x_spin->setEnabled(state);
  this->ui->move_y_spin->setEnabled(state);
  this->ui->move_z_spin->setEnabled(state);
  this->ui->rotate_x_spin->setEnabled(state);
  this->ui->rotate_y_spin->setEnabled(state);
  this->ui->rotate_z_spin->setEnabled(state);
  this->ui->scale_x_spin->setEnabled(state);
  this->ui->scale_y_spin->setEnabled(state);
  this->ui->scale_z_spin->setEnabled(state);
}
