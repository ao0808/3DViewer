#define GL_SILENCE_DEORECATIONS

#include "myglwidget.h"

#include "mainwindow.h"

double x_ = 1;
double y_ = 1;
double z_ = 1;

double x_1 = 1;
double y_1 = 1;
double z_1 = 1;

MyGLWidget::MyGLWidget(QWidget *parent) : QOpenGLWidget(parent) {
  FILE *file = NULL;
  char file_name[150] =
      "/Users/aleksandrkurbatov/Downloads/work 2/New_hope/chel.obj";
  file = fopen(file_name, "r");
  flag = core_reader(file, &capt);
  fclose(file);
}

void MyGLWidget::scale_center(struct capt *capt, int mode, double scale_value,
                              double *prev_scale_value) {
  if (mode == 1) {
    printf("%lf %lf\n", scale_value, *prev_scale_value);
  }
  toCenter_toScale(capt, mode, scale_value, *prev_scale_value);
  if (mode == 1) {
    *prev_scale_value = scale_value;
  }
  update();
}

void MyGLWidget::move_xyz(char symb, double val) {
  if (symb == 'x') {
    double tmp = val;
    if (val > x_) {
      val = val - x_;
      movePoint(&capt, val, symb);
    } else if (val < x_) {
      val = (x_ - val) * -1;
      movePoint(&capt, val, symb);
    } else {
    }
    x_ = tmp;

  } else if (symb == 'y') {
    double tmp = val;
    if (val > y_) {
      val = val - y_;
      movePoint(&capt, val, symb);
    } else if (val < y_) {
      val = (y_ - val) * -1;
      movePoint(&capt, val, symb);
    } else {
    }
    y_ = tmp;
  } else {
    double tmp = val;
    if (val > z_) {
      val = val - z_;
      movePoint(&capt, val, symb);
    } else if (val < z_) {
      val = (z_ - val) * -1;
      movePoint(&capt, val, symb);
    } else {
    }
    z_ = tmp;
  }
  update();
}
void MyGLWidget::axes_xyz(char symb, double val) {
  int end_ = 0;
  if (symb == 'x') {
    double tmp = val;
    if (val > x_1) {
      val = val - x_1;
    } else if (val < x_1) {
      val = (x_1 - val) * -1;
    } else {
    }
    x_1 = tmp;
  } else if (symb == 'y') {
    double tmp = val;
    if (val > y_1) {
      val = val - y_1;
    } else if (val < y_1) {
      val = (y_1 - val) * -1;
    } else {
    }
    y_1 = tmp;
  } else {
    double tmp = val;
    if (val > z_1) {
      val = val - z_1;
    } else if (val < z_1) {
      val = (z_1 - val) * -1;
    } else {
    }
    z_1 = tmp;
  }
  if (!end_) {
    matrix_t matrix;
    s21_create_matrix(3, 3, &matrix);
    if (symb == 'x') {
      matrix.matrix[0][0] = 1;
      matrix.matrix[0][1] = 0;
      matrix.matrix[0][2] = 0;

      matrix.matrix[1][0] = 0;
      matrix.matrix[1][1] = cos(val);
      matrix.matrix[1][2] = -1 * sin(val);

      matrix.matrix[2][0] = 0;
      matrix.matrix[2][1] = sin(val);
      matrix.matrix[2][2] = cos(val);

      for (int i = 0; i < capt.xyz->vert_numb; i++) {
        double x__ = capt.xyz->coord[i].x;
        double y__ = capt.xyz->coord[i].y;
        capt.xyz->coord[i].x = capt.xyz->coord[i].x * matrix.matrix[0][0] +
                               capt.xyz->coord[i].y * matrix.matrix[1][0] +
                               capt.xyz->coord[i].z * matrix.matrix[2][0];
        capt.xyz->coord[i].y = x__ * matrix.matrix[0][1] +
                               capt.xyz->coord[i].y * matrix.matrix[1][1] +
                               capt.xyz->coord[i].z * matrix.matrix[2][1];
        capt.xyz->coord[i].z = x__ * matrix.matrix[0][2] +
                               y__ * matrix.matrix[1][2] +
                               capt.xyz->coord[i].z * matrix.matrix[2][2];
      }
    }

    if (symb == 'y') {
      matrix.matrix[0][0] = cos(val);
      matrix.matrix[0][1] = 0;
      matrix.matrix[0][2] = sin(val);

      matrix.matrix[1][0] = 0;
      matrix.matrix[1][1] = 1;
      matrix.matrix[1][2] = 0;

      matrix.matrix[2][0] = -sin(val);
      matrix.matrix[2][1] = 0;
      matrix.matrix[2][2] = cos(val);

      for (int i = 0; i < capt.xyz->vert_numb; i++) {
        double x__ = capt.xyz->coord[i].x;
        double y__ = capt.xyz->coord[i].y;
        capt.xyz->coord[i].x = capt.xyz->coord[i].x * matrix.matrix[0][0] +
                               capt.xyz->coord[i].y * matrix.matrix[1][0] +
                               capt.xyz->coord[i].z * matrix.matrix[2][0];
        capt.xyz->coord[i].y = x__ * matrix.matrix[0][1] +
                               capt.xyz->coord[i].y * matrix.matrix[1][1] +
                               capt.xyz->coord[i].z * matrix.matrix[2][1];
        capt.xyz->coord[i].z = x__ * matrix.matrix[0][2] +
                               y__ * matrix.matrix[1][2] +
                               capt.xyz->coord[i].z * matrix.matrix[2][2];
      }
    }

    if (symb == 'z') {
      matrix.matrix[0][0] = cos(val);
      matrix.matrix[0][1] = -sin(val);
      matrix.matrix[0][2] = 0;

      matrix.matrix[1][0] = sin(val);
      matrix.matrix[1][1] = cos(val);
      matrix.matrix[1][2] = 0;

      matrix.matrix[2][0] = 0;
      matrix.matrix[2][1] = 0;
      matrix.matrix[2][2] = 1;

      for (int i = 0; i < capt.xyz->vert_numb; i++) {
        double x__ = capt.xyz->coord[i].x;
        double y__ = capt.xyz->coord[i].y;
        capt.xyz->coord[i].x = capt.xyz->coord[i].x * matrix.matrix[0][0] +
                               capt.xyz->coord[i].y * matrix.matrix[1][0] +
                               capt.xyz->coord[i].z * matrix.matrix[2][0];
        capt.xyz->coord[i].y = x__ * matrix.matrix[0][1] +
                               capt.xyz->coord[i].y * matrix.matrix[1][1] +
                               capt.xyz->coord[i].z * matrix.matrix[2][1];
        capt.xyz->coord[i].z = x__ * matrix.matrix[0][2] +
                               y__ * matrix.matrix[1][2] +
                               capt.xyz->coord[i].z * matrix.matrix[2][2];
      }
    }
    update();
    s21_remove_matrix(&matrix);
  }
}
void MyGLWidget::mousePressEvent(QMouseEvent *mo) { mPos = mo->pos(); }

