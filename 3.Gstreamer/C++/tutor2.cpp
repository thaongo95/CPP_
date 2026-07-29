#include <gst/gst.h>
#include <iostream>

int main(int argc, char **argv){
	GstElement *pipeline, *source, *convert, *filter, *sink;
	GstBus *bus;
	GstMessage *msg;
	GstStateChangeReturn ret;
	
	gst_init (&argc, &argv);
	source = gst_element_factory_make("videotestsrc", "source");
	convert = gst_element_factory_make("videoconvert", "convert");
	filter = gst_element_factory_make("edgetv", "filter");
	sink = gst_element_factory_make("glimagesink", "sink");
	
	pipeline = gst_pipeline_new("test-pipeline");
	
	if (!pipeline || !source || !convert || !filter ||  !sink){
		std::cout << "Not all elements could be created." << std::endl;
		if (pipeline)
        		gst_object_unref(pipeline);

    		return -1;
	}
	
	gst_bin_add_many (GST_BIN(pipeline), source, convert, filter, sink, nullptr);
	if (!gst_element_link_many(source, convert, filter, sink, nullptr)){
		std::cout << "Element could not be linked." << std::endl;
		gst_object_unref(pipeline);
		return -1;
	}
	
	g_object_set (source, "pattern", 0, nullptr);
	ret = gst_element_set_state(pipeline, GST_STATE_PLAYING);
	if (ret == GST_STATE_CHANGE_FAILURE){
		std::cout << "Unable to set the pipeline to the playing state."<< std::endl;
		gst_object_unref(pipeline);
		return -1;
	}
	
	bus = gst_element_get_bus(pipeline);
	msg = gst_bus_timed_pop_filtered (bus, GST_CLOCK_TIME_NONE, static_cast<GstMessageType> (GST_MESSAGE_ERROR | GST_MESSAGE_EOS));
	
	if (msg != nullptr) {
		GError *err;
    		gchar *debug_info;

    		switch (GST_MESSAGE_TYPE (msg)) {
      			case GST_MESSAGE_ERROR:
        			gst_message_parse_error (msg, &err, &debug_info);
        			std::cout << "Error received from element" << GST_OBJECT_NAME (msg->src) << ": "  << err->message << std::endl;
        			std::cout << "Debugging information:" << (debug_info ? debug_info : "none") << std::endl;
        			g_clear_error (&err);
        			g_free (debug_info);
        			break;
      			case GST_MESSAGE_EOS:
        			std::cout <<  "End-Of-Stream reached." << std::endl;
        			break;
      			default:
        			/* We should not reach here because we only asked for ERRORs and EOS */
        			std::cout << "Unexpected message received." << std::endl;
        			break;
    		}
    		gst_message_unref (msg);
  	}
  	
  	gst_object_unref(bus);
  	gst_element_set_state(pipeline, GST_STATE_NULL);
  	gst_object_unref(pipeline);
  	return 0;  	
  	
}
