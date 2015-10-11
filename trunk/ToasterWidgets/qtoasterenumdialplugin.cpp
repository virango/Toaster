#include "qtoasterenumdial.h"
#include "qtoasterenumdialplugin.h"

#include <QtPlugin>

QToasterEnumDialPlugin::QToasterEnumDialPlugin(QObject *parent)
  : QObject(parent)
{
  m_initialized = false;
}

void QToasterEnumDialPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
  if (m_initialized)
    return;

  // Add extension registrations, etc. here

  m_initialized = true;
}

bool QToasterEnumDialPlugin::isInitialized() const
{
  return m_initialized;
}

QWidget *QToasterEnumDialPlugin::createWidget(QWidget *parent)
{
  return new QToasterEnumDial(parent);
}

QString QToasterEnumDialPlugin::name() const
{
  return QLatin1String("QToasterEnumDial");
}

QString QToasterEnumDialPlugin::group() const
{
  return QLatin1String("");
}

QIcon QToasterEnumDialPlugin::icon() const
{
  return QIcon(":/resources/DialIcon.png");
}

QString QToasterEnumDialPlugin::toolTip() const
{
  return QLatin1String("");
}

QString QToasterEnumDialPlugin::whatsThis() const
{
  return QLatin1String("");
}

bool QToasterEnumDialPlugin::isContainer() const
{
  return false;
}

QString QToasterEnumDialPlugin::domXml() const
{
  return QLatin1String("<widget class=\"QToasterEnumDial\" name=\"qToasterEnumDial\">\n</widget>\n");
}

QString QToasterEnumDialPlugin::includeFile() const
{
  return QLatin1String("qtoasterenumdial.h");
}
