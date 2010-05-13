#ifndef RAGEFORM_H
#define RAGEFORM_H

#include <stdlib.h>
#include "ui_rageform.h"

#define ACCEL_FILE "/sys/class/i2c-adapter/i2c-3/3-001d/coord"
#define SHAKE_UPDATE_MSEC		100			/* granularity of shake testing */
#define MIN_SHAKE_THRES			2000		/* lowest val considered a shake */
#define MAX_SHAKE_VAL			12000		/* reasonably high observed val */
#define MAX_SHAKE_PERCENT		50			/* percent rage for a max shake */

class RageGPS;

class RageForm : public QWidget, private Ui::RageForm
{
	Q_OBJECT

public:
	RageForm(QWidget *parent = 0);
	~RageForm(void);
	/* ugh, fucking C++... */
	void setlabel2_text(QString str);

private slots:
	void on_pushButton_clicked(void);
	void on_horizontalSlider_valueChanged(int value);
	void update_shakes(void);

private:
	unsigned int rage_amt;
	int ac_cur_x;
	int ac_cur_y;
	int ac_cur_z;
	RageGPS *gps;
};

#ifdef __MAEMO5__

#include <location/location-gps-device.h>
#include <location/location-gpsd-control.h>

class RageGPS {

public:
	RageGPS(RageForm *_parent);
	~RageGPS(void);
	double get_latitude(void);
	double get_longitude(void);
	friend void gps_changed(LocationGPSDevice *device, RageGPS *gps);

private:
	RageForm *parent;
	LocationGPSDControl *control;
	LocationGPSDevice *device;
	double latitude;
	double longitude;
};

void gps_changed(LocationGPSDevice *device, RageGPS *gps);

#else 
class RageGPS {

public:
	RageGPS(RageForm *_parent);
	double get_latitude(void);
	double get_longitude(void);
private:
	RageForm *parent;
	double latitude;
	double longitude;
};
#endif /* __MAEMO5__ */

#endif /* RAGEFORM_H */