void MyGLWidget::mouseMoveEvent(QMouseEvent *mo) {
  XRoad = 1 / M_PI * (mo->pos().y() - mPos.y());
  YRoad = 1 / M_PI * (mo->pos().x() - mPos.x());
  update();
}
void MyGLWidget::initializeGL() { glEnable(GL_DEPTH_TEST); }

void MyGLWidget::paintGL() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if (paramSet.value("presp/presp_value") == 0) {
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
void MyGLWidget::pars_obj(char *path) {
  memset(&capt, 0, sizeof(capt));

  FILE *file = NULL;
  char *file_name = path;
  file = fopen(file_name, "r");
  flag = core_reader(file, &capt);
  fclose(file);
  update();
}

void MyGLWidget::paint_obj() {
  if (flag == 0) {
    glClearColor(paramSet.value("R_f/R_f_value").toDouble(),
                 paramSet.value("G_f/G_f_value").toDouble(),
                 paramSet.value("B_f/B_f_value").toDouble(), 0);  //  цвет фона
    glEnable(GL_LINE_STIPPLE);   // запуск отрисовки
    glMatrixMode(GL_MODELVIEW);  // инициализация матрицы
    glClear(GL_COLOR_BUFFER_BIT |
            GL_DEPTH_BUFFER_BIT);  // очищает цвет и матрицы
    glLineWidth(paramSet.value("LineWidth/LineWidth_value")
                    .toDouble());  // толщина линий
    glColor3b(paramSet.value("R_m/R_m_value").toDouble(),
              paramSet.value("G_m/G_m_value").toDouble(),
              paramSet.value("B_m/B_m_value").toDouble());  // цвет линий
    if (paramSet.value("solid/solid_value").toDouble() == 1) {
      glLineStipple(0, 40);  // пунктирная линия
    } else {
      glDisable(GL_LINE_STIPPLE);
    }
    for (int i = 0; i < capt.pol_number; i++) {
      glBegin(GL_LINE_LOOP);
      for (int j = 0; j < capt.poligon[i].poligon_count; j++) {
        glVertex3d(capt.xyz->coord[capt.poligon[i].poligon_arr[j]].x,
                   capt.xyz->coord[capt.poligon[i].poligon_arr[j]].y,
                   capt.xyz->coord[capt.poligon[i].poligon_arr[j]].z);
      }
      glEnd();
    }
    if (paramSet.value("point_on/point_on_value").toDouble()) {
      glColor3d(paramSet.value("R_dot/R_dot_value").toDouble(),
                paramSet.value("G_dot/G_dot_value").toDouble(),
                paramSet.value("B_dot/B_dot_value").toDouble());  // цвет точек
      glPointSize(paramSet.value("DotWidth/DotWidth_value")
                      .toDouble());  // толщина точек
      if (paramSet.value("point_smooth/point_smooth_value").toDouble()) {
        glEnable(GL_POINT_SMOOTH);  // круглые точки значение 2832
      } else {
        glDisable(GL_POINT_SMOOTH);  // отключает круглые точки
      }
      glBegin(GL_POINTS);
      for (int i = 0; i < capt.xyz->vert_numb; i++) {
        glVertex3d(capt.xyz->coord[i].x, capt.xyz->coord[i].y,
                   capt.xyz->coord[i].z);
      }
      glEnd();
    }
  }
}

void MyGLWidget::resizeGL(int w, int h) {}
