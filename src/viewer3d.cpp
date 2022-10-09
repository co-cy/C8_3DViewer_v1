#include "viewer3d.h"

#include <QFileDialog>

#include "./ui_viewer3d.h"

Viewer3D::Viewer3D(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::Viewer3D) {
  ui->setupUi(this);

  this->setEnableTools(this->current_obj3);

  connect(ui->load_file, SIGNAL(clicked()), this, SLOT(load_file()));

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

  connect(ui->color_red_spin, SIGNAL(valueChanged(int)), this,
          SLOT(changeBackgroundColor()));
  connect(ui->color_green_spin, SIGNAL(valueChanged(int)), this,
          SLOT(changeBackgroundColor()));
  connect(ui->color_blue_spin, SIGNAL(valueChanged(int)), this,
          SLOT(changeBackgroundColor()));

  connect(ui->jpeg_button, SIGNAL(clicked()), this,
          SLOT(saveJpegImage()));
  connect(ui->bmp_button, SIGNAL(clicked()), this,
          SLOT(saveBmpImage()));
  connect(ui->gif_button, SIGNAL(clicked()), this,
          SLOT(saveGifImage()));

  this->loadSettings();
  ui->openGLWidget->cur_obect = &(this->current_obj3);
}

void Viewer3D::loadSettings() {
  FILE* file;
  if (fopen_s(&file, "settings.my", "r")) return;

  double d_tmp;
  int int_tmp;
  if (!fscanf_s(file, "%Lf", &d_tmp))
    return;
  this->ui->move_x_spin->setValue(d_tmp);
  if (!fscanf_s(file, "%Lf", &d_tmp))
    return;
  this->ui->move_y_spin->setValue(d_tmp);
  if (!fscanf_s(file, "%Lf", &d_tmp))
    return;
  this->ui->move_z_spin->setValue(d_tmp);
  if (!fscanf_s(file, "%Lf", &d_tmp))
    return;
  this->ui->rotate_x_spin->setValue(d_tmp);
  if (!fscanf_s(file, "%Lf", &d_tmp))
    return;
  this->ui->rotate_y_spin->setValue(d_tmp);
  if (!fscanf_s(file, "%Lf", &d_tmp))
    return;
  this->ui->rotate_z_spin->setValue(d_tmp);
  if (!fscanf_s(file, "%Lf", &d_tmp))
    return;
  this->ui->scale_x_spin->setValue(d_tmp);
  if (!fscanf_s(file, "%Lf", &d_tmp))
    return;
  this->ui->scale_y_spin->setValue(d_tmp);
  if (!fscanf_s(file, "%Lf", &d_tmp))
    return;
  this->ui->scale_z_spin->setValue(d_tmp);
  if (!fscanf_s(file, "%u", &int_tmp))
    return;
  this->ui->color_red_spin->setValue(int_tmp);
  if (!fscanf_s(file, "%u", &int_tmp))
    return;
  this->ui->color_green_spin->setValue(int_tmp);
  if (!fscanf_s(file, "%u", &int_tmp))
    return;
  this->ui->color_blue_spin->setValue(int_tmp);

  fclose(file);
}

void Viewer3D::saveSettings() {
  FILE* file;
  if (fopen_s(&file, "settings.my", "w")) return;
  fprintf_s(file, "%Lf %Lf %Lf %Lf %Lf %Lf %Lf %Lf %Lf %u %u %u",
            this->ui->move_x_spin->value(),
            this->ui->move_y_spin->value(),
            this->ui->move_z_spin->value(),
            this->ui->rotate_x_spin->value(),
            this->ui->rotate_y_spin->value(),
            this->ui->rotate_z_spin->value(),
            this->ui->scale_x_spin->value(),
            this->ui->scale_y_spin->value(),
            this->ui->scale_z_spin->value(),
            this->ui->color_red_spin->value(),
            this->ui->color_green_spin->value(),
            this->ui->color_blue_spin->value()
                );
  fclose(file);
}

