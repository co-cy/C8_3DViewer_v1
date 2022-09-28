#ifndef VIEWER3D_H
#define VIEWER3D_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Viewer3D; }
QT_END_NAMESPACE

class Viewer3D : public QMainWindow
{
    Q_OBJECT

public:
    Viewer3D(QWidget *parent = nullptr);
    ~Viewer3D();

private:
    Ui::Viewer3D *ui;

private slots:
    void load_file();
};
#endif // VIEWER3D_H
