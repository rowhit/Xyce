//-----------------------------------------------------------------------------
// Copyright Notice
//
//   Copyright 2002 Sandia Corporation. Under the terms
//   of Contract DE-AC04-94AL85000 with Sandia Corporation, the U.S.
//   Government retains certain rights in this software.
//
//    Xyce(TM) Parallel Electrical Simulator
//    Copyright (C) 2002-2013  Sandia Corporation
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <http://www.gnu.org/licenses/>.
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Filename       : $RCSfile: N_DEV_DeviceTable.h,v $
//
// Purpose        : Describe the purpose of the contents of the file. If the
//                  contains the header file of a class, provide a clear
//                  description of the nature of the class.
//
// Special Notes  : Specify any "hidden" or subtle details of the class here.
//                  Portability details, error handling information, etc.
//
// Creator        : Eric R. Keiter, SNL, Parallel Computational Sciences
//
// Creation Date  : 02/28/00
//
// Revision Information:
// ---------------------
//
// Revision Number: $Revision: 1.6.2.2 $
//
// Revision Date  : $Date: 2013/10/03 17:23:37 $
//
// Current Owner  : $Author: tvrusso $
//-----------------------------------------------------------------------------

#ifndef Xyce_N_DEV_DeviceTable_h
#define Xyce_N_DEV_DeviceTable_h

#include <N_DEV_Device.h>

namespace Xyce {
namespace Device {

//-----------------------------------------------------------------------------
// Class         : DeviceTable : public Device
// Purpose       : This derived device class exists mainly for the use of
//                 experimental data.  The device's RHS and Jacobian
//                 elements will be determined entirely by numerical tables.
// Special Notes :
// Creator       : Eric Keiter
// Creation Date :
//-----------------------------------------------------------------------------
class DeviceTable : public Device
{
public:
  DeviceTable(SolverState & ss1,
              DeviceOptions & do1);

  DeviceTable(const DeviceTable &right);

  ~DeviceTable();

protected:

private:

private:

};

} // namespace Device
} // namespace Xyce

typedef Xyce::Device::DeviceTable N_DEV_DeviceTable;

#endif

