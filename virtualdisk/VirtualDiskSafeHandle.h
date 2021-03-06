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

#ifndef __VIRTUALDISKSAFEHANDLE_H_
#define __VIRTUALDISKSAFEHANDLE_H_
#pragma once

#pragma warning(push, 4)				// Enable maximum compiler warnings

using namespace System;
using namespace Microsoft::Win32::SafeHandles;

BEGIN_ROOT_NAMESPACE(zuki::storage)

//---------------------------------------------------------------------------
// Class VirtualDiskSafeHandle (internal)
//
// A SafeHandle-dervied class for unmanaged virtual disk handles, use a stack
// insatnce of VirtualDiskSafeHandle::Reference to safely access the HANDLE
// and ensure that the safe handle is not prematurely destroyed
//---------------------------------------------------------------------------

ref class VirtualDiskSafeHandle : public SafeHandleZeroOrMinusOneIsInvalid
{
public:

	// Instance Constructor
	//
	VirtualDiskSafeHandle(HANDLE handle);

	// Class Reference
	//
	// Accesses the unmanaged type referred to by the safe handle
	ref class Reference
	{
	public:

		// Instance Constructor
		//
		Reference(VirtualDiskSafeHandle^ handle);

		// Destructor
		//
		~Reference();

		// HANDLE conversion operator
		//
		operator HANDLE();

	private:

		// Contained VirtualDiskSafeHandle instance
		//
		VirtualDiskSafeHandle^ m_handle;

		// Flag indicating if the safe handle should be released during destruction
		//
		bool m_release = false;
	};

	//-----------------------------------------------------------------------
	// Member Functions

	// ReleaseHandle (SafeHandleZeroOrMinusOneIsInvalid)
	//
	// Frees the unmanaged handle object
	virtual bool ReleaseHandle(void) override;
};

//---------------------------------------------------------------------------

END_ROOT_NAMESPACE(zuki::storage)

#pragma warning(pop)

#endif	// __VIRTUALDISKSAFEHANDLE_H_
