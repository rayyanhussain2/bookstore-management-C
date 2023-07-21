#include <gtk/gtk.h>

int main(){
  gtk_init();
  gtk_main();
  GtkWidget* window = gtk_window_new();
  gtk_quit();
}