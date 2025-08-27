/*
 * Copyright (c) 2025 Analog Devices, Inc.
 * Copyright (c) 2025 Antmicro <www.antmicro.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

extern "C" {
#include <model.h>
#include <zpl/inference_event.h>
}

#include <tensorflow/lite/micro/micro_interpreter.h>
#include <tensorflow/lite/micro/micro_mutable_op_resolver.h>
#include <tensorflow/lite/micro/system_setup.h>
#include <tensorflow/lite/schema/schema_generated.h>

#ifdef CONFIG_ZPL_TFLM_PROFILER
#include <zpl/tflm_profiler.hpp>

static zpl::TFLMProfiler *gp_profiler = nullptr;
#endif /* CONFIG_ZPL_TFLM_PROFILER */

tflite::MicroMutableOpResolver<TFLITE_RESOLVER_SIZE> g_tflite_resolver;
static tflite::MicroInterpreter *gp_interpreter = nullptr;
static tflite::MicroAllocator *gp_allocator = nullptr;

static uint8_t __attribute__((aligned(32))) g_tflite_buffer[CONFIG_ZPL_SAMPLE_TFLM_BUFFER_SIZE * 1024];

void model_init(void)
{
	g_tflite_resolver.AddConv2D();
	g_tflite_resolver.AddFullyConnected();
	g_tflite_resolver.AddMaxPool2D();
	g_tflite_resolver.AddReshape();
	g_tflite_resolver.AddSoftmax();
}

int model_load(const uint8_t *model, uint32_t model_size)
{
	uint8_t *tensor_arena = g_tflite_buffer + model_size;
	uint32_t tensor_arena_size = CONFIG_ZPL_SAMPLE_TFLM_BUFFER_SIZE * 1024 - model_size;

#ifdef CONFIG_ZPL_TFLM_PROFILER
	if (nullptr != gp_profiler) {
		delete gp_profiler;
		gp_profiler = nullptr;
	}
#endif /* CONFIG_ZPL_TFLM_PROFILER */
	if (nullptr != gp_interpreter) {
		delete gp_interpreter;
		gp_interpreter = nullptr;
	}

	memcpy(g_tflite_buffer, model, model_size);

	const tflite::Model *tflite_model = tflite::GetModel(g_tflite_buffer);
	if (tflite_model->version() != TFLITE_SCHEMA_VERSION) {
		return 1;
	}

#ifdef CONFIG_ZPL_TFLM_PROFILER
	gp_profiler = new zpl::TFLMProfiler;
#endif /* CONFIG_ZPL_TFLM_PROFILER */

	gp_allocator = tflite::MicroAllocator::Create(
	    tensor_arena, tensor_arena_size, tflite::MemoryPlannerType::kGreedy);

#ifdef CONFIG_ZPL_TFLM_PROFILER
	gp_interpreter = new tflite::MicroInterpreter(
	    tflite_model, g_tflite_resolver, gp_allocator, nullptr, gp_profiler);
#else /* CONFIG_ZPL_TFLM_PROFILER */
	gp_interpreter = new tflite::MicroInterpreter(
	    tflite_model, g_tflite_resolver, gp_allocator, nullptr);
#endif /* CONFIG_ZPL_TFLM_PROFILER */

#ifdef CONFIG_ZPL_TFLM_PROFILER
	gp_profiler->SetInterpreter(gp_interpreter);
	gp_profiler->SetAllocator(gp_allocator);
#endif /* CONFIG_ZPL_TFLM_PROFILER */

	TfLiteStatus allocate_status = gp_interpreter->AllocateTensors();
	if (allocate_status != kTfLiteOk) {
		return 1;
	}

	return 0;
}

int model_load_input(const uint8_t *input, uint32_t input_size)
{
	TfLiteTensor *model_input = gp_interpreter->input(0);
	if (model_input->bytes != input_size) {
		printk("%d != %d\n", model_input->bytes, input_size);
		return 1;
	}
	memcpy(model_input->data.data, input, model_input->bytes);
	return 0;
}

int model_run(void)
{
#ifdef CONFIG_ZPL_INFERENCE_PROFILING
	zpl_inference_enter();
#endif /* CONFIG_ZPL_INFERENCE_PROFILING */
	TfLiteStatus status = gp_interpreter->Invoke();
#ifdef CONFIG_ZPL_INFERENCE_PROFILING
	zpl_inference_exit();
#endif /* CONFIG_ZPL_INFERENCE_PROFILING */
	if (status != kTfLiteOk) {
		return 1;
	}
#ifdef CONFIG_ZPL_TFLM_PROFILER
	if (nullptr != gp_profiler) {
		gp_profiler->DumpEvents();
	}
#endif /* CONFIG_ZPL_TFLM_PROFILER */

	return 0;
}

int model_get_output(uint8_t *output, uint32_t output_size)
{
	TfLiteTensor *model_output = gp_interpreter->output(0);
	if (model_output->bytes != output_size) {
		return 1;
	}
	memcpy(output, model_output->data.data, model_output->bytes);
	return 0;
}
