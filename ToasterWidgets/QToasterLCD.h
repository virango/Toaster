#ifndef QTOASTERLCD_H
#define QTOASTERLCD_H
#include <QWidget>
#include <QMap>
#include "Commons.h"

#define ENABLED "background-color: rgb(50,50,50);%1;border-color: rgb(0, 0, 0);border-radius: 3px;"
#define DISABLED "background-color: rgb(128,128,128);%1;border-color: rgb(0, 0, 0);border-radius: 3px;"

#define COLOR_STANDARD "color: rgb(167, 179, 175)"
#define COLOR_ORANGE   "color: rgb(207, 137, 90)"
#define COLOR_RED      "color: rgb(210, 53, 53)"
#define COLOR_YELLOW   "color: rgb(201, 201, 63)"
#define COLOR_CYAN     "color: rgb(0, 193, 193)"
#define COLOR_BLUE     "color: rgb(103, 103, 239)"
#define COLOR_PURPLE   "color: rgb(148, 20, 216)"
#define COLOR_WHITE    "color: rgb(210, 210, 210)"
#define COLOR_GREEN    "color: rgb(54, 224, 54)"

struct ICtxMenuProvider;

class QToasterLCD : public QWidget
{
  Q_OBJECT
  Q_ENUMS(Color)
  Q_ENUMS(Page)
  Q_PROPERTY(Color color READ color WRITE setColor)
  Q_PROPERTY(Page currentPage READ currentPage WRITE setCurrentPage)
  Q_PROPERTY(Page maxPage READ maxPage WRITE setMaxPage)
public:
  enum Color
  {
    Standard    = 0,
    Orange      = 1,
    Red         = 2,
    Yellow      = 3,
    Cyan        = 4,
    Blue        = 5,
    Purple      = 6,
    White       = 7,
    Green       = 8,
    NoOfColors  = 9      // must be always last
  };

  enum Page
  {
    Page1 = 0,
    Page2 = 1,
    Page3 = 2
  };


  explicit QToasterLCD(QWidget *parent);
  ~QToasterLCD();

  Color color() const { return mColor; }
  Page currentPage() const { return mCurrentPage; }
  Page maxPage() const { return mMaxPage; }

  void setCtxMenuProvider(ICtxMenuProvider* ctxMenuProvider) { mpCtxMenuProvider = ctxMenuProvider; }

public slots:
  virtual void setColor(Color color);
  virtual void setCurrentPage(Page page);
  virtual void setMaxPage(Page page);

protected:
  void createSkin();
  void displayStompEnabled(QWidget& w, bool enabled);

  QList<QPixmap> mSkinPixmaps;
  Color mColor;
  Page  mMaxPage;
  Page  mCurrentPage;

  ICtxMenuProvider* mpCtxMenuProvider;

  static QMap<Color, QString>  sColor2StyleSheetsMap;
  static QMap<FXType, QString> sFXType2ShortNameMap;
};




#endif // QTOASTERLCD_H
