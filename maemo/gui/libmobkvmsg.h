#ifndef LIBMOBKV_H
#define LIBMOBKV_H

#include <QtCore>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QByteArray>

/* Flags, or whatever */
#define MOBKV_BLOB			1

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
	QNetworkAccessManager net_man;
	QByteArray buf;
	QUrl url;
};

#endif /* LIBMOBKV_H */
