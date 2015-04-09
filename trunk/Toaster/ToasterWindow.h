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

private:
    Ui::ToasterWindow *ui;
};

#endif // TOASTERWINDOW_H
