#include <gtk/gtk.h>
#include <xfconf/xfconf.h>
#define WNCK_I_KNOW_THIS_IS_UNSTABLE 1
#include <libwnck/libwnck.h>

/* Gingdev - Symfony Style Coding */

static void cb_xfwm4_channel_property_changed(
  XfconfChannel *channel,
  const gchar *property_name,
  const GValue *value,
  WnckScreen *screen
) {
  wnck_screen_change_workspace_count(screen, g_value_get_int(value));
}

int main(int argc, char *argv[]) {

  if (!xfconf_init(NULL)) {
    g_critical("Xfconf could not be initialized");
    return 0;
  }

  gtk_init(&argc, &argv);

  WnckScreen *screen = wnck_screen_get_default();

  XfconfChannel *xfsettings = xfconf_channel_new_with_property_base(
    "xfwm4",
    "/general/workspace_count"
  );

  g_signal_connect(
    xfsettings,
    "property-changed",
    G_CALLBACK(cb_xfwm4_channel_property_changed),
    screen
  );

  gtk_main();

  return 0;
}
