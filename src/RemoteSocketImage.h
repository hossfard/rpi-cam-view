#ifndef REMOTESOCKETIMAGE_H_
#define REMOTESOCKETIMAGE_H_

#include <QQuickPaintedItem>
#include <QWebSocket>
#include <QPixmap>

class QPainter;

/** Render MJPEG frames transmitted by remote websocket
 *
 * Internally, a hard-coded authentication token is sent to remote
 * websocket once connection is established.
 *
 */
class RemoteSocketImage : public QQuickPaintedItem
{
  Q_OBJECT
  Q_PROPERTY(QString url READ url WRITE setUrl NOTIFY urlChanged);
  Q_PROPERTY(QString connectToken READ connectToken WRITE setConnectToken);
public:
  explicit RemoteSocketImage(QString url = "", QQuickItem *parent = nullptr);

  /** Remote URL
   *
   * @return Remote URL, empty if not set
   */
  QString url() const;

  /** Set remote url
   *
   * @param url remote URL
   */
  void setUrl(QString url);

  /** Return token to be sent to ws server on connect
   *
   * @return Connect token string, empty if not set
   */
  QString connectToken() const;

  /** Set token to be sent to ws server on connect
   *
   * @param token token string
   */
  void setConnectToken(QString const& token);

protected:
  void paint(QPainter *painter) override;

signals:
  void urlChanged(QString url);

private slots:
  void websocketConnected();
  void textMessageReceived(QString const& msg);

private:
  QString m_url;
  QString m_connectToken;
  QWebSocket m_websocket;
  QPixmap m_cache;
};



#endif /* REMOTESOCKETIMAGE_H_ */
