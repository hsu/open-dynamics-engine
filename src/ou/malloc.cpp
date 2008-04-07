/*************************************************************************
 *                                                                       *
 * ODER's Utilities Library. Copyright (C) 2008 Oleh Derevenko.          *
 * All rights reserved.  e-mail: olah_daravanko@sourceforge.net          *
 * (change all "a" to "e")                                               *
 *                                                                       *
 * This library is free software; you can redistribute it and/or         *
 * modify it under the terms of EITHER:                                  *
 *   (1) The GNU Lesser General Public License as published by the Free  *
 *       Software Foundation; either version 3 of the License, or (at    *
 *       your option) any later version. The text of the GNU Lesser      *
 *       General Public License is included with this library in the     *
 *       file LICENSE-LESSER.TXT. Since LGPL is the extension of GPL     *
 *       the text of GNU General Public License is also provided for     *
 *       your information in file LICENSE.TXT.                           *
 *   (2) The BSD-style license that is included with this library in     *
 *       the file LICENSE-BSD.TXT.                                       *
 *                                                                       *
 * This library is distributed WITHOUT ANY WARRANTY, including implied   *
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.      *
 * See the files LICENSE.TXT and LICENSE-LESSER.TXT or LICENSE-BSD.TXT   *
 * for more details.                                                     *
 *                                                                       *
 *************************************************************************/

#include <ou/malloc.h>
#include <ou/assert.h>
#include <ou/customization.h>
#include <ou/macros.h>


BEGIN_NAMESPACE_OU();


/*extern*/ void *_OU_CONVENTION_API AllocateMemoryBlock(size_t nBlockSize)
{
	CMemoryAllocationProcedure fnMemoryAllocationProcedure = CMemoryManagerCustomization::GetMemoryAllocationCustomProcedure();
	void *pv_NewBlock = fnMemoryAllocationProcedure(nBlockSize);
	OU_ASSERT(OU_ALIGNED_SIZE((size_t)pv_NewBlock, _OU_MEMORY_REQUIRED_ALIGNMENT) == (size_t)pv_NewBlock); // Memory must be aligned

	return pv_NewBlock;
}

/*extern*/ void *_OU_CONVENTION_API ReallocateMemoryBlock(void *pv_ExistingBlock, size_t nNewBlockSize)
{
	OU_ASSERT(OU_ALIGNED_SIZE((size_t)pv_ExistingBlock, _OU_MEMORY_REQUIRED_ALIGNMENT) == (size_t)pv_ExistingBlock); // Memory must be aligned
	
	CMemoryReallocationProcedure fnMemoryReallocationProcedure = CMemoryManagerCustomization::GetMemoryReallocationCustomProcedure();
	void *pv_NewBlock = fnMemoryReallocationProcedure(pv_ExistingBlock, nNewBlockSize);
	OU_ASSERT(OU_ALIGNED_SIZE((size_t)pv_NewBlock, _OU_MEMORY_REQUIRED_ALIGNMENT) == (size_t)pv_NewBlock); // Memory must be aligned
	
	return pv_NewBlock;
}

/*extern*/ void _OU_CONVENTION_API FreeMemoryBlock(void *pv_ExistingBlock)
{
	OU_ASSERT(OU_ALIGNED_SIZE((size_t)pv_ExistingBlock, _OU_MEMORY_REQUIRED_ALIGNMENT) == (size_t)pv_ExistingBlock); // Memory must be aligned

	CMemoryDeallocationProcedure fnMemoryDeallocationProcedure = CMemoryManagerCustomization::GetMemoryDeallocationCustomProcedure();
	fnMemoryDeallocationProcedure(pv_ExistingBlock);
}


END_NAMESPACE_OU();

