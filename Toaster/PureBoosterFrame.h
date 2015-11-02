#ifndef PUREBOOSTERFRAME_H
#define PUREBOOSTERFRAME_H

#include <QWidget>

namespace Ui {
class PureBoosterFrame;
}

class PureBoosterFrame : public QWidget
{
  Q_OBJECT

public:
  explicit PureBoosterFrame(QWidget *parent = 0);
  ~PureBoosterFrame();

private:
  Ui::PureBoosterFrame *ui;
};

#endif // PUREBOOSTERFRAME_H
