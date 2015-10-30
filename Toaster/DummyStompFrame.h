#ifndef DUMMYSTOMPFRAME_H
#define DUMMYSTOMPFRAME_H

#include <QWidget>

namespace Ui {
class DummyStompFrame;
}

class DummyStompFrame : public QWidget
{
  Q_OBJECT

public:
  explicit DummyStompFrame(QWidget *parent = 0);
  ~DummyStompFrame();

private:
  Ui::DummyStompFrame *ui;
};

#endif // DUMMYSTOMPFRAME_H
