// Copyright 2018 Google Inc. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef DBG_REFERENCE_OBJECT_H_
#define DBG_REFERENCE_OBJECT_H_

#include "dbg_object.h"

namespace google_cloud_debugger {

class IDbgObjectFactory;

// This class represents a .NET object of reference type.
class DbgReferenceObject : public DbgObject {
 public:
  // obj_factory is needed to create members of reference object.
  DbgReferenceObject(ICorDebugType *debug_type, int depth,
                     std::shared_ptr<ICorDebugHelper> debug_helper,
                     std::shared_ptr<IDbgObjectFactory> obj_factory)
      : DbgObject(debug_type, depth, debug_helper),
        object_factory_(obj_factory) {
  }

  // Searches the object for non-static field field_name and returns
  // the value in field_value.
  virtual HRESULT GetNonStaticField(const std::string &field_name,
                                    std::shared_ptr<DbgObject> *field_value);

  // Returns object_handle_.
  virtual HRESULT GetICorDebugValue(ICorDebugValue **debug_value,
                                    ICorDebugEval *debug_eval) override;

  // Returns the underlying ICorDebugHandleValue for this object.
  HRESULT GetDebugHandle(ICorDebugHandleValue **result);

 protected:
  // Handle for the object.
  // Only applicable for class, array and string.
  CComPtr<ICorDebugHandleValue> object_handle_;

  std::shared_ptr<IDbgObjectFactory> object_factory_;
};

}  //  namespace google_cloud_debugger

#endif  //  DBG_OBJECT_H_
