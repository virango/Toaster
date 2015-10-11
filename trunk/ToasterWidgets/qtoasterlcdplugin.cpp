#include "QToasterLCD.h"
#include "qtoasterlcdplugin.h"

#include <QtPlugin>

QToasterLCDPlugin::QToasterLCDPlugin(QObject *parent)
  : QObject(parent)
{
  m_initialized = false;
}

void QToasterLCDPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
  if (m_initialized)
    return;

  // Add extension registrations, etc. here

  m_initialized = true;
}

bool QToasterLCDPlugin::isInitialized() const
{
  return m_initialized;
}

QWidget *QToasterLCDPlugin::createWidget(QWidget *parent)
{
  return new QToasterLCD(parent);
}

QString QToasterLCDPlugin::name() const
{
  return QLatin1String("QToasterLCD");
}

QString QToasterLCDPlugin::group() const
{
  return QLatin1String("");
}

QIcon QToasterLCDPlugin::icon() const
{
  return QIcon();
}

QString QToasterLCDPlugin::toolTip() const
{
  return QLatin1String("");
}

QString QToasterLCDPlugin::whatsThis() const
{
  return QLatin1String("");
}

bool QToasterLCDPlugin::isContainer() const
{
  return false;
}

QString QToasterLCDPlugin::domXml() const
{
  return QLatin1String("<widget class=\"QToasterLCD\" name=\"qToasterLCD\">\n</widget>\n");
}

QString QToasterLCDPlugin::includeFile() const
{
  return QLatin1String("QToasterLCD.h");
}

