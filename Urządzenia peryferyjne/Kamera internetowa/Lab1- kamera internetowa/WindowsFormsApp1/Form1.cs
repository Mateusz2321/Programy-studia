using System;
using System.Collections;
using System.Drawing;
using System.Windows.Forms;
using System.Runtime.InteropServices;

namespace WindowsFormsApp1
{
    public partial class Form1 : Form
    {
        public Form1()  //Konstruktor klasy Form1
        {
            InitializeComponent();
        }       
        WebCam oWebCam;
        ArrayList list = new ArrayList();  //Lista przechowuje informacje o dostępnych urządzeniach
        /*
         * Procedura obsługuje zdarzenia związane z przyciśnięciem
         * przycisku Start Camera.
         */
        private void button4_Click(object sender, EventArgs e)
        {       
            oWebCam.OpenConnection(); //Otwarcie połączenia z wybranym wcześniej urządzeniem
        }
        /*
         * Procedura obsługuje zdarzenia związane z przyciśnięciem
         * przycisku Stop Camera.
         */
        private void button2_Click(object sender, EventArgs e)
        {
            oWebCam.Dispose(); //Zamknięcie połączenia z urządzeniem.
        }
        /*
         * Procedura obsługi przycisku Save picture
         */ 
        private void btnSave_Click_1(object sender, EventArgs e)
        {
            oWebCam.SaveImage();                                   //Wywołanie procedury umożliwiającej zapis obrazu do pliku

        }
        /*
         * Procedura jest wywoływana przy starcie okna programu.
         * Wykonuje wszelkie niezbędne inicjalizacje.
         */ 
        private void Form1_Load_1(object sender, EventArgs e)
        {
            oWebCam = new WebCam();                     //Stworzenie obiektu klasy WebCam
            oWebCam.Container = pictureBox1;            
            oWebCam.Load();                             
            list = oWebCam.listOfDevices();             //Pobranie listy dostępnych urządzeń
            for (int i = 0; i < list.Count; i++)
                comboBox1.Items.Add(list[i]);           //Dodanie urządzeń do listy

            oWebCam.setID(comboBox1.SelectedIndex);     //Ustawienie ID urządzenia do przechwytywania

        }
        /*
         * Obsługa operacji wyboru elementu z listy rozwijanej.
         */ 
        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            oWebCam.setID(comboBox1.SelectedIndex); //Ustawienie ID urządzenia do przechwytywania
        }       
        /*
         * Obsługa przycisku pozwalającego na zmianę rozdzielczości obrazu.
         */ 
        private void btnDisplay_Click(object sender, EventArgs e)
        {
            oWebCam.setDisplayParameters();                 //Modyfikacja rozdzielczości
        }
        /*
         * Obsługa przycisku pozwalającego na zmianę jasności, kontrastu i innych parametrów obrazu.
         */
        private void button2_Click_2(object sender, EventArgs e)
        {
            oWebCam.setDisplayParameters2();                //Modyfikacja jasności, kontrastu i innych parametrów obrazu
        }
    }
    public class WebCam : IDisposable
    {
        //Używane stałe
        private const short WM_CAP = 0x400;
        private const int WM_CAP_DRIVER_CONNECT = 0x40a;
        private const int WM_CAP_DRIVER_DISCONNECT = 0x40b;
        private const int WM_CAP_EDIT_COPY = 0x41e;
        private const int WM_CAP_SET_PREVIEW = 0x432;
        private const int WM_CAP_DLG_VIDEOFORMAT = WM_CAP + 41;
        private const int WM_CAP_DLG_VIDEOSOURCE = WM_CAP + 42;
        private const int WM_CAP_SET_PREVIEWRATE = 0x434;
        private const int WM_CAP_SET_SCALE = 0x435;
        private const int WS_CHILD = 0x40000000;
        private const int WS_VISIBLE = 0x10000000;
        private const short SWP_NOMOVE = 0x2;
        private short SWP_NOZORDER = 0x4;
        private short HWND_BOTTOM = 1;

        //Funkcja umożliwia wyliczenie dostępnych kamer internetowych
        [System.Runtime.InteropServices.DllImport("avicap32.dll")]
        protected static extern bool capGetDriverDescriptionA(short wDriverIndex,
            [MarshalAs(UnmanagedType.VBByRefStr)]ref String lpszName,
           int cbName, [MarshalAs(UnmanagedType.VBByRefStr)] ref String lpszVer, int cbVer);

        //Ta funkcja umożliwia utworzenie okna potomnego
        [DllImport("avicap32.dll")]
        protected static extern int capCreateCaptureWindowA([MarshalAs(UnmanagedType.VBByRefStr)] ref string
    lpszWindowName,
            int dwStyle, int x, int y, int nWidth, int nHeight, int hWndParent, int nID);

        //Ta funkcja umożliwia ustawianie zmian rozmiaru i pozycji okna potomnego
        [DllImport("user32")]
        protected static extern int SetWindowPos(int hwnd, int hWndInsertAfter, int x, int y, int cx, int cy, int wFlags);

        //Funkcja umożliwia wysłanie określonej wiadomości do okna lub okien
        [DllImport("user32", EntryPoint = "SendMessageA")]
        protected static extern int SendMessage(int hwnd, int wMsg, int wParam, [MarshalAs(UnmanagedType.AsAny)] object
    lParam);

        //Funkcja umożliwia zamknięcie okna potomnego
        [DllImport("user32")]
        protected static extern bool DestroyWindow(int hwnd);
      
  
        //ID używanego urządzenia
        int DeviceID = 0;
        //Uchwyt do poprzedniego okna
        int hHwnd = 0;

        //Lista urządzeń      
        public ArrayList ListOfDevices = new ArrayList();
        /*
         * Funkcja zwraca listę dostępnych urządzeń.
         */
        public ArrayList listOfDevices()
        {
            return ListOfDevices;
        }
        /*
         * Funkcja umożliwia ustawienie id urządzenia, które wybrał użytkownik.
         */
        public void setID(int id)
        {
            DeviceID = id;
        }
        /*
         * Procedura zajmuje się wyświetlaniem okna dialogowego, umożliwiającego między innymi zmianę rozdzielczości obrazu.
         */ 
        public void setDisplayParameters()
        {
            SendMessage(hHwnd, WM_CAP_DLG_VIDEOFORMAT, DeviceID, 0);   
            
        }
        /*
         * Procedura zajmuje się wyświetlaniem okna dialogowego, umożliwiającego między innymi zmianę kontrastu, nasycenia i innych parametrów.
         */ 
        public void setDisplayParameters2()
        {
            SendMessage(hHwnd, WM_CAP_DLG_VIDEOSOURCE, DeviceID, 0);                 

        }
        //Obraz, który będzie wyświetlany
        public PictureBox Container { get; set; }

       /*
        * Funkcja pobiera listę wszystkich dostępnych urządzeń.
        */
        public void Load()
        {
            string Name = String.Empty.PadRight(100);
            string Version = String.Empty.PadRight(100);
            bool EndOfDeviceList = false;
            short index = 0;

            //Zapisanie wszystkich dostępnych urządzeń do listy
            do
            {
                // Pobranie nazwy urządzenia i wersji
                EndOfDeviceList = capGetDriverDescriptionA(index, ref Name, 100, ref Version, 100);
                //Jeśli urządzenie zostało znalezione, dodajemy nazwę urządzenia do listy
                if (EndOfDeviceList) ListOfDevices.Add(Name.Trim());
                index += 1;
            }
            while (!(EndOfDeviceList == false));
        }

        /*
         * Procedura jest używana do połączenia z urządzeniem oraz wyświetlania
         * obrazu z kamery w aplikacji.
         */ 
        public void OpenConnection()
        {
            string DeviceIndex = Convert.ToString(DeviceID);
            IntPtr oHandle = Container.Handle;          

            //Stworzenie okna przechwytywania
            hHwnd = capCreateCaptureWindowA(ref DeviceIndex, WS_VISIBLE | WS_CHILD, 0, 0, 640, 480, oHandle.ToInt32(), 0);

            //Połączenie z urządzeniem
            if (SendMessage(hHwnd, WM_CAP_DRIVER_CONNECT, DeviceID, 0) != 0)    //Połączenie z urządzeniem
            {
                //Ustawienie skali podglądu
                SendMessage(hHwnd, WM_CAP_SET_SCALE, -1, 0);
                //Ustawienie częstotliwości pobierania obrazu z kamery
                SendMessage(hHwnd, WM_CAP_SET_PREVIEWRATE, 66, 0);

                // Rozpoczęcie przechwytywania obrazu z kamery
                SendMessage(hHwnd, WM_CAP_SET_PREVIEW, -1, 0);

                // Zmiana rozmiaru okna, aby zmieściło się w polu na zdjęcia
                SetWindowPos(hHwnd, HWND_BOTTOM, 0, 0, Container.Height, Container.Width, SWP_NOMOVE | SWP_NOZORDER);     
        }
            else
            {
                //Zamknięcie okna ze względu na błąd łączenia z urządzeniem
                DestroyWindow(hHwnd);
            }
        }

        //Zamykanie połączenia z kamerą
        void CloseConnection()

        {
            SendMessage(hHwnd, WM_CAP_DRIVER_DISCONNECT, DeviceID, 0);
            //Zamknięcie okna
            DestroyWindow(hHwnd);
        }

        /*
         * Procedura umożliwia zapis aktualnego obrazu z kamery do pliku 
         */ 
        public void SaveImage()
        {
            IDataObject data;
            Image oImage;
            SaveFileDialog sfdImage = new SaveFileDialog();
            sfdImage.Filter = "(*.bmp)|*.bmp";
            //Skopiowanie obrazu do schowka
            SendMessage(hHwnd, WM_CAP_EDIT_COPY, 0, 0);

            //Pobranie obrazu ze schowka i przekonwertowanie go na bitmapę
            data = Clipboard.GetDataObject();
            if (data.GetDataPresent(typeof(System.Drawing.Bitmap)))
            {
                oImage = (Image)data.GetData(typeof(System.Drawing.Bitmap));
                Container.Image = oImage;
                CloseConnection();                                                          //Zamknięcie połączenia
                if (sfdImage.ShowDialog() == DialogResult.OK)
                {
                    oImage.Save(sfdImage.FileName, System.Drawing.Imaging.ImageFormat.Bmp); //Zapis do pliku
                }
            }
        }

        /*
         * Procedura obsługuje zamknięcie okna przez użytkownika.
         * Pochodzi z interfejsu IDisposable.
         * Zamyka połączenie z kamerą przed zamknięciem okna.
         */ 
        #region IDisposable Members

        public void Dispose()

        {
            CloseConnection();  //Wywołanie procedury zamykającej połączenie
        }
        #endregion
    }
    
}

