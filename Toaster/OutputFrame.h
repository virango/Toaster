#ifndef OUTPUTFRAME_H
#define OUTPUTFRAME_H

#include <QWidget>

namespace Ui {
class OutputFrame;
}

class OutputFrame : public QWidget
{
  Q_OBJECT

public:
  explicit OutputFrame(QWidget *parent = 0);
  ~OutputFrame();

private:
  Ui::OutputFrame *ui;
};

#endif // OUTPUTFRAME_H