Viewer3D::~Viewer3D() {
  this->saveSettings();

  free_object3(&this->current_obj3);
  delete ui;
}

void Viewer3D::changeBackgroundColor() {
  this->ui->openGLWidget->changeBackgroundColor(
      this->ui->color_red_spin->value(),
      this->ui->color_green_spin->value(),
      this->ui->color_blue_spin->value());
}

void Viewer3D::obj3_move_x(double new_x) {
  if (!this->current_obj3 || this->ignore_event) return;

  double shift = new_x - this->current_obj3->shift.x;
  if (fabs(shift) > 0.0001) object3_move(this->current_obj3, {shift, 0, 0});
  this->ui->openGLWidget->update();
}

void Viewer3D::obj3_move_y(double new_y) {
  if (!this->current_obj3 || this->ignore_event) return;

  double shift = new_y - this->current_obj3->shift.y;
  if (fabs(shift) > 0.0001) object3_move(this->current_obj3, {0, shift, 0});
  this->ui->openGLWidget->update();
}

void Viewer3D::obj3_move_z(double new_z) {
  if (!this->current_obj3 || this->ignore_event) return;

  double shift = new_z - this->current_obj3->shift.z;
  if (fabs(shift) > 0.0001) object3_move(this->current_obj3, {0, 0, shift});
  this->ui->openGLWidget->update();
}

void Viewer3D::obj3_rotate_x(double new_x) {
  if (!this->current_obj3 || this->ignore_event) return;

  double shift = new_x - this->current_obj3->rotate.x;
  if (fabs(shift) > 0.0001) object3_rotate(this->current_obj3, {shift, 0, 0});
  this->ui->openGLWidget->update();
}

void Viewer3D::obj3_rotate_y(double new_y) {
  if (!this->current_obj3 || this->ignore_event) return;

  double shift = new_y - this->current_obj3->rotate.y;
  if (fabs(shift) > 0.0001) object3_rotate(this->current_obj3, {0, shift, 0});
  this->ui->openGLWidget->update();
}

void Viewer3D::obj3_rotate_z(double new_z) {
  if (!this->current_obj3 || this->ignore_event) return;

  double shift = new_z - this->current_obj3->rotate.z;
  if (fabs(shift) > 0.0001) object3_rotate(this->current_obj3, {0, 0, shift});
  this->ui->openGLWidget->update();
}

void Viewer3D::obj3_scale_x(double new_x) {
  if (!this->current_obj3 || this->ignore_event) return;

  double shift = new_x / this->current_obj3->scale.x;
  if (fabs(shift) > 0.0001) object3_scale(this->current_obj3, {shift, 0, 0});
  this->ui->openGLWidget->update();
}

void Viewer3D::obj3_scale_y(double new_y) {
  if (!this->current_obj3 || this->ignore_event) return;

  double shift = new_y / this->current_obj3->scale.y;
  if (fabs(shift) > 0.0001) object3_scale(this->current_obj3, {0, shift, 0});
  this->ui->openGLWidget->update();
}

void Viewer3D::obj3_scale_z(double new_z) {
  if (!this->current_obj3 || this->ignore_event) return;

  double shift = new_z / this->current_obj3->scale.z;
  if (fabs(shift) > 0.0001) object3_scale(this->current_obj3, {0, 0, shift});
  this->ui->openGLWidget->update();
}

