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
	GstElement *playbin = nullptr;
  	gboolean playing = FALSE;
  	gboolean terminate = FALSE;
  	gboolean seek_enabled = FALSE;
  	gboolean seek_done = FALSE;
  	
  	gint64 duration = GST_CLOCK_TIME_NONE;
  	
  	GstBus *bus = nullptr;
  	GstMessage *msg = nullptr;
  	GstStateChangeReturn ret;
 
private:
	void handle_message(GstMessage *msg); 
};


void CustomData::init(){
	gst_init (nullptr, nullptr);
	playbin = gst_element_factory_make ("playbin", "playbin");
  	
  	if (!playbin) {
    		std::cout << "Not all elements could be created." << std::endl;
    		return;
 	}
	
}
void CustomData::play(const std::string & _uri){
	 terminate = FALSE;
	 seek_done = FALSE;
	 duration = GST_CLOCK_TIME_NONE;
	 g_object_set (playbin, "uri", _uri.c_str(), NULL);
	 ret = gst_element_set_state (playbin, GST_STATE_PLAYING);
	 if (ret==GST_STATE_CHANGE_FAILURE){
	 	std::cout << "Playing error" << std::endl;
	 	return;
	 }
	 bus = gst_element_get_bus(playbin);
	 do {
	 	msg = gst_bus_timed_pop_filtered (bus, 100 * GST_MSECOND, static_cast<GstMessageType>(GST_MESSAGE_STATE_CHANGED | GST_MESSAGE_ERROR | GST_MESSAGE_EOS | GST_MESSAGE_DURATION_CHANGED));
	 	if (msg!= NULL) handle_message(msg);
	 	else {
	 		if (playing == TRUE){
		 		gint64 current = -1;
		 		if (!gst_element_query_position(playbin, GST_FORMAT_TIME, &current)){
		 			std::cout << "Could not query current position" << std::endl;
		 		}
		 		
		 		if(!GST_CLOCK_TIME_IS_VALID(duration)){
		 			if(!gst_element_query_duration(playbin, GST_FORMAT_TIME, &duration)){
		 			std::cout << "Could not query current duration" << std::endl;
		 			}
		 		}
		 		g_print ("Position %" GST_TIME_FORMAT " / %" GST_TIME_FORMAT "\r", GST_TIME_ARGS (current), GST_TIME_ARGS (duration));
		 		if (seek_enabled && !seek_done && current > 5*GST_SECOND){
		 			std::cout << "Reached 15s, performing seek..." << std::endl;
		 			gst_element_seek_simple (playbin, GST_FORMAT_TIME, static_cast<GstSeekFlags>(GST_SEEK_FLAG_FLUSH | GST_SEEK_FLAG_KEY_UNIT), 1 * GST_SECOND);
		 			seek_done = TRUE;
		 		}	
		 	}
	 		
	 	} 
	 }while (!terminate);
	 
}
void CustomData::stop(){
	 
         if (playbin)
	 {
	 	if (bus) gst_object_unref (bus);
		gst_element_set_state(playbin, GST_STATE_NULL);
		gst_object_unref(playbin);
		bus = nullptr;
		playbin = nullptr;
	 }
}
void CustomData::handle_message(GstMessage *msg){
	GError *err;
	gchar *debug_info;
	switch (GST_MESSAGE_TYPE(msg)){
		case GST_MESSAGE_ERROR:
			gst_message_parse_error (msg, &err, &debug_info);
			g_printerr ("Error received from element %s: %s\n", GST_OBJECT_NAME (msg->src), err->message);
      			g_printerr ("Debugging information: %s\n", debug_info ? debug_info : "none");
      			g_clear_error (&err);
      			g_free (debug_info);
      			terminate = TRUE;
      			break;
      		case GST_MESSAGE_EOS:
      			std::cout << "End of stream reached" << std::endl;
      			terminate = TRUE;
      			break;
		case GST_MESSAGE_DURATION_CHANGED:
      			duration = GST_CLOCK_TIME_NONE;
      			break;
      		case GST_MESSAGE_STATE_CHANGED:
	      		{
	      			GstState old_state, new_state, pending_state;
	      			gst_message_parse_state_changed (msg, &old_state, &new_state, &pending_state);
	      			if (GST_MESSAGE_SRC(msg) == GST_OBJECT (playbin)){
	      				std::cout << gst_element_state_get_name(old_state) << " -> " << gst_element_state_get_name(new_state) << std::endl;
	      				playing = (new_state == GST_STATE_PLAYING);
	      				if (playing){
	      					GstQuery *query;
	      					gint64 start, end;
	      					query = gst_query_new_seeking (GST_FORMAT_TIME);
	      					if (gst_element_query(playbin, query)){
	      						gst_query_parse_seeking (query, nullptr, &seek_enabled, &start, &end);
	      						if (seek_enabled) {
		      						g_print ("Seeking is ENABLED from %" GST_TIME_FORMAT " to %" GST_TIME_FORMAT "\n", GST_TIME_ARGS (start), GST_TIME_ARGS (end));
		      					}
		      					else { 
		      						std::cout << "Seeking is DISABLED for this stream" << std::endl;
		      					}
	      					}
	      					else {
	      						std::cout << "Seeking query failed" << std::endl;
	      					}
	      					gst_query_unref(query);
	      				}
	      			}
	      		}
	      		break;
	      	default:
	      		std::cout << "Unexpected message received" << std::endl;
	      		break;
	      			
	}
	gst_message_unref(msg);

	
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
