/*
 * Copyright (C) 2021 Emmanuel Engelhart <kelson@kiwix.org>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * is provided AS IS, WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, and
 * NON-INFRINGEMENT.  See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA
 *
 */

#include <iostream>
#include <sstream>

#include <zim/version.h>
#include <zim/zim_config.h>
#include <config.h>
#include <zstd.h>
#include <lzma.h>

#if defined(ENABLE_XAPIAN)
#include <xapian.h>
#include <unicode/uversion.h>
#endif

namespace zim
{
  LibVersions getVersions() {
    LibVersions versions = {
      { "libzim",  LIBZIM_VERSION      },
      { "libzstd", ZSTD_VERSION_STRING },
      { "liblzma", LZMA_VERSION_STRING }
    };

#if defined(ENABLE_XAPIAN)
    // Libxapian is not a mandatory dependence
    versions.push_back({ "libxapian", XAPIAN_VERSION });

    // U_ICU_VERSION does not include the patch level if 0
    std::ostringstream libicu_version;
    libicu_version << U_ICU_VERSION_MAJOR_NUM << "." << U_ICU_VERSION_MINOR_NUM << "." << U_ICU_VERSION_PATCHLEVEL_NUM;
    versions.push_back({ "libicu", libicu_version.str() });
#endif

    return versions;
  }

void printVersions() {
  LibVersions versions = getVersions();
  for (const auto& iter : versions) {
    std::cout << iter.first << " " << iter.second << std::endl;
  }
}

} //namespace zim
