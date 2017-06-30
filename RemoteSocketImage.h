#ifndef REMOTESOCKETIMAGE_H_
#define REMOTESOCKETIMAGE_H_

#include <QQuickPaintedItem>
#include <QWebSocket>
#include <QPixmap>

class QPainter;

/* Render MJPEG frames transmitted by remote websocket
 *
 * Internally, a hard-coded authentication token is sent to remote
 * websocket once connection is established.
 *
 */

class RemoteSocketImage : public QQuickPaintedItem
{
  Q_OBJECT
  Q_PROPERTY(QString url READ url WRITE setUrl NOTIFY urlChanged);
public:
  RemoteSocketImage(QString url = "", QQuickItem *parent = nullptr);

  // Set remote websocket URL
  QString url() const;
  void setUrl(QString url);

protected:
  void paint(QPainter *painter) override;

signals:
  void urlChanged(QString url);

private slots:
  void websocketConnected();
  void textMessageReceived(QString const& msg);

private:
  QString url_;
  QWebSocket websocket_;
  QPixmap cache_;
};



#endif /* REMOTESOCKETIMAGE_H_ */
