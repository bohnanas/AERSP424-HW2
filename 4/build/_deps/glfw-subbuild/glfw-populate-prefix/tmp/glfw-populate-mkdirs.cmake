# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "D:/VISUAL STUDIO CODE/PROJECTS/AERSP424 HW2/HW2/4/build/_deps/glfw-src"
  "D:/VISUAL STUDIO CODE/PROJECTS/AERSP424 HW2/HW2/4/build/_deps/glfw-build"
  "D:/VISUAL STUDIO CODE/PROJECTS/AERSP424 HW2/HW2/4/build/_deps/glfw-subbuild/glfw-populate-prefix"
  "D:/VISUAL STUDIO CODE/PROJECTS/AERSP424 HW2/HW2/4/build/_deps/glfw-subbuild/glfw-populate-prefix/tmp"
  "D:/VISUAL STUDIO CODE/PROJECTS/AERSP424 HW2/HW2/4/build/_deps/glfw-subbuild/glfw-populate-prefix/src/glfw-populate-stamp"
  "D:/VISUAL STUDIO CODE/PROJECTS/AERSP424 HW2/HW2/4/build/_deps/glfw-subbuild/glfw-populate-prefix/src"
  "D:/VISUAL STUDIO CODE/PROJECTS/AERSP424 HW2/HW2/4/build/_deps/glfw-subbuild/glfw-populate-prefix/src/glfw-populate-stamp"
)

set(configSubDirs Debug)
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "D:/VISUAL STUDIO CODE/PROJECTS/AERSP424 HW2/HW2/4/build/_deps/glfw-subbuild/glfw-populate-prefix/src/glfw-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "D:/VISUAL STUDIO CODE/PROJECTS/AERSP424 HW2/HW2/4/build/_deps/glfw-subbuild/glfw-populate-prefix/src/glfw-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
