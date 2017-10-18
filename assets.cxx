#include <iostream>
#include <string>
#include <bitset>
#include <stdint.h>
#include <algorithm>
#include <vector>
#include <sstream>
#include <math.h>
#include <climits>
#include <map>
#include <time.h>

// All feature dev : x86_64-redhat-linux arch_32=i686 UTF-8
// as compiled for : C++98 -O3 -Wall (GCC 4.4.7) -fopenmp

// can be fast comp : g++ test.cxx -o main -lrt

//math banking 
namespace mBank 
{
    //R/O MM [START]
    
    /**
     * endianess test value
     */
    static const unsigned int m4_ndian = 2;
    
    /**
     * RFC 3548     The Base16, Base32, and Base64 Data Encodings     July 2003
     * @see RFC 3548 https://tools.ietf.org/html/rfc3548
     */
    static const char ka_b64[64] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'};

    /**
     * @see merge bit const char test-evaluator
     */
    static const char ka_bitmov[4] = {0x08, 0x04, 0x02, 0x01};
    
    /**
     * @see UTF-8 table ASCII 2 HEX expander
     */
    static const char ka_chargov[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
    
    /**
     * @see ASCII and EBCDIC conversion tables @IBM InfoSphere DataStage
     */
    static const char ka_ebcdic[256] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 
                                        0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 
                                        0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 
                                        0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F, 
                                        0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 
                                        0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F, 
                                        0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F, 
                                        0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7A, 0x7B, 0x7C, 0x7D, 0x7E, 0x7F,
                                        
                                        0x00, 0x01, 0x02, 0x03, 0x1A, 0x09, 0x1A, 0x7F, 0x1A, 0x1A, 0x1A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 
                                        0x10, 0x11, 0x12, 0x13, 0x3C, 0x3D, 0x32, 0x26, 0x18, 0x19, 0x3F, 0x27, 0x1C, 0x1D, 0x1E, 0x1F, 
                                        0x40, 0x4F, 0x7F, 0x7B, 0x5B, 0x6C, 0x50, 0x7D, 0x4D, 0x5D, 0x5C, 0x4E, 0x6B, 0x60, 0x4B, 0x61, 
                                        0xF0, 0xF1, 0xF2, 0xF3, 0xF4, 0xF5, 0xF6, 0xF7, 0xF8, 0xF9, 0x7A, 0x5E, 0x4C, 0x7E, 0x6E, 0x6F, 
                                        0x7C, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xD1, 0xD2, 0xD3, 0xD4, 0xD5, 0xD6, 
                                        0xD7, 0xD8, 0xD9, 0xE2, 0xE3, 0xE4, 0xE5, 0xE6, 0xE7, 0xE8, 0xE9, 0x4A, 0xE0, 0x5A, 0x5F, 0x6D, 
                                        0x79, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 
                                        0x97, 0x98, 0x99, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xC0, 0x6A, 0xD0, 0xA1, 0x07};
    
    /**
     * const signed char of fields needed to reach our matchingKey
     */
    static const signed char k1a_fieldLength[]  = {
       8, //  0 : xxxxxxxxxxxxx
       8, //  1 : xxxxxxxxxxxxx
      -1, //  2 : xxxxxxxxxxxxx
       3, //  3 : xxxxxxxxxxxxx
       6, //  4 : xxxxxxxxxxxxx
       6, //  5 : xxxxxxxxxxxxx
       6, //  6 : xxxxxxxxxxxxx
       5, //  7 : xxxxxxxxxxxxx
       4, //  8 : xxxxxxxxxxxxx
       4, //  9 : xxxxxxxxxxxxx
       4, // 10 : xxxxxxxxxxxxx
       3, // 11 : xxxxxxxxxxxxx
    };
    
    /**
     * @see function configuration value for TCP decode function
     */
    static const unsigned int k4_targetField = 11, k4_msgIdLength = 4, k4_headerLength = 40;
    
    //R/O MM [END]
    
