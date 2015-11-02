#ifndef RECTISHAPERFRAME_H
#define RECTISHAPERFRAME_H

#include <QWidget>

namespace Ui {
class RectiShaperFrame;
}

class RectiShaperFrame : public QWidget
{
  Q_OBJECT

public:
  explicit RectiShaperFrame(QWidget *parent = 0);
  ~RectiShaperFrame();

private:
  Ui::RectiShaperFrame *ui;
};

#endif // RECTISHAPERFRAME_H
