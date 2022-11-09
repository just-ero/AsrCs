namespace WasiTesting;

public class Program
{
    public static void Main()
    {
        Console.WriteLine("this is _start");
    }

    public static void Update()
    {
        Asr.TimerSplit();
        Asr.RuntimePrintMessage("FooBar");

        var pId = Asr.ProcessAttach("Notepad.exe");
        Asr.RuntimePrintMessage(pId.ToString("X"));

        while (Asr.ProcessIsOpen(0, pId) != 0)
        {
            Console.WriteLine("Is open.");
        }
    }
}