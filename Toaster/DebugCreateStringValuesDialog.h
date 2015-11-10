#ifndef DEBUGCREATESTRINGVALUESDIALOG_H
#define DEBUGCREATESTRINGVALUESDIALOG_H

#include <QDialog>


namespace Ui {
class DebugCreateStringValuesDialog;
}

class QTimer;

class DebugCreateStringValuesDialog : public QDialog
{
  Q_OBJECT

public:
  explicit DebugCreateStringValuesDialog(QWidget *parent = 0);
  ~DebugCreateStringValuesDialog();

private slots:
  void on_raw2ValFileButton_clicked();
  void on_val2rawFileButton_clicked();
  void on_startButton_clicked();
  void on_closeButton_clicked();
  void onTimer();

private:
  Ui::DebugCreateStringValuesDialog *ui;

  unsigned char mAdressPage;
  unsigned char mParameter;
  int mLowerRange;
  int mUpperRange;

  int mCurrValue;

  QTimer* mTimer;
};

#endif // DEBUGCREATESTRINGVALUESDIALOG_H
