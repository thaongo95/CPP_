#include <iostream>
#include <gst/gst.h>

class AudioPlayer {
public:
    ~AudioPlayer();
    void init();
    void play(const std::string &filePath);
    void stop();
private:
    GMainLoop *loop = nullptr;
    GstElement *pipeline = nullptr;
    GstElement *source = nullptr;
    GstElement *demuxer = nullptr;
    GstElement *decoder = nullptr;
    GstElement *audioconvert = nullptr;
    GstElement *audiosink = nullptr;
    GstBus *bus = nullptr;
    guint bus_watch_id = 0;
private:
    static void on_pad_added(GstElement *element, GstPad *pad, gpointer data);
    static gboolean bus_call(GstBus *bus, GstMessage *msg, gpointer data);  
    static gboolean cb_print_position(GstElement *pipeline);
};