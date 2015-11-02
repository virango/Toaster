#ifndef METALDSFRAME_H
#define METALDSFRAME_H

#include <QWidget>

namespace Ui {
class MetalDSFrame;
}

class MetalDSFrame : public QWidget
{
  Q_OBJECT

public:
  explicit MetalDSFrame(QWidget *parent = 0);
  ~MetalDSFrame();

private:
  Ui::MetalDSFrame *ui;
};

#endif // METALDSFRAME_H
