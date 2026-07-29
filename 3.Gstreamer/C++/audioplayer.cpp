#include "audioplayer.h"

AudioPlayer::~AudioPlayer() {
    if (bus_watch_id) {
        g_source_remove(bus_watch_id);
    }
    if (bus) {
        gst_object_unref(bus);
    }
    if (pipeline) {
        gst_element_set_state(pipeline, GST_STATE_NULL);
        gst_object_unref(pipeline);
    }
    if (loop) {
        g_main_loop_unref(loop);
    }
}
void AudioPlayer::init() {
    gst_init(nullptr, nullptr);
    loop = g_main_loop_new (NULL, FALSE);
    pipeline = gst_pipeline_new("audio-player");
    source = gst_element_factory_make("filesrc", "source");
    demuxer = gst_element_factory_make("oggdemux", "demuxer");
    decoder = gst_element_factory_make("vorbisdec", "decoder");
    audioconvert = gst_element_factory_make("audioconvert", "audioconvert");
    audiosink = gst_element_factory_make("autoaudiosink", "audiosink");

    if (!pipeline || !source || !demuxer || !decoder || !audioconvert || !audiosink) {
        std::cerr << "Failed to create GStreamer elements." << std::endl;
        return;
    }

    gst_bin_add_many(GST_BIN(pipeline), source, demuxer, decoder, audioconvert, audiosink, nullptr);
    gst_element_link(source, demuxer);
    g_signal_connect(demuxer, "pad-added", G_CALLBACK(on_pad_added), decoder);
    gst_element_link_many(decoder, audioconvert, audiosink, nullptr);

    bus = gst_pipeline_get_bus(GST_PIPELINE(pipeline));
    bus_watch_id = gst_bus_add_watch(bus, bus_call, this);
}
void AudioPlayer::play(const std::string &filePath) {
    g_object_set(G_OBJECT(source), "location", filePath.c_str(), nullptr);
    gst_element_set_state(pipeline, GST_STATE_PLAYING);
    g_timeout_add_seconds(1, (GSourceFunc)cb_print_position, pipeline);
    g_main_loop_run (loop);
}
void AudioPlayer::stop() {
    gst_element_set_state(pipeline, GST_STATE_NULL);
}
void AudioPlayer::on_pad_added(GstElement *element, GstPad *pad, gpointer data) {
    GstPad *sink_pad = gst_element_get_static_pad((GstElement *)data, "sink");
    gst_pad_link(pad, sink_pad);
    gst_object_unref(sink_pad);
}
gboolean AudioPlayer::bus_call(GstBus *bus, GstMessage *msg, gpointer data) {
    AudioPlayer *player = static_cast<AudioPlayer *>data;
    switch (GST_MESSAGE_TYPE(msg)) {
        case GST_MESSAGE_EOS:
            std::cout << "End of stream" << std::endl;
            player->stop();                         
            break;
        case GST_MESSAGE_ERROR: {
            GError *err;
            gchar *debug_info;
            gst_message_parse_error(msg, &err, &debug_info);
            std::cerr << "Error received from element " << GST_OBJECT_NAME(msg->src)
                      << ": " << err->message << std::endl;
            std::cerr << "Debugging information: " << (debug_info ? debug_info : "none") << std::endl;
            g_clear_error(&err);
            g_free(debug_info);
            player->stop();
            break;
        }
        default:
            break;
    }
    return TRUE;
}
gboolean AudioPlayer::cb_print_position(GstElement *pipeline) {
    gint64 pos = GST_CLOCK_TIME_NONE;
    gint64 len = GST_CLOCK_TIME_NONE;
    if (gst_element_query_position(pipeline, GST_FORMAT_TIME, &pos)&&
        gst_element_query_duration(pipeline, GST_FORMAT_TIME, &len)) {
        double pos_time = (double)pos / GST_SECOND;
        double len_time = (double)len / GST_SECOND;
        g_print("\rTime: %.1f / %.1f sec", pos_time, len_time);
    }
    return TRUE;
}
