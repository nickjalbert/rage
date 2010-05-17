#include "libmobkvmsg.h"

#ifdef __MAEMO5__
void ConnectionEventCallback(ConIcConnection* /*connection*/,
                             ConIcConnectionEvent* event, gpointer user_data)
{
	ConnectionType *data = (ConnectionType*)user_data;

	bool connected = (con_ic_connection_event_get_status(event) ==
	                  CON_IC_STATUS_CONNECTED);
	if (connected)
	{
		const gchar* bearer = con_ic_event_get_bearer_type(CON_IC_EVENT(event));
		if (strcmp(bearer,CON_IC_BEARER_WLAN_ADHOC) == 0 ||
		           strcmp(bearer,CON_IC_BEARER_WLAN_INFRA) == 0)
			*data =  CONN_TYPE_WIFI;
		else if (strcmp(bearer,"GPRS") == 0)
			*data = CONN_TYPE_CELLULAR;
	}
}
#endif /* __MAEMO5__ */

// TODO: pass in the header?
MobKVMessage::MobKVMessage(QUrl url, QObject *parent) : QObject(parent)
{
	this->url = url;
	connect(&net_man, SIGNAL(finished(QNetworkReply*)),
	        this, SLOT(replyFinished(QNetworkReply*)));
	// TODO: want a better post variable?
	buf.append("incident=<incident>");

#ifdef __MAEMO5__
	/* Init and start a request for the network type */
	con_type = CONN_TYPE_INIT;
	ConIcConnection *connection = con_ic_connection_new();
	g_object_ref_sink(connection);
	g_signal_connect(G_OBJECT(connection), "connection-event",
	                 G_CALLBACK(ConnectionEventCallback), &con_type);
	con_ic_connection_connect(connection,
	                          CON_IC_CONNECT_FLAG_AUTOMATICALLY_TRIGGERED);
	/* somewhat ugly, spin til there's a response to the connection */
	while (con_type == CONN_TYPE_INIT)
		QCoreApplication::instance()->processEvents();
#else
	con_type = CONN_TYPE_WIFI;
#endif /* __MAEMO5__ */
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
	/* 1 = Wifi, 2 = Cell, 0 = nothing */
	printf("Connection status is %d\n", con_type);
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
	/* Cleanup ourselves too.  Don't want to do this unless we're completely
	 * done. */
	this->deleteLater();
}