    //M/F LISTING :
    /*
        static bool isLitEnd()
        void e_swap(uint16_t & p4r_val)
        bool sml_cut(const std::string & pzr_source, std::vector<int> & pvr_dest)
        bool char_inc(std::string & pzr_source)
        int nb_str(std::string & pzr_source)
        std::vector<bool> bit_bol(const std::string & pzr_source)
        uint8_t bind_(const char & p1r_left, const char & p1r_right)
        uint16_t bind_(const uint8_t & p1r_left, const uint8_t & p1r_right)
        uint32_t bind_(const uint16_t & p1r_left, const uint16_t & p1r_right)
        uint64_t bind_(const uint32_t & p1r_left, const uint32_t & p1r_right)
        std::string & str_unpad(std::string & pzr_source, const char & p1r_unpad, const bool & p1r_dir)
        std::string & str_padchar(std::string & pzr_source, const char & p1r_padchar, const int p4r_length, const bool & p1r_dir)
        std::vector<int> merge_bit(const std::string & pzr_sourceA, const std::string & pzr_sourceB)
        const std::string & subref(const unsigned short & p2r_pos, const unsigned short & p2r_qt, std::string & pzr_s)
        bool sql_spe(const std::string & pzr_tabName, const std::string & pzr_fetch, const std::vector<std::pair<std::string, std::string> > & pvr_colQual, std::map<int, std::string> & pmr_queryText)
        bool is_olc(const std::string & pzr_source, const char & p1r_exp)
        std::map<std::string, std::string> un_tkn(const std::string & pzr_source, const int & p4r_tagSize, const int & p4r_lenSize, const std::map<std::string, int> & pmr_scheme)
        std::string build_56(const std::string & pzr_source)
        const char & showRawByte(const char & p1r_val)
        std::string showBitmapBitStatus(const std::string & pzr_val)
        unsigned int decodeLength(const unsigned int & pb1r_cutPos, const std::string & pzr_netMsg)
        std::string ascii2hexf(const std::string & pzr_source)
        std::string hexf2ascii(const std::string & pzr_source)
        bool decode(const std::string & pzr_mcMsg)
        std::bitset<32> to_b64(const char & p1r_b1 = 0x00, const char & p1r_b2 = 0x00, const char & p1r_b3 = 0x00)
        std::string ex_b64(const std::bitset<32> & pcr_32bits)
        std::string & sd_c3(std::string & pzr_b255)
    */
    
    /**
     * endianess function
     * @return true if little
     */
    static bool isLitEnd() 
    {
        return (bool)((char *)&m4_ndian)[0]; 
    }

    /**
     * method which swap the endianess to little if big for 16bits
     * @param p4r_val uint16_t reference
     * @return void
     */
    void e_swap(uint16_t & p4r_val)
    {
        if(!isLitEnd())
            p4r_val = (p4r_val >> 8) | ((p4r_val & 0xff) << 8);
    }

    /**
     * function sml_cut cutter which extract ID in a string to a vector<int>
     * @see pzr_source must be formatted as follow : 4000,8000,4580 you can use whatever you want as a delimiter char, but keep a constant use of 4 numeric chars followed by a delimiter only if another MTI will be used.
     * @param const string reference pzr_source
     * @param vector<byte4> reference pvr_dest
     * @return bool false if not well formated pzr_source
     */
    bool sml_cut(const std::string & pzr_source, std::vector<int> & pvr_dest)
    {
        pvr_dest.clear();
        
        for(int i = 0, j = 0; i < pzr_source.size() / 4; j += 5, ++i)
        {
            if(pzr_source[j] > 57 || 
               pzr_source[j] < 48 || 
               pzr_source[j+1] > 57 || 
               pzr_source[j+1] < 48 || 
               pzr_source[j+2] > 57 || 
               pzr_source[j+2] < 48 || 
               pzr_source[j+3] > 57 || 
               pzr_source[j+3] < 48)
            {
                pvr_dest.clear();
                return false;
            }
            
            pvr_dest.push_back(((pzr_source[j] - 48) & 0xFF) * 1000 + 
                               ((pzr_source[j+1] - 48) & 0xFF) * 100 + 
                               ((pzr_source[j+2] - 48) & 0xFF) * 10 + 
                               ((pzr_source[j+3] - 48) & 0xFF));
        }
        return true;
    }

    /**
     * function which increment the last char value of a string parameter if and only if numeric
     * @see if your string is something as follow : counter_1 the string returned will be : counter_2 or if : compute99 returned string : compute100
     * @param string reference pzr_source
     * @return bool false if not well computed source string
     */
    bool char_inc(std::string & pzr_source)
    {
        int l4_cdtor = 0, l4_inc = 1;
        
        for(int l4_rs = pzr_source.size()-1; l4_rs && pzr_source[l4_rs] > 47 && pzr_source[l4_rs] < 58; --l4_rs, l4_inc *= 10)
            l4_cdtor += ((pzr_source[l4_rs] - 48) & 0xFF) * l4_inc;
        
        l4_inc = log10(l4_inc);
        
        if(++l4_cdtor >= pow(10, l4_inc))
            pzr_source.replace(pzr_source.size() - l4_inc, l4_inc + 1, std::string(1, 0x31) + std::string(l4_inc, 0x30));
        else
            pzr_source.replace(pzr_source.size() - l4_inc, l4_inc, static_cast<std::ostringstream*>(&(std::ostringstream() << l4_cdtor))->str());
        
        return true;
    }

