#ifndef PEDALPITCHFRAME_H
#define PEDALPITCHFRAME_H

#include <QWidget>

namespace Ui {
class PedalPitchFrame;
}

class PedalPitchFrame : public QWidget
{
  Q_OBJECT

public:
  explicit PedalPitchFrame(QWidget *parent = 0);
  ~PedalPitchFrame();

private:
  Ui::PedalPitchFrame *ui;
};

#endif // PEDALPITCHFRAME_H
