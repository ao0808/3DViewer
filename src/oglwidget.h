#ifndef OGLWIDGET_H
#define OGLWIDGET_H

#include <qopenglfunctions.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <QFileDialog>
#include <QMouseEvent>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QSettings>
#include <QThread>
#include <QTimer>
#include <QWidget>

extern "C" {
#include "parcer.h"
#include "s21_matrix.h"
}

#define GL_SILENCE_DEORECATIONS

/**
 * @brief класс отрисовки
 *
 */
class OGLWidget : public QOpenGLWidget {
 public:
  int flag = 1;
  QSettings settings;
  OGLWidget(QWidget *parent = 0);
  ~OGLWidget();
  void pars_obj(char *path);
  char path[1000] = "";
  void paintGL() override;
  QString *path1;
  main_struct obj;
  void paint_obj();
  int presp = 0;
  void resizeGL(int w, int h) override;

 private:
  double x;
  double y;
  int xa = 0;
  float XRoad, YRoad, ZRoad;
  QPoint mPos;
  QTimer tmr;
  void drawCube(float a);
  void mousePressEvent(QMouseEvent *) override;
  void mouseMoveEvent(QMouseEvent *) override;
  void mouseWheeel(QMoveEvent *);
  void initializeGL() override;

 protected:
};

#endif  // OGLWIDGET_H
