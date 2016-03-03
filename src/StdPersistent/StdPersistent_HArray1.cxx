// Copyright (c) 2015 OPEN CASCADE SAS
//
// This file is part of Open CASCADE Technology software library.
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License version 2.1 as published
// by the Free Software Foundation, with special exception defined in the file
// OCCT_LGPL_EXCEPTION.txt. Consult the file LICENSE_LGPL_21.txt included in OCCT
// distribution for complete text of the license and disclaimer of any warranty.
//
// Alternatively, this file may be used under the terms of Open CASCADE
// commercial license or contractual agreement.

#include <StdPersistent_HArray1.hxx>
#include <StdObjMgt_ReadData.hxx>


void StdPersistent_HArray1::Shape1::readValue (StdObjMgt_ReadData& theReadData,
                                               const Standard_Integer theIndex)
{
  theReadData.ReadObject (myArray->ChangeValue (theIndex));
}