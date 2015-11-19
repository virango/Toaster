#ifndef FLANGERFRAME_H
#define FLANGERFRAME_H

#include <QWidget>

namespace Ui {
class FlangerFrame;
}

class FlangerFrame : public QWidget
{
  Q_OBJECT

public:
  explicit FlangerFrame(QWidget *parent = 0);
  ~FlangerFrame();

private:
  Ui::FlangerFrame *ui;
};

#endif // FLANGERFRAME_H
