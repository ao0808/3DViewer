
#include "mainwindow.h"

#include "header_file.h"
#include "myglwidget.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  ui->spin_z_9->setValue(
      ui->widget->paramSet.value("R_f/R_f_value").toDouble());
  ui->spin_z_8->setValue(
      ui->widget->paramSet.value("G_f/G_f_value").toDouble());
  ui->spin_z_7->setValue(
      ui->widget->paramSet.value("B_f/B_f_value").toDouble());

  ui->spin_z_4->setValue(
      ui->widget->paramSet.value("R_m/R_m_value").toDouble());
  ui->spin_z_5->setValue(
      ui->widget->paramSet.value("G_m/G_m_value").toDouble());
  ui->spin_z_6->setValue(
      ui->widget->paramSet.value("B_m/B_m_value").toDouble());

  ui->spin_z_10->setValue(
      ui->widget->paramSet.value("B_dot/B_dot_value").toDouble());
  ui->spin_z_11->setValue(
      ui->widget->paramSet.value("R_dot/R_dot_value").toDouble());
  ui->spin_z_12->setValue(
      ui->widget->paramSet.value("G_dot/G_dot_value").toDouble());

  ui->spin_z_3->setValue(
      ui->widget->paramSet.value("LineWidth/LineWidth_value").toDouble());
  ui->spin_z_13->setValue(
      ui->widget->paramSet.value("DotWidth/DotWidth_value").toDouble());
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_spin_valueChanged(double arg1) {
  if (arg1 != 0) {
    ui->widget->scale_center(&ui->widget->capt, 1, arg1,
                             &ui->widget->prev_scale);
  }
}

void MainWindow::on_spin_x_valueChanged(double arg1) {
  ui->widget->move_xyz('x', arg1);
}

void MainWindow::on_spin_y_valueChanged(double arg1) {
  ui->widget->move_xyz('y', arg1);
}

void MainWindow::on_spin_z_valueChanged(double arg1) {
  ui->widget->move_xyz('z', arg1);
}

void MainWindow::on_spin_x_2_valueChanged(double arg1) {
  ui->widget->axes_xyz('x', arg1);
}

void MainWindow::on_spin_y_2_valueChanged(double arg1) {
  ui->widget->axes_xyz('y', arg1);
}

void MainWindow::on_spin_z_2_valueChanged(double arg1) {
  ui->widget->axes_xyz('z', arg1);
}

void MainWindow::on_pushButton_clicked() {
  QString file1Name =
      QFileDialog::getOpenFileName(this, tr(""), "", tr("OBJ (*.obj)"));

  QByteArray something = file1Name.toLatin1();
  ui->file_name->setText(file1Name);
  char *example = something.data();
  ui->widget->pars_obj(example);
}

void MainWindow::on_pushButton_2_clicked() {
  if (ui->widget->presp == 0) {
    ui->widget->presp = 1;
  } else {
    ui->widget->presp = 0;
  }

  ui->widget->paramSet.setValue("presp/presp_value", ui->widget->presp);
  ui->widget->update();
}

void MainWindow::on_pushButton_3_clicked() {
  if (ui->widget->solid == 0) {
    ui->widget->solid = 1;
  } else {
    ui->widget->solid = 0;
  }

  ui->widget->paramSet.setValue("solid/solid_value", ui->widget->solid);
  ui->widget->update();
}

void MainWindow::on_spin_z_3_valueChanged(double arg) {
  ui->widget->LineWidth = arg;

  ui->widget->paramSet.setValue("LineWidth/LineWidth_value",
                                ui->widget->LineWidth);

  ui->widget->update();
}

void MainWindow::on_spin_z_4_valueChanged(double arg1) {
  ui->widget->R_m = arg1;
  printf("R_m = %lf", arg1);
  ui->widget->paramSet.setValue("R_m/R_m_value", ui->widget->R_m);

  ui->widget->update();
}

void MainWindow::on_spin_z_5_valueChanged(double arg1) {
  ui->widget->G_m = arg1;
  printf("G_m = %lf", arg1);
  ui->widget->paramSet.setValue("G_m/G_m_value", ui->widget->G_m);

  ui->widget->update();
}

void MainWindow::on_spin_z_6_valueChanged(double arg1) {
  ui->widget->B_m = arg1;
  printf("B_m = %lf", arg1);
  ui->widget->paramSet.setValue("B_m/B_m_value", ui->widget->B_m);

  ui->widget->update();
}

void MainWindow::on_spin_z_9_valueChanged(double arg1) {
  ui->widget->R_f = arg1;

  ui->widget->paramSet.setValue("R_f/R_f_value", ui->widget->R_f);

  ui->widget->update();
}

void MainWindow::on_spin_z_7_valueChanged(double arg1) {
  ui->widget->B_f = arg1;

  ui->widget->paramSet.setValue("B_f/B_f_value", ui->widget->B_f);

  ui->widget->update();
}

