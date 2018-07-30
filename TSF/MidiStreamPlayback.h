#ifndef __MIDI_STREAM_PLAYBACK_H__
#define __MIDI_STREAM_PLAYBACK_H__

#include "reference.h"
#include "resource.h"
#include "servers/audio/audio_stream.h"
#include "os/file_access.h"


class MidiStreamPlayback : public AudioStreamPlayback {
	GDCLASS(MidiStreamPlayback, AudioStreamPlayback);
	friend class MidiStream;
	FileAccess *f;
	String file;
private :

	enum {
		PCM_BUFFER_SIZE = 4096
	};
	enum {
		MIX_FRAC_BITS = 13,
		MIX_FRAC_LEN = (1 << MIX_FRAC_BITS),
		MIX_FRAC_MASK = MIX_FRAC_LEN - 1,
	};
	void* pcm_buffer;
	Ref<MidiStream> base;
	bool active;

public:
	virtual void start(float p_from_pos = 0.0);
	virtual void stop();
	virtual bool is_playing() const;
	virtual int get_loop_count() const; //times it looped
	virtual float get_playback_position() const;
	virtual void seek(float p_time);
	virtual void mix(AudioFrame *p_buffer, float p_rate_scale, int p_frames);
	virtual float get_length() const; //if supported, otherwise return 0
	MidiStreamPlayback();
	~MidiStreamPlayback();
	
};
#endif 
