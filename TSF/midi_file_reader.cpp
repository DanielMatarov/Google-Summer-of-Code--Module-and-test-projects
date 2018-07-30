#include "tsf.h"
#include "tml.h"
#include "midi_file_reader.h"
#include "servers/audio/audio_stream.h"


MidiFileReader::MidiFileReader() {
	pointer = NULL;
	
	data = NULL;
	data_len = 0;
}

void MidiFileReader::clear_data() {
	if (data) {
		AudioServer::get_singleton()->audio_data_free(data);
		data = NULL;
		data_len = 0;

	}
}

void MidiFileReader::set_data(const PoolVector<uint8_t> &p_data) {
	//set the midi pointer by loading from memory
	printf("data getting set");
	clear_data();

	data_len = p_data.size();
	data = AudioServer::get_singleton()->audio_data_alloc(data_len, p_data.read().ptr());

	pointer = tml_load_memory(data, data_len);
	
}

PoolVector<uint8_t> MidiFileReader::get_data() const {

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


void MidiFileReader::_bind_methods() {
	ClassDB::bind_method(D_METHOD("_set_data", "data"), &MidiFileReader::set_data);
	ClassDB::bind_method(D_METHOD("_get_data"), &MidiFileReader::get_data);

	ADD_PROPERTY(PropertyInfo(Variant::POOL_BYTE_ARRAY, "data", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_NOEDITOR | PROPERTY_USAGE_INTERNAL), "_set_data", "_get_data");
}

