#ifndef WAHPHASERFRAME_H
#define WAHPHASERFRAME_H

#include <QWidget>

namespace Ui {
class WahPhaserFrame;
}

class WahPhaserFrame : public QWidget
{
  Q_OBJECT

public:
  explicit WahPhaserFrame(QWidget *parent = 0);
  ~WahPhaserFrame();

private:
  Ui::WahPhaserFrame *ui;
};

#endif // WAHPHASERFRAME_H