    /**
     * function which return the number located at the end of a string
     * @see if your string is something as follow : counter_45, the returned number will be 45
     * @param string reference pzr_source
     * @return int number at end of pzr_source
     */
    int nb_str(std::string & pzr_source)
    {
        int l4_cdtor = 0;
        
        for(int l4_rs = pzr_source.size()-1, l4_inc = 1; l4_rs && pzr_source[l4_rs] > 47 && pzr_source[l4_rs] < 58; --l4_rs, l4_inc *= 10)
            l4_cdtor += ((pzr_source[l4_rs] - 48) & 0xFF) * l4_inc;
        
        return l4_cdtor;
    }

    /**
     * function which return a bitmap string argument as a vector<bool> expression field state
     * @see e.g : string("4FC01") will return -> 01001111110000000001
     * @param const string reference pzr_source
     * @return vector<bool>
     */
    std::vector<bool> bit_bol(const std::string & pzr_source)
    {
        std::vector<bool> lv_bitmap;
        lv_bitmap.reserve(pzr_source.size()*4);
        
        for(int l4_i = 0, l4_tmp = 0; l4_i < pzr_source.size(); ++l4_i)
        {
            l4_tmp = (pzr_source[l4_i] > 54) ? pzr_source[l4_i] - 55 : pzr_source[l4_i];
            lv_bitmap.push_back((l4_tmp & 0x08));
            lv_bitmap.push_back((l4_tmp & 0x04));
            lv_bitmap.push_back((l4_tmp & 0x02));
            lv_bitmap.push_back((l4_tmp & 0x01));
        }
        
        return lv_bitmap;
    }

    /**
     * function's which serialize a 2x4:8/2x8:16/2x16:32/2x32:64 stream
     * @param p1r_left const reference of char/uint8_t/uint16_t/uint32_t
     * @param p1r_right const reference of char/uint8_t/uint16_t/uint32_t
     * @return uint8_t/uint16_t/uint32_t/uint64_t
     */
    uint8_t bind_(const char & p1r_left, const char & p1r_right)
    {
        return (uint8_t)((((p1r_left & 0x0F) << ((sizeof(uint8_t) * 8) / 2)) | (p1r_right & 0x0F)) & 0xFF);
    }
    uint16_t bind_(const uint8_t & p1r_left, const uint8_t & p1r_right)
    {
        return (uint16_t)((((p1r_left & 0x00FF) << ((sizeof(uint16_t) * 8) / 2)) | (p1r_right & 0x00FF)) & 0xFFFF);
    }
    uint32_t bind_(const uint16_t & p1r_left, const uint16_t & p1r_right)
    {
        return (uint32_t)((((p1r_left & 0x0000FFFF) << ((sizeof(uint32_t) * 8) / 2)) | (p1r_right & 0x0000FFFF)) & 0xFFFFFFFF);
    }
    uint64_t bind_(const uint32_t & p1r_left, const uint32_t & p1r_right)
    {
        return (uint64_t)((((p1r_left & 0x00000000FFFFFFFF) << ((sizeof(uint64_t) * 8) / 2)) | (p1r_right & 0x00000000FFFFFFFF)) & 0xFFFFFFFFFFFFFFFF);
    }

    /**
     * function which unpad a specific char from a string beside a given direction
     * @see e.g : for string("htr0000") removing 0x30 will end in a return string("htr")
     * @param pzr_source string reference
     * @param p1r_unpad const char reference
     * @param p1r_dir const bool reference (TRUE for left 2 right, FALSE vice versa)
     * @return pzr_source string reference
     */
    std::string & str_unpad(std::string & pzr_source, const char & p1r_unpad, const bool & p1r_dir)
    {
        if(!p1r_dir)
            while(pzr_source.erase(pzr_source.size() - 1,1)[pzr_source.size() - 2] == p1r_unpad);
        else
            while(pzr_source.erase(0,1)[0] == p1r_unpad);
        
        return pzr_source;
    }

