#ifndef REMOTEIMAGE_H_
#define REMOTEIMAGE_H_

#include <QtQuick/QQuickPaintedItem>
#include <QString>
#include <QPixmap>
#include <QTimer>
#include <QNetworkAccessManager>
#include <QNetworkReply>

/** Periodically fetch and draw remote image
 *
 */
class QPainter;

class RemoteImage : public QQuickPaintedItem
{
  Q_OBJECT
  Q_PROPERTY(QString url READ url WRITE setUrl NOTIFY urlChanged)
  Q_PROPERTY(int reloadInterval READ reloadInterval WRITE setReloadInterval
             NOTIFY reloadIntervalChanged)

public:
  explicit RemoteImage(QString url = "", QQuickItem *parent = nullptr);

  /** Return the remote URL
   *
   * @return Remote URL, empty if not set
   */
  QString url() const;

  /** Set remote url
   *
   * @param url remote URL
   */
  void setUrl(QString url);

  /** Set perioid interval for fetching image
   *
   * @return reload interval in milliseconds
   */
  int reloadInterval() const;

  /** Specify interval to fetch remote image and update
   *
   * Set interval to zero or negative to stop remote update
   *
   * @param interval reload interval in milliseconds
   */
  void setReloadInterval(int interval);

protected:
  void paint(QPainter *painter) override;

signals:
  /** Signal emitted when remote URL is changed
   *
   * @param url changed remote URL
   */
  void urlChanged(QString url);

  /** Signal emitted when reload interval is changed
   *
   */
  void reloadIntervalChanged(int interval);

  /** Error emitted when fetching remote image fails
   *
   * @param err string representation of error
   */
  void error(QString err);

private slots:
  void requestFinished(QNetworkReply *reply);
  void timersUp();
  void networkError(QNetworkReply::NetworkError code);

private:
  int m_reloadInterval;
  QString m_url;
  QPixmap m_cache;
  QTimer m_timer;
  QNetworkReply *m_reply;
  QNetworkAccessManager m_webCtrl;
};

#endif /* REMOTEIMAGE_H_ */
