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

  connect(ui->openGLWidget, SIGNAL(rightButtonMove(QPoint)), this,
          SLOT(updateShift(QPoint)));
  connect(ui->openGLWidget, SIGNAL(leftButtonMove(QPoint)), this,
          SLOT(updateRotate(QPoint)));
  connect(ui->openGLWidget, SIGNAL(mouseScroll(int)), this,
          SLOT(updateScale(int)));
}

Viewer3D::~Viewer3D() {
  free_object3(current_obj3);

  delete ui;
}

void Viewer3D::obj3_move_x(double new_x) {
  if (!this->current_obj3 || this->ignore_event) return;

  double shift = new_x - this->current_obj3->shift.x;
  if (shift > 0.0001) object3_move(this->current_obj3, {shift, 0, 0});
}

void Viewer3D::obj3_move_y(double new_y) {
  if (!this->current_obj3 || this->ignore_event) return;

  double shift = new_y - this->current_obj3->shift.y;
  if (shift > 0.0001) object3_move(this->current_obj3, {0, shift, 0});
}

void Viewer3D::obj3_move_z(double new_z) {
  if (!this->current_obj3 || this->ignore_event) return;

  double shift = new_z - this->current_obj3->shift.z;
  if (shift > 0.0001) object3_move(this->current_obj3, {0, 0, shift});
}

void Viewer3D::obj3_rotate_x(double new_x) {
  if (!this->current_obj3 || this->ignore_event) return;

  double shift = new_x - this->current_obj3->rotate.x;
  if (shift > 0.0001) object3_rotate(this->current_obj3, {shift, 0, 0});
}

void Viewer3D::obj3_rotate_y(double new_y) {
  if (!this->current_obj3 || this->ignore_event) return;

  double shift = new_y - this->current_obj3->rotate.y;
  if (shift > 0.0001) object3_rotate(this->current_obj3, {0, shift, 0});
}

void Viewer3D::obj3_rotate_z(double new_z) {
  if (!this->current_obj3 || this->ignore_event) return;

  double shift = new_z - this->current_obj3->rotate.z;
  if (shift > 0.0001) object3_rotate(this->current_obj3, {0, 0, shift});
}

void Viewer3D::obj3_scale_x(double new_x) {
  if (!this->current_obj3 || this->ignore_event) return;

  double shift = new_x / this->current_obj3->scale.x;
  if (shift > 0.0001) object3_scale(this->current_obj3, {shift, 0, 0});
}

void Viewer3D::obj3_scale_y(double new_y) {
  if (!this->current_obj3 || this->ignore_event) return;

  double shift = new_y / this->current_obj3->scale.y;
  if (shift > 0.0001) object3_scale(this->current_obj3, {0, shift, 0});
}

void Viewer3D::obj3_scale_z(double new_z) {
  if (!this->current_obj3 || this->ignore_event) return;

  double shift = new_z / this->current_obj3->scale.z;
  if (shift > 0.0001) object3_scale(this->current_obj3, {0, 0, shift});
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
        "Вершин: " + QString::number(this->current_obj3->list_vector3.size);
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

void Viewer3D::updateShift(QPoint shift) {
  if (!this->current_obj3) return;

  vector3_t vector = {(double)shift.x(), (double)shift.y(), 0};
  vector3_rotate(&vector, this->current_obj3->rotate);

  this->ignore_event = true;
  this->ui->move_x_spin->setValue(this->ui->move_x_spin->value() + vector.x);
  this->ui->move_y_spin->setValue(this->ui->move_y_spin->value() + vector.y);
  this->ui->move_z_spin->setValue(this->ui->move_z_spin->value() + vector.z);
  this->ignore_event = false;

  object3_move(this->current_obj3,
               {this->ui->move_x_spin->value(), this->ui->move_y_spin->value(),
                this->ui->move_z_spin->value()});
}

void Viewer3D::updateRotate(QPoint shift) {
  if (!this->current_obj3) return;

  vector3_t ang = {(double)shift.x(), (double)shift.y(), 0};
  vector3_rotate(&ang, this->current_obj3->rotate);

  this->ignore_event = true;
  this->ui->rotate_x_spin->setValue(this->ui->rotate_x_spin->value() + ang.x);
  this->ui->rotate_y_spin->setValue(this->ui->rotate_y_spin->value() + ang.y);
  this->ui->rotate_z_spin->setValue(this->ui->rotate_z_spin->value() + ang.z);
  this->ignore_event = false;

  object3_rotate(this->current_obj3, {this->ui->rotate_x_spin->value(),
                                      this->ui->rotate_y_spin->value(),
                                      this->ui->rotate_z_spin->value()});
}

void Viewer3D::updateScale(int y) {
  if (!this->current_obj3) return;

  y /= abs(y);

  this->ignore_event = true;
  this->ui->scale_x_spin->setValue(this->ui->scale_x_spin->value() + y);
  this->ui->scale_y_spin->setValue(this->ui->scale_y_spin->value() + y);
  this->ui->scale_z_spin->setValue(this->ui->scale_z_spin->value() + y);
  this->ignore_event = false;

  vector3_t vector3 = {this->ui->scale_x_spin->value(),
                       this->ui->scale_y_spin->value(),
                       this->ui->scale_z_spin->value()};
  object3_scale(this->current_obj3, vector3);
}
