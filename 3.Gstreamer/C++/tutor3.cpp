#include <gst/gst.h>
#include <iostream>
#include "audioplayer.h"


class CustomData{

public:

	~CustomData(){stop();}
	void init();
	void play(const std::string & _uri);
	void stop();
	

private:
	GstElement *pipeline = nullptr;
  	GstElement *source = nullptr;
  	GstElement *convert = nullptr;
  	GstElement *resample = nullptr;
  	GstElement *sink = nullptr;
  	GstBus *bus;
  	GstMessage *msg;
  	GstStateChangeReturn ret;
  	//gboolean terminate = FALSE;
private:
	static void pad_added_handler(GstElement *src, GstPad *pad, gpointer data); 
};


void CustomData::init(){
	gst_init (nullptr, nullptr);
	source = gst_element_factory_make ("uridecodebin", "source");
  	convert = gst_element_factory_make ("audioconvert", "convert");
  	resample = gst_element_factory_make ("audioresample", "resample");
  	sink = gst_element_factory_make ("autoaudiosink", "sink");
  	
  	pipeline = gst_pipeline_new ("test-pipeline");
  	if (!pipeline || !source || !convert || !resample || !sink) {
    		std::cout << "Not all elements could be created." << std::endl;
    		return;
 	}
 	gst_bin_add_many (GST_BIN (pipeline), source, convert, resample, sink, NULL);
 	if (!gst_element_link_many (convert, resample, sink, NULL)) {
		std::cout << "Elements could not be linked." << std::endl;
		gst_object_unref (pipeline);
		return;
	}
	g_signal_connect (source, "pad-added", G_CALLBACK (pad_added_handler), convert);
	
}
void CustomData::play(const std::string & _uri){
	 g_object_set (source, "uri", _uri.c_str(), NULL);
	 ret = gst_element_set_state (pipeline, GST_STATE_PLAYING);
	 if (ret==GST_STATE_CHANGE_FAILURE){
	 	std::cout << "Playing error" << std::endl;
	 	return;
	 }
	 bus = gst_element_get_bus(pipeline);
	 msg = gst_bus_timed_pop_filtered(bus, GST_CLOCK_TIME_NONE, static_cast<GstMessageType>(GST_MESSAGE_ERROR |GST_MESSAGE_EOS));
}
void CustomData::stop(){
	 
         if (pipeline)
	 {
	 	gst_message_unref(msg);
	 	gst_object_unref (bus);
		gst_element_set_state(pipeline, GST_STATE_NULL);
		gst_object_unref(pipeline);
		pipeline = nullptr;
	 }
}
void CustomData::pad_added_handler(GstElement *src, GstPad *new_pad, gpointer data){
	GstPad *sink_pad = gst_element_get_static_pad (static_cast<GstElement *> (data), "sink");
  	GstPadLinkReturn ret_link;
  	GstCaps *new_pad_caps = NULL;
  	GstStructure *new_pad_struct = NULL;
  	const gchar *new_pad_type = NULL;

	//g_print ("Received new pad '%s' from '%s':\n", GST_PAD_NAME (new_pad), GST_ELEMENT_NAME (src));

	/* If our converter is already linked, we have nothing to do here */
	if (gst_pad_is_linked (sink_pad)) {
	//g_print ("We are already linked. Ignoring.\n");
	goto exit;
	}

	/* Check the new pad's type */
	new_pad_caps = gst_pad_get_current_caps (new_pad);
	new_pad_struct = gst_caps_get_structure (new_pad_caps, 0);
	new_pad_type = gst_structure_get_name (new_pad_struct);
	if (!g_str_has_prefix (new_pad_type, "audio/x-raw")) {
		g_print ("It has type '%s' which is not raw audio. Ignoring.\n", new_pad_type);
	goto exit;
	}

	/* Attempt the link */
	ret_link = gst_pad_link (new_pad, sink_pad);
	if (GST_PAD_LINK_FAILED (ret_link)) {
		//g_print ("Type is '%s' but link failed.\n", new_pad_type);
	} else {
		//g_print ("Link succeeded (type '%s').\n", new_pad_type);
	}

	exit:
	/* Unreference the new pad's caps, if we got them */
	if (new_pad_caps != NULL)
		gst_caps_unref (new_pad_caps);

	/* Unreference the sink pad */
	gst_object_unref (sink_pad);
}
int main(int argc, char **argv){
	
    	CustomData data;
    	data.init();
    	std::cout << "start" << std::endl;
    	data.play("https://gstreamer.freedesktop.org/data/media/sintel_trailer-480p.webm");
    	std::cout << "exit" << std::endl;
    	//data.stop;
  	return 0;  	
  	
}
