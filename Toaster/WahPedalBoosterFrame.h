#ifndef WAHPEDALBOOSTERFRAME_H
#define WAHPEDALBOOSTERFRAME_H

#include <QWidget>

namespace Ui {
class WahPedalBoosterFrame;
}

class WahPedalBoosterFrame : public QWidget
{
  Q_OBJECT

public:
  explicit WahPedalBoosterFrame(QWidget *parent = 0);
  ~WahPedalBoosterFrame();

private:
  Ui::WahPedalBoosterFrame *ui;
};

#endif // WAHPEDALBOOSTERFRAME_H
