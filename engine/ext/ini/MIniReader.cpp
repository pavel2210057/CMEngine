#include "MIni.hpp"
#include <string>

class MIniParser {
	std::string m_raw;
	size_t m_cur;

	MIniParser(std::string raw) noexcept :
		m_raw(raw),
		m_cur(0) { }

	~MIniParser() noexcept = default;

	void buildNextNode(MIniParentNodesMap& parents) noexcept {
		int last_cur = this->m_cur;

		std::string pname = this->m_raw.substr(
			(last_cur = this->m_raw.find(
				static_cast<const char>(MIniTokens::ParentBracketOpen),
				last_cur
			)) + 1,
			(this->m_cur = this->m_raw.find(
				static_cast<const char>(MIniTokens::ParentBracketClose),
				this->m_cur
			)) - last_cur - 1
		);
		++this->m_cur; //pass '\n'

		MIniValueNodesMap values;
		do {
			last_cur = this->m_cur;
			std::string vname = this->m_raw.substr(
				last_cur + 1,
				(this->m_cur = this->m_raw.find(
					static_cast<const char>(MIniTokens::ValueSeparator),
					this->m_cur
				)) - last_cur - 1
			);

			last_cur = this->m_cur;
			std::string vval = this->m_raw.substr(
				last_cur + 1,
				(this->m_cur = this->m_raw.find(
					static_cast<const char>(MIniTokens::ValueEnd),
					this->m_cur
				)) - last_cur - 1
			);

			values[vname] = vval;
		} while (this->m_raw[this->m_cur + 1] !=
			static_cast<const char>(MIniTokens::ParentBracketOpen) &&
			this->m_cur < this->m_raw.size() - 1);

		parents[pname] = values;
	}

	size_t getCursor() const { return this->m_cur; }
public:
	static void parse(std::fstream& stream, MIniRoot* root) noexcept {
		std::string raw, line;
		while (stream >> line) raw += line + '\n';

		MIniParser parser = { raw };

		if (root->values)
			delete root->values;
		root->values = new MIniParentNodesMap;

		do
			parser.buildNextNode(*root->values);
		while (parser.getCursor() < raw.size() - 1);
	}
};

MIniReader::MIniReader(const char* path) noexcept :
	MIniCommon(path, std::ios::in) { update(); }

void MIniReader::update() noexcept {
	MIniParser::parse(this->m_stream, &this->m_root);
}