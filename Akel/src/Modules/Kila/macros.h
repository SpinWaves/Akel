// This file is a part of Akel
// Author : @kbz_8
// CREATED : 14/11/2021
// UPDATED : 15/11/2021

#ifndef __AK_KILA_MACROS__
#define __AK_KILA_MACROS__

#include <Akpch.h>

namespace Ak::Kl
{
    enum class entries
    {
        vert,
        frag,
        global
    };
    class Macros
    {
        public:
            explicit Macros() = delete;

            inline static void new_set(const std::string& source, const std::string& dest) { _sets[source] = dest; }
            inline static void remove_set(const std::string& set) { _sets.erase(set); }
            inline static std::unordered_map<std::string, std::string>& get_sets() { return _sets; }

            inline static entries get_current_entry() { return _entry; }
            inline static void set_entry(entries entry) { _entry = entry; }

            inline static std::vector<std::string>& get_onces() { return _onces; }
            static bool have_once(const std::string& name);
            inline static void add_once(const std::string& name) { _onces.push_back(name); }

            ~Macros() = delete;

        private:
            inline static std::unordered_map<std::string, std::string> _sets;
            inline static entries _entry;
            inline static std::vector<std::string> _onces;
    };
}

#endif // __AK_KILA_MACROS__
