//
// Created by stf20 on 29.09.2022.
//

#include "MyQOpenGLWidget.h"

MyQOpenGLWidget::MyQOpenGLWidget(QWidget* parent) : QOpenGLWidget(parent) {}
MyQOpenGLWidget::~MyQOpenGLWidget() {
  delete prog;
};

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

void MyQOpenGLWidget::changeBackgroundColor(int r, int g, int b) {
  this->color = QColor(r, g, b);
  update();
}

void MyQOpenGLWidget::initializeGL() {
  initializeOpenGLFunctions();
  glEnable(GL_DEPTH_TEST);

  const char *vertexShaderSource =
      "attribute vec3 position;\n"
      "uniform mat4 projection;\n"
      "uniform mat4 persp;\n"
      "uniform vec3 color;\n"
      "void main()\n"
      "{\n"
      "gl_Position = persp * projection * vec4(position.x, position.y, "
      "position.z, "
      "1.0);\n"
      "}\0";
  const char *fragmentShaderSource =
      "uniform vec3 color;\n"
      "void main()\n"
      "{\n"
      "gl_FragColor = vec4(color.x, color.y, color.z, 1);\n"
      "}\n\0";
  prog = new QOpenGLShaderProgram;
  prog->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
  prog->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
  prog->bindAttributeLocation("position", 0);
  prog->link();
}
void MyQOpenGLWidget::paintGL() {
  glClearColor(color.redF(), color.greenF(), color.blueF(), 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
}

void MyQOpenGLWidget::saveBmpImage(const QString& filename) {
  this->grabFramebuffer().save(filename, "bmp");
}

void MyQOpenGLWidget::saveJpegImage(const QString& filename) {
  this->grabFramebuffer().save(filename, "jpeg");
}
