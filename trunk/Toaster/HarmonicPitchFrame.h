#ifndef HARMONICPITCHFRAME_H
#define HARMONICPITCHFRAME_H

#include <QWidget>

namespace Ui {
class HarmonicPitchFrame;
}

class HarmonicPitchFrame : public QWidget
{
  Q_OBJECT

public:
  explicit HarmonicPitchFrame(QWidget *parent = 0);
  ~HarmonicPitchFrame();

private:
  Ui::HarmonicPitchFrame *ui;
};

#endif // HARMONICPITCHFRAME_H
