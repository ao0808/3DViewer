#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>

#include "./gifimage/qgifimage.h"
#include "header_file.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

  QGifImage gif[100];
  int gif_count = 0;
  QTimer *timer;
  int count_screen = 0;
  int screen = 0;
  int gifka = 0;
  int time;
  int img_taker = 0;
  int img_type = 0;

 private slots:

  void on_spin_valueChanged(double arg1);

  void on_spin_x_valueChanged(double arg1);

  void on_spin_y_valueChanged(double arg1);

  void on_spin_z_valueChanged(double arg1);

  void on_spin_x_2_valueChanged(double arg1);

  void on_spin_y_2_valueChanged(double arg1);

  void on_spin_z_2_valueChanged(double arg1);

  void on_pushButton_clicked();

  // void on_change_perspective_clicked();

  void on_pushButton_2_clicked();

  void on_pushButton_3_clicked();

  void on_spin_z_3_valueChanged(double arg);

  void on_spin_z_4_valueChanged(double arg1);

  void on_spin_z_5_valueChanged(double arg1);

  void on_spin_z_6_valueChanged(double arg1);

  void on_spin_z_9_valueChanged(double arg1);

  void on_spin_z_7_valueChanged(double arg1);

  void on_spin_z_8_valueChanged(double arg1);

  void on_spin_z_11_valueChanged(double arg1);

  void on_spin_z_12_valueChanged(double arg1);

  void on_spin_z_10_valueChanged(double arg1);

  void on_spin_z_13_valueChanged(double arg1);

  void on_pushButton_4_clicked();

  void on_pushButton_5_clicked();

  void on_pushButton_6_clicked();
  void on_comboBox_currentTextChanged(const QString &arg1);

  void saving_frames();
  void save_gif();

  void on_pushButton_8_clicked();

  void on_pushButton_7_clicked();

 private:
  Ui::MainWindow *ui;
};
#endif  // MAINWINDOW_H
