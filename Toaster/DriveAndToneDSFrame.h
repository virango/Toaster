#ifndef DRIVEANDTONEDSFRAME_H
#define DRIVEANDTONEDSFRAME_H

#include <QWidget>

namespace Ui {
class DriveAndToneDSFrame;
}

class DriveAndToneDSFrame : public QWidget
{
  Q_OBJECT

public:
  explicit DriveAndToneDSFrame(QWidget *parent = 0);
  ~DriveAndToneDSFrame();

private:
  Ui::DriveAndToneDSFrame *ui;
};

#endif // DRIVEANDTONEDSFRAME_H
