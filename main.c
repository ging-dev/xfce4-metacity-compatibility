#include <gtk/gtk.h>
#include <xfconf/xfconf.h>

/* Gingdev - Symfony Style Coding */

static void cb_xfwm4_channel_property_changed(
  XfconfChannel *channel,
  const gchar *property_name,
  const GValue *value,
  GSettings *settings
) {
  g_settings_set_int(settings,
    "num-workspaces",
    g_value_get_int(value)
  );
}

int main(int argc, char *argv[]) {

  if (!xfconf_init(NULL)) {
    g_critical("Xfconf could not be initialized");
    return 0;
  }

  gtk_init(&argc, &argv);

  GSettings *settings = g_settings_new("org.gnome.desktop.wm.preferences");

  XfconfChannel *xfsettings = xfconf_channel_new_with_property_base(
    "xfwm4",
    "/general/workspace_count"
  );

  g_signal_connect(
    xfsettings,
    "property-changed",
    G_CALLBACK(cb_xfwm4_channel_property_changed),
    settings
  );

  gtk_main();

  return 0;
}