void Viewer3D::load_file() {
  QString fileName =
      QFileDialog::getOpenFileName(this, "Выбрать файл",
                                   nullptr, "Object(*.obj)");
  if (fileName.isNull())
    return;
  this->ui->file_info->setText("File: " + fileName);

  if (this->current_obj3) free_object3(&this->current_obj3);

  this->current_obj3 =
      parse_object3_from_obj_file(fileName.toStdString().c_str());
  if (this->current_obj3) {
    QString vertexes =
        "Вершин: " + QString::number(this->current_obj3->list_vertex3.count);
    QString polygon =
        " Полигонов: " + QString::number(this->current_obj3->list_polygon.count);
    this->ui->vertical_info->setText(vertexes + polygon);

    object3_move(this->current_obj3, {this->ui->move_x_spin->value(),
                                      this->ui->move_y_spin->value(),
                                      this->ui->move_z_spin->value()});
    object3_rotate(this->current_obj3, {this->ui->rotate_x_spin->value(),
                                        this->ui->rotate_y_spin->value(),
                                        this->ui->rotate_z_spin->value()});
    object3_scale(this->current_obj3, {this->ui->scale_x_spin->value(),
                                       this->ui->scale_y_spin->value(),
                                       this->ui->scale_z_spin->value()});
    this->ui->openGLWidget->update();
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
  this->ui->color_red_spin->setEnabled(state);
  this->ui->color_green_spin->setEnabled(state);
  this->ui->color_blue_spin->setEnabled(state);
  this->ui->color_red_slider->setEnabled(state);
  this->ui->color_green_slider->setEnabled(state);
  this->ui->color_blue_slider->setEnabled(state);
}

void Viewer3D::updateShift(QPoint shift) {
  if (!this->current_obj3) return;


  this->ignore_event = true;
  this->ui->move_x_spin->setValue(this->ui->move_x_spin->value() + (double)shift.x() / 250);
  this->ui->move_y_spin->setValue(this->ui->move_y_spin->value() + -(double)shift.y() / 250);
  this->ignore_event = false;

  object3_move(this->current_obj3,
               {this->ui->move_x_spin->value() - this->current_obj3->shift.x,
                this->ui->move_y_spin->value() - this->current_obj3->shift.y,
                0});
  this->ui->openGLWidget->update();
}

void Viewer3D::updateRotate(QPoint shift) {
  if (!this->current_obj3) return;

  vector3_t ang = {-(double)shift.y(), (double)shift.x(), 0};
//  vector3_rotate(&ang, this->current_obj3->rotate);

  this->ignore_event = true;
  this->ui->rotate_x_spin->setValue(this->ui->rotate_x_spin->value() + ang.x);
  this->ui->rotate_y_spin->setValue(this->ui->rotate_y_spin->value() + ang.y);
  this->ui->rotate_z_spin->setValue(this->ui->rotate_z_spin->value() + ang.z);
  this->ignore_event = false;

  object3_rotate(this->current_obj3, {this->ui->rotate_x_spin->value() - this->current_obj3->rotate.x,
                                      this->ui->rotate_y_spin->value() - this->current_obj3->rotate.y,
                                      this->ui->rotate_z_spin->value() - this->current_obj3->rotate.z});
  this->ui->openGLWidget->update();
}

void Viewer3D::updateScale(int y) {
  if (!this->current_obj3) return;

  double new_y = y / fabs(y) / 10;

  this->ignore_event = true;
  this->ui->scale_x_spin->setValue(this->ui->scale_x_spin->value() + new_y);
  this->ui->scale_y_spin->setValue(this->ui->scale_y_spin->value() + new_y);
  this->ui->scale_z_spin->setValue(this->ui->scale_z_spin->value() + new_y);
  this->ignore_event = false;

  object3_scale(this->current_obj3, {this->ui->scale_x_spin->value() / this->current_obj3->scale.x,
                                     this->ui->scale_y_spin->value() / this->current_obj3->scale.y,
                                     this->ui->scale_z_spin->value() / this->current_obj3->scale.z});
this->ui->openGLWidget->update();
}


void Viewer3D::saveJpegImage() {
  QString fileName = QFileDialog::getSaveFileName(this, "Сохранить файл",
                                                  nullptr, "Image(*.jpeg)");
  if (fileName.isNull())
    return;
  this->ui->openGLWidget->saveJpegImage(fileName);
}

void Viewer3D::saveBmpImage() {
  QString fileName = QFileDialog::getSaveFileName(this, "Сохранить файл",
                                                  nullptr, "Image(*.bmp)");
  if (fileName.isNull())
    return;
  this->ui->openGLWidget->saveBmpImage(fileName);
}

void Viewer3D::saveGifImage() {

}
