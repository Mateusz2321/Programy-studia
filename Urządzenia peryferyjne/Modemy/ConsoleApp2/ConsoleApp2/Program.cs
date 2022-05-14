using System;
using System.IO.Ports;  //obsuga portu szeregowego
using System.Threading; //obsługa wątków

namespace ConsoleApp2
{
    class Program
    {
        static SerialPort serialPort = new SerialPort();    //obiekt obsługujący port szeregowy
        static bool ifWork; //zmienna do obsługi głównej pętli

        static void Main(string[] args)
        {

            Thread thread = new Thread(Read); //wątek obsługujący otrzymywanie i wysyłanie wiadomości
            string message;
            StringComparer stringComparer = StringComparer.OrdinalIgnoreCase;
        //ustawienie parametrów modemu
            serialPort.PortName = "COM1";
            serialPort.BaudRate = 9600;
            serialPort.DataBits = 8;
            serialPort.StopBits = StopBits.One;
            serialPort.Parity = Parity.None;
            serialPort.RtsEnable = true;
            serialPort.DtrEnable = true;
            serialPort.ReadTimeout = 3000;
            serialPort.WriteTimeout = 3000;




            serialPort.Open();
            ifWork = true;
            thread.Start();

            while (ifWork)
            {
                if (Console.KeyAvailable)
                {

                    ConsoleKeyInfo name = Console.ReadKey();    //odczytywanie znaku wciśniętego na klawiaturze
                    if (name.KeyChar == '-')                //wciśnięcie "-" kończy działanie programu
                    {
                        ifWork = false;
                    }
                    else
                    {
                        serialPort.Write(String.Format(name.KeyChar.ToString()));   //wysyłanie wiadomości na port
                    }
                }
            }

            thread.Join();
            serialPort.Close();

        }
        public static void Read()
        {
            while (ifWork)
            {
                try
                {
                    string message = serialPort.ReadExisting(); //odczytywanie wiadomości z portu
                    Console.Write(message);         //wyświetlenie wiadomości na konsoli

                }
                catch (TimeoutException) { }
            }
        }


    }
}