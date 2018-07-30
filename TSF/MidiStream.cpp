#define TSF_IMPLEMENTATION
#define TML_IMPLEMENTATION
#include "tsf.h"
#include "tml.h"
#include "midi_file_reader.h"
#include "servers/audio/audio_stream.h"
#include "MidiStream.h"
#include "MidiStreamPlayback.h"


MidiStream::MidiStream(){
	sample_rate=44100;
	gain = 0;

	// these pointers store audio and midi data and are used by every TSF function 
	tsf_pointer = NULL;
	midi_pointer = NULL;

	midi_pb_time = 0;

	data = NULL;
	data_len = 0;

	preset = 0;
}


Ref<AudioStreamPlayback> MidiStream::instance_playback() {
	Ref<MidiStreamPlayback> talking_tree;
	talking_tree.instance();
	talking_tree->base = Ref<MidiStream>(this);
	return talking_tree;
}

void MidiStream::set_position(uint64_t p) {
	pos = p;
}

void MidiStream::set_filename(const String&filename) {
	// this function can be used with GDscript to load a file 
	tsf_pointer = tsf_load_filename(filename.utf8().get_data());
	if (tsf_pointer){
		//if the file is successfully loaded the output is set
		tsf_set_output(tsf_pointer, TSF_STEREO_INTERLEAVED, sample_rate, gain);
	}
	else{
		printf("error loading file");
	}
	
}

void MidiStream::clear_data() {
	if (data) {
		AudioServer::get_singleton()->audio_data_free(data);
		data = NULL;
		data_len = 0;
		
	}
}

void MidiStream::set_data(const PoolVector<uint8_t> &p_data) {
	//loads sound font data from memory and sets output 
	clear_data();
	
	data_len = p_data.size();
	data = AudioServer::get_singleton()->audio_data_alloc(data_len, p_data.read().ptr());
	
		tsf_pointer = tsf_load_memory(data, data_len);
	if (tsf_pointer) {
		tsf_set_output(tsf_pointer, TSF_STEREO_INTERLEAVED, sample_rate, gain);
		
	}
	
}


void MidiStream::render_buffer(float* b, int s){
	//render samples to a buffer, which is then used in the mix function of MidiStreamPlayback
	if (tsf_pointer == NULL) {
		return;
	}
		tsf_render_float(tsf_pointer, b, s, 0);
}

PoolVector<uint8_t> MidiStream::get_data() const {
	
		PoolVector<uint8_t> vdata;
	
		if (data_len && data) {
		vdata.resize(data_len);
		{
			PoolVector<uint8_t>::Write w = vdata.write();
			copymem(w.ptr(), data, data_len);
			}
		
	}
	
		return vdata;
}

void MidiStream::note_on(int n, float v)
{
	//plays a note
	if (tsf_pointer == NULL) {
		return;
	}
	tsf_note_on(tsf_pointer, preset, n, v);
}

void MidiStream::note_off(int n)
{
	// ends a note
	ERR_FAIL_NULL(tsf_pointer)
	tsf_note_off(tsf_pointer, preset, n);
}

void MidiStream::reset() {
	set_position(0);
}

void MidiStream::set_preset(int pr)
{
	// select your soundfont preset. each sound font file can have up to 16 presets
	preset = pr;
}

char* MidiStream::get_preset_name(int pr)
{
	//get the name of the preset you are currently using
	 ERR_FAIL_NULL_V(tsf_pointer, 0)
 	 return (char*)tsf_get_presetname(tsf_pointer, pr);
}

int MidiStream::get_preset_count()
{
	ERR_FAIL_NULL_V(tsf_pointer, 0)
	return tsf_get_presetcount(tsf_pointer);
}

void MidiStream::set_channel_pan(int chn, float pan)
{

	ERR_FAIL_NULL(tsf_pointer)
	tsf_channel_set_pan(tsf_pointer, chn, pan);
}

void MidiStream::set_channel_volume(int chn, float vol)
{
	ERR_FAIL_NULL(tsf_pointer)
	tsf_channel_set_volume(tsf_pointer, chn, vol);
}

void MidiStream::set_channel_tuning(int chn, float tun)
{
	// set the HZ tuning, however it works with floats from 0 to 10 and not actual HZ values
	ERR_FAIL_NULL(tsf_pointer)
	tsf_channel_set_tuning(tsf_pointer, chn, tun);
}

void MidiStream::set_channel_pitchwheel(int chn, float pw)
{
	// pitch wheel function
	ERR_FAIL_NULL(tsf_pointer)
	tsf_channel_set_pitchwheel(tsf_pointer, chn, pw);
}

void MidiStream::set_channel_pitchrange(int chn, float pr)
{
	ERR_FAIL_NULL(tsf_pointer)
	tsf_channel_set_pitchrange(tsf_pointer, chn, pr);
}

