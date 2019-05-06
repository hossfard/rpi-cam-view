#include "RemoteImage.h"
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QPainter>
#include <QUrl>
#include <QDebug>


RemoteImage::
RemoteImage(QString url /* = "" */, QQuickItem *parent /*= nullptr*/)
  : QQuickPaintedItem(parent)
{
  m_reloadInterval = 2000;
  m_url = url;
  connect(&m_webCtrl, SIGNAL(finished(QNetworkReply*)),
          this, SLOT(requestFinished(QNetworkReply*)));
}


QString
RemoteImage::
url() const{
  return m_url;
}


void
RemoteImage::
setUrl(QString url){
  if (url == m_url){
    return;
  }

  m_url = url;
  QUrl qurl = QUrl(url);
  QNetworkRequest req(qurl);
  m_reply = m_webCtrl.get(req);
  connect(m_reply, SIGNAL(error(QNetworkReply::NetworkError)),
          this, SLOT(networkError(QNetworkReply::NetworkError)));

  connect(&m_timer, SIGNAL(timeout()), this, SLOT(timersUp()));
  m_timer.start(m_reloadInterval);

  update();
  emit urlChanged(m_url);
}


void
RemoteImage::
networkError(QNetworkReply::NetworkError code){
  qDebug() << "Network error code " << code;
  emit error(QString("Network error code %0").arg(code));
}


void
RemoteImage::
paint(QPainter *painter){
 if (m_cache.isNull()){
   return;
 }

 auto w = boundingRect().width();
 auto h = boundingRect().height();
 painter->drawPixmap(QRectF(0,0, w, h),
                     m_cache.scaled(w,h),
                     QRectF(0,0, w, h));
}


int
RemoteImage::
reloadInterval() const{
  return m_reloadInterval;
}


void
RemoteImage::
setReloadInterval(int interval){
  if (interval == m_reloadInterval){
    return;
  }

  // Stop requesting and reloading image
  if (interval <= 0){
    m_timer.stop();
    m_reloadInterval = 0;
  }
  else{
    // Update reload interval
    m_reloadInterval = interval;
    connect(&m_timer, SIGNAL(timeout()), this, SLOT(timersUp()));
    m_timer.start(m_reloadInterval);
  }
  emit reloadIntervalChanged(interval);
}


void
RemoteImage::
timersUp(){
  if (m_reply->isRunning()){
    return;
  }

  QUrl qurl = QUrl(m_url);
  QNetworkRequest req(qurl);
  m_reply->deleteLater();
  m_reply = m_webCtrl.get(req);
  connect(m_reply, SIGNAL(error(QNetworkReply::NetworkError)),
          this, SLOT(networkError(QNetworkReply::NetworkError)));
}


// Redraw the image
void
RemoteImage::
requestFinished(QNetworkReply *reply){
  m_cache.loadFromData(reply->readAll());
  update();
}
