# Install script for directory: /home/citesoft01/Frameworks/Qt-Frameworks1/Gpu-Midas-Journal-800

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xDevelopmentx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES
    "/home/citesoft01/Frameworks/Qt-Frameworks1/Gpu-Midas-Journal-800/itkGradientDifferenceMultiImageToImageMetric.h"
    "/home/citesoft01/Frameworks/Qt-Frameworks1/Gpu-Midas-Journal-800/itkGradientDifferenceSingleImageToImageMetric.h"
    "/home/citesoft01/Frameworks/Qt-Frameworks1/Gpu-Midas-Journal-800/itkGradientDifferenceSingleImageToImageMetric.txx"
    "/home/citesoft01/Frameworks/Qt-Frameworks1/Gpu-Midas-Journal-800/itkMeanSquaresMultiImageToImageMetric.h"
    "/home/citesoft01/Frameworks/Qt-Frameworks1/Gpu-Midas-Journal-800/itkMultiImageRegistrationMacro.h"
    "/home/citesoft01/Frameworks/Qt-Frameworks1/Gpu-Midas-Journal-800/itkMultiImageToImageMetric.h"
    "/home/citesoft01/Frameworks/Qt-Frameworks1/Gpu-Midas-Journal-800/itkMultiImageToImageMetric.txx"
    "/home/citesoft01/Frameworks/Qt-Frameworks1/Gpu-Midas-Journal-800/itkMultiImageToImageRegistrationMethod.h"
    "/home/citesoft01/Frameworks/Qt-Frameworks1/Gpu-Midas-Journal-800/itkMultiImageToImageRegistrationMethod.txx"
    "/home/citesoft01/Frameworks/Qt-Frameworks1/Gpu-Midas-Journal-800/itkMultiResolutionMultiImageToImageRegistrationMethod.h"
    "/home/citesoft01/Frameworks/Qt-Frameworks1/Gpu-Midas-Journal-800/itkMultiResolutionMultiImageToImageRegistrationMethod.txx"
    "/home/citesoft01/Frameworks/Qt-Frameworks1/Gpu-Midas-Journal-800/itkNormalizedGradientCorrelationImageToImageMetric.h"
    "/home/citesoft01/Frameworks/Qt-Frameworks1/Gpu-Midas-Journal-800/itkNormalizedGradientCorrelationImageToImageMetric.txx"
    "/home/citesoft01/Frameworks/Qt-Frameworks1/Gpu-Midas-Journal-800/itkNormalizedGradientCorrelationMultiImageToImageMetric.h"
    "/home/citesoft01/Frameworks/Qt-Frameworks1/Gpu-Midas-Journal-800/itkPatchedRayCastInterpolateImageFunction.h"
    "/home/citesoft01/Frameworks/Qt-Frameworks1/Gpu-Midas-Journal-800/itkPatchedRayCastInterpolateImageFunction.txx"
    "/home/citesoft01/Frameworks/Qt-Frameworks1/Gpu-Midas-Journal-800/itkPatternIntensityImageToImageMetric.h"
    "/home/citesoft01/Frameworks/Qt-Frameworks1/Gpu-Midas-Journal-800/itkPatternIntensityImageToImageMetric.txx"
    "/home/citesoft01/Frameworks/Qt-Frameworks1/Gpu-Midas-Journal-800/itkPatternIntensityMultiImageToImageMetric.h"
    "/home/citesoft01/Frameworks/Qt-Frameworks1/Gpu-Midas-Journal-800/itkPatternIntensityMultiImageToImageMetric.txx"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xRuntimex" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/MultiImageSearch" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/MultiImageSearch")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/MultiImageSearch"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/home/citesoft01/Frameworks/Qt-Frameworks1/Gpu-Midas-Journal-800/build/MultiImageSearch")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/MultiImageSearch" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/MultiImageSearch")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/MultiImageSearch"
         OLD_RPATH "/usr/lib/x86_64-linux-gnu/libOpenCL.so:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/MultiImageSearch")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xRuntimex" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/MultiImageRegistration" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/MultiImageRegistration")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/MultiImageRegistration"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/home/citesoft01/Frameworks/Qt-Frameworks1/Gpu-Midas-Journal-800/build/MultiImageRegistration")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/MultiImageRegistration" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/MultiImageRegistration")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/MultiImageRegistration"
         OLD_RPATH "/usr/lib/x86_64-linux-gnu/libOpenCL.so:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/MultiImageRegistration")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xRuntimex" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/ReadCmd" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/ReadCmd")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/ReadCmd"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/home/citesoft01/Frameworks/Qt-Frameworks1/Gpu-Midas-Journal-800/build/ReadCmd")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/ReadCmd" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/ReadCmd")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/ReadCmd"
         OLD_RPATH "/usr/lib/x86_64-linux-gnu/libOpenCL.so:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/ReadCmd")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/citesoft01/Frameworks/Qt-Frameworks1/Gpu-Midas-Journal-800/build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
