#include "tsf.h"
#include "tml.h"
#include "midi_file_reader.h"
#include "MidiStream.h"
#include "MidiStreamPlayback.h"
#include "math/math_funcs.h"
#include "print_string.h"


class MidiStream;

MidiStreamPlayback::MidiStreamPlayback()
		: active(false) {
		AudioServer::get_singleton()->lock();
		pcm_buffer = AudioServer::get_singleton()->audio_data_alloc(PCM_BUFFER_SIZE*sizeof(float)*2);
		zeromem(pcm_buffer, PCM_BUFFER_SIZE);
		AudioServer::get_singleton()->unlock();
	}

MidiStreamPlayback::~MidiStreamPlayback() {
	if (pcm_buffer) {
		AudioServer::get_singleton()->audio_data_free(pcm_buffer);
		pcm_buffer = NULL;
	}
}

void MidiStreamPlayback::stop() {
	active = false;
	base->reset();
}

void MidiStreamPlayback::start(float p_from_pos) {
	seek(p_from_pos);
	active = true;
}

void MidiStreamPlayback::seek(float p_time) {
	float max = get_length();
	if (p_time < 0) {
		p_time = 0;
	}
	base->set_position(uint64_t(p_time * base->sample_rate) << MIX_FRAC_BITS);
}

void MidiStreamPlayback::mix(AudioFrame *p_buffer, float p_rate, int p_frames) {
	ERR_FAIL_COND(!active);
	if (!active) {
		return;
	}
	float *buf = (float *)pcm_buffer;
	// this checks if a .midi file is loaded and calls the midi file playback function if it is
	if (base->midi_pointer != NULL) {
		base->midi_file_playback((uint8_t*)buf, MAX(PCM_BUFFER_SIZE, p_frames) * 2);
	}
	// call on the render function to 
	base->render_buffer(buf, MIN(PCM_BUFFER_SIZE, p_frames));
	
	for (int i = 0; i < p_frames; i++) {
		float l = *buf++;
		float r = *buf++;
		p_buffer[i] = AudioFrame(l, r);
	}
}

int MidiStreamPlayback::get_loop_count() const {
	return 0;
}

float MidiStreamPlayback::get_playback_position() const {
	return 0.0;
}

float MidiStreamPlayback::get_length() const {
	return 0.0;
}

bool MidiStreamPlayback::is_playing() const {
	return active;
}


