#ifndef QTOASTERSTOMPEDITLCD_H
#define QTOASTERSTOMPEDITLCD_H

#include <QWidget>
#include "Commons.h"
#include "ToasterWidgetsLib.h"

namespace Ui {
  class QToasterStompEditLCD;
}

struct ICtxMenuProvider;

class TOASTERWIDGETS_EXPORT QToasterStompEditLCD : public QWidget
{
  Q_OBJECT
  Q_ENUMS(Color)
  Q_ENUMS(Page)
  Q_PROPERTY(Color color READ color WRITE setColor)
  Q_PROPERTY(QString stompInstance READ stompInstance WRITE setStompInstance)
  Q_PROPERTY(QString stompName READ stompName WRITE setStompName)
  Q_PROPERTY(QString value1Title READ value1Title WRITE setValue1Title)
  Q_PROPERTY(QString value2Title READ value2Title WRITE setValue2Title)
  Q_PROPERTY(QString value3Title READ value3Title WRITE setValue3Title)
  Q_PROPERTY(QString value4Title READ value4Title WRITE setValue4Title)
  Q_PROPERTY(QString value5Title READ value5Title WRITE setValue5Title)
  Q_PROPERTY(QString value6Title READ value6Title WRITE setValue6Title)
  Q_PROPERTY(QString value7Title READ value7Title WRITE setValue7Title)
  Q_PROPERTY(QString value8Title READ value8Title WRITE setValue8Title)
  Q_PROPERTY(QString value9Title READ value9Title WRITE setValue9Title)
  Q_PROPERTY(QString value10Title READ value10Title WRITE setValue10Title)
  Q_PROPERTY(QString value11Title READ value11Title WRITE setValue11Title)
  Q_PROPERTY(QString value12Title READ value12Title WRITE setValue12Title)
  Q_PROPERTY(QString value13Title READ value13Title WRITE setValue13Title)
  Q_PROPERTY(QString value14Title READ value14Title WRITE setValue14Title)
  Q_PROPERTY(QString value15Title READ value15Title WRITE setValue15Title)
  Q_PROPERTY(QString value16Title READ value16Title WRITE setValue16Title)
  Q_PROPERTY(Page currentPage READ currentPage WRITE setCurrentPage)
  Q_PROPERTY(Page maxPage READ maxPage WRITE setMaxPage)

public:
  explicit QToasterStompEditLCD(QWidget *parent = 0);
  ~QToasterStompEditLCD();

  enum Page
  {
    Page1 = 0,
    Page2 = 1
  };

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

  Color color() const { return mColor; }
  QString stompInstance() const;
  QString stompName() const;
  QString value1Title() const;
  QString value2Title() const;
  QString value3Title() const;
  QString value4Title() const;
  QString value5Title() const;
  QString value6Title() const;
  QString value7Title() const;
  QString value8Title() const;
  QString value9Title() const;
  QString value10Title() const;
  QString value11Title() const;
  QString value12Title() const;
  QString value13Title() const;
  QString value14Title() const;
  QString value15Title() const;
  QString value16Title() const;
  Page currentPage() const { return mCurrentPage; }
  Page maxPage() const { return mMaxPage; }

  void setCtxMenuProvider(ICtxMenuProvider* ctxMenuProvider) { mpCtxMenuProvider = ctxMenuProvider; }


public slots:
  void setColor(QToasterStompEditLCD::Color color);
  void setStompInstance(QString stompInstance);
  void setStompName(QString stompName);
  void setValue1Title(QString title);
  void setValue2Title(QString title);
  void setValue3Title(QString title);
  void setValue4Title(QString title);
  void setValue5Title(QString title);
  void setValue6Title(QString title);
  void setValue7Title(QString title);
  void setValue8Title(QString title);
  void setValue9Title(QString title);
  void setValue10Title(QString title);
  void setValue11Title(QString title);
  void setValue12Title(QString title);
  void setValue13Title(QString title);
  void setValue14Title(QString title);
  void setValue15Title(QString title);
  void setValue16Title(QString title);
  void setValue1(QString value);
  void setValue2(QString value);
  void setValue3(QString value);
  void setValue4(QString value);
  void setValue5(QString value);
  void setValue6(QString value);
  void setValue7(QString value);
  void setValue8(QString value);
  void setValue9(QString value);
  void setValue10(QString value);
  void setValue11(QString value);
  void setValue12(QString value);
  void setValue13(QString value);
  void setValue14(QString value);
  void setValue15(QString value);
  void setValue16(QString value);

  void setCurrentPage(Page page);
  void setMaxPage(Page page);

  void setStompAFXType(FXType fxType);
  void setStompBFXType(FXType fxType);
  void setStompCFXType(FXType fxType);
  void setStompDFXType(FXType fxType);
  void setStompXFXType(FXType fxType);
  void setStompModFXType(FXType fxType);

  void setStompAEnabled(bool enabled);
  void setStompBEnabled(bool enabled);
  void setStompCEnabled(bool enabled);
  void setStompDEnabled(bool enabled);
  void setStompXEnabled(bool enabled);
  void setStompModEnabled(bool enabled);
  void setDelayEnabled(bool enabled);
  void setReverbEnabled(bool enabled);

protected:
  void createSkin();
  void paintEvent(QPaintEvent*);
  void contextMenuEvent(QContextMenuEvent * cme);

  void setEnabled(QWidget& w, bool enabled);

  void updatePageInfo();

private:
  Ui::QToasterStompEditLCD *ui;

  QList<QPixmap> mSkinPixmaps;
  Color mColor;
  Page  mMaxPage;
  Page  mCurrentPage;

  ICtxMenuProvider* mpCtxMenuProvider;
};

#endif // QTOASTERSTOMPEDITLCD_H
