#ifndef TOASTERWINDOW_H
#define TOASTERWINDOW_H

#include <QMainWindow>

namespace Ui {
class ToasterWindow;
}

class ToasterWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ToasterWindow(QWidget *parent = 0);
    ~ToasterWindow();

private slots:
  void on_actionRequest_triggered();

  void on_actionSettings_triggered();

  void on_actionCmd_triggered();

private:
  void showSettingsDialog();
  Ui::ToasterWindow *ui;
};

#endif // TOASTERWINDOW_H
