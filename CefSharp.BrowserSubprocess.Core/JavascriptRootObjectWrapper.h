// Copyright � 2010-2014 The CefSharp Project. All rights reserved.
//
// Use of this source code is governed by a BSD-style license that can be found in the LICENSE file.

#pragma once

#include "Stdafx.h"
#include "include/cef_app.h"
#include "include/cef_base.h"
#include "include/cef_v8.h"

#include "JavascriptObjectWrapper.h"

using namespace System::Linq;
using namespace System::Collections::Generic;

using namespace CefSharp::Internals;

namespace CefSharp
{
    public ref class JavascriptRootObjectWrapper
    {
    private:
        JavascriptRootObject^ _rootObject;
        List<JavascriptObjectWrapper^>^ _wrappedObjects;

    internal:
        MCefRefPtr<CefV8Value> V8Value;

    public:
        JavascriptRootObjectWrapper(JavascriptRootObject^ rootObject)
        {
            _rootObject = rootObject;
            _wrappedObjects = gcnew List<JavascriptObjectWrapper^>();
        }
        
        void Bind()
        {
            auto memberObjects = _rootObject->MemberObjects;
            for each (JavascriptObject^ obj in Enumerable::OfType<JavascriptObject^>(memberObjects))
            {
                auto wrapperObject = gcnew JavascriptObjectWrapper(obj);
                wrapperObject->V8Value = V8Value;
                wrapperObject->Bind();

                _wrappedObjects->Add(wrapperObject);
            }
        };
    };
}

