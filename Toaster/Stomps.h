#ifndef STOMPS_H
#define STOMPS_H

#include <QFrame>

namespace Ui {
class Stomps;
}

class Stomps : public QFrame
{
  Q_OBJECT

public:
  explicit Stomps(QWidget *parent = 0);
  ~Stomps();

  void requestValues();

private slots:
  void on_minmaxBt_clicked(bool checked);

private:
  Ui::Stomps *ui;

  void adjustParentsSize();
};

#endif // STOMPS_H
