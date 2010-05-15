#include "libmobkvmsg.h"

// TODO: pass in the header?
MobKVMessage::MobKVMessage(QUrl url, QObject *parent) : QObject(parent)
{
	this->url = url;
	connect(&net_man, SIGNAL(finished(QNetworkReply*)),
	        this, SLOT(replyFinished(QNetworkReply*)));
	// TODO: want a better post variable?
	buf.append("incident=<incident>");
}

MobKVMessage::~MobKVMessage(void)
{
}

int MobKVMessage::addKeyValue(QString key, QString value, int flags)
{
	buf.append("<" + key + ">");
	buf.append(value);
	buf.append("</" + key + ">");
	return 0;
}

int MobKVMessage::addKeyValue(QString key, QByteArray blob, int flags)
{
	return -1;
}

void MobKVMessage::send(void)
{
	buf.append("</incident>");
	net_man.post(QNetworkRequest(url), buf);
}

/* TODO: how about a diff way to check on progress?, signals, etc.  can't just
 * call this at any point in time, and we probably want to just destruct it.*/
void MobKVMessage::close(void)
{
	// this->deleteLater();
}

void MobKVMessage::replyFinished(QNetworkReply *reply)
{
	#if 0
	printf("Got reply from %s\n", reply->url().toString().toAscii().data());
	printf("Error: %d\n", reply->error());
	QList<QByteArray> list = reply->rawHeaderList();
	printf("%d headers:\n", list.count());
	for (int i = 0; i < list.size(); i++) {
		printf("%s: ", list.at(i).data());
		printf("%s\n", reply->rawHeader(list.at(i)).data());
	}
	#endif
	reply->close();
	reply->deleteLater();
	/* Cleanup ourselves too */
	this->deleteLater();
}
