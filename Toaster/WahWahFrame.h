#ifndef WahWahFrame_H
#define WahWahFrame_H

#include <QWidget>

namespace Ui {
  class WahWahFrame;
}

class WahWahFrame : public QWidget
{
  Q_OBJECT

public:
  explicit WahWahFrame(QWidget *parent = 0);
  ~WahWahFrame();

private slots:


  void on_manualDial_valueChanged(double arg1);

  void on_peakDial_valueChanged(double arg1);

  void on_pedalRangeDial_valueChanged(double arg1);

  void on_peakRangeDial_valueChanged(double arg1);

  void on_pedalModeDial_valueChanged(int valueIndex);

  void on_mixDial_valueChanged(double arg1);

  void on_duckingDial_valueChanged(double arg1);

  void on_page1Dial_valueChanged(double arg1);

private:
  Ui::WahWahFrame *ui;
};

#endif // WahWahFrame_H
