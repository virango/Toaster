#include "qtoasterdial.h"
#include "qtoasterdialplugin.h"

#include <QtPlugin>

QToasterDialPlugin::QToasterDialPlugin(QObject *parent)
  : QObject(parent)
{
  m_initialized = false;
}

void QToasterDialPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
  if (m_initialized)
    return;

  // Add extension registrations, etc. here

  m_initialized = true;
}

bool QToasterDialPlugin::isInitialized() const
{
  return m_initialized;
}

QWidget *QToasterDialPlugin::createWidget(QWidget *parent)
{
  return new QToasterDial(parent);
}

QString QToasterDialPlugin::name() const
{
  return QLatin1String("QToasterDial");
}

QString QToasterDialPlugin::group() const
{
  return QLatin1String("");
}

QIcon QToasterDialPlugin::icon() const
{
  return QIcon(":/resources/DialIcon.png");
}

QString QToasterDialPlugin::toolTip() const
{
  return QLatin1String("");
}

QString QToasterDialPlugin::whatsThis() const
{
  return QLatin1String("");
}

bool QToasterDialPlugin::isContainer() const
{
  return false;
}

QString QToasterDialPlugin::domXml() const
{
  return QLatin1String("<widget class=\"QToasterDial\" name=\"qToasterDial\">\n</widget>\n");
}

QString QToasterDialPlugin::includeFile() const
{
  return QLatin1String("qtoasterdial.h");
}

