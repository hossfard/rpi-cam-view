#include "RemoteSocketImage.h"
#include <QByteArray>
#include <QPainter>
#include <QDebug>


RemoteSocketImage::
RemoteSocketImage(QString url, QQuickItem *parent)
  : QQuickPaintedItem(parent)
{
  url_ = url;

  connect(&websocket_, SIGNAL(connected()), this, SLOT(websocketConnected()));

  // The server is expected to only send frames as base64 UTF8 data
  connect(&websocket_, SIGNAL(textMessageReceived(QString const&)),
          this, SLOT(textMessageReceived(QString const&)));

  connect(&websocket_, &QWebSocket::disconnected, [=](){
      qDebug() << "disconnected";
    });

  connect(&websocket_, static_cast<void(QWebSocket::*)(QAbstractSocket::SocketError)>(&QWebSocket::error),
          [=](QAbstractSocket::SocketError err){
            qDebug() << "error: " <<  err;
          });

  connect(&websocket_, &QWebSocket::stateChanged, [=](QAbstractSocket::SocketState s){
      qDebug() << "state changed: " << s;
    });
}


void
RemoteSocketImage::
setUrl(QString url){
  if (url != url_){
    url_ = url;
    websocket_.open(url);
    qDebug() << "url = " << url;
    emit urlChanged(url);
  }
}


QString
RemoteSocketImage::
url() const{
  return url_;
}


void
RemoteSocketImage::
paint(QPainter *painter){
  if (! cache_.isNull()){
    auto w = boundingRect().width();
    auto h = boundingRect().height();
    painter->drawPixmap(QRectF(0,0, w, h),
                        cache_.scaled(w,h),
                        QRectF(0,0, w, h));
  }
}


void
RemoteSocketImage::
websocketConnected(){
  qDebug() << "connected ";
  websocket_.sendTextMessage("0YE07uoK27jNBq92tHADQmw/CS0ayGkk5Ocnjq4+gto=");
}


void
RemoteSocketImage::
textMessageReceived(QString const& msg){
  if (cache_.loadFromData(QByteArray::fromBase64(msg.toUtf8()))){
    update();
  }
}
