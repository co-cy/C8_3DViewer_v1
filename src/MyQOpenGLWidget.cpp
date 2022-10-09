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
  glEnable(GL_DEPTH_TEST); // включаем буфер глубины для отображения Z-координаты.

  glLoadIdentity();
  glMatrixMode(GL_PROJECTION);

}
void MyQOpenGLWidget::paintGL() {
  glClearColor(color.redF(), color.greenF(), color.blueF(), 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  if ((*this->cur_obect)) {

/*  glLoadIdentity(); // единичная матрица
      glMatrixMode(GL_MODELVIEW); // перейти в режим представления модели

      glLoadIdentity();
      glMatrixMode(GL_PROJECTION)*/;
  //    glOrtho(-2,2, -2,2, -1,1);
  //    glFrustum(-10,10, -10,10, 2, 100); // задает для перспективной проекции

//      glTranslatef(0, 0, -50);
//          glScalef(0.1f, 0.1f, 0.1f);
//          glRotated(45, 1.0, 0.0, 0.0);

//      glRotated(30, 0.0, 1.0, 0.0);

//      glClearColor(0.1f, 0.1f, 0.1f, 0.0f); // background color
//      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_TEST);

      glVertexPointer(3, GL_DOUBLE, 0, (*this->cur_obect)->list_vertex3.vertex3); // array_of_coord
      glEnableClientState(GL_VERTEX_ARRAY); // Enable state Opengl
          glColor3f(1, 0, 0); // color point
          glEnable(GL_POINT_SMOOTH);
              glPointSize(10);
              glDrawArrays(GL_POINTS, 0, ((*this->cur_obect)->list_vertex3.count));
          glDisable(GL_POINT_SMOOTH);

          glColor3f(0.12, 0.69, 0.55); // color lines
          glEnable(GL_LINE_STIPPLE);
          glLineStipple(1, 0x3333); // pattern lines
          glLineWidth(2);

      glDrawElements(GL_LINES, (*this->cur_obect)->list_polygon.size, GL_UNSIGNED_INT, (*this->cur_obect)->list_polygon.polygons);
      glDisableClientState(GL_VERTEX_ARRAY); // Disable state Opengl
  }
}

void MyQOpenGLWidget::saveBmpImage(const QString& filename) {
  this->grabFramebuffer().save(filename, "bmp");
}

void MyQOpenGLWidget::saveJpegImage(const QString& filename) {
  this->grabFramebuffer().save(filename, "jpeg");
}

void MyQOpenGLWidget::shift(double x, double y, double z) {
//    glTranslatef(x, y, z);
}
