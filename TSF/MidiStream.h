#ifndef MIDISTREAM_H
#define MIDISTREAM_H

#include "reference.h"
#include "resource.h"
#include "servers/audio/audio_stream.h"
#include <stdio.h>



class MidiStream : public AudioStream {
	GDCLASS(MidiStream, AudioStream)
	OBJ_SAVE_TYPE(AudioStream)
	RES_BASE_EXTENSION("sf2str")

	friend class MidiStreamPlayback;

	uint64_t pos;

	int sample_rate;
	float gain;
	int preset;

	char* sf_filename;
	tsf* tsf_pointer;
	
	void *data;
	uint32_t data_len;
	
	Ref<MidiFileReader> mfile;
public:
	MidiStream();

	void reset();
	void set_position(uint64_t pos);

	void set_preset(int pr);
	char* get_preset_name(int pr);
	int get_preset_count();

	void set_filename(const String&filename);
	void set_data(const PoolVector<uint8_t> &p_data);
	PoolVector<uint8_t> get_data() const;
	void clear_data();
	

	tml_message * midi_pointer;
	double midi_pb_time;
	void midi_load_filename(const String&filename);
	void set_midi_file(Ref<MidiFileReader> midi_file);
	virtual Ref<MidiFileReader> get_midi_file();
	void midi_file_playback(uint8_t *b, int s);
	
	void note_on(int n,float v);
	void note_off(int n);
	void set_channel_pan(int chn, float pan);
	void set_channel_tuning(int chn, float tun);
	void set_channel_volume(int chn, float vol);
	void set_channel_pitchwheel(int chn, float pw);
	void set_channel_pitchrange(int chn, float pr);

	void render_buffer(float* b, int s);

	virtual Ref<AudioStreamPlayback> instance_playback();
    
	virtual String get_stream_name() const;
	virtual float get_length() const { return 0; }
	

	
protected:
	static void _bind_methods();
};

#endif 
