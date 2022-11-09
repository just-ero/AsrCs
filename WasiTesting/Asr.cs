using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;

namespace WasiTesting;

public partial class Asr
{
    [MethodImpl(MethodImplOptions.InternalCall)]
    public static extern uint TimerGetState();

    [MethodImpl(MethodImplOptions.InternalCall)]
    public static extern void TimerStart();

    [MethodImpl(MethodImplOptions.InternalCall)]
    public static extern void TimerSplit();

    [MethodImpl(MethodImplOptions.InternalCall)]
    public static extern void TimerReset();

    [MethodImpl(MethodImplOptions.InternalCall)]
    public static extern void TimerSetVariable(
        string key,
        nuint keyLen,
        string value,
        nuint valueLen);

    [MethodImpl(MethodImplOptions.InternalCall)]
    public static extern void TimerSetGameTime(
        int nanos,
        long secs);

    [MethodImpl(MethodImplOptions.InternalCall)]
    public static extern void TimerPauseGameTime();

    [MethodImpl(MethodImplOptions.InternalCall)]
    public static extern void TimerResumeGameTime();

    [MethodImpl(MethodImplOptions.InternalCall)]
    public static extern ulong ProcessAttach(
        string name);

    [MethodImpl(MethodImplOptions.InternalCall)]
    public static extern void ProcessDetach(
        ulong pId);

    [MethodImpl(MethodImplOptions.InternalCall)]
    public static extern int ProcessIsOpen(
        int _,
        ulong pId);

    [MethodImpl(MethodImplOptions.InternalCall)]
    [return: MarshalAs(UnmanagedType.U8)]
    public static unsafe extern bool ProcessRead(
        ulong pId,
        ulong addr,
        void* buf,
        nuint bufSize);

    [MethodImpl(MethodImplOptions.InternalCall)]
    public static extern ulong ProcessGetModuleAddress(
        ulong pId,
        string moduleName,
        nuint moduleNameLen);

    [MethodImpl(MethodImplOptions.InternalCall)]
    public static extern void RuntimeSetTickRate(
        int _,
        double ticksPerSecond);

    [MethodImpl(MethodImplOptions.InternalCall)]
    public static extern void RuntimePrintMessage(
        string message);
}