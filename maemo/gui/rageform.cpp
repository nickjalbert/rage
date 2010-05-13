#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <QtGui>
#include "rageform.h"

RageForm::RageForm(QWidget *parent) : QWidget(parent)
{
	setupUi(this);
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
}

RageForm::~RageForm(void)
{
	delete gps;
}

void RageForm::on_pushButton_clicked(void)
{
	QMessageBox::information(this, tr("Help!!"), tr("HELLLLP!!!"),
	                         QMessageBox::Cancel);
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

