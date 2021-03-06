//---------------------------------------------------------------------------
// Copyright (c) 2016 Michael G. Brehm
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//---------------------------------------------------------------------------

#ifndef __STORAGEOBJECTENUMERATOR_H_
#define __STORAGEOBJECTENUMERATOR_H_
#pragma once

#include "ComStorage.h"					// Include ComStorage declarations
#include "ComStream.h"					// Include ComStream declarationss
#include "StorageException.h"			// Include StorageException declarations
#include "StorageExceptions.h"			// Include exception declarations
#include "StorageUtil.h"				// Include StorageUtil declarations

#pragma warning(push, 4)				// Enable maximum compiler warnings

using namespace System;
using namespace System::Collections;
using namespace System::Collections::Generic;

BEGIN_ROOT_NAMESPACE(zuki::storage)

//---------------------------------------------------------------------------
// Forward Class Declarations
//
// Include the specified header files in the .CPP file for this class
//---------------------------------------------------------------------------

ref class StructuredStorage;				// <-- StructuredStorage.h
ref class StorageObject;					// <-- StorageObject.h

//---------------------------------------------------------------------------
// Class StorageObjectEnumerator
//
// StorageObjectEnumerator generates an IEnumerator<> implementation. The
// enumeration is based on a 'snapshot' of the current set of objects
// that are contained within the parent container rather than a cached off
// collection. This allows for much more advanced techniques than were 
// possible with the old collection implementation.
//---------------------------------------------------------------------------

STRUCTURED_STORAGE_PUBLIC ref class StorageObjectEnumerator sealed : 
	public Generic::IEnumerator<StorageObject^>
{
public:

	//-----------------------------------------------------------------------
	// IEnumerator<T> Implementation

	virtual property StorageObject^ Current { StorageObject^ get(void); }
	
	virtual bool MoveNext(void);
	virtual void Reset(void);

internal:

	// INTERNAL CONSTRUCTOR
	StorageObjectEnumerator(StructuredStorage^ root, ComStorage^ storage);

private:

	// DESTRUCTOR / FINALIZER
	~StorageObjectEnumerator() { m_disposed = true; }

	//-----------------------------------------------------------------------
	// Private Member Functions

	virtual property Object^ _Current {
		Object^ get(void) sealed = Collections::IEnumerator::Current::get { return Current; }
	}

	//-----------------------------------------------------------------------
	// Member Variables

	bool						m_disposed;			// Object disposal flag
	StructuredStorage^			m_root;				// Root Storage object
	ComStorage^					m_storage;			// Contained ComStorage
	int							m_current;			// Current item index
	array<Guid>^				m_items;			// Enumerated object guids
};

//---------------------------------------------------------------------------

END_ROOT_NAMESPACE(zuki::storage)

#pragma warning(pop)

#endif	// __STORAGEOBJECTENUMERATOR_H_