    /**
     * function which pad a char in a given direction for a specific amount
     * @see e.g : pad 0 x6 at end of string("abc") -> abc000000
     * @param pzr_source string reference
     * @param p1r_padchar const char reference
     * @param p4r_length const int reference
     * @param p1r_dir const bool reference
     * @return pzr_source string reference
     */
    std::string & str_padchar(std::string & pzr_source, const char & p1r_padchar, const int p4r_length, const bool & p1r_dir)
    {
        return (p1r_dir) ? pzr_source.append(std::string(p4r_length, p1r_padchar)) : pzr_source.assign(std::string(p4r_length, p1r_padchar) + pzr_source);
    }

    /**
     * function which merge and expose the distinct field upon two different received bitmaps
     * @see e.g : for a("F2") and b("F3") -> 1111 0010 and 1111 0011 only field number 8 will be exposed. (XOR) be aware that if a string size difference occur an empty vector will be returned
     * @param pzr_sourceA const string reference
     * @param pzr_sourceB const string reference
     * @return std::vector<int> with fields number (AD)
     */
    std::vector<int> merge_bit(const std::string & pzr_sourceA, const std::string & pzr_sourceB)
    {
        std::vector<int> lv_fieldDiff;

        if(pzr_sourceA.size() != pzr_sourceB.size())
            return lv_fieldDiff;

        for(int l4_i = 0, l4_j = 0; l4_i < pzr_sourceA.size(); ++l4_i)
        {
            for(l4_j = 0; l4_j < 4; ++l4_j)
            {
                if((((pzr_sourceA[l4_i] & ka_bitmov[l4_j]) ^ (pzr_sourceB[l4_i] & ka_bitmov[l4_j])) & ka_bitmov[l4_j])) 
                    lv_fieldDiff.push_back(l4_i * 4 + l4_j + 1);
            }
        }
        
        if(lv_fieldDiff.empty())
            lv_fieldDiff.push_back(0);
        
        return lv_fieldDiff;
    }

    /**
     * function which do the same process as STL std::string::substr() over a given reference
     * @see this function is 2x time faster than std::string::substr() until you reach a cut of 10 chars (linear prog.)
     * @param p2r_pos const unsigned short reference (starting char position)
     * @param p2r_qt const unsigned short reference (quantity to cut & realloc)
     * @param pzr_s string reference
     * @return pzr_s const string reference
     */
    const std::string & subref(const unsigned short & p2r_pos, const unsigned short & p2r_qt, std::string & pzr_s)
    {
        for(unsigned short l2_ni = 0; l2_ni < p2r_qt; pzr_s[l2_ni] = *&pzr_s[p2r_pos + l2_ni++]);
        
        return pzr_s.erase(p2r_qt, pzr_s.size());
    }

    /**
     * function which initialize the SQL QUERY MAP : mm_queryText 
     * @see create a string SQL query and add it to mm_queryText following the fetching scheme qualifier(s) contained inside pvr_colQual
     * @param pzr_tabName const string reference
     * @param pzr_fetch const string reference
     * @param pvr_colQual const vector of pair made of string and string reference
     * @param pmr_queryText map of int and string reference
     * @return bool
     */
    bool sql_spe(const std::string & pzr_tabName, const std::string & pzr_fetch, const std::vector<std::pair<std::string, std::string> > & pvr_colQual, std::map<int, std::string> & pmr_queryText)
    {
        if(pvr_colQual.empty() || pzr_fetch.empty() || pzr_tabName.empty())
            return false;
        
        std::string lz_sqlQ("SELECT " + pzr_fetch + " FROM " + pzr_tabName + " WHERE " + pvr_colQual[0].first + " = '" + pvr_colQual[0].second + "' ");
        
        for(int l4_i = 1; l4_i < pvr_colQual.size(); lz_sqlQ.append(" AND " + pvr_colQual[l4_i].first + " = '" + pvr_colQual[++l4_i].second + "' "));
        
        pmr_queryText.insert(std::make_pair<int, std::string>(pmr_queryText.end()->first + 1, lz_sqlQ));
        
        return true;
    }

    /**
     * function which check the full char consistency of a given string based over a give char as padding argument
     * @see if s("aaaaa") and char = 'a' return true, elsewhere if s has something else than a return false
     * @param pzr_source const string reference
     * @param p1r_exp const char reference
     * @return bool, true if string if fully padded with the given char as arg
     */
    bool is_olc(const std::string & pzr_source, const char & p1r_exp)
    {
        return (bool)((std::size_t)pzr_source.find_first_not_of(p1r_exp) == std::string::npos);
    }

    /**
     * function which unpach a set of token data inside a string into a map<string, string>
     * @param pzr_source const string reference : raw string
     * @param p4r_tagSize const int reference : size of token tags
     * @param p4r_lenSize const int reference : size of token length
     * @param pmr_scheme const map reference : scheme of unpacking first = tag name, second = max length size
     * @return map<string, string> of first : token data name, second : token data value
     */
    std::map<std::string, std::string> un_tkn(const std::string & pzr_source, const int & p4r_tagSize, const int & p4r_lenSize, const std::map<std::string, int> & pmr_scheme)
    {
        std::map<std::string, std::string> lm_tokens;
        
        if(!pzr_source.empty() && !pmr_scheme.empty())
        {
            std::map<std::string, int>::const_iterator lik_scheme;
            bool l1_flag = false;
            unsigned int lu4_runner = 0, lu4_length = 0;
            std::string lz_tempCut;
            
            while(!l1_flag)
            {
                lik_scheme = pmr_scheme.find(pzr_source.substr(lu4_runner, p4r_tagSize));
                
                if(lik_scheme == pmr_scheme.end() || (lu4_runner + p4r_tagSize + p4r_lenSize) > pzr_source.size())
                    return lm_tokens;
                
                lz_tempCut.assign(pzr_source.substr(lu4_runner + p4r_tagSize, p4r_lenSize));
                lu4_length = nb_str(lz_tempCut);
                
                if(lu4_length > lik_scheme->second || (lu4_runner + p4r_tagSize + lu4_length) > pzr_source.size())
                    return lm_tokens;
                
                lz_tempCut.assign(pzr_source.substr(lu4_runner + p4r_tagSize + p4r_lenSize, lu4_length));
                lm_tokens.insert(std::make_pair<std::string, std::string>(pzr_source.substr(lu4_runner, p4r_tagSize), lz_tempCut));
                
                lu4_runner += p4r_tagSize + p4r_lenSize + lu4_length;
                
                if(lu4_runner == pzr_source.size())
                    ++l1_flag;
            }
        }
        
        return lm_tokens;
    }

    /**
     * function which build a specific field
     * @see it follow the scheme : LLL PAR LLL 01 LL DATA, e.g : 026PAR02001164587545896523546
     * @param pzr_source const string reference : paymentAccountRef
     * @return string : paymentAccountData
     */
    std::string build_sf(const std::string & pzr_source)
    {
        std::string lz_p56, lz_dataL;
        
        if(pzr_source.size() > 29 || pzr_source.empty())
            return lz_p56;
        
        for(int l4_i = 0; l4_i < (int)(log10(pzr_source.size() + 4) + 1); ++l4_i) 
            lz_dataL.append((!l4_i) ? 
                                std::string(1, (((pzr_source.size() + 4) % 10) | 0x30)) : 
                                std::string(1, (((pzr_source.size() + 4) / (int)(pow(10, l4_i))) | 0x30)));
        
        std::reverse(lz_dataL.begin(), lz_dataL.end());
        
        return lz_p56.assign("PAR" + 
                             lz_dataL.assign(std::string(3 - lz_dataL.size(), 0x30) + lz_dataL) + 
                             "01" + 
                             std::string(1, ((pzr_source.size() / 10) | 0x30)) + 
                             std::string(1, ((pzr_source.size() % 10) | 0x30)) + 
                             pzr_source);
    }

    /**
     * function which echo the bit state in a 1 byte value
     * @see if our hex-ASCII byte is > 0x39 then the std::bitset container is reversed (bits order is reversed NOT ~ !!!)
     * @param p1r_val const char reference
     * @return const char reference of p1r_val
     */
    const char & showRawByte(const char & p1r_val)
    {
        std::string lz_tmp(std::string(std::bitset<8>(p1r_val).to_string().c_str()).substr(4, 4));
        
        if(p1r_val > 0x39)
            reverse(lz_tmp.begin(), lz_tmp.end());   
        
        std::cout << "[INFO showRawByte msg] 1 byte : " << p1r_val << " - right nibble : " << lz_tmp << std::endl;
        
        return p1r_val;
    }

    /** 
     * function which will provide some output in order to show the bits state of the bitmap, and the field presence
     * @param pzr_val const string reference
     * @return string which'll be a LOG
     */
    std::string showBitmapBitStatus(const std::string & pzr_val)
    {
        std::string lz_log("\nbitmap is : " + pzr_val + "\nbits : "), lz_tmp, lz_tmp2, lz_logN("\npresent fields : ");
        unsigned char l1_fieldNb = 1;
        
        for(std::string::const_iterator l1_itt = pzr_val.begin(); l1_itt != pzr_val.end(); ++l1_itt)
        {
            lz_tmp.assign(std::string(std::bitset<8>(*l1_itt).to_string().c_str()).substr(4, 4));
            
            if(*l1_itt > 0x39)
                reverse(lz_tmp.begin(), lz_tmp.end());
            
            lz_log.append(lz_tmp);
            lz_tmp2.append(lz_tmp);
        }
        
        for(std::string::const_iterator l1_itt = lz_tmp2.begin(); l1_itt != lz_tmp2.end(); ++l1_itt, ++l1_fieldNb)
        {
            if(*l1_itt == 0x31)
                lz_logN.append(static_cast<std::ostringstream*>(&(std::ostringstream() << l1_fieldNb))->str() + std::string(1, 0x2F));
        }
        
        return lz_log.append(lz_logN);
    }

    /**
     * function which decode the length of a field inside the main data()
     * @see in our case length is always on 2 bytes so 2 right nibbles
     * @param pb1r_cutPos const ubyte4 reference
     * @param pzr_netMsg const string reference
     * @return unsigned int
     */
    unsigned int decodeLength(const unsigned int & pb1r_cutPos, const std::string & pzr_netMsg)
    {   
        if(pzr_netMsg.size() < pb1r_cutPos + 2)
            return false;

        unsigned char u1l_first  = (pzr_netMsg[pb1r_cutPos] >= 65) ? pzr_netMsg[pb1r_cutPos] - 55 : pzr_netMsg[pb1r_cutPos],
                      u1l_second = (pzr_netMsg[pb1r_cutPos + 1] >= 65) ? pzr_netMsg[pb1r_cutPos + 1] - 55 : pzr_netMsg[pb1r_cutPos + 1];
        
        unsigned int ul4_full = (((u1l_first << 4) | (u1l_second & 0x0F)) & 0x000000FF);
        
        if(ul4_full % 2)
            ++ul4_full;
        
        return ul4_full;
    }

    /**
     * function which translate an ascii string to it's hex ascii format following the UTF-8 scheme
     * @see UTF-8 HEX scheme e.g : '0' to "30" | BE AWARE OF THE INPUT STRING SIZE LIMITNESS : max = 0 to 18,446,744,073,709,551,615
     * @param pzr_source const string reference
     * @return string
     */ 
    std::string ascii2hexf(const std::string & pzr_source)
    {
        std::string lz_temp;
        for(unsigned long long l8_i = 0; l8_i < pzr_source.size(); lz_temp.append(std::string(1, ka_chargov[((pzr_source[l8_i] >> 4) & 0x0F)]) + 
                                                                                  std::string(1, ka_chargov[(pzr_source[l8_i] & 0x0F)])), ++l8_i);

        return lz_temp;
    }

    /**
     * function which translate a hex string to the ascii format
     * @see following the UTF-8 scheme e.g : "31" to "1"
     * @param pzr_source const string reference
     * @return string
     */
    std::string hexf2ascii(const std::string & pzr_source)
    {
        std::string lz_temp;
        
        if(pzr_source.size() % 2 || pzr_source.find_first_not_of("0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"))
            return lz_temp;
        
        for(unsigned long long l8_i = 0; l8_i < pzr_source.size(); l8_i += 2)
        {
            lz_temp.append(std::string(1, (((((pzr_source[l8_i] - (((pzr_source[l8_i] - 48) > 10) ? 55 : 48)) << 4) & 0xF0) | 
                                             ((pzr_source[l8_i + 1] - (((pzr_source[l8_i + 1] - 48) > 10) ? 55 : 48)) & 0x0F)) & 0xFF)));
        }
        
        return lz_temp;
    }

    /**
     * function which decode the fields based over the bits state of the bitmap by size
     * @see the main purpoose is to reach the xxxxxxxxx, cut it, assign it to mz_matchingKey
     * @param pzr_mcMsg const string reference
     * @return bool 1 if decoding is OK
     */
    bool decode(const std::string & pzr_mcMsg)
    {
        std::string lz_mcMsg(ascii2hexf(pzr_mcMsg)), mz_protocolMsgId("TCP"), mz_matchingKey;
            
        /** init itt temp data
         * ul1_i      : unsigned char, used as a bits itterator inside a nibble, range [0;3], ONLY used to do 4 loops
         * ub1_cTyp   : unsigned char, used as a boolean, true if hex-ASCII char equal [0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39]
         * ul1_rNibb  : unsigned char, used as a begin iterator, valued at 0 if ub1_cTyp true OR 3 if !ub1_cTyp
         * ul4_gCtn   : unsigned byte4, used as an iterator to represent the actual field number
         * ul1_ct     : unsigned char, used as an iterator to represent the actual bitmap byte
         * ul4_netCut : 4 bytes, increment used to count the size cutout from the netData before the xxxxxxxxx
         */
        unsigned char ul1_i = 3, ub1_cTyp = false, ul1_rNibb, ul1_ct = 0;
        unsigned int ul4_gCtn = 1, ul4_fieldSize = 0, ul4_netCut = k4_headerLength + k4_msgIdLength + k1a_fieldLength[0] * 2;
        
        //out sized OR no bitmap !Failure
        if(lz_mcMsg.size() < k4_headerLength + k4_msgIdLength || lz_mcMsg.size() < k4_headerLength + k4_msgIdLength + static_cast<unsigned int>(k1a_fieldLength[0]) * 2)
            return false;

        std::bitset<8> lb_Rnib = std::bitset<8>(lz_mcMsg[k4_headerLength + k4_msgIdLength + ul1_ct]);
        mz_protocolMsgId.assign(lz_mcMsg.substr(k4_headerLength, k4_msgIdLength));
        
        /** @see that for loop is used ONLY to iterate through all the [hex-ASCII bytes] of the bitmap */
        for(; ul1_ct < k1a_fieldLength[0] * 2; ub1_cTyp = (lz_mcMsg[k4_headerLength + k4_msgIdLength + ++ul1_ct] > 0x39), lb_Rnib = std::bitset<8>(lz_mcMsg[k4_headerLength + k4_msgIdLength + ul1_ct]), ul1_i = (ub1_cTyp) ? 0 : 3)
        {
            /** @see that for loop is used ONLY to iterate through all the [bits of the r-nibble] in 1 hex-ASCII bytes of the bitmap */
            for(ul1_rNibb = 0; ul1_rNibb++ < 4; ++ul4_gCtn)
            {
                /** @see if our hex-ASCII byte is > 0x39 then the std::bitset container is reversed (bits order is reversed NOT ~ !!!) */
                if(lb_Rnib[(ub1_cTyp) ? ul1_i++ : ul1_i--])
                {
                    /** @see in case of FIXED size fields */
                    if(k1a_fieldLength[ul4_gCtn] > 0)
                    {
                        //out sized !Failure
                        if(lz_mcMsg.size() < (ul4_netCut + k1a_fieldLength[ul4_gCtn] * 2))
                            return false;
                        
                        if(ul4_gCtn == k4_targetField)
                        {
                            mz_matchingKey.assign(lz_mcMsg.substr(ul4_netCut, k1a_fieldLength[k4_targetField] * 2));
                            return true;
                        }
                        ul4_netCut += k1a_fieldLength[ul4_gCtn] * 2;
                    }
                    /** @see in case of VARIABLE size fields */
                    else
                    {
                        ul4_fieldSize = decodeLength(ul4_netCut, lz_mcMsg);
                        
                        //out sized !Failure
                        if(!ul4_fieldSize || lz_mcMsg.size() < ul4_netCut + 2 + ul4_fieldSize)
                            return false;
                        
                        if(ul4_gCtn == k4_targetField)
                        {
                            mz_matchingKey.assign(lz_mcMsg.substr(ul4_netCut + 2, ul4_fieldSize));
                            return true;
                        }
                        
                        ul4_netCut += 2 + ul4_fieldSize;
                    }
                }
            }
        }
        return false;
    }

    /**
     * function which cut 3 bytes to 4 base 64 x6 bits.
     * @param p1r_b1 const char reference
     * @param p1r_b2 const char reference
     * @param p1r_b3 const char reference
     * @return bitset<32> 4 concatenated raw bytes with the first set to 0x00
     */
    std::bitset<32> to_b64(const char & p1r_b1 = 0x00, const char & p1r_b2 = 0x00, const char & p1r_b3 = 0x00)
    {
        unsigned int l4_j = 1;
        uint32_t b24_holder = p1r_b3;
        
        for(char l1_i[3] = {p1r_b3, p1r_b2, p1r_b1}; l4_j < 3; b24_holder <<= 8, b24_holder |= l1_i[l4_j], ++l4_j);
        
        return std::bitset<32>(b24_holder);
    }

