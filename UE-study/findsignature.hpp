#pragma once
#include <windows.h>
#include <cstdint>
#include <algorithm>
#include <sstream>
#include <string_view>
#include <array>
#include <vector>

// Reference: https://github.com/haram/splendid_implanter/blob/master/splendid_implant/mem_utils.hpp

#define FIND_NT_HEADER(x) reinterpret_cast<PIMAGE_NT_HEADERS>( uint64_t(x) + reinterpret_cast<PIMAGE_DOS_HEADER>(x)->e_lfanew )

template <size_t N>
uint8_t* find_signature(const char* module, const char(&signature)[N]) {
    std::array<uint8_t, N> signature_bytes{};

    {
        std::istringstream string_stream{signature};

        for (auto& byte : signature_bytes) {
            if (string_stream.eof()) {
                byte = 0;
            } else {
                std::string byte_str;
                string_stream >> byte_str;

                if (byte_str == "?") {
                    byte = 0;
                } else {
                    byte = static_cast<uint8_t>(std::stoi(byte_str, nullptr, 16));
                }
            }
        }
    }

    uint8_t* found_bytes = nullptr;

    {
        const auto module_base = reinterpret_cast<uint8_t*>(GetModuleHandleA(module));
        if (!module_base) return nullptr;

        const auto nt_headers = FIND_NT_HEADER(module_base);
        const auto image_start = module_base;
        const auto image_end = image_start + nt_headers->OptionalHeader.SizeOfImage;

        const auto result = std::search(image_start, image_end, signature_bytes.cbegin(), signature_bytes.cend(), [](uint8_t left, uint8_t right) -> bool {
            return right == 0ui8 || left == right;
        });

        found_bytes = (result != image_end) ? result : nullptr;
    }

    return found_bytes;
}
