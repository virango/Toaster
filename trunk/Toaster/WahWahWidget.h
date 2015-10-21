#ifndef WAHWAHWIDGET_H
#define WAHWAHWIDGET_H

#include <QWidget>

namespace Ui {
  class WahWahWidget;
}

class WahWahWidget : public QWidget
{
  Q_OBJECT

public:
  explicit WahWahWidget(QWidget *parent = 0);
  ~WahWahWidget();

private:
  Ui::WahWahWidget *ui;
};

#endif // WAHWAHWIDGET_H
