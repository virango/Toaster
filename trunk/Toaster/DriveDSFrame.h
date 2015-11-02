#ifndef DRIVEDSFRAME_H
#define DRIVEDSFRAME_H

#include <QWidget>

namespace Ui {
class DriveDSFrame;
}

class DriveDSFrame : public QWidget
{
  Q_OBJECT

public:
  explicit DriveDSFrame(QWidget *parent = 0);
  ~DriveDSFrame();

private:
  Ui::DriveDSFrame *ui;
};

#endif // DRIVEDSFRAME_H
