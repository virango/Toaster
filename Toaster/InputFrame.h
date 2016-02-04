#ifndef INPUTFRAME_H
#define INPUTFRAME_H

#include <QWidget>

namespace Ui {
class InputFrame;
}

class InputFrame : public QWidget
{
  Q_OBJECT

public:
  explicit InputFrame(QWidget *parent = 0);
  ~InputFrame();

private:
  Ui::InputFrame *ui;
};

#endif // INPUTFRAME_H
