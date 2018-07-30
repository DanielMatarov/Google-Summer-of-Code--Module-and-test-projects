#include "tsf.h"
#include "tml.h"
#include "midi_loader.h"
#include "io/resource_saver.h"
#include "os/file_access.h"
#include "scene/resources/texture.h"

String ResourceImporterMidi::get_importer_name() const {
	return "midi";
}

String ResourceImporterMidi::get_visible_name() const {
	return "MIDI";
}

void ResourceImporterMidi::get_recognized_extensions(List<String> *p_extensions) const {
	p_extensions->push_back("mid");
}

String ResourceImporterMidi::get_save_extension() const {
	return "midstr";
}

String ResourceImporterMidi::get_resource_type() const {
	return "MidiFileReader";
}

bool ResourceImporterMidi::get_option_visibility(const String &p_option, const Map<StringName, Variant> &p_options) const {
	return true;
}

int ResourceImporterMidi::get_preset_count() const {
	return 0;
}

String ResourceImporterMidi::get_preset_name(int p_idx) const {
	return String();
}

void ResourceImporterMidi::get_import_options(List<ImportOption> *r_options, int p_preset) const {

}

Error ResourceImporterMidi::import(const String &p_source_file, const String &p_save_path, const Map<StringName, Variant> &p_options, List<String> *r_platform_variants, List<String> *r_gen_files) {
	//writes .midi file data to memory and calls on set data function in MidiFileReader
	FileAccess *f = FileAccess::open(p_source_file, FileAccess::READ);
	if (!f) {
		ERR_FAIL_COND_V(!f, ERR_CANT_OPEN);
	}

	size_t len = f->get_len();

	PoolVector<uint8_t> data;

	data.resize(len);
	PoolVector<uint8_t>::Write w = data.write();

	f->get_buffer(w.ptr(), len);

	memdelete(f);

	Ref<MidiFileReader> midi_file;
	midi_file.instance();

	printf("%s %d\n", __FUNCTION__, __LINE__);
	midi_file->set_data(data);
	ERR_FAIL_COND_V(!midi_file->get_data().size(), ERR_FILE_CORRUPT);

	return ResourceSaver::save(p_save_path + ".midstr", midi_file);

}


ResourceImporterMidi::ResourceImporterMidi() {

}
