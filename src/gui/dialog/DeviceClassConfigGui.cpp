#include "DeviceClassConfigGui.h"

#include "SettingsDialog.h"
#include "control/settings/Settings.h"
#include "control/settings/ButtonConfig.h"
#include "util/DeviceListHelper.h"

#include <config.h>
#include <i18n.h>
#include <Util.h>

DeviceClassConfigGui::DeviceClassConfigGui(GladeSearchpath* gladeSearchPath, GtkWidget* w, Settings* settings, InputDevice device)
 : GladeGui(gladeSearchPath, "settingsDeviceClassConfig.glade", "offscreenwindow"), settings(settings), device(device)
{
	XOJ_INIT_TYPE(DeviceClassConfigGui);

	GtkWidget* mainGrid = get("deviceClassGrid");
	gtk_container_remove(GTK_CONTAINER(getWindow()), mainGrid);
	gtk_box_pack_end(GTK_BOX(w), mainGrid, true, true, 0);
	gtk_widget_show_all(mainGrid);

	this->labelDevice = get("labelDevice");
	this->cbDeviceClass = get("cbDeviceClass");
	gtk_label_set_text(GTK_LABEL(this->labelDevice), (device.getName() + " (" + device.getType() + ")").c_str());

	loadSettings();
}

DeviceClassConfigGui::~DeviceClassConfigGui()
{
	XOJ_CHECK_TYPE(DeviceClassConfigGui);

	XOJ_RELEASE_TYPE(DeviceClassConfigGui);
}

void DeviceClassConfigGui::loadSettings()
{
	XOJ_CHECK_TYPE(DeviceClassConfigGui);

	int deviceType = this->settings->getDeviceClassForDevice(this->device.getDevice());
	gtk_combo_box_set_active(GTK_COMBO_BOX(this->cbDeviceClass), deviceType);
}

void DeviceClassConfigGui::show(GtkWindow* parent)
{
	// Not implemented! This is not a dialog!
}

void DeviceClassConfigGui::saveSettings()
{
	XOJ_CHECK_TYPE(DeviceClassConfigGui);

	int deviceClass = gtk_combo_box_get_active(GTK_COMBO_BOX(this->cbDeviceClass));
	this->settings->setDeviceClassForDevice(this->device.getDevice(), deviceClass);
}
