// This file is a part of Akel
// Authors : @kbz_8
// Created : 11/11/2021
// Updated : 15/05/2022

#ifndef __AK_KILA_FILE__
#define __AK_KILA_FILE__

namespace Ak::Kl
{
    class File
    {
        public:
            File(const char* path);
            File(const File&) = delete;

            void operator=(const File&) = delete;
            inline int operator()() const { return fgetc(_fp); }
            inline bool is_eof() const { return feof(_fp); }
            inline std::string& get_path() { return _path; }
            
            ~File();

        private:
            std::string _path;
            FILE* _fp = nullptr;
    };
}

#endif // __AK_KILA_FILE__
