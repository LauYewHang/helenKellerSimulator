#include <gtk/gtk.h>

GObject *window = NULL;
GtkCssProvider *cssSource = NULL;

int createGTKApp(int argc, char *argv[]);
static void startApp(GtkApplication *app, gpointer data);

int createGTKApp(int argc, char *argv[]){
    int status = 0;
    GtkApplication *app = NULL;

    app = gtk_application_new("com.uwu.helenkellersimulator", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(startApp), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);

    g_object_unref(app);
    return status;
}

static void startApp(GtkApplication *app, gpointer data){
    GtkBuilder *builder = gtk_builder_new_from_file("main.ui");
    GObject *window = gtk_builder_get_object(builder, "window");

    cssSource = gtk_css_provider_new();
    gtk_css_provider_load_from_path(cssSource, "main.css");
    gtk_style_context_add_provider_for_display(gdk_display_get_default(), GTK_STYLE_PROVIDER(cssSource), GTK_STYLE_PROVIDER_PRIORITY_USER);

    gtk_window_maximize(GTK_WINDOW(window));
    gtk_window_set_application(GTK_WINDOW(window), app);
    gtk_window_set_title(GTK_WINDOW(window), "Helen Keller Simulator");

    gtk_widget_set_visible(GTK_WIDGET(window), TRUE);
    g_object_unref(builder);
}

int main(int argc, char *argv[]){
    int status = createGTKApp(argc, argv);
    return status;
}