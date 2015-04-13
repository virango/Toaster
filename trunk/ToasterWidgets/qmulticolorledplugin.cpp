#include "qmulticolorled.h"
#include "qmulticolorledplugin.h"

#include <QtPlugin>

QMultiColorLedPlugin::QMultiColorLedPlugin(QObject *parent)
  : QObject(parent)
{
  m_initialized = false;
}

void QMultiColorLedPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
  if (m_initialized)
    return;

  // Add extension registrations, etc. here

  m_initialized = true;
}

bool QMultiColorLedPlugin::isInitialized() const
{
  return m_initialized;
}

QWidget *QMultiColorLedPlugin::createWidget(QWidget *parent)
{
  return new QMultiColorLed(parent);
}

QString QMultiColorLedPlugin::name() const
{
  return QLatin1String("QMultiColorLed");
}

QString QMultiColorLedPlugin::group() const
{
  return QLatin1String("");
}

QIcon QMultiColorLedPlugin::icon() const
{
  return QIcon();
}

QString QMultiColorLedPlugin::toolTip() const
{
  return QLatin1String("");
}

QString QMultiColorLedPlugin::whatsThis() const
{
  return QLatin1String("");
}

bool QMultiColorLedPlugin::isContainer() const
{
  return false;
}

QString QMultiColorLedPlugin::domXml() const
{
  return QLatin1String("<widget class=\"QMultiColorLed\" name=\"qMultiColorLed\">\n</widget>\n");
}

QString QMultiColorLedPlugin::includeFile() const
{
  return QLatin1String("qmulticolorled.h");
}

