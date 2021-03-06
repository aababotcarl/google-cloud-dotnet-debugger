// Copyright 2017 Google Inc. All Rights Reserved.
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

#ifndef I_EVAL_COORDINATOR_MOCK_H_
#define I_EVAL_COORDINATOR_MOCK_H_

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "i_eval_coordinator.h"

namespace google_cloud_debugger_test {

// We have to break up methods that have more than 10 parameters since google
// mock cannot mock them.
class IEvalCoordinatorMock : public google_cloud_debugger::IEvalCoordinator {
 public:
  MOCK_METHOD1(CreateEval, HRESULT(ICorDebugEval **eval));

  MOCK_METHOD3(WaitForEval, HRESULT(BOOL *exception_thrown, ICorDebugEval *eval,
                                    ICorDebugValue **eval_result));

  MOCK_METHOD1(SignalFinishedEval, void(ICorDebugThread *debug_thread));

  MOCK_METHOD0(HandleException, void());

  MOCK_METHOD4(
      ProcessBreakpoints,
      HRESULT(
          ICorDebugThread *debug_thread,
          google_cloud_debugger::IBreakpointCollection *breakpoint_collection,
          std::vector<std::shared_ptr<google_cloud_debugger::DbgBreakpoint>> breakpoint,
          const std::vector<std::shared_ptr<
              google_cloud_debugger_portable_pdb::IPortablePdbFile>>
              &pdb_files));

  MOCK_METHOD0(WaitForReadySignal, void());

  MOCK_METHOD0(SignalFinishedPrintingVariable, void());

  MOCK_METHOD1(GetActiveDebugThread, HRESULT(ICorDebugThread **debug_thread));

  MOCK_METHOD1(GetActiveDebugFrame, HRESULT(ICorDebugILFrame **debug_frame));

  MOCK_METHOD0(WaitingForEval, BOOL());

  MOCK_METHOD1(SetPropertyEvaluation, void(BOOL eval));

  MOCK_METHOD0(PropertyEvaluation, BOOL());

  MOCK_METHOD0(MethodEvaluation, BOOL());

  MOCK_METHOD1(SetMethodEvaluation, void(BOOL eval));

  MOCK_METHOD1(CreateStackWalk, HRESULT(ICorDebugStackWalk **debug_stack_walk));
};

}  // namespace google_cloud_debugger_test

#endif  //  I_EVAL_COORDINATOR_MOCK_H_
