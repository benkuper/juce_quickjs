/*
  ==============================================================================

   This file is part of the JUCE library.
   Copyright (c) 2017 - ROLI Ltd.

   JUCE is an open source library subject to commercial or open-source
   licensing.

   The code included in this file is provided under the terms of the ISC license
   http://www.isc.org/downloads/software-support-policy/isc-license. Permission
   To use, copy, modify, and/or distribute this software for any purpose with or
   without fee is hereby granted provided that the above copyright notice and
   this permission notice appear in all copies.

   JUCE IS PROVIDED "AS IS" WITHOUT ANY WARRANTY, AND ALL WARRANTIES, WHETHER
   EXPRESSED OR IMPLIED, INCLUDING MERCHANTABILITY AND FITNESS FOR PURPOSE, ARE
   DISCLAIMED.

  ==============================================================================
*/

#pragma warning(disable:4100)
namespace quickjs
{

//==============================================================================
struct QuickJSEngine::RootObject   : public DynamicObject
{
    RootObject()
    {
       
    }

    Time timeout;

    using Args = const var::NativeFunctionArgs&;
    using TokenType = const char*;

    void execute (const String& code)
    {
       //TOFILL
    }

    var evaluate (const String& code)
    {
        //TOFILL
		return var();
    }

    //==============================================================================
    static bool areTypeEqual (const var& a, const var& b)
    {
        return true;
    }

 
};


class MyClass
{
public:
	MyClass() {}
	MyClass(std::vector<int>) {}

	double member_variable = 5.5;
	std::string member_function(const std::string& s) { return "Hello, " + s; }
};

void println(const std::string& str) { DBG(str); }


//==============================================================================
QuickJSEngine::QuickJSEngine()  :
	maximumExecutionTime (2.0),
	root (new RootObject()),
	context(runtime)
{
	try
	{
		// export classes as a module
		auto& module = context.addModule("MyModule");
		module.function<&println>("println");
		module.class_<MyClass>("MyClass")
			.constructor<>()
			.constructor<std::vector<int>>("MyClassA")
			.fun<&MyClass::member_variable>("member_variable")
			.fun<&MyClass::member_function>("member_function");

		// import module
		context.eval("import * as my from 'MyModule'; globalThis.my = my;", "<import>", JS_EVAL_TYPE_MODULE);
		// evaluate js code
		context.eval("let v1 = new my.MyClass();" "\n"
			"v1.member_variable = 1;" "\n"
			"let v2 = new my.MyClassA([1,2,3]);" "\n"
			"function my_callback(str) {" "\n"
			"  my.println(v2.member_function(str));" "\n"
			"}" "\n"
		);

		// callback
		auto cb = (std::function<void(const std::string&)>) context.eval("my_callback");
		cb("world");
	}
	catch (qjs::exception)
	{
		auto exc = context.getException();
		std::cerr << (std::string) exc << std::endl;
		if ((bool)exc["stack"])
			std::cerr << (std::string) exc["stack"] << std::endl;
		//return 1;
	}

}

QuickJSEngine::~QuickJSEngine() {}

void QuickJSEngine::prepareTimeout() const noexcept   { root->timeout = Time::getCurrentTime() + maximumExecutionTime; }
void QuickJSEngine::stop() noexcept                   { root->timeout = {}; }

void QuickJSEngine::registerNativeObject (const Identifier& name, DynamicObject* object)
{
    root->setProperty (name, object);
}

Result QuickJSEngine::execute (const String& code)
{
    try
    {
        prepareTimeout();
        root->execute (code);
    }
    catch (String& error)
    {
        return Result::fail (error);
    }

    return Result::ok();
}

var QuickJSEngine::evaluate (const String& code, Result* result)
{
    try
    {
        prepareTimeout();
        if (result != nullptr) *result = Result::ok();
        return root->evaluate (code);
    }
    catch (String& error)
    {
        if (result != nullptr) *result = Result::fail (error);
    }

    return var::undefined();
}

var QuickJSEngine::callFunction (const Identifier& function, const var::NativeFunctionArgs& args, Result* result)
{
    auto returnVal = var::undefined();

    try
    {
        prepareTimeout();
        if (result != nullptr) *result = Result::ok();
       //TOFILL
		//RootObject::Scope ({}, *root, *root).findAndInvokeMethod (function, args, returnVal);
    }
    catch (String& error)
    {
        if (result != nullptr) *result = Result::fail (error);
    }

    return returnVal;
}

var QuickJSEngine::callFunctionObject (DynamicObject* objectScope, const var& functionObject,
                                          const var::NativeFunctionArgs& args, Result* result)
{
    auto returnVal = var::undefined();

    try
    {
        prepareTimeout();
        if (result != nullptr) *result = Result::ok();

		//TOFILL
       /* RootObject::Scope rootScope ({}, *root, *root);
        RootObject::Scope (&rootScope, *root, DynamicObject::Ptr (objectScope))
            .invokeMethod (functionObject, args, returnVal);
			*/
    }
    catch (String& error)
    {
        if (result != nullptr) *result = Result::fail (error);
    }

    return returnVal;
}

const NamedValueSet& QuickJSEngine::getRootObjectProperties() const noexcept
{
    return root->getProperties();
}

} // namespace quickjs