    /**
     * function which express 24 bits into base 64 string
     * @param pcr_32bits const bitset<32> reference
     * @return string in base 64 format
     */
    std::string ex_b64(const std::bitset<32> & pcr_32bits)
    {
        std::string lz_b64;
        std::bitset<8> lb_holder;
        
        for(int l4_j = 0, l4_k = 0; l4_j < 30; l4_j++, l4_k++)
        {
            if(l4_k == 6)
            {
                lb_holder[6] = lb_holder[7] = l4_k = 0;
                lz_b64.append(1, ka_b64[lb_holder.to_ulong()]);
            }
            lb_holder[l4_k] = pcr_32bits[l4_j];
        }
        
        std::reverse(lz_b64.begin(),lz_b64.end());
        return lz_b64;
    }

    /**
     * function which cut each 3 char of a b255 string and append back the result as b64 string
     * @param pzr_b255 string reference as b255
     * @return pzr_b255 reference as b64
     */
    std::string & sd_c3(std::string & pzr_b255)
    {
        pzr_b255.append((pzr_b255.size() + (pzr_b255.size() % 3)) % 3, 0x7F);
        int l4_l = pzr_b255.size();
        for(int l4_o = 0; l4_o < l4_l; 
            pzr_b255.append(ex_b64(to_b64(pzr_b255[l4_o++], pzr_b255[l4_o++], pzr_b255[l4_o++]))));
        
        return pzr_b255.erase(0, l4_l);
    }
    
    /**
     * function which convert a long to a string
     * @param const long reference p8r_source
     * @return string
     */
    std::string long_str(const long & p8r_source)
    {
        std::string lz_out;
        for(long l8_i = p8r_source; l8_i; lz_out.append(std::string(1, (0x30 | ((l8_i % 10) & 0x0F)))), l8_i /= 10);
        
        std::reverse(lz_out.begin(), lz_out.end());
        
        return lz_out;
    }
    
    /**
     * function which return the full time at calling for log purposes
     * @see time() returns the time as the number of seconds since the Epoch, 1970-01-01 00:00:00 +0000 (UTC).
     * @return string
     */
    std::string inst_t()
    {
        std::string lz_timing;
        timespec lct_secnan;
        
        if(clock_gettime(CLOCK_REALTIME, &lct_secnan))
            return lz_timing;
        
        lz_timing.append(long_str(lct_secnan.tv_nsec % 1000) + "ns\n");
        lz_timing.append(long_str((lct_secnan.tv_nsec / 1000) % 1000) + "µs\n");
        lz_timing.append(long_str((lct_secnan.tv_nsec / 1000000) % 1000) + "ms\n");
        lz_timing.append(long_str(lct_secnan.tv_sec) + "s\n");
        
        return lz_timing;
    }
    
    /**
     * template which swap the byte order in T
     * @see bytes swapping
     * @param ptr_in T reference 
     * @return T ptr_in as reference
     */
    template<class T>
    T & remake_swapAD(T & ptr_in)
    {
        T lt_tmp = ptr_in >> (sizeof(T) * 8 - 8);
        
        for(char l1_i = 1; l1_i < sizeof(T); 
            lt_tmp |= ((ptr_in & (T)(pow(2, 8 * l1_i) - pow(2, 8 * (l1_i - 1)))) >> (8 * l1_i)), 
            ++l1_i);
        
        std::swap(lt_tmp, ptr_in);
        
        return ptr_in;
    };
    
    /**
     * function which unpack 2 nibbles of 1 bytes in 2 bytes
     * @see use case : 0xF5 will give a string(0x0F + 0x05) "F5"
     * @param p1r_source const char reference
     * @return string
     */
    std::string exp2_byte(const char & p1r_source)
    {
        return std::string(std::string(1, ka_chargov[((p1r_source >> 4) & 0x0F)]) + 
                           std::string(1, ka_chargov[(p1r_source & 0x0F)]));
    }
    
    /**
     * function ASCII to EBCDIC
     * @see EBCDIC IBM table
     * @param pzr_source string reference
     * @return pzr_source reference
     */
    std::string & to_ebcdic(std::string & pzr_source)
    {
        for(int l4_size = 0; l4_size < pzr_source.size(); pzr_source[l4_size] = ka_ebcdic[128 + pzr_source[l4_size++]]);
        return pzr_source;
    }
     
}; //mBank::


int main(int argc, char *argv[])
{
    std::string a("545789652"), b;
    a = mBank::to_ebcdic(a);
    
    for(int i = 0; i < a.size(); ++i)
    {
        b.append(mBank::exp2_byte(a[i]));
    }
    
    std::cout << b << std::endl;
};
