# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/daniel/Curso-Plataformas-Abiertas-UCR-I-2025/Class10/build/_deps/picotool-src"
  "/home/daniel/Curso-Plataformas-Abiertas-UCR-I-2025/Class10/build/_deps/picotool-build"
  "/home/daniel/Curso-Plataformas-Abiertas-UCR-I-2025/Class10/build/_deps"
  "/home/daniel/Curso-Plataformas-Abiertas-UCR-I-2025/Class10/build/picotool/tmp"
  "/home/daniel/Curso-Plataformas-Abiertas-UCR-I-2025/Class10/build/picotool/src/picotoolBuild-stamp"
  "/home/daniel/Curso-Plataformas-Abiertas-UCR-I-2025/Class10/build/picotool/src"
  "/home/daniel/Curso-Plataformas-Abiertas-UCR-I-2025/Class10/build/picotool/src/picotoolBuild-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/daniel/Curso-Plataformas-Abiertas-UCR-I-2025/Class10/build/picotool/src/picotoolBuild-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/daniel/Curso-Plataformas-Abiertas-UCR-I-2025/Class10/build/picotool/src/picotoolBuild-stamp${cfgdir}") # cfgdir has leading slash
endif()
