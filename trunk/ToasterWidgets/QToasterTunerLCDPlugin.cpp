#include "QToasterTunerLCDPlugin.h"
#include "QToasterTunerLCD.h"

QToasterTunerLCDPlugin::QToasterTunerLCDPlugin(QObject *parent) :
  QObject(parent)
{
    m_initialized = false;
}

void QToasterTunerLCDPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
  if (m_initialized)
    return;

  // Add extension registrations, etc. here

  m_initialized = true;
}

bool QToasterTunerLCDPlugin::isInitialized() const
{
  return m_initialized;
}

QWidget *QToasterTunerLCDPlugin::createWidget(QWidget *parent)
{
  return new QToasterTunerLCD(parent);
}

QString QToasterTunerLCDPlugin::name() const
{
  return QLatin1String("QToasterTunerLCD");
}

QString QToasterTunerLCDPlugin::group() const
{
  return QLatin1String("");
}

QIcon QToasterTunerLCDPlugin::icon() const
{
  return QIcon();
}

QString QToasterTunerLCDPlugin::toolTip() const
{
  return QLatin1String("");
}

QString QToasterTunerLCDPlugin::whatsThis() const
{
  return QLatin1String("");
}

bool QToasterTunerLCDPlugin::isContainer() const
{
  return false;
}

QString QToasterTunerLCDPlugin::domXml() const
{
  return QLatin1String("<widget class=\"QToasterTunerLCD\" name=\"toasterTunerLCD\">\n</widget>\n");
}

QString QToasterTunerLCDPlugin::includeFile() const
{
  return QLatin1String("QToasterTunerLCD.h");
}


