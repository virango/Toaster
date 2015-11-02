#ifndef TONEANDDUCKINGDSFRAME_H
#define TONEANDDUCKINGDSFRAME_H

#include <QWidget>

namespace Ui {
class ToneAndDuckingDSFrame;
}

class ToneAndDuckingDSFrame : public QWidget
{
  Q_OBJECT

public:
  explicit ToneAndDuckingDSFrame(QWidget *parent = 0);
  ~ToneAndDuckingDSFrame();

private:
  Ui::ToneAndDuckingDSFrame *ui;
};

#endif // TONEANDDUCKINGDSFRAME_H
