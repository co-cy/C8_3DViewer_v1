#ifndef VIEWER3D_H
#define VIEWER3D_H

#include <QMainWindow>

#include <iostream>
#include "./parser/core.h"
#include "QtGifImage-master/src/gifimage/qgifimage.h"
#include <QTimer>


QT_BEGIN_NAMESPACE
namespace Ui {
class Viewer3D;
}
QT_END_NAMESPACE

class Viewer3D : public QMainWindow {
  Q_OBJECT

 public:
  explicit Viewer3D(QWidget *parent = nullptr);
  ~Viewer3D() override;

 private:
  Ui::Viewer3D *ui;
  int startTime, tmpTime;
  float timePrint;
  const int gifFps = 10, gifLength = 5;
  QTimer* timer;
  QGifImage* gif;

 protected:
  object3_t *current_obj3 = nullptr;
  bool ignore_event = false;

  void setEnableTools(bool state);

  void loadSettings();
  void saveSettings();

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

  void changeBackgroundColor();

  void saveJpegImage();
  void saveBmpImage();
  void saveGifImage();
private slots:
  void on_edges_dashed_pressed();
  void on_edges_solid_pressed();
  void on_edges_cir_slider_valueChanged(int value);
  void on_edges_size_slider_valueChanged(int value);
  void on_ver_cir_slider_valueChanged(int value);
  void on_ver_size_slider_valueChanged(int value);
  void on_vertices_circle_pressed();
  void on_vertices_square_pressed();
  void on_vertices_no_pressed();
  void on_perspective_pressed();
  void on_orthographic_pressed();
  void oneGif();
};
#endif  // VIEWER3D_H
