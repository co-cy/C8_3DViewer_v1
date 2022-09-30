//
// Created by stf20 on 29.09.2022.
//

#include "MyQOpenGLWidget.h"

MyQOpenGLWidget::MyQOpenGLWidget(QWidget* parent) : QOpenGLWidget(parent) {}
MyQOpenGLWidget::~MyQOpenGLWidget() {}

void MyQOpenGLWidget::mousePressEvent(QMouseEvent* event) {
  Qt::MouseButton button = event->button();
  if (button == Qt::LeftButton) {
    this->leftButtonPress = true;
    this->leftButtonPoint = event->pos();
  } else if (button == Qt::RightButton) {
    this->rightButtonPress = true;
    this->rightButtonPoint = event->pos();
  }
}

void MyQOpenGLWidget::mouseReleaseEvent(QMouseEvent* event) {
  Qt::MouseButton button = event->button();
  if (button == Qt::LeftButton)
    this->leftButtonPress = false;
  else if (button == Qt::RightButton)
    this->rightButtonPress = false;
}

void MyQOpenGLWidget::mouseMoveEvent(QMouseEvent* event) {
  if (this->leftButtonPress) {
    emit leftButtonMove(event->pos() - this->leftButtonPoint);
    this->leftButtonPoint = event->pos();
  }

  if (this->rightButtonPress) {
    emit rightButtonMove(event->pos() - this->rightButtonPoint);
    this->rightButtonPoint = event->pos();
  }
}

void MyQOpenGLWidget::wheelEvent(QWheelEvent* event) {
  emit this->mouseScroll(event->angleDelta().y());
}
