/**
 * Copyright 2015 Google Inc. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "field_evaluator.h"

#include "compiler_helpers.h"
#include "dbg_class_property.h"
#include "dbg_object.h"
#include "dbg_stack_frame.h"
#include "error_messages.h"

namespace google_cloud_debugger {

// Maximum depth of inner classes we support to follow the implicit
// chain of references.
static constexpr int kMaxInnerClassesDepth = 10;

FieldEvaluator::FieldEvaluator(
    std::unique_ptr<ExpressionEvaluator> instance_source,
    std::string identifier_name, std::string possible_class_name,
    std::string field_name)
    : instance_source_(std::move(instance_source)),
      identifier_name_(std::move(identifier_name)),
      possible_class_name_(std::move(possible_class_name)),
      field_name_(std::move(field_name)) {}

HRESULT FieldEvaluator::Compile(DbgStackFrame *stack_frame,
                                std::ostream *err_stream) {
  HRESULT hr = CompileInstanceField(stack_frame, err_stream);
  if (SUCCEEDED(hr)) {
    return true;
  }

  hr = CompileStaticField(stack_frame, err_stream);
  if (SUCCEEDED(hr)) {
    return hr;
  }

  return E_FAIL;
}

HRESULT FieldEvaluator::CompileInstanceField(DbgStackFrame *stack_frame,
                                             std::ostream *err_stream) {
  HRESULT hr = instance_source_->Compile(stack_frame, err_stream);
  if (FAILED(hr)) {
    return hr;
  }

  const TypeSignature &instance_source_signature =
      instance_source_->GetStaticType();

  if (instance_source_signature.type_name.empty()) {
    *err_stream << kTypeNameNotAvailable;
    return false;
  }

  return CompileClassMemberHelper(instance_source_signature.type_name,
                                  field_name_, stack_frame, err_stream);
}

HRESULT FieldEvaluator::CompileStaticField(DbgStackFrame *stack_frame,
                                           std::ostream *err_stream) {
  if (possible_class_name_.empty()) {
    return E_FAIL;
  }

  return CompileClassMemberHelper(possible_class_name_, field_name_,
                                  stack_frame, err_stream);
}

HRESULT FieldEvaluator::CompileClassMemberHelper(const std::string &class_name,
                                                 const std::string &member_name,
                                                 DbgStackFrame *stack_frame,
                                                 std::ostream *err_stream) {
  // To find member of a class, we need the corresponding
  // ICorDebugModule and IMetaDataImport of the module that class
  // is in. We will also need the metadata token associated with
  // that class.
  CComPtr<ICorDebugModule> debug_module;
  CComPtr<IMetaDataImport> metadata_import;
  mdTypeDef class_token;

  HRESULT hr = stack_frame->GetClassTokenAndModule(
      class_name, &class_token, &debug_module, &metadata_import);
  if (hr == S_FALSE) {
    return E_FAIL;
  }

  HRESULT hr = stack_frame->GetFieldFromClass(
      class_token, member_name, &result_type_, metadata_import, err_stream);
  if (SUCCEEDED(hr)) {
    return hr;
  }

  hr = stack_frame->GetPropertyFromClass(
      class_token, member_name, &class_property_, metadata_import, err_stream);
  if (FAILED(hr)) {
    return hr;
  }

  return class_property_->GetTypeSignature(&result_type_);
}

HRESULT FieldEvaluator::Evaluate(std::shared_ptr<DbgObject> *dbg_object,
                                 IEvalCoordinator *eval_coordinator,
                                 std::ostream *err_stream) const {
  // TODO(quoct): IMPLEMENT THIS.
  return E_NOTIMPL;
}

}  // namespace google_cloud_debugger
