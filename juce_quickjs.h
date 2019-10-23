/*
  ==============================================================================

  ==============================================================================
*/


/*******************************************************************************
 The block below describes the properties of this module, and is read by
 the Projucer to automatically generate project code that uses it.
 For details about the syntax and how to create or use a module, see the
 JUCE Module Format.txt file.


 BEGIN_JUCE_MODULE_DECLARATION

  ID:               juce_quickjs
  vendor:           benkuper & tommag
  version:          1.0.0
  name:             QuickJS
  description:      QuickJS Javascript Engine for JUCE
  website:          https://github.com/benkuper/juce_quickjs
  license:          GPLv3

  dependencies:     juce_core
  linuxLibs:        quickjs
  OSXLibs:          quickjs
  windowsLibs:      quickjs
  
 END_JUCE_MODULE_DECLARATION

*******************************************************************************/


#pragma once
#define JUCE_QUICKJS_H_INCLUDED

//==============================================================================
#ifdef _MSC_VER
 #pragma warning (push)
 // Disable warnings for long class names, padding, and undefined preprocessor definitions.
 #pragma warning (disable: 4251 4786 4668 4820)
#endif

#include <juce_core/juce_core.h>

using namespace juce;

#include "quickjspp.hpp"
#include "QuickJSEngine.h"