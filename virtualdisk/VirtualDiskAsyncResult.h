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

#ifndef __VIRTUALDISKASYNCRESULT_H_
#define __VIRTUALDISKASYNCRESULT_H_
#pragma once

#pragma warning(push, 4)				// Enable maximum compiler warnings

using namespace System;
using namespace System::ComponentModel;
using namespace System::Threading;

BEGIN_ROOT_NAMESPACE(zuki::storage)

// FORWARD DECLARATIONS
//
enum class	VirtualDiskAsyncOperation;
ref class	VirtualDiskSafeHandle;

//---------------------------------------------------------------------------
// Class VirtualDiskAsyncResult (internal)
//
// IAsyncResult-based object used to manage the asynchronous calls to virtual
// disk API functions
//---------------------------------------------------------------------------

ref class VirtualDiskAsyncResult : IAsyncResult
{
public:

	// Instance Constructor
	//
	VirtualDiskAsyncResult(VirtualDiskSafeHandle^ handle, ManualResetEvent^ waithandle, NativeOverlapped* overlapped,
		CancellationToken cancellation, IProgress<int>^ progress);

	//-----------------------------------------------------------------------
	// Member Functions

	// CompleteAsynchronously (static)
	//
	// Completes the operation asynchronously
	static void CompleteAsynchronously(IAsyncResult^ asyncresult);

	// CompleteSynchronously
	//
	// Completes the operation synchronously
	void CompleteSynchronously(unsigned int status);

	//-----------------------------------------------------------------------
	// Properties

	// AsyncState (IAsyncResult)
	//
	// Gets a user-defined object that qualifies the asynchronous operation
	property Object^ AsyncState
	{
		virtual Object^ get(void);
	}

	// AsyncWaitHandle (IAsyncResult)
	//
	// Gets a WaitHandle that is used to wait for an asynchronous operation to complete
	property WaitHandle^ AsyncWaitHandle
	{
		virtual WaitHandle^ get(void);
	}

	// CompletedSynchronously (IAsyncResult)
	//
	// Gets a value that indicates whether the asynchronous operation completed synchronously
	property bool CompletedSynchronously
	{
		virtual bool get(void);
	}

	// IsCompleted (IAsyncResult)
	//
	// Gets a value that indicates whether the asynchronous operation has completed
	property bool IsCompleted
	{
		virtual bool get(void);
	}

private:

	//-----------------------------------------------------------------------
	// Private Member Functions

	// Cancel
	//
	// Attempts to cancel the operation
	void Cancel(void);

	// Complete
	//
	// Completes the operation
	void Complete(void);

	// ProgressThread
	//
	// Thread entry point for progress reporting
	void ProgressThread(void);

	//-----------------------------------------------------------------------
	// Member Variables

	VirtualDiskSafeHandle^			m_handle;			// Virtual disk safe handle
	ManualResetEvent^				m_waithandle;		// Operation wait handle
	NativeOverlapped*				m_overlapped;		// Native OVERLAPPED data
	bool							m_synchronous;		// Flag for synchronous completion
	int								m_completed;		// Flag if operation completed
	CancellationTokenRegistration	m_cancelreg;		// Cancellation token registration
	IProgress<int>^					m_progress;			// Progress callback
	Thread^							m_progressthread;	// Progress worker thread
};

//---------------------------------------------------------------------------

END_ROOT_NAMESPACE(zuki::storage)

#pragma warning(pop)

#endif	// __VIRTUALDISKASYNCRESULT_H_
