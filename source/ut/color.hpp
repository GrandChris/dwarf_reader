///
/// @file:   given.cpp
/// @author: GrandChris
/// @date:   2021-12-31
/// @note:   Modified version from https://github.com/Bareflank/bsl
///

#pragma once

#include <string_view>

constexpr bool ENABLE_COLOR = false;

namespace ut
{
    namespace details
    {
        /// <!-- description -->
        ///   @brief Returns val if color is enabled, "" otherwise
        ///
        /// <!-- inputs/outputs -->
        ///   @param val the color to return if color is enabled
        ///   @return Returns val if color is enabled, "" otherwise
        ///
        [[nodiscard]] constexpr auto
        if_color_enabled(char const * const val) noexcept -> char const *
        {
            if constexpr (ENABLE_COLOR) {
                return val;
            }

            return "";
        }
    }

    /// @brief resets the color output of debug statements
    constexpr std::string_view rst{details::if_color_enabled("\033[0m")};

    /// @brief changes the foreground color to normal black
    constexpr std::string_view blk{details::if_color_enabled("\033[0;90m")};
    /// @brief changes the foreground color to normal red
    constexpr std::string_view red{details::if_color_enabled("\033[0;91m")};
    /// @brief changes the foreground color to normal green
    constexpr std::string_view grn{details::if_color_enabled("\033[0;92m")};
    /// @brief changes the foreground color to normal yellow
    constexpr std::string_view ylw{details::if_color_enabled("\033[0;93m")};
    /// @brief changes the foreground color to normal blue
    constexpr std::string_view blu{details::if_color_enabled("\033[0;94m")};
    /// @brief changes the foreground color to normal magenta
    constexpr std::string_view mag{details::if_color_enabled("\033[0;95m")};
    /// @brief changes the foreground color to normal cyan
    constexpr std::string_view cyn{details::if_color_enabled("\033[0;96m")};
    /// @brief changes the foreground color to normal white
    constexpr std::string_view wht{details::if_color_enabled("\033[0;97m")};

    /// @brief changes the foreground color to bold black
    constexpr std::string_view bold_blk{details::if_color_enabled("\033[1;90m")};
    /// @brief changes the foreground color to bold red
    constexpr std::string_view bold_red{details::if_color_enabled("\033[1;91m")};
    /// @brief changes the foreground color to bold green
    constexpr std::string_view bold_grn{details::if_color_enabled("\033[1;92m")};
    /// @brief changes the foreground color to bold yellow
    constexpr std::string_view bold_ylw{details::if_color_enabled("\033[1;93m")};
    /// @brief changes the foreground color to bold blue
    constexpr std::string_view bold_blu{details::if_color_enabled("\033[1;94m")};
    /// @brief changes the foreground color to bold magenta
    constexpr std::string_view bold_mag{details::if_color_enabled("\033[1;95m")};
    /// @brief changes the foreground color to bold cyan
    constexpr std::string_view bold_cyn{details::if_color_enabled("\033[1;96m")};
    /// @brief changes the foreground color to bold white
    constexpr std::string_view bold_wht{details::if_color_enabled("\033[1;97m")};
}

