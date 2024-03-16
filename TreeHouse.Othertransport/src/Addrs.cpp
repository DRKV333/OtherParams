#include "Addrs.h"

#include <algorithm>

#define DEFTABLE(TYPE, NAME, INITER)                                \
static constexpr TYPE NAME = []()                                   \
{                                                                   \
	auto $ = TYPE();                                                \
	INITER                                                          \
	return $;                                                       \
}();                                                                \
static_assert(std::ranges::find(NAME, 0) == std::ranges::end(NAME), \
	"Every address must be specified.");                            \

DEFTABLE(Addrs::table_t, test32,
{
	$[Addrs::base]                      = 0x00400000;
	$[Addrs::unrealMain]                = 0x01137840;
	$[Addrs::getRakPeerInterface]       = 0x01747550;
	$[Addrs::destroyRakPeerInterface]   = 0x01747560;
	$[Addrs::parseIpV4]                 = 0x01b5ec20;
	$[Addrs::wstring_cstr_ptr]          = 0x01e513a8;
	$[Addrs::atlasUELogAppender_append] = 0x01076130;
})

void Addrs::initialize()
{
	current = test32;

	HMODULE mainModule = GetModuleHandleA("Otherland-Test.exe");
	intptr_t baseOffset = reinterpret_cast<uintptr_t>(mainModule) - current[Addrs::base];

	for (uintptr_t& ptr : current)
	{
		ptr += baseOffset;
	}
}