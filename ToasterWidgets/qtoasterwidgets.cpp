#include "qtoasterdialplugin.h"
#include "qtoasterenumdialplugin.h"
#include "QToasterBrowserLCDPlugin.h"
#include "QToasterStompEditLCDPlugin.h"
//#include "qbigdialplugin.h"
//#include "qsmalldialplugin.h"
#include "qmulticolorledplugin.h"
//#include "qsmallknobplugin.h"
#include "qtoasterbuttonplugin.h"
#include "qchickenheaddialplugin.h"
#include "qtoasterwidgets.h"

QToasterWidgets::QToasterWidgets(QObject *parent)
  : QObject(parent)
{
  m_widgets.append(new QToasterDialPlugin(this));
  m_widgets.append(new QToasterEnumDialPlugin(this));
  m_widgets.append(new QToasterBrowserLCDPlugin(this));
  m_widgets.append(new QToasterStompEditLCDPlugin(this));
//m_widgets.append(new QBigDialPlugin(this));
//  m_widgets.append(new QSmallDialPlugin(this));
  m_widgets.append(new QMultiColorLedPlugin(this));
//  m_widgets.append(new QSmallKnobPlugin(this));
  m_widgets.append(new QToasterButtonPlugin(this));
  m_widgets.append(new QChickenHeadDialPlugin(this));
}

QList<QDesignerCustomWidgetInterface*> QToasterWidgets::customWidgets() const
{
  return m_widgets;
}

#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(qtoasterwidgetsplugin, QToasterWidgets)
#endif // QT_VERSION < 0x050000
