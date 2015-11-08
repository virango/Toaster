#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
  Q_OBJECT

public:
  explicit SettingsDialog(QWidget *parent = 0);
  ~SettingsDialog();

  void init();

private slots:
  void on_buttonBox_accepted();


  void on_printValuesCheckBox_clicked(bool checked);

  void on_createValueMapCheckBox_clicked(bool checked);

  void on_fileEdit_textChanged(const QString &fileName);

  void on_fileButton_clicked();

private:
  Ui::SettingsDialog *ui;
};

#endif // SETTINGSDIALOG_H
