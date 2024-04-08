#include "scanner.h"

scanner::scanner(const char* module_name)
{
    this->module_address = reinterpret_cast<uintptr_t>(GetModuleHandleA(module_name));
    if (this->module_address == 0)
    {
        // Module not found, handle error
        throw std::runtime_error("Module not found");
    }
}

std::vector<int> scanner::ConvPatternToByte(const char* pattern)
{
    auto bytes = std::vector<int>();

    auto pattern_start = const_cast<char*>(pattern);
    auto pattern_end = const_cast<char*>(pattern) + strlen(pattern);

    for (auto current_byte = pattern_start; current_byte < pattern_end; ++current_byte)
    {
        if (*current_byte == '?')
        {
            ++current_byte;
            if (*current_byte == '?') ++current_byte;
            bytes.push_back(-1);
        }
        else
        {
            bytes.push_back(strtoul(current_byte, &current_byte, 16));
        }
    }

    if (bytes.empty())
    {
        // Invalid pattern, handle error
        throw std::invalid_argument("Invalid pattern");
    }

    return bytes;
}

Handle scanner::scan(const char* pattern)
{
    // Convert pattern to bytes
    std::vector<int> pattern_bytes;
    try
    {
        pattern_bytes = this->ConvPatternToByte(pattern);
    }
    catch (const std::exception& e)
    {
        // Handle error from ConvPatternToByte
        throw std::runtime_error("Error converting pattern to bytes: " + std::string(e.what()));
    }

    auto dos_header = reinterpret_cast<IMAGE_DOS_HEADER*>(this->module_address);
    auto nt_header = reinterpret_cast<IMAGE_NT_HEADERS*>(reinterpret_cast<std::uint8_t*>(this->module_address) + dos_header->e_lfanew);
    auto size = nt_header->OptionalHeader.SizeOfImage;
    auto start_module = reinterpret_cast<std::uint8_t*>(this->module_address);

    // Iterate through module memory to find pattern
    for (auto i = 0; i < size - pattern_bytes.size(); ++i)
    {
        bool found_byte_set = true;
        for (auto j = 0; j < pattern_bytes.size(); ++j)
        {
            if (start_module[i + j] != pattern_bytes[j] && pattern_bytes[j] != -1)
            {
                found_byte_set = false;
                break;
            }
        }
        if (found_byte_set)
        {
            // Pattern found, return handle with address
            return Handle(reinterpret_cast<std::uintptr_t>(&start_module[i]));
        }
    }

    // Pattern not found, handle error
    throw std::runtime_error("Pattern not found");
}
