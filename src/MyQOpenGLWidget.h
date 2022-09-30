//
// Created by stf20 on 29.09.2022.
//

#ifndef INC_3DVIEWER_V1_MYQOPENGLWIDGET_H
#define INC_3DVIEWER_V1_MYQOPENGLWIDGET_H

#include <QMouseEvent>
#include <QOpenGLWidget>
#include <QWheelEvent>

class MyQOpenGLWidget : public QOpenGLWidget {
  Q_OBJECT

 public:
  MyQOpenGLWidget(QWidget* parent = nullptr);
  ~MyQOpenGLWidget();

  void mousePressEvent(QMouseEvent* event);
  void mouseReleaseEvent(QMouseEvent* event);
  void mouseMoveEvent(QMouseEvent* event);
  void wheelEvent(QWheelEvent* event);
 protected:
  bool leftButtonPress = false;
  bool rightButtonPress = false;

  QPoint leftButtonPoint;
  QPoint rightButtonPoint;

 signals:
  void leftButtonMove(QPoint shift);
  void rightButtonMove(QPoint shift);
  void mouseScroll(int y);
};

#endif  // INC_3DVIEWER_V1_MYQOPENGLWIDGET_H
