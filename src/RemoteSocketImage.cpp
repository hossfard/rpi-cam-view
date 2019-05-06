#include "RemoteSocketImage.h"
#include <QByteArray>
#include <QPainter>


RemoteSocketImage::
RemoteSocketImage(QString url, QQuickItem *parent)
  : QQuickPaintedItem(parent)
{
  m_url = url;
  setRotation(180);
  connect(&m_websocket, SIGNAL(connected()), this, SLOT(websocketConnected()));

  // The server is expected to only send frames as base64 UTF8 data
  connect(&m_websocket, SIGNAL(textMessageReceived(QString const&)),
          this, SLOT(textMessageReceived(QString const&)));
}


void
RemoteSocketImage::
setUrl(QString url){
  if (url == m_url){
    return;
  }

  m_url = url;
  m_websocket.open(url);
  emit urlChanged(url);
}


QString
RemoteSocketImage::
url() const{
  return m_url;
}


void
RemoteSocketImage::
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

void
RemoteSocketImage::
websocketConnected(){
  if (m_connectToken.isEmpty())
    return;

  m_websocket.sendTextMessage(m_connectToken);
}

void
RemoteSocketImage::
textMessageReceived(QString const& msg){
  if (m_cache.loadFromData(QByteArray::fromBase64(msg.toUtf8()))){
    update();
  }
}

QString
RemoteSocketImage::
connectToken() const{
  return m_connectToken;
}

void
RemoteSocketImage::
setConnectToken(QString const& token){
  m_connectToken = token;
}
