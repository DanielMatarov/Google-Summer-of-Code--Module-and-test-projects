#include "tsf.h"
#include "tml.h"
#include "midi_file_reader.h"
#include "sfont_loader.h"
#include "io/resource_saver.h"
#include "os/file_access.h"
#include "scene/resources/texture.h"

String ResourceImporterSfont::get_importer_name() const {
	return "sound_font";
}

String ResourceImporterSfont::get_visible_name() const {
	return "SoundFont";
}

void ResourceImporterSfont::get_recognized_extensions(List<String> *p_extensions) const {
	p_extensions->push_back("sf2");
}

String ResourceImporterSfont::get_save_extension() const {
	return "sf2str";
}

String ResourceImporterSfont::get_resource_type() const {
	return "MidiStream";
}

bool ResourceImporterSfont::get_option_visibility(const String &p_option, const Map<StringName, Variant> &p_options) const {
	return true;
}

int ResourceImporterSfont::get_preset_count() const {
	return 0;
}

String  ResourceImporterSfont::get_preset_name(int p_idx) const {
	printf("get preset name");
	return String();
}

void ResourceImporterSfont::get_import_options(List<ImportOption> *r_options, int p_preset) const {
	printf("import options");
	
}

Error ResourceImporterSfont::import(const String &p_source_file, const String &p_save_path, const Map<StringName, Variant> &p_options, List<String> *r_platform_variants, List<String> *r_gen_files){
	//writes .sf2 file data to memory and calls on set data function in MidiStream 
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
	
	Ref<MidiStream> midi_stream;
	midi_stream.instance();

	printf("%s %d\n", __FUNCTION__, __LINE__);
	midi_stream->set_data(data);
	ERR_FAIL_COND_V(!midi_stream->get_data().size(), ERR_FILE_CORRUPT);

	return ResourceSaver::save(p_save_path + ".sf2str", midi_stream);
	
}

ResourceImporterSfont::ResourceImporterSfont() {
}
