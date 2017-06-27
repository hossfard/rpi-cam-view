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
  reloadInterval_ = 2000;
  url_ = url;
  connect(&webCtrl_, SIGNAL(finished(QNetworkReply*)),
          this, SLOT(requestFinished(QNetworkReply*)));
}


QString
RemoteImage::
url() const{
  return url_;
}


void
RemoteImage::
setUrl(QString url){
  if (url != url_){
    url_ = url;
    QUrl qurl = QUrl(url);
    QNetworkRequest req(qurl);
    reply_ = webCtrl_.get(req);
    connect(reply_, SIGNAL(error(QNetworkReply::NetworkError)),
            this, SLOT(networkError(QNetworkReply::NetworkError)));

    connect(&timer_, SIGNAL(timeout()), this, SLOT(timersUp()));
    timer_.start(reloadInterval_);

    update();
    emit urlChanged(url_);
  }
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
  if (! cache_.isNull()){
    auto w = boundingRect().width();
    auto h = boundingRect().height();
    painter->drawPixmap(QRectF(0,0, w, h),
                        cache_.scaled(w,h),
                        QRectF(0,0, w, h));
  }
}


int
RemoteImage::
reloadInterval() const{
  return reloadInterval_;
}


void
RemoteImage::
setReloadInterval(int interval){
  if (interval != reloadInterval_){
    // Stop requesting and reloading image
    if (interval <= 0){
      timer_.stop();
      reloadInterval_ = 0;
    }
    else{
      // Update reload interval
      reloadInterval_ = interval;
      connect(&timer_, SIGNAL(timeout()), this, SLOT(timersUp()));
      timer_.start(reloadInterval_);
    }
    emit reloadIntervalChanged(interval);
  }
}


void
RemoteImage::
timersUp(){
  if (!reply_->isRunning()){
    QUrl qurl = QUrl(url_);
    QNetworkRequest req(qurl);
    reply_->deleteLater();
    reply_ = webCtrl_.get(req);
    connect(reply_, SIGNAL(error(QNetworkReply::NetworkError)),
            this, SLOT(networkError(QNetworkReply::NetworkError)));
  }
}

// Redraw the image
void
RemoteImage::
requestFinished(QNetworkReply *reply){
  cache_.loadFromData(reply->readAll());
  update();
}
