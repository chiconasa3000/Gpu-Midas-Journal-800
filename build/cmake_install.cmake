# Install script for directory: /home/administrador/frameworks/midas-journal-800-master

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

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Development")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES
    "/home/administrador/frameworks/midas-journal-800-master/itkGradientDifferenceMultiImageToImageMetric.h"
    "/home/administrador/frameworks/midas-journal-800-master/itkGradientDifferenceSingleImageToImageMetric.h"
    "/home/administrador/frameworks/midas-journal-800-master/itkGradientDifferenceSingleImageToImageMetric.txx"
    "/home/administrador/frameworks/midas-journal-800-master/itkMeanSquaresMultiImageToImageMetric.h"
    "/home/administrador/frameworks/midas-journal-800-master/itkMultiImageRegistrationMacro.h"
    "/home/administrador/frameworks/midas-journal-800-master/itkMultiImageToImageMetric.h"
    "/home/administrador/frameworks/midas-journal-800-master/itkMultiImageToImageMetric.txx"
    "/home/administrador/frameworks/midas-journal-800-master/itkMultiImageToImageRegistrationMethod.h"
    "/home/administrador/frameworks/midas-journal-800-master/itkMultiImageToImageRegistrationMethod.txx"
    "/home/administrador/frameworks/midas-journal-800-master/itkMultiResolutionMultiImageToImageRegistrationMethod.h"
    "/home/administrador/frameworks/midas-journal-800-master/itkMultiResolutionMultiImageToImageRegistrationMethod.txx"
    "/home/administrador/frameworks/midas-journal-800-master/itkNormalizedGradientCorrelationImageToImageMetric.h"
    "/home/administrador/frameworks/midas-journal-800-master/itkNormalizedGradientCorrelationImageToImageMetric.txx"
    "/home/administrador/frameworks/midas-journal-800-master/itkNormalizedGradientCorrelationMultiImageToImageMetric.h"
    "/home/administrador/frameworks/midas-journal-800-master/itkPatchedRayCastInterpolateImageFunction.h"
    "/home/administrador/frameworks/midas-journal-800-master/itkPatchedRayCastInterpolateImageFunction.txx"
    "/home/administrador/frameworks/midas-journal-800-master/itkPatternIntensityImageToImageMetric.h"
    "/home/administrador/frameworks/midas-journal-800-master/itkPatternIntensityImageToImageMetric.txx"
    "/home/administrador/frameworks/midas-journal-800-master/itkPatternIntensityMultiImageToImageMetric.h"
    "/home/administrador/frameworks/midas-journal-800-master/itkPatternIntensityMultiImageToImageMetric.txx"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Runtime")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/MultiImageSearch" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/MultiImageSearch")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/MultiImageSearch"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/home/administrador/frameworks/midas-journal-800-master/build/MultiImageSearch")
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

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Runtime")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/MultiImageRegistration" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/MultiImageRegistration")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/MultiImageRegistration"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/home/administrador/frameworks/midas-journal-800-master/build/MultiImageRegistration")
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

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/administrador/frameworks/midas-journal-800-master/build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
