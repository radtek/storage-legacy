//-----------------------------------------------------------------------------
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
//-----------------------------------------------------------------------------

#ifndef __VIRTUALDISKSOURCEDISKPARAMETERS_H_
#define __VIRTUALDISKSOURCEDISKPARAMETERS_H_
#pragma once

#include "VirtualDiskStorageType.h"

#pragma warning(push, 4)				// Enable maximum compiler warnings

using namespace System;
using namespace System::IO;

BEGIN_ROOT_NAMESPACE(zuki.storage)

//---------------------------------------------------------------------------
// Class VirtualDiskSourceDiskParameters
//
// Contains information about a source disk when creating a new virtual disk
//---------------------------------------------------------------------------

public ref class VirtualDiskSourceDiskParameters sealed
{
public:

	//-----------------------------------------------------------------------
	// Properties

	// Path
	//
	// Gets/sets the fully qualified path to the source disk object
	property String^ Path
	{
		String^ get(void) { return m_path; }
		void set(String^ value) 
		{ 
			if(!String::IsNullOrEmpty(value) && !System::IO::Path::IsPathRooted(value)) 
				throw gcnew ArgumentException("path must be fully qualified", "value");
			m_path = value; 
		}
	}

	// PreventWrites
	//
	// Flag that indicates the source disk should be locked read-only
	// while the new disk is being created
	property bool PreventWrites
	{
		bool get(void) { return m_preventWrites; }
		void set(bool value) { m_preventWrites = value; }
	}

	// Type
	//
	// Gets/sets the virtual disk type of the source disk object
	property VirtualDiskStorageType Type
	{
		VirtualDiskStorageType get(void) { return m_storageType; }
		void set(VirtualDiskStorageType value) { m_storageType = value; }
	}

internal:

	// INTERNAL CONSTRUCTOR
	VirtualDiskSourceDiskParameters() 
	{
		m_path = String::Empty;
		m_storageType = VirtualDiskStorageType::Auto;
		m_preventWrites = true;
	}

private:

	//-----------------------------------------------------------------------
	// Member Variables

	String^						m_path;
	VirtualDiskStorageType		m_storageType;
	bool						m_preventWrites;
};

//---------------------------------------------------------------------------

END_ROOT_NAMESPACE(zuki.storage)

#pragma warning(pop)

#endif	// __VIRTUALDISKSOURCEDISKPARAMETERS_H_
