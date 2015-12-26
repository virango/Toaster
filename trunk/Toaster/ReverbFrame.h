#ifndef REVERBFRAME_H
#define REVERBFRAME_H

#include <QWidget>

namespace Ui {
class ReverbFrame;
}

class ReverbFrame : public QWidget
{
  Q_OBJECT

public:
  explicit ReverbFrame(QWidget *parent = 0);
  ~ReverbFrame();

private:
  Ui::ReverbFrame *ui;
};

#endif // REVERBFRAME_H
