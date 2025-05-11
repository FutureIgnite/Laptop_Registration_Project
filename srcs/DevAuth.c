#include "../includes/header_files.h"

static void on_window_destroy(GtkWidget *widget, gpointer data)
{
   gtk_main_quit();
}

int main(int argc, char *argv[])
{
   /*our home page*/
   GtkWidget *home;

   gtk_init(&argc, &argv);

   home = gtk_window_new(GTK_WINDOW_TOPLEVEL);

   gtk_window_set_title(GTK_WINDOW(home), "MULAPIZI");
   gtk_window_set_default_size(GTK_WINDOW(home), 800, 600);
   
   g_signal_connect(
       home,
       "destroy",
       G_CALLBACK(on_window_destroy),
       NULL
   );

   gtk_widget_show_all(home);

   gtk_main();

   return 0;
}
