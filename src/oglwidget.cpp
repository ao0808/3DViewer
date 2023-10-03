#include "oglwidget.h"

#include "mainwindow.h"
OGLWidget::OGLWidget(QWidget *parent) : QOpenGLWidget(parent) {
  pars_obj(path);
}

OGLWidget::~OGLWidget() {}

void OGLWidget::mousePressEvent(QMouseEvent *mo) { mPos = mo->pos(); }

void OGLWidget::mouseMoveEvent(QMouseEvent *mo) {
  XRoad = 1 / M_PI * (mo->pos().y() - mPos.y());
  YRoad = 1 / M_PI * (mo->pos().x() - mPos.x());
  update();
}

void OGLWidget::initializeGL() { glEnable(GL_DEPTH_TEST); }

void OGLWidget::paintGL() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if (presp == 0) {
    glFrustum(-1, 1, -1, 1, 2, 6);
    glTranslatef(0, 0, -3);
  } else {
    glOrtho(-1, 1, -1, 1, -1, 5);
    glTranslatef(0, 0, -0);
  }
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_TEST);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0, 0, 0);
  glRotatef(XRoad, 1, 0, 0);
  glRotatef(YRoad, 0, 1, 0);
  paint_obj();
}

void OGLWidget::pars_obj(char *path) {
  memset(&obj, 0, sizeof(main_struct));
  flag = parser(path, &obj);
}

void OGLWidget::paint_obj() {
  if (flag == 0) {
    glClearColor(settings.value("fon_color/color_r").toInt(),
                 settings.value("fon_color/color_g").toInt(),
                 settings.value("fon_color/color_b").toInt(), 0);
    glEnable(GL_LINE_STIPPLE);   // запуск отрисовки
    glMatrixMode(GL_MODELVIEW);  // инициализация матрицы
    glClear(GL_COLOR_BUFFER_BIT |
            GL_DEPTH_BUFFER_BIT);  // очищает цвет и матрицы
    glLineWidth(settings.value("ribs/size").toInt());
    glColor3b(settings.value("ribs/color_r").toInt(),
              settings.value("ribs/color_g").toInt(),
              settings.value("ribs/color_b").toInt());  // цвет

    if (settings.value("ribs/sposob").toInt()) {
      glLineStipple(0, 40);  // пунктирная линия
    } else {
      glDisable(GL_LINE_STIPPLE);
    }
    for (int i = 0; i < obj.struct_count; i++) {
      glBegin(settings.value("ribs/no_show_2").toInt());
      for (int j = 0; j < obj.p[i]->poligon_sum; j++) {
        glVertex3d(obj.v->vertex_matrix[obj.p[i]->poligon_arr[j]][0],
                   obj.v->vertex_matrix[obj.p[i]->poligon_arr[j]][1],
                   obj.v->vertex_matrix[obj.p[i]->poligon_arr[j]][2]);
      }
      glEnd();
    }
    glColor3b(settings.value("peaks/color_r").toInt(),
              settings.value("peaks/color_g").toInt(),
              settings.value("peaks/color_b").toInt());
    glPointSize(settings.value("peaks/size").toInt());  // толщина точек
    if (settings.value("peaks/sposob").toInt()) {
      glEnable(GL_POINT_SMOOTH);  // круглые точки значение 2832
    } else {
      glDisable(GL_POINT_SMOOTH);  // отключает круглые точки
    }
    glBegin(settings.value("peaks/no_show")
                .toInt());  // значение 0, при 10к ничего не видно
    for (int i = 0; i < obj.v->vertex_mount; i++) {
      glVertex3d(obj.v->vertex_matrix[i][0], obj.v->vertex_matrix[i][1],
                 obj.v->vertex_matrix[i][2]);
    }
    glEnd();
  }
}

void OGLWidget::resizeGL(int w, int h) {}
