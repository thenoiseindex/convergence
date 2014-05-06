/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#ifndef BINARYDATA_H_90236299_INCLUDED
#define BINARYDATA_H_90236299_INCLUDED

namespace BinaryData
{
    extern const char*   CMakeLists_txt;
    const int            CMakeLists_txtSize = 197;

    extern const char*   COPYING;
    const int            COPYINGSize = 1087;

    extern const char*   libcurl_lib;
    const int            libcurl_libSize = 2630234;

    extern const char*   Makefile;
    const int            MakefileSize = 1798;

    extern const char*   twitcurl_dsp;
    const int            twitcurl_dspSize = 3571;

    extern const char*   twitcurl_dsw;
    const int            twitcurl_dswSize = 539;

    extern const char*   twitcurl_sln;
    const int            twitcurl_slnSize = 890;

    extern const char*   twitcurl_vcproj;
    const int            twitcurl_vcprojSize = 7480;

    extern const char*   us_pos_tree;
    const int            us_pos_treeSize = 21766;

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Number of elements in the namedResourceList array.
    const int namedResourceListSize = 9;

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes) throw();
}

#endif
