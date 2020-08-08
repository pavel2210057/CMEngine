#include "MIni.hpp"

MIniWriter::MIniWriter(const char* path, bool isAppend) noexcept :
	MIniCommon(path, std::ios::out | std::ios::app & isAppend) {}

void MIniWriter::assign(MIniParentNodesMap map) noexcept {
	if (this->m_root.values)
		delete this->m_root.values;
	this->m_root.values = new MIniParentNodesMap(map);
}

void MIniWriter::merge(MIniParentNodesMap map) noexcept {
	this->m_root.values->insert(map.begin(), map.end());
}

void MIniWriter::push() noexcept {
	for (auto pvalue : *this->m_root.values) {
		this->m_stream <<
			static_cast<const char>(MIniTokens::ParentBracketOpen) <<
			pvalue.first <<
			static_cast<const char>(MIniTokens::ParentBracketClose) <<
			static_cast<const char>(MIniTokens::ValueEnd);
		
		for (auto vvalue : pvalue.second) {
			this->m_stream <<
				vvalue.first <<
				static_cast<const char>(MIniTokens::ValueSeparator) <<
				vvalue.second <<
				static_cast<const char>(MIniTokens::ValueEnd);
		}
	}
}