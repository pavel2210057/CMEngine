#include "MIni.hpp"

MIniCommon::MIniCommon(const char* path, int mode) noexcept :
	m_stream(path, mode | std::ios::binary),
	m_root({ path, nullptr }) {}

MIniCommon::~MIniCommon() noexcept { this->m_stream.close(); }

int MIniCommon::asInt(MIniValueNodesMap& values, const char* name) const noexcept {
	return atoi(values[name].c_str());
}

double MIniCommon::asDouble(MIniValueNodesMap& values, const char* name) const noexcept {
	return atof(values[name].c_str());
}

bool MIniCommon::asBool(MIniValueNodesMap& values, const char* name) const noexcept {
	if (values[name] == "true")
		return true;
	return false;
}

std::string MIniCommon::asString(MIniValueNodesMap& values, const char* name) const noexcept {
	return values[name];
}