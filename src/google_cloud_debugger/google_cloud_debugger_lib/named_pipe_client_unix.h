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

#ifdef PLATFORM_UNIX

#ifndef NAMED_PIPE_CLIENT_H_
#define NAMED_PIPE_CLIENT_H_

#include <string>

#include "i_named_pipe.h"
#include "constants.h"

namespace google_cloud_debugger {

// A named pipe client for unix.
class NamedPipeClient : public INamedPipe {
 public:
  NamedPipeClient(std::string pipe_name);
  ~NamedPipeClient();
  HRESULT Initialize() override;
  HRESULT WaitForConnection() override;
  HRESULT Read(std::string *message) override;
  HRESULT Write(const std::string &message) override;
  HRESULT ShutDown() override;

 private:
  // The name of the pipe.
  std::string pipe_name_;

  // The socket descriptor for the pipe.
  int pipe_ = -1;
};

}  // namespace google_cloud_debugger

#endif  //  NAMED_PIPE_CLIENT_H_
#endif  //  PLATFORM_UNIX
