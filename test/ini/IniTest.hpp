#ifndef INITEST_HPP
#define INITEST_HPP

#define _CRT_SECURE_NO_WARNINGS

#include <engine/ext/ini/MIni.hpp>
#include <iostream>

MIniValueNodesMap read_test() {
	MIniReader reader("files/read_test.ini");

	auto map = reader.getValueNodesMap("ParamA");
	int i = reader.asInt(map, "IProp");
	double d = reader.asDouble(map, "DProp");
	bool b = reader.asBool(map, "BProp");
	std::string s = reader.asString(map, "SProp");

	std::cout <<
		"ParamA:\n\t-IProp = " << i <<
		"\n\t-DProp = " << d <<
		"\n\t-BProp = " << b <<
		"\n\t-SProp = " << s << "\n";

	return map;
}

void write_test(MIniValueNodesMap map) {
	MIniWriter writer("files/write_test.ini", false);
	writer.assign({ 
		{ "ParamA", map },
		{ "ParamB", { { "Prop1", "Val1" } } }
	});

	writer.push();
}

void test() {
	auto map = read_test();
	write_test(map);
}

#endif //!INITEST_HPP