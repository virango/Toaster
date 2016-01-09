#ifndef CONNECTIONSTATUSFRAME_H
#define CONNECTIONSTATUSFRAME_H

#include <QWidget>

namespace Ui {
class ConnectionStatusFrame;
}

class ConnectionStatusFrame : public QWidget
{
  Q_OBJECT

public:
  explicit ConnectionStatusFrame(QWidget *parent = 0);
  ~ConnectionStatusFrame();

public slots:
  void setMidiStatus(bool isConnected);
  void setKPAStatus(bool isConnected);

private:
  Ui::ConnectionStatusFrame *ui;
};

#endif // CONNECTIONSTATUSFRAME_H
