#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

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
#include "header_file.h"
}

class MyGLWidget : public QOpenGLWidget {
  Q_OBJECT
 public:
  MyGLWidget(QWidget *parent = nullptr);

 public:
  int flag = 1;
  int scale_action = 0;
  double prev_scale = 1;
  struct capt capt = {0};
  char path[100] = "daeed";
  void mousePressEvent(QMouseEvent *) override;
  void mouseMoveEvent(QMouseEvent *) override;
  void initializeGL();
  void paintGL();
  void resizeGL(int width, int height);
  void pars_obj(char *path);
  void paint_obj();
  void scale_center(struct capt *capt, int mode, double scale_value,
                    double *prev_scale_value);
  void move_xyz(char symb, double val);
  void axes_xyz(char symb, double val);
  int presp = 0;
  int solid = 0;
  int point_on = 0;
  int point_smooth = 0;
  int int_vert_numb = 0;
  int int_pol_number = 0;
  double R_m = 0;
  double G_m = 0;
  double B_m = 0;
  double R_f = 127;
  double G_f = 127;
  double B_f = 127;
  double R_dot = 127;
  double G_dot = 0;
  double B_dot = 0;
  double LineWidth = 1;
  double DotWidth = 3;
  QSettings paramSet;

 private:
  float XRoad, YRoad, ZRoad;
  QPoint mPos;
  QTimer tmr;
 signals:
};

#endif  // MYGLWIDGET_H
