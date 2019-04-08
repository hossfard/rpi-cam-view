#ifndef REMOTEIMAGE_H_
#define REMOTEIMAGE_H_

#include <QtQuick/QQuickPaintedItem>
#include <QString>
#include <QPixmap>
#include <QTimer>
#include <QNetworkAccessManager>
#include <QNetworkReply>

/* Fetch and draw remote image */

class QPainter;

class RemoteImage : public QQuickPaintedItem
{
  Q_OBJECT
  Q_PROPERTY(QString url READ url WRITE setUrl NOTIFY urlChanged)
  Q_PROPERTY(int reloadInterval READ reloadInterval WRITE setReloadInterval
             NOTIFY reloadIntervalChanged)

public:
  RemoteImage(QString url = "", QQuickItem *parent = nullptr);

  // Remote URL. Returns empty string if not set
  QString url() const;

  // Set or update remote URL
  void setUrl(QString url);

  // Interval used for fetching remote image
  int reloadInterval() const;

  /* Specify interval in milliseconds to fetch remote image and update
   *
   * Set interval to zero or negative to stop remote update
   */
  void setReloadInterval(int interval);

protected:
  void paint(QPainter *painter) override;

signals:
  // Signal emitted when remote URL is changed
  void urlChanged(QString url);

  // Signal emitted when reload interval is changed
  void reloadIntervalChanged(int interval);

  // Error emitted when fetching remote image fails
  void error(QString err);

private slots:
  void requestFinished(QNetworkReply *reply);
  void timersUp();
  void networkError(QNetworkReply::NetworkError code);

private:
  int reloadInterval_;
  QString url_;
  QPixmap cache_;
  QTimer timer_;
  QNetworkReply *reply_;
  QNetworkAccessManager webCtrl_;
};

#endif /* REMOTEIMAGE_H_ */
