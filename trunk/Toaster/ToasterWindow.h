#ifndef TOASTERWINDOW_H
#define TOASTERWINDOW_H

#include <QMainWindow>

namespace Ui {
class ToasterWindow;
}

class ToasterWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ToasterWindow(QWidget *parent = 0);
    ~ToasterWindow();

private slots:
  void on_actionRequestValues_triggered();

  void on_actionCmd_triggered();

  void on_actionConfigure_triggered();

  void on_actionOpenMIDIPorts_triggered();

  void on_actionConnectToKPA_triggered();

  void on_actionDisconnectFromKPA_triggered();

  void on_actionUploadKIPRFile_triggered();

  void on_actionExit_triggered();

  void on_actionClose_MIDI_Ports_triggered();

  void on_actionCreateStringValuesTable_triggered();

  void on_actionSendSySex_triggered();

private:
  //QTimer* timer;
  void showSettingsDialog();
  Ui::ToasterWindow *ui;
};

#endif // TOASTERWINDOW_H
