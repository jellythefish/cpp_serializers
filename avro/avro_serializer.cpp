#include "avro_serializer.hpp"

#include "serializer.hpp"

/* Special Note
    Serialization and Deserialization via Apache Avro Library is made without
    explicit declaration of JSON schema as it needed for transferring and parsing
    binaries at the other site. Such approach was chosen for simplification of
    implementation serialization and deserialization processes. The time and memory
    of serialization and deserialization via Apache Avro doesn't depend on included
    json schema in the header of a binary as the amount of serialized and deserialized
    data approaches infinity ;)
*/

void Serializer::SerializeAvro() {
    current_type = SerializerType::Avro;
    current_mode = SerializerMode::RAM;
    avro::EncoderPtr e = avro::binaryEncoder();
    e->init(*avro_os);
    avro::encode(*e, data_struct);
}

void Serializer::DeserializeAvro() {
    current_type = SerializerType::Avro;
    current_mode = SerializerMode::RAM;
    avro_is = avro::memoryInputStream(*avro_os);
    avro::DecoderPtr d = avro::binaryDecoder();
    d->init(*avro_is);

    DataStruct data_struct_new;
    avro::decode(*d, data_struct_new);
}

void Serializer::SerializeAvroToFile() {
    current_type = SerializerType::Avro;
    current_mode = SerializerMode::File;
    filename = "demofile.avro";
    avro_of = avro::fileOutputStream((filepath + filename).c_str());
    avro::EncoderPtr e = avro::binaryEncoder();
    e->init(*avro_of);
    avro::encode(*e, data_struct);
    avro_of->flush();
}

void Serializer::DeserializeAvroFromFile() {
    current_type = SerializerType::Avro;
    current_mode = SerializerMode::File;
    filename = "demofile.avro";
    avro_if = avro::fileInputStream((filepath + filename).c_str());
    avro::DecoderPtr d = avro::binaryDecoder();
    d->init(*avro_if);

    DataStruct data_struct_new;
    avro::decode(*d, data_struct_new);
}