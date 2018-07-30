#include "tsf.h"
#include "tml.h"
#include "midi_file_reader.h"
#include "register_types.h"
#include "class_db.h"
#include "MidiStream.h"
#include "MidiStreamPlayback.h"
#include "sfont_loader.h"

#include "midi_loader.h"



void register_TSF_types() {

#ifdef TOOLS_ENABLED
	Ref<ResourceImporterSfont> sfont_import;
	Ref<ResourceImporterMidi> midi_import;
	midi_import.instance();
	sfont_import.instance();
		ResourceFormatImporter::get_singleton()->add_importer(sfont_import);
		ResourceFormatImporter::get_singleton()->add_importer(midi_import);
#endif     
		ClassDB::register_class<MidiStream>();
        ClassDB::register_class<MidiStreamPlayback>();
		ClassDB::register_class<MidiFileReader>();
}

void unregister_TSF_types() {
	
}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        
