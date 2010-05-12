#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <QtGui>
#include "rageform.h"

RageForm::RageForm(QWidget *parent) : QWidget(parent)
{
	setupUi(this);
	rage_amt = 0;
	current_x = current_y = current_z = 0;

	/* init shake data */
	FILE *ac_fd = fopen(ACCEL_FILE, "r");
	if (!ac_fd)
		printf("Cannot access the accelerometer, won't have the shakes\n");
	else {
  		if (fscanf(ac_fd, "%i %i %i", &current_x, &current_y, &current_z) != 3)
			printf("Error initializing shake data!\n");
		fclose(ac_fd);
	}

	/* consider only setting the timer if we have the accel.  depends if we use
	 * it for anything else. */
	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(update_shakes()));
	timer->start(SHAKE_UPDATE_MSEC);
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
		delta_x = abs(new_x - current_x);
		delta_y = abs(new_y - current_y);
		delta_z = abs(new_z - current_z);
		
		current_x = new_x;
		current_y = new_y;
		current_z = new_z;
		
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
