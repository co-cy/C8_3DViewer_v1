//
// Created by stf20 on 29.09.2022.
//

#ifndef INC_3DVIEWER_V1_MYQOPENGLWIDGET_H
#define INC_3DVIEWER_V1_MYQOPENGLWIDGET_H

#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QOpenGLBuffer>
#include <QMouseEvent>
#include <QWheelEvent>
#include "struct/object3/object3.h"

class MyQOpenGLWidget : public QOpenGLWidget, public QOpenGLFunctions {
  Q_OBJECT

 public:
  explicit MyQOpenGLWidget(QWidget* parent = nullptr);
  ~MyQOpenGLWidget() override;

   object3_t** cur_obect = nullptr;

  void mousePressEvent(QMouseEvent* event) override;
  void mouseReleaseEvent(QMouseEvent* event) override;
  void mouseMoveEvent(QMouseEvent* event) override;
  void wheelEvent(QWheelEvent* event) override;

  void saveBmpImage(const QString& filename);
  void saveJpegImage(const QString& filename);
  void shift(double x, double y, double z);
 protected:
  bool leftButtonPress = false;
  bool rightButtonPress = false;

  QPoint leftButtonPoint;
  QPoint rightButtonPoint;

  // QOpenGLWidget interface
  QColor color = QColor();
  QOpenGLShaderProgram *prog = nullptr;
  void initializeGL() override;
   void paintGL() override;

 signals:
  void leftButtonMove(QPoint shift);
  void rightButtonMove(QPoint shift);
  void mouseScroll(int y);

 public slots:
  void changeBackgroundColor(int r, int g, int b);
};

#endif  // INC_3DVIEWER_V1_MYQOPENGLWIDGET_H
