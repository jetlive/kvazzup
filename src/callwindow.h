#pragma once

#include "mediamanager.h"
#include "callnegotiation.h"
#include "conferenceview.h"
#include "settings.h"

#include <QMainWindow>

// This class is the heart of this software. It is responsible for directing
// all the other classes based on user input. It would be best if
// this class did as little as possible apart from that


class StatisticsWindow;

namespace Ui {
class CallWindow;
class CallerWidget;
}

class CallWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit CallWindow(QWidget *parent);
  ~CallWindow();

  void startStream();

  void closeEvent(QCloseEvent *event);

public slots:
   void addParticipant();
   void openStatistics(); // Opens statistics window

   void micState();
   void cameraState();

   void incomingCall(QString callID, QString caller);
   void callOurselves(QString callID, std::shared_ptr<SDPMessageInfo> info);

   void ringing(QString callID);

   void ourCallRejected(QString callID);

   void callNegotiated(QString callID, std::shared_ptr<SDPMessageInfo> peerInfo,
                       std::shared_ptr<SDPMessageInfo> localInfo);

   // UI messages
   void acceptCall();
   void rejectCall();

   void endCall(QString callID, QString ip);

private slots:
   void on_settings_clicked();

   void recordChangedSettings();

private:

  void createParticipant(QString& callID, const std::shared_ptr<SDPMessageInfo> peerInfo,
                         const std::shared_ptr<SDPMessageInfo> localInfo);

  Ui::CallWindow *ui_;

  Settings settingsView_;
  StatisticsWindow *stats_;

  QMutex conferenceMutex_;
  ConferenceView conference_;

  CallNegotiation callNeg_;
  MediaManager media_;

  QTimer *timer_; // for GUI update

  uint16_t portsOpen_;
};
