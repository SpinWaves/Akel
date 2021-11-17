// This file is a part of Akel
// CREATED : 11/11/2021
// UPDATED : 15/11/2021

#ifndef __AK_KILA_FILE__
#define __AK_KILA_FILE__

namespace Ak::Kl
{
    class File
    {
        public:
            explicit File(const char* path);
            File(const File&) = delete;

            void operator=(const File&) = delete;
            inline int operator()() const { return fgetc(_fp); }
            inline bool is_eof() const { return feof(_fp); }
            inline std::string& get_path() { return _path; }
            
            ~File();

        private:
            FILE* _fp;
            std::string _path;
    };
}

#endif // __AK_KILA_FILE__
