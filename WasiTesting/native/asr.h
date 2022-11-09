#pragma once

#include <mono-wasi/driver.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

/*
    DD
    DDD
    DDDD
    DDI
    DI
    DID
    DIDD
    FF
    FFF
    FFFF
    FFI
    FIF
    FIFF
    I
    II
    III
    IIII
    IIIII
    IIIIII
    IIIIIII
    IIIIIIII
    IIIIIIIII
    IIIIIIIIII
    IIIIL
    IIIL
    IIL
    IILI
    IILIIIL
    IILL
    IILLI
    L
    LI
    LIIIL
    LIL
    LILI
    LILL
    V
    VI
    VII
    VIII
    VIIII
    VIIIII
    VIIIIII
    VIIIIIII
    VIIL
    VL
*/

typedef enum TimerState
{
    /// The timer is not running.
    NOT_RUNNING = 0,
    /// The timer is running.
    RUNNING = 1,
    /// The timer started but got paused. This is separate from the game
    /// time being paused. Game time may even always be paused.
    PAUSED = 2,
    /// The timer has ended, but didn't get reset yet.
    ENDED = 3,
} TimerState;

typedef uint64_t ProcessId;
typedef uint64_t Address;

__attribute__((import_name("timer_get_state"))) TimerState timer_get_state(void);

/// Starts the timer.
__attribute__((import_name("timer_start"))) void timer_start(void);
/// Splits the current segment.
__attribute__((import_name("timer_split"))) void timer_split(void);
/// Resets the timer.
__attribute__((import_name("timer_reset"))) void timer_reset(void);
/// Sets a custom key value pair. This may be arbitrary information that
/// the auto splitter wants to provide for visualization.
__attribute__((import_name("timer_set_variable"))) void timer_set_variable(char const* key_ptr, size_t key_len, char const* value_ptr, size_t value_len);

/// Sets the game time.
__attribute__((import_name("timer_set_game_time"))) void timer_set_game_time(int64_t secs, int32_t nanos);
/// Pauses the game time. This does not pause the timer, only the
/// automatic flow of time for the game time.
__attribute__((import_name("timer_pause_game_time"))) void timer_pause_game_time(void);
/// Resumes the game time. This does not resume the timer, only the
/// automatic flow of time for the game time.
__attribute__((import_name("timer_resume_game_time"))) void timer_resume_game_time(void);

/// Attaches to a process based on its name. Returns 0 if the process can't be
/// found.
__attribute__((import_name("process_attach"))) ProcessId process_attach(char const* name_ptr, size_t name_len);
/// Detaches from a process.
__attribute__((import_name("process_detach"))) void process_detach(ProcessId process);
/// Checks whether is a process is still open. You should detach from a
/// process and stop using it if this returns `false`.
__attribute__((import_name("process_is_open"))) bool process_is_open(ProcessId process);
/// Reads memory from a process at the address given. This will write
/// the memory to the buffer given. Returns `false` if this fails.
__attribute__((import_name("process_read"))) bool process_read(ProcessId process, Address address, void* buf_ptr, size_t buf_len);
/// Gets the address of a module in a process.
__attribute__((import_name("process_get_module_address"))) Address process_get_module_address(ProcessId process, char const* name_ptr, size_t name_len);

/// Sets the tick rate of the runtime. This influences the amount of
/// times the `update` function is called per second.
__attribute__((import_name("runtime_set_tick_rate"))) void runtime_set_tick_rate(double ticks_per_second);
/// Prints a log message for debugging purposes.
__attribute__((import_name("runtime_print_message"))) void runtime_print_message(char const* text_ptr, size_t text_len);

void mono_free(void* _);

bool process_is_open_IIL(int32_t _, ProcessId process) {
    return process_is_open(process);
}

ProcessId process_attach_LI(MonoString* text_ptr) {
    const char* text = mono_string_to_utf8(text_ptr);

    ProcessId pId = process_attach(text, strlen(text));
    mono_free(text);

    return pId;
}

void runtime_print_message_VI(MonoString* text_ptr) {
    const char* text = mono_string_to_utf8(text_ptr);

    runtime_print_message(text, strlen(text));
    mono_free(text);
}

void timer_set_game_time_VIL(int32_t nanos, int64_t secs) {
    timer_set_game_time(nanos, secs);
}

void runtime_set_tick_rate_VID(int32_t _, double ticks_per_second) {
    runtime_set_tick_rate(ticks_per_second);
}