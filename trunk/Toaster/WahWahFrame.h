#ifndef WahWahFrame_H
#define WahWahFrame_H

#include <QWidget>

namespace Ui {
  class WahWahFrame;
}

class WahWahFrame : public QWidget
{
  Q_OBJECT

public:
  explicit WahWahFrame(QWidget *parent = 0);
  ~WahWahFrame();

private:
  Ui::WahWahFrame *ui;
};

#endif // WahWahFrame_H
