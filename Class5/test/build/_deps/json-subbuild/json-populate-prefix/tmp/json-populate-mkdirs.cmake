# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/daniel/Curso-Plataformas-Abiertas-UCR-I-2025/Class5/test/build/_deps/json-src"
  "/home/daniel/Curso-Plataformas-Abiertas-UCR-I-2025/Class5/test/build/_deps/json-build"
  "/home/daniel/Curso-Plataformas-Abiertas-UCR-I-2025/Class5/test/build/_deps/json-subbuild/json-populate-prefix"
  "/home/daniel/Curso-Plataformas-Abiertas-UCR-I-2025/Class5/test/build/_deps/json-subbuild/json-populate-prefix/tmp"
  "/home/daniel/Curso-Plataformas-Abiertas-UCR-I-2025/Class5/test/build/_deps/json-subbuild/json-populate-prefix/src/json-populate-stamp"
  "/home/daniel/Curso-Plataformas-Abiertas-UCR-I-2025/Class5/test/build/_deps/json-subbuild/json-populate-prefix/src"
  "/home/daniel/Curso-Plataformas-Abiertas-UCR-I-2025/Class5/test/build/_deps/json-subbuild/json-populate-prefix/src/json-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/daniel/Curso-Plataformas-Abiertas-UCR-I-2025/Class5/test/build/_deps/json-subbuild/json-populate-prefix/src/json-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/daniel/Curso-Plataformas-Abiertas-UCR-I-2025/Class5/test/build/_deps/json-subbuild/json-populate-prefix/src/json-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
