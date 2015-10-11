#ifndef PROFILE_H
#define PROFILE_H

#include <QObject>
#include "ProfileMidi.h"

class Profile : public QObject, public ProfileMidi
{
  Q_OBJECT
public:
  explicit Profile(QObject *parent = 0);
  ~Profile();

  void requestAllValues();

signals:
  void rigNameReceived(const QString& rigName);
  void rigAuthorReceived(const QString& rigAuthor);
  void rigDateTimeReceived(const QString& rigDateTime);
  void rigCommentReceived(const QString& rigComment);
  void ampNameReceived(const QString& ampName);
  void ampAuthorReceived(const QString& ampAuthor);
  void ampDateReceived(const QString& ampDate);
  void ampTimeReceived(const QString& ampTime);
  void cabNameReceived(const QString& cabName);

public slots:
  void applyRigName(const QString& rigName);
  void applyRigAuthor(const QString& rigAuthor);
  void applyRigDateTime(const QString& rigDateTime);
  void applyRigComment(const QString& rigComment);
  void applyAmpName(const QString& ampName);
  void applyAmpAuthor(const QString& ampAuthor);
  void applyAmpDate(const QString& ampDate);
  void applyAmpTime(const QString& ampTime);
  void applyCabName(const QString& cabName);
  void applyRigPrev();
  void applyRigNext();

protected:
  virtual void midiRigNameReceived(const QString& rigName);
  virtual void midiRigAuthorReceived(const QString& rigAuthor);
  virtual void midiRigDateTimeReceived(const QString& rigDateTime);
  virtual void midiRigCommentReceived(const QString& rigComment);
  virtual void midiAmpNameReceived(const QString& ampName);
  virtual void midiAmpAuthorReceived(const QString& ampAuthor);
  virtual void midiAmpDateReceived(const QString& ampDate);
  virtual void midiAmpTimeReceived(const QString& ampTime);
  virtual void midiCabNameReceived(const QString& cabName);
};

#endif // PROFILE_H
