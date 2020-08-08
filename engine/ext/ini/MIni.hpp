#ifndef MINI_HPP
#define MINI_HPP

#include <unordered_map>
#include <string>
#include <fstream>

using MIniValueNodesMap = std::unordered_map<std::string, std::string>;
using MIniParentNodesMap = std::unordered_map<std::string, MIniValueNodesMap>;

struct MIniRoot {
	const char* filename;
	MIniParentNodesMap* values;
};

enum class MIniTokens {
	ParentBracketOpen = '[',
	ParentBracketClose = ']',
	ValueSeparator = '=',
	ValueEnd = '\n'
};

class MIniCommon {
protected:
	MIniRoot m_root;
	std::fstream m_stream;

	MIniCommon(const char* path, int mode) noexcept;
public:
	virtual ~MIniCommon() noexcept;

	MIniValueNodesMap getValueNodesMap(const char* name) noexcept {
		return (*(this->m_root.values))[name];
	}

	int asInt(MIniValueNodesMap& values, const char* name) const noexcept;

	double asDouble(MIniValueNodesMap& values, const char* name) const noexcept;

	bool asBool(MIniValueNodesMap& values, const char* name) const noexcept;

	std::string asString(MIniValueNodesMap& values, const char* name) const noexcept;
};

class MIniReader : public MIniCommon {
public:
	MIniReader(const char* path) noexcept;

	virtual ~MIniReader() noexcept = default;

	void update() noexcept;
};

class MIniWriter : public MIniCommon {
public:
	MIniWriter(const char* path, bool isAppend) noexcept;

	virtual ~MIniWriter() noexcept = default;

	void assign(MIniParentNodesMap map) noexcept;

	void merge(MIniParentNodesMap map) noexcept;

	void push() noexcept;
};

#endif //!MINI_HPP