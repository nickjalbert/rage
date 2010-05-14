#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <QtGui>
#include "rageform.h"

RageForm::RageForm(QWidget *parent) : QWidget(parent)
{
	setupUi(this);
	uid = 1337; // TODO: get a better value
	rage_amt = 0;
	ac_cur_x = ac_cur_y = ac_cur_z = 0;
	gps = new RageGPS(this);

	/* init shake data */
	FILE *ac_fd = fopen(ACCEL_FILE, "r");
	if (!ac_fd)
		printf("Cannot access the accelerometer, won't have the shakes\n");
	else {
  		if (fscanf(ac_fd, "%i %i %i", &ac_cur_x, &ac_cur_y, &ac_cur_z) != 3)
			printf("Error initializing shake data!\n");
		fclose(ac_fd);
	}
	/* consider only setting the timer if we have the accel.  depends if we use
	 * it for anything else. */
	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(update_shakes()));
	timer->start(SHAKE_UPDATE_MSEC);
	lineEdit->setFocus();
}

RageForm::~RageForm(void)
{
	delete gps;
}

void RageForm::post_info(void)
{
	printf("Lat: %f\n", gps->get_latitude());
	printf("Long: %f\n", gps->get_longitude());
	printf("Rage: %d\n", rage_amt);
	printf("Comment: %s\n", lineEdit->text().toAscii().data());

	QByteArray *buf = new QByteArray();
	buf->append("incident=<incident>");
	buf->append("<timestamp>");
	buf->append(QString::number(time(0), 10));
	buf->append("</timestamp>");
	buf->append("<uid>");
	buf->append(QString::number(uid, 10));
	buf->append("</uid>");
	buf->append("<rage>");
	buf->append(QString::number(rage_amt, 10));
	buf->append("</rage>");
	buf->append("<lat>");
	buf->append(QString::number(gps->get_latitude(), 'g', 10));
	buf->append("</lat>");
	buf->append("<long>");
	buf->append(QString::number(gps->get_longitude(), 'g', 10));
	buf->append("</long>");
	buf->append("<comment>");
	buf->append(lineEdit->text());
	buf->append("</comment>");
	buf->append("</incident>");
	/* TODO: put in the constructor and private space, reuse, etc */
	QNetworkAccessManager *manager = new QNetworkAccessManager(this);
	connect(manager, SIGNAL(finished(QNetworkReply*)),
	        this, SLOT(replyFinished(QNetworkReply*)));
	manager->post(QNetworkRequest(QUrl(RAGE_BACKEND)), *buf);
}

void RageForm::replyFinished(QNetworkReply *reply)
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
}

void RageForm::on_submitButton_clicked(void)
{
	post_info();
	QMessageBox::information(this, tr("Status"), tr("Rage Sending!!!"),
	                         QMessageBox::Ok);
	horizontalSlider->setValue(0);
	lineEdit->clear();
	lineEdit->setFocus();
}

void RageForm::on_clearButton_clicked(void)
{
	lineEdit->setFocus();
}

void RageForm::on_horizontalSlider_valueChanged(int value)
{
	rage_amt = value;
}

void RageForm::update_shakes(void)
{
	int shake_amt, retval;
	int new_x, new_y, new_z, delta_x, delta_y, delta_z;
	FILE *ac_fd = fopen(ACCEL_FILE, "r");

	if (ac_fd) {
  		retval = fscanf(ac_fd, "%i %i %i", &new_x, &new_y, &new_z);	
		fclose(ac_fd);
		if (retval != 3) {
			printf("Read invalid input (%i %i %i) from ac_fd!\n",
			       new_x, new_y, new_z);
			return;
		}
		delta_x = abs(new_x - ac_cur_x);
		delta_y = abs(new_y - ac_cur_y);
		delta_z = abs(new_z - ac_cur_z);
		
		ac_cur_x = new_x;
		ac_cur_y = new_y;
		ac_cur_z = new_z;
		
		shake_amt = delta_x + delta_y + delta_z;
	} else {
		shake_amt = 5;
	}
	/* debugging */
	label_1->setText("Shakes: " + QString::number(shake_amt, 10));

	if (shake_amt > MIN_SHAKE_THRES) {
		rage_amt += shake_amt * MAX_SHAKE_PERCENT / MAX_SHAKE_VAL;
		rage_amt = rage_amt > 100 ? 100 : rage_amt;
		progressBar->setValue(rage_amt);
	}
}

void RageForm::setlabel2_text(QString str)
{
	label_2->setText(str);
}

/* GPS stuff, platform specific */
#ifdef __MAEMO5__
RageGPS::RageGPS(RageForm *_parent)
{
	parent = _parent;
	latitude = longitude = 0.0;
	control = location_gpsd_control_get_default();
	device = (LocationGPSDevice*)g_object_new(LOCATION_TYPE_GPS_DEVICE, NULL);
	g_object_set(G_OBJECT(control),
	             "preferred-method", LOCATION_METHOD_USER_SELECTED,
	             "preferred-interval", LOCATION_INTERVAL_DEFAULT,
	             NULL);
	g_signal_connect(device, "changed", G_CALLBACK(gps_changed), this);
	location_gpsd_control_start(control);
}

RageGPS::~RageGPS(void)
{
	location_gpsd_control_stop(control);			
}

void gps_changed(LocationGPSDevice *device, RageGPS *gps)
{
	if (device->fix) {
		if (device->fix->fields) {
			gps->latitude = device->fix->latitude;
			gps->longitude = device->fix->longitude;
			/* debugging */
			gps->parent->setlabel2_text(
			             "Lat: " + QString::number(gps->latitude, 'g', 4) +
			             " Long: " + QString::number(gps->longitude, 'g', 4));
			printf("lat = %f, long = %f\n", gps->latitude,
			       gps->longitude);
		}
	} else {
		printf("GPS changed, but no fix!\n");
	}
}
#else
RageGPS::RageGPS(RageForm *_parent)
{
	printf("No GPS, location will be 0, 0\n");
	parent = _parent;
	latitude = longitude = 0.0;
}
#endif /* __MAEMO5__ */

double RageGPS::get_latitude(void)
{
	return latitude;
}

double RageGPS::get_longitude(void)
{
	return longitude;
}

