/* Copyright 2019-2020 Canaan Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#pragma once
#include "../../node.h"
#include <xtensor/xtensor.hpp>

namespace nncase
{
namespace hlir
{
    namespace k210
    {
        class kpu_upload : public node
        {
        public:
            DEFINE_NODE_OPCODE(op_k210_kpu_upload);

            input_connector &input() { return input_at(0); }
            output_connector &output() { return output_at(0); }

            kpu_upload(shape_t input_shape)
            {
                add_input("input", dt_uint8, input_shape);
                add_output("output", dt_uint8, input_shape, mem_k210_kpu);
            }

            void compile(hlir_compile_context &context) override;
        };

        class kpu_download : public node
        {
        public:
            DEFINE_NODE_OPCODE(op_k210_kpu_download);

            input_connector &input() { return input_at(0); }
            output_connector &output() { return output_at(0); }

            kpu_download(shape_t input_shape)
            {
                add_input("input", dt_uint8, input_shape);
                add_output("output", dt_uint8, input_shape);
            }

            void compile(hlir_compile_context &context) override;
        };
    }
}
}