void MidiStream::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_filename", "filename"), &MidiStream::set_filename);
	ClassDB::bind_method(D_METHOD("set_midi_filename", "filename"), &MidiStream::midi_load_filename);
	ClassDB::bind_method(D_METHOD("get_stream_name"), &MidiStream::get_stream_name);
	ClassDB::bind_method(D_METHOD("note_on", "note", "velocity"), &MidiStream::note_on);
	ClassDB::bind_method(D_METHOD("note_off", "note"), &MidiStream::note_off);
	ClassDB::bind_method(D_METHOD("set_preset","preset"), &MidiStream::set_preset);
	ClassDB::bind_method(D_METHOD("get_preset_name", "preset"), &MidiStream::get_preset_name);
	ClassDB::bind_method(D_METHOD("get_preset_count"), &MidiStream::get_preset_count);
	ClassDB::bind_method(D_METHOD("set_channel_pan", "channel", "pan"), &MidiStream::set_channel_pan);
	ClassDB::bind_method(D_METHOD("set_channel_tuning", "channel", "tuning"), &MidiStream::set_channel_tuning);
	ClassDB::bind_method(D_METHOD("set_channel_volume", "channel", "volume"), &MidiStream::set_channel_volume);
	ClassDB::bind_method(D_METHOD("set_channel_pitchwheel", "channel", "pitch_wheel"), &MidiStream::set_channel_pitchwheel);
	ClassDB::bind_method(D_METHOD("set_channel_pitchrange", "channel", "pitch_range"), &MidiStream::set_channel_pitchrange);
	ClassDB::bind_method(D_METHOD("_set_data", "data"), &MidiStream::set_data);
	ClassDB::bind_method(D_METHOD("_get_data"), &MidiStream::get_data);
	ClassDB::bind_method(D_METHOD("set_midi_file", "midi_file"), &MidiStream::set_midi_file);
	ClassDB::bind_method(D_METHOD("get_midi_file"), &MidiStream::get_midi_file);

	ADD_PROPERTY(PropertyInfo(Variant::POOL_BYTE_ARRAY, "data", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_NOEDITOR | PROPERTY_USAGE_INTERNAL), "_set_data", "_get_data");
	//adding the midi file loading as a property
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "midi_file", PROPERTY_HINT_RESOURCE_TYPE, "MidiFileReader"), "set_midi_file", "get_midi_file");

	
}


String MidiStream::get_stream_name() const {
	return "MidiStream";
}


void MidiStream::midi_load_filename(const String&filename)
{
	// use with GDscript to load a midi file, sets playback time to 0 when a file is loaded
	midi_pb_time = 0;
	midi_pointer = tml_load_filename(filename.utf8().get_data());
}

void MidiStream::set_midi_file(Ref<MidiFileReader> midi_file) {
	//calling the MidiFileReader pointer and assign it to midi_pointer used for the playback function
	if (midi_file.is_valid()) {
		mfile = midi_file;
		midi_pointer = midi_file->pointer;
	}
}

Ref<MidiFileReader> MidiStream::get_midi_file() {
	return mfile ;
}

void MidiStream::midi_file_playback(uint8_t *b, int s) {

	
	// Number of samples to process
	int sampleBlock, sampleCount = (s / (2 * sizeof(float)));
	for (sampleBlock = TSF_RENDER_EFFECTSAMPLEBLOCK; sampleCount; sampleCount -= sampleBlock, b += (sampleBlock * (2 * sizeof(float)))) {

		//Progressing through the MIDI playback and then processing TSF_RENDER_EFFECTSAMPLEBLOCK samples 
		if (sampleBlock > sampleCount) sampleBlock = sampleCount;

		//Loop through MIDI messages up until the current playback time 
		for (midi_pb_time += sampleBlock * (1000.0 / 44100.0); midi_pointer && midi_pb_time >= midi_pointer->time; midi_pointer = midi_pointer->next)
		{
			switch (midi_pointer->type)
			{
				case TML_PROGRAM_CHANGE:
					tsf_channel_set_presetnumber(tsf_pointer, midi_pointer->channel, midi_pointer->program, (midi_pointer->channel == 9));
				case TML_NOTE_ON:
					tsf_channel_note_on(tsf_pointer, midi_pointer->channel, midi_pointer->key, midi_pointer->velocity / 127.0f);
					break;
				case TML_NOTE_OFF:
					tsf_channel_note_off(tsf_pointer, midi_pointer->channel, midi_pointer->key);
					break;
				case TML_PITCH_BEND:
					tsf_channel_set_pitchwheel(tsf_pointer, midi_pointer->channel, midi_pointer->pitch_bend);
					break;
				case TML_CONTROL_CHANGE:
					tsf_channel_midi_control(tsf_pointer, midi_pointer->channel, midi_pointer->control, midi_pointer->control_value);
					break;
			}
		}
		
		
	}

}

