#include <gst/gst.h>
//#include <TargetConditionals.h>


int main(int argc, char **argv){
	GstElement *pipeline;
	GstBus *bus;
	GstMessage *msg;
	
	gst_init (&argc, &argv);
	
	pipeline = gst_parse_launch( "playbin uri=https://www.youtube.com/watch?v=hH8N8WOJf7o", NULL);
	
	gst_element_set_state (pipeline, GST_STATE_PLAYING);
	
	bus = gst_element_get_bus (pipeline);
	msg = gst_bus_timed_pop_filtered(bus, GST_CLOCK_TIME_NONE, static_cast<GstMessageType>(GST_MESSAGE_ERROR | GST_MESSAGE_EOS));
	
	if (GST_MESSAGE_TYPE(msg) == GST_MESSAGE_ERROR){
		g_printerr( " there's a error");
	}
	gst_message_unref(msg);
	gst_object_unref(bus);
	gst_element_set_state (pipeline, GST_STATE_NULL);
	gst_object_unref(pipeline);
	return 0;



}

