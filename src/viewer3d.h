#ifndef VIEWER3D_H
#define VIEWER3D_H

#include <QMainWindow>

#include "./parser/core.h"
#include "./transformations/transformations.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Viewer3D;
}
QT_END_NAMESPACE

class Viewer3D : public QMainWindow {
  Q_OBJECT

 public:
  Viewer3D(QWidget *parent = nullptr);
  ~Viewer3D();

 private:
  Ui::Viewer3D *ui;

 protected:
  object3_t *current_obj3 = NULL;
  bool ignore_event = false;

  void setEnableTools(bool state);

 protected slots:
  void load_file();

  void obj3_move_x(double new_x);
  void obj3_move_y(double new_y);
  void obj3_move_z(double new_z);

  void obj3_rotate_x(double new_x);
  void obj3_rotate_y(double new_y);
  void obj3_rotate_z(double new_z);

  void obj3_scale_x(double new_x);
  void obj3_scale_y(double new_y);
  void obj3_scale_z(double new_z);

  void updateShift(QPoint shift);
  void updateRotate(QPoint shift);
  void updateScale(int y);
};
#endif  // VIEWER3D_H
