#include "qlcddisplay.h"
#include "qlcddisplayplugin.h"

#include <QtPlugin>

QLCDDisplayPlugin::QLCDDisplayPlugin(QObject *parent)
  : QObject(parent)
{
  m_initialized = false;
}

void QLCDDisplayPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
  if (m_initialized)
    return;

  // Add extension registrations, etc. here

  m_initialized = true;
}

bool QLCDDisplayPlugin::isInitialized() const
{
  return m_initialized;
}

QWidget *QLCDDisplayPlugin::createWidget(QWidget *parent)
{
  return new QLCDDisplay(parent);
}

QString QLCDDisplayPlugin::name() const
{
  return QLatin1String("QLCDDisplay");
}

QString QLCDDisplayPlugin::group() const
{
  return QLatin1String("");
}

QIcon QLCDDisplayPlugin::icon() const
{
  return QIcon();
}

QString QLCDDisplayPlugin::toolTip() const
{
  return QLatin1String("");
}

QString QLCDDisplayPlugin::whatsThis() const
{
  return QLatin1String("");
}

bool QLCDDisplayPlugin::isContainer() const
{
  return false;
}

QString QLCDDisplayPlugin::domXml() const
{
  return QLatin1String("<widget class=\"QLCDDisplay\" name=\"qLCDDisplay\">\n</widget>\n");
}

QString QLCDDisplayPlugin::includeFile() const
{
  return QLatin1String("qlcddisplay.h");
}

