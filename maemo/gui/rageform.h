#ifndef RAGEFORM_H
#define RAGEFORM_H

#include <stdlib.h>
#include "ui_rageform.h"

#define ACCEL_FILE "/sys/class/i2c-adapter/i2c-3/3-001d/coord"
#define SHAKE_UPDATE_MSEC		100			/* granularity of shake testing */
#define MIN_SHAKE_THRES			2000		/* lowest val considered a shake */
#define MAX_SHAKE_VAL			12000		/* reasonably high observed val */
#define MAX_SHAKE_PERCENT		50			/* percent rage for a max shake */

class RageForm : public QWidget, private Ui::RageForm
{
	Q_OBJECT

public:
	RageForm(QWidget *parent = 0);

private slots:
	void on_pushButton_clicked(void);
	void on_horizontalSlider_valueChanged(int value);
	void update_shakes(void);

private:
	unsigned int rage_amt;
	int current_x;
	int current_y;
	int current_z;
};

#endif /* RAGEFORM_H */