void MainWindow::on_spin_z_8_valueChanged(double arg1) {
  ui->widget->G_f = arg1;

  ui->widget->paramSet.setValue("G_f/G_f_value", ui->widget->G_f);

  ui->widget->update();
}

void MainWindow::on_spin_z_11_valueChanged(double arg1) {
  ui->widget->R_dot = arg1;

  ui->widget->paramSet.setValue("R_dot/R_dot_value", ui->widget->R_dot);

  ui->widget->update();
}

void MainWindow::on_spin_z_12_valueChanged(double arg1) {
  ui->widget->G_dot = arg1;

  ui->widget->paramSet.setValue("G_dot/G_dot_value", ui->widget->G_dot);

  ui->widget->update();
}

void MainWindow::on_spin_z_10_valueChanged(double arg1) {
  ui->widget->B_dot = arg1;

  ui->widget->paramSet.setValue("B_dot/B_dot_value", ui->widget->B_dot);

  ui->widget->update();
}

void MainWindow::on_spin_z_13_valueChanged(double arg1) {
  ui->widget->DotWidth = arg1;

  ui->widget->paramSet.setValue("DotWidth/DotWidth_value",
                                ui->widget->DotWidth);

  ui->widget->update();
}

void MainWindow::on_pushButton_4_clicked() {
  if (ui->widget->point_smooth == 0) {
    ui->widget->point_smooth = 1;
  } else {
    ui->widget->point_smooth = 0;
  }

  ui->widget->paramSet.setValue("point_smooth/point_smooth_value",
                                ui->widget->point_smooth);

  ui->widget->update();
}

void MainWindow::on_pushButton_5_clicked() {
  if (ui->widget->point_on == 0) {
    ui->widget->point_on = 1;
  } else {
    ui->widget->point_on = 0;
  }

  ui->widget->paramSet.setValue("point_on/point_on_value",
                                ui->widget->point_on);

  ui->widget->update();
}

void MainWindow::on_pushButton_6_clicked() {
  int res_calk = ui->widget->capt.xyz->vert_numb;
  int res_calk_1 = ui->widget->capt.pol_number;
  QString ress_1 = QString::number(res_calk_1, 'g', 6);
  QString ress = QString::number(res_calk, 'g', 6);
  ui->label_21->setText("Points: " + ress + ", Poligons: " + ress_1);
  ui->widget->update();
}

void MainWindow::on_comboBox_currentTextChanged(const QString &arg1) {
  if (arg1 == ".JPEG") {
    img_type = 1;
  } else if (".BMP") {
    img_type = 0;
  }
}

void MainWindow::saving_frames() {
  if (time == 100 && screen == 1) {
    timer->stop();
    QString name;

    if (img_type == 1) {
      name += QFileDialog::getSaveFileName(this, tr("Save file"), "Jpeg_image",
                                           tr("*.jpeg"));

    } else {
      name += QFileDialog::getSaveFileName(this, tr("Save file"), "BMP_image",
                                           tr("*.bmp"));
    }
    gif[gif_count].setDefaultDelay(100);
    gif[gif_count].save(name);
  } else {
    gif[gif_count].addFrame(ui->widget->grab().toImage());
  }

  if (time == 5000 && gifka == 1) {
    QString name;
    timer->stop();
    name += QFileDialog::getSaveFileName(this, tr("Save file"), "GIF_image",
                                         tr("*.gif"));

    gif[gif_count].setDefaultDelay(100);
    gif[gif_count].save(name);
  } else {
    gif[gif_count].addFrame(ui->widget->grab().toImage());
  }
  time += 100;
}

void MainWindow::save_gif() {
  time = 0.0;
  QGifImage gif(QSize(600, 400));
  QVector<QRgb> ctable;
  ctable << qRgb(255, 255, 255) << qRgb(0, 0, 0) << qRgb(255, 0, 0)
         << qRgb(0, 255, 0) << qRgb(0, 0, 255) << qRgb(255, 255, 0)
         << qRgb(0, 255, 255) << qRgb(255, 0, 255);
  gif.setGlobalColorTable(ctable, Qt::black);
}

void MainWindow::on_pushButton_8_clicked()  // sceenshot
{
  gif[gif_count].addFrame(ui->widget->grab().toImage());
  screen = 1;
  gifka = 0;

  save_gif();

  timer = new QTimer(0);
  connect(timer, SIGNAL(timeout()), this, SLOT(saving_frames()));

  timer->setInterval(100);
  timer->start();

  gif_count += 1;
}

void MainWindow::on_pushButton_7_clicked()  // gif
{
  screen = 0;
  gifka = 1;

  save_gif();

  timer = new QTimer(0);

  connect(timer, SIGNAL(timeout()), this, SLOT(saving_frames()));
  timer->setInterval(100);
  timer->start();

  gif_count += 1;
}
