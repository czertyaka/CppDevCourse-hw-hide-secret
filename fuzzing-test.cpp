#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <span>
#include <string>

#include "hide-secret.hpp"

extern "C" int LLVMFuzzerTestOneInput(const std::uint8_t* data,
    std::size_t size)
{
    const std::span<const std::uint8_t> input{data, size};
    const auto zeroIt = std::find(input.begin(), input.end(), 0);
    if (zeroIt == input.begin() || zeroIt == input.end())
    {
        return 0;
    }
    const auto zeroPos = std::distance(input.begin(), zeroIt);

    std::string text{};
    text.reserve(zeroPos + 1);
    text.append(reinterpret_cast<const char*>(data), zeroPos - 1);
    text.push_back('\0');

    std::string secret{};
    secret.reserve(size - zeroPos);
    secret.append(reinterpret_cast<const char*>(data + zeroPos + 1),
        size - zeroPos - 1);
    secret.push_back('\0');

    hide_secret(text.data(), secret.data());

    return 0;
}
