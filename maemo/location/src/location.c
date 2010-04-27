#include "location.h"

static void on_error(LocationGPSDControl *control, LocationGPSDControlError error, gpointer data)
{ 
	g_main_loop_quit((GMainLoop *) data);
}

static void on_changed(LocationGPSDevice *device, gpointer data)
{
	if (!device)
		return;

	if (device->fix) {
		if (device->fix->fields & LOCATION_GPS_DEVICE_LATLONG_SET) {
		  location_gpsd_control_stop((LocationGPSDControl *) data);			
			post_rage_data(device->fix->latitude, device->fix->longitude, 929, 6258);
		}
	}
} 

static void on_stop(LocationGPSDControl *control, gpointer data)
{
	g_main_loop_quit((GMainLoop *) data);
} 

static gboolean start_location(gpointer data)
{
	location_gpsd_control_start((LocationGPSDControl *) data);
	return FALSE;
}

int main(int argc, char *argv[])
{
	LocationGPSDControl *control;
	LocationGPSDevice *device;
	GMainLoop *loop;

	g_type_init();

	loop = g_main_loop_new(NULL, FALSE);

	control = location_gpsd_control_get_default();
	device = g_object_new(LOCATION_TYPE_GPS_DEVICE, NULL);

	g_object_set(G_OBJECT(control),
		"preferred-method", LOCATION_METHOD_USER_SELECTED,
		"preferred-interval", LOCATION_INTERVAL_DEFAULT,
		NULL);

	g_signal_connect(control, "error-verbose", G_CALLBACK(on_error), loop);
	g_signal_connect(device, "changed", G_CALLBACK(on_changed), control);
	g_signal_connect(control, "gpsd-stopped", G_CALLBACK(on_stop), loop);

	g_idle_add(start_location, control);

	g_main_loop_run(loop);

	g_object_unref(device);
	g_object_unref(control);

	return 0;
}

