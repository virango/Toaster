#include "qtoasterbutton.h"
#include "qtoasterbuttonplugin.h"

#include <QtPlugin>

QToasterButtonPlugin::QToasterButtonPlugin(QObject *parent)
  : QObject(parent)
{
  m_initialized = false;
}

void QToasterButtonPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
  if (m_initialized)
    return;

  // Add extension registrations, etc. here

  m_initialized = true;
}

bool QToasterButtonPlugin::isInitialized() const
{
  return m_initialized;
}

QWidget *QToasterButtonPlugin::createWidget(QWidget *parent)
{
  return new QToasterButton(parent);
}

QString QToasterButtonPlugin::name() const
{
  return QLatin1String("QToasterButton");
}

QString QToasterButtonPlugin::group() const
{
  return QLatin1String("");
}

QIcon QToasterButtonPlugin::icon() const
{
  return QIcon(":/resources/ButtonIcon.png");
}

QString QToasterButtonPlugin::toolTip() const
{
  return QLatin1String("");
}

QString QToasterButtonPlugin::whatsThis() const
{
  return QLatin1String("");
}

bool QToasterButtonPlugin::isContainer() const
{
  return false;
}

QString QToasterButtonPlugin::domXml() const
{
  return QLatin1String("<widget class=\"QToasterButton\" name=\"qToasterButton\">\n</widget>\n");
}

QString QToasterButtonPlugin::includeFile() const
{
  return QLatin1String("qtoasterbutton.h");
}

