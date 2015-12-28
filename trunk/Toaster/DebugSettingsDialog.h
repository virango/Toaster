#ifndef DEBUGSETTINGSDIALOG_H
#define DEBUGSETTINGSDIALOG_H

#include <QDialog>

namespace Ui {
class DebugSettingsDialog;
}

class DebugSettingsDialog : public QDialog
{
  Q_OBJECT

public:
  explicit DebugSettingsDialog(QWidget *parent = 0);
  ~DebugSettingsDialog();

private slots:
  void on_printValuesCheckBox_clicked(bool checked);

private:
  Ui::DebugSettingsDialog *ui;
};

#endif // DEBUGSETTINGSDIALOG_H
