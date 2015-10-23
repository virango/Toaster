#ifndef TUNERFRAME_H
#define TUNERFRAME_H

#include <QWidget>

namespace Ui {
  class TunerFrame;
}

class TunerFrame : public QWidget
{
  Q_OBJECT

public:
  explicit TunerFrame(QWidget *parent = 0);
  ~TunerFrame();

private:
  Ui::TunerFrame *ui;
};

#endif // TUNERFRAME_H
