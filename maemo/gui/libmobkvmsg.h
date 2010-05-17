#ifndef LIBMOBKVMSG_H
#define LIBMOBKVMSG_H

#include <QtCore>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QByteArray>

/* Flags, or whatever */
#define MOBKV_BLOB			1

#ifdef __MAEMO5__
#include <conic/conicconnection.h>
#include <conic/conicconnectionevent.h>
#include <conic/conicevent.h>
#endif /* __MAEMO5__ */

enum ConnectionType
{
    CONN_TYPE_UNKNOWN,
    CONN_TYPE_WIFI,
    CONN_TYPE_CELLULAR,
    CONN_TYPE_INIT,
};

class MobKVMessage : public QObject
{
	Q_OBJECT

public:
	MobKVMessage(QUrl url, QObject *parent = 0);
	~MobKVMessage(void);
	int addKeyValue(QString key, QString value, int flags);
	int addKeyValue(QString key, QByteArray blob, int flags);
	void send(void); // Callee deletes the obj

	/* TODO: how about a diff way to check on progress?, signals, etc */
	void close(void);

private slots:
	void replyFinished(QNetworkReply *reply);

private:
	ConnectionType con_type;
	QNetworkAccessManager net_man;
	QByteArray buf;
	QUrl url;
	/* this won't work right - these lists get freed when the obj dies */
	QList<QByteArray> fast_msgs;
	QList<QByteArray> slow_msgs;
};

#endif /* LIBMOBKVMSG_H */
