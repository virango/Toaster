#ifndef STOMPCONTROLSTACKEDWIDGET_H
#define STOMPCONTROLSTACKEDWIDGET_H

#include <QStackedWidget>

namespace Ui {
  class StompControlStackedWidget;
}

class StompControlStackedWidget : public QStackedWidget
{
  Q_OBJECT

public:
  explicit StompControlStackedWidget(QWidget *parent = 0);
  ~StompControlStackedWidget();

private:
  Ui::StompControlStackedWidget *ui;
};

#endif // STOMPCONTROLSTACKEDWIDGET_H
