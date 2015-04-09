#ifndef QTOASTERBUTTON_H
#define QTOASTERBUTTON_H

#include <QWidget>
#include <QMap>
#include <QLabel>
#include <QMovie>
#include <QTimer>

#define MAP_INSERT(x, y, z) x[y] = z

class QToasterButton : public QWidget
{
  Q_OBJECT
  Q_ENUMS(Type)
  Q_ENUMS(State)
  Q_PROPERTY(Type type READ type WRITE setType)
  Q_PROPERTY(bool triState READ triState WRITE setTriState)

public:
  QToasterButton(QWidget *parent = 0);

  enum Type
  {
    Big, Small
  };

  enum State
  {
    Off = 0,
    On = 1,
    Tri = 2
  };

  Type type() const { return mType; }
  bool triState() const { return mTriState; }

signals:
  void valueChanged(QToasterButton::State);

public slots:
  void setType(Type type);
  void setTriState(bool triState);
  void setState(State state);

private slots:
  void singleClick();

protected:
  void createSkin();
  void paintEvent(QPaintEvent* pe);
  void mousePressEvent(QMouseEvent* me);
  void mouseReleaseEvent(QMouseEvent* me);
  void mouseDoubleClickEvent(QMouseEvent* me);

  void toggleOnOff();

private:
  QList<QPixmap> mSkinPixmaps;

  Type    mType;
  bool    mTriState;
  State   mCurrState;
  State   mPrevState;

  bool    mDblClick;
  QTimer  mSingleClickTimer;

  QLabel  mAnimLabel;
  QMovie  mMovie;

  QMap<Type, QString> mSkins;
  QMap<Type, QString> mAnims;
  static const int mSkinNoOfFrames = 2;
};

#endif
