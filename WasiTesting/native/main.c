#include <mono-wasi/driver.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include "asr.h"

MonoMethod* update_method;

__attribute__((export_name("update"))) void update() {
  if (!update_method) {
    update_method = lookup_dotnet_method("WasiTesting.dll", "WasiTesting", "Program", "Update", -1);
    assert(update_method);
  }

  MonoObject* exception;
  MonoObject* result = mono_wasm_invoke_method(update_method, NULL, NULL, &exception);
  assert(!exception);
}

void attach_internal_calls() {
  mono_add_internal_call("WasiTesting.Asr::TimerGetState", timer_get_state);
  mono_add_internal_call("WasiTesting.Asr::TimerStart", timer_start);
  mono_add_internal_call("WasiTesting.Asr::TimerSplit", timer_split);
  mono_add_internal_call("WasiTesting.Asr::TimerReset", timer_reset);
  mono_add_internal_call("WasiTesting.Asr::TimerSetVariable", timer_set_variable);
  mono_add_internal_call("WasiTesting.Asr::TimerSetGameTime", timer_set_game_time_VIL);
  mono_add_internal_call("WasiTesting.Asr::TimerPauseGameTime", timer_pause_game_time);
  mono_add_internal_call("WasiTesting.Asr::TimerResumeGameTime", timer_resume_game_time);
  mono_add_internal_call("WasiTesting.Asr::ProcessAttach", process_attach_LI);
  mono_add_internal_call("WasiTesting.Asr::ProcessDetach", process_detach);
  mono_add_internal_call("WasiTesting.Asr::ProcessIsOpen", process_is_open_IIL);
  mono_add_internal_call("WasiTesting.Asr::ProcessRead", process_read);
  mono_add_internal_call("WasiTesting.Asr::ProcessGetModuleAddress", process_get_module_address);
  mono_add_internal_call("WasiTesting.Asr::RuntimeSetTickRate", runtime_set_tick_rate_VID);
  mono_add_internal_call("WasiTesting.Asr::RuntimePrintMessage", runtime_print_message_VI);
}
