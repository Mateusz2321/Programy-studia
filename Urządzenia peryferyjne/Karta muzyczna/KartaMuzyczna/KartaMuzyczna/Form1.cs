using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using WMPLib;
//using NAudio;
//using WaveStream;
//using SharpDX.Multimedia;
//using SharpDX;
//using SharpDX.DirectSound;
//using SharpDX.;
namespace KartaMuzyczna
{
    


    public partial class Form1 : Form
    {
        [DllImport("winmm.dll")]
        private static extern long mciSendString(string command, string pointerToReturnMessage,int size,int pointer);

        private string pathToFile = "";
        private int ChunkSize,Subchunk1Size, Subchunk2Size,SampleRate, ByteRate;
        private short AudioFormat, NumChannels, BlockAlign, BitsPerSample;
        private bool play = false,  pause = false,record=false;
        WMPLib.WindowsMediaPlayer wmp=new WindowsMediaPlayer();
        private bool WMP_play = false, WMP_pause = false, WMP_record = false;
        //NAudio.Wave.IWavePlayer waveOutDevice;  //NAudio
        //NAudio.Wave.AudioFileReader audioFileReader;                        //NAudio   XAudio2
        //SharpDX.XAudio2.AudioBuffer audioBuffer;
        //SharpDX.XAudio2.SourceVoice sourceVoice;
       
        private void button6_MouseClick(object sender, MouseEventArgs e)    //DirectX stop
        {
            // audioBuffer.Stream;
            //sourceVoice.ProcessingPassStart();


            //sourceVoice.SubmitSourceBuffer(audioBuffer,0);



            ////SharpDX.Direct3D.Blob blob = new SharpDX.Direct3D.Blob();
            ////SharpDX.DataStream stream = new SharpDX.DataStream(blob);
            ////audioBuffer = new SharpDX.XAudio2.AudioBuffer(stream);
            //audioBuffer.AudioData = reader;
            //audioBuffer.Stream = reader;
            //SharpDX.XAudio2.
            //SharpDX.
            //sourceVoice=new SharpDX.XAudio2.SourceVoice()
           // var xaudio2 = new XAudio2();
           // var masteringVoice = new MasteringVoice(xaudio2);
          //  SharpDX.XAudio2.XAudio2  device= new SharpDX.XAudio2.XAudio2();// = new DeviceDetails();
           // var stream = new SoundStream(File.OpenRead(pathToFile));
          //  var waveFormat = stream.Format;
            //var buffer = new AudioBuffer
            //{
            // Stream = stream.ToDataStream(),
            // AudioBytes = (int)stream.Length,
            // Flags = BufferFlags.EndOfStream
            // };
           // var buffer = new AudioBuffer();
            //stream.Close();
            //var sourceVoice = new SourceVoice(device, waveFormat, true);
            //sourceVoice.SubmitSourceBuffer(buffer, stream.DecodedPacketsInfo);


           // sourceVoice.Start();
            
        }

        private void button10_MouseClick(object sender, MouseEventArgs e)   //DirectX pause
        {

        }

        private void button5_MouseClick(object sender, MouseEventArgs e)    //WaveOutWrite start
        {
            if (pathToFile.Length > 0)
            {
              //  waveOutDevice = new NAudio.Wave.WaveOut();
              //  audioFileReader = new NAudio.Wave.AudioFileReader(pathToFile);
               // waveOutDevice.Init(audioFileReader);
               // waveOutDevice.Play();


            }     
            

        }

        private void button4_MouseClick(object sender, MouseEventArgs e)    //WaveOut stop
        {
           //// waveOutDevice.Stop();
          //  waveOutDevice.Dispose();

        }

        private void button9_MouseClick(object sender, MouseEventArgs e)    //WaveOut pause
        {

        }

        private void button8_MouseClick(object sender, MouseEventArgs e)    //Wwindows Media PLayer start
        {
            if (WMP_play == false && pathToFile.Length>0)
            {
                wmp.URL = pathToFile;
               
                wmp.controls.play();
                WMP_play = true;
            }
            



        }

        private void button7_MouseClick(object sender, MouseEventArgs e)    //Windows Media Player stop
        {
            if (WMP_play == true)
            {
                wmp.controls.stop();
                WMP_play = false;
            }
            
        }

        private void button11_MouseClick(object sender, MouseEventArgs e)   //Windows media player pause
        {
            if (WMP_play == true)
            {
                if (WMP_pause == false)
                {
                    wmp.controls.pause();
                    WMP_pause = true;
                    button11.Text = "Resume";
                }
                else
                {
                    wmp.controls.play();
                    WMP_pause = false;
                   button11.Text = "Pause";
                }
               
            }
            
        }

        private void button12_MouseClick(object sender, MouseEventArgs e)   //mci start
        {
            if (pathToFile.Length > 0 && play==false)
            {
                string com = "Open \"" + pathToFile + "\" alias wavFile";
                mciSendString(com, null, 0, 0);
                com = "Play wavFile";
                mciSendString(com, null, 0, 0);
                play = true;
            }
            



        }

        private void button13_MouseClick(object sender, MouseEventArgs e)   //mci stop
        {
            if(pathToFile.Length > 0)
            {
                if (play == true)
                {
                    string com = "Close wavFile";
                    mciSendString(com, null, 0, 0);
                    play = false;
                }
            }
          

        }

        private void button14_MouseClick(object sender, MouseEventArgs e)   //mci pauses
        {
            if (pathToFile.Length > 0)
            {
                if (pause == false)
                {
                    string com = "Pause wavFile";
                    mciSendString(com, null, 0, 0);
                    pause = true;
                    button14.Text = "Resume";
                }
                else
                {
                    string com = "Play wavFile";
                    mciSendString(com, null, 0, 0);
                    pause = false;
                    button11.Text = "Pause";
                }
            }   
        }

        private void button15_MouseClick(object sender, MouseEventArgs e)   //start record mci
        {
            if (record == false)
            {
                mciSendString("open new Type waveaudio Alias rec", "", 0, 0);
                mciSendString("record rec", "", 0, 0);
                richTextBox1.AppendText("Nagrywanie rozpoczęte\n");
                record = true;
            }
           
        }

        private void button16_MouseClick(object sender, MouseEventArgs e)   // stop record mci
        {
            if (record == true)
            {
                mciSendString("stop rec", "", 0, 0);
                SaveFileDialog d = new SaveFileDialog();    //////////////////////////////////////////////////////////////
                d.Filter = "Audio files (.wav)|*.wav";      //Ścieżka do pliku nie może zawierać spacji, bo wtedy nie działa.
                if (d.ShowDialog() == DialogResult.OK)      //////////////////////////////////////////////////////////////
                {
                    string savePath = d.FileName;
                    richTextBox1.AppendText( savePath + "\n");
                    string com = "save rec " + savePath;
                    mciSendString(com, "", 0, 0);
                    richTextBox1.AppendText("Nagrywanie zakończone\n");
                    richTextBox1.AppendText("Zapisano w pliku " + savePath + "\n");
                }else richTextBox1.AppendText("Nagrywanie zakończone\n");
                mciSendString("close rec ", "", 0, 0);
                record = false;
            }           
        }

        private void button2_MouseClick(object sender, MouseEventArgs e)    //DirectX start
        {

        }

        private string ChunkID,Format,Subchunk1ID,Subchunk2ID;


        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void button3_Click(object sender, EventArgs e)  //Wyświetlanie nagłówka pliku wav
        {
            if (pathToFile.Length > 0)
            {

                FileStream fileStream = new FileStream(pathToFile, FileMode.Open, FileAccess.Read);
                BinaryReader reader = new BinaryReader(fileStream);
                byte[] waveHeader = reader.ReadBytes(44);
                fileStream.Position = 0;

                var temp = Encoding.Default.GetString(waveHeader);
                richTextBox1.AppendText("Nagłówek pliku wav:\n");
                ChunkID = temp.Substring(0,4);
                richTextBox1.AppendText("ChunkID: " + ChunkID + "\n");
                ChunkSize = reader.ReadInt32();
               // byte[] bytes = BitConverter.GetBytes(ChunkSize);
               // Array.Reverse(bytes, 0, bytes.Length);
                //ChunkSize = BitConverter.ToInt32(bytes);
                richTextBox1.AppendText("ChunkSize: " + ChunkSize.ToString() + "\n");
                Format = temp.Substring(8, 4);
                richTextBox1.AppendText("Format: " + Format + "\n");
                Subchunk1ID = temp.Substring(12, 4);
                richTextBox1.AppendText("Subchunk1ID: " + Subchunk1ID + "\n");
                fileStream.Position=16;
                Subchunk1Size = reader.ReadInt32();
               
                //bytes = BitConverter.GetBytes(Subchunk1Size);
                //Array.Reverse(bytes, 0, bytes.Length);
                //Subchunk1Size = BitConverter.ToInt32(bytes);
             
                richTextBox1.AppendText("Subchunk1Size: " + Subchunk1Size + "\n");
                AudioFormat = reader.ReadInt16();
                richTextBox1.AppendText("AudioFormat: " + AudioFormat.ToString() + "\n");
                NumChannels = reader.ReadInt16();
                richTextBox1.AppendText("NumChannels: " + NumChannels.ToString() + "\n");
                SampleRate = reader.ReadInt32();
                richTextBox1.AppendText("SampleRate: " + SampleRate.ToString() + "\n");
                ByteRate = reader.ReadInt32();
                richTextBox1.AppendText("ByteRate: " + ByteRate.ToString() + "\n");
                BlockAlign = reader.ReadInt16();
                richTextBox1.AppendText("BlockAlign: " + BlockAlign.ToString() + "\n");
                BitsPerSample = reader.ReadInt16();
                richTextBox1.AppendText("BitsPerSample: " + BitsPerSample.ToString() + "\n");
                Subchunk2ID = temp.Substring(36, 4);
                richTextBox1.AppendText("Subchunk2ID: " + Subchunk2ID + "\n");
                fileStream.Position = 40;
                Subchunk2Size = reader.ReadInt32();
               // bytes = BitConverter.GetBytes(Subchunk2Size);
                //Array.Reverse(bytes, 0, bytes.Length);
                //Subchunk2Size = BitConverter.ToInt32(bytes);
                richTextBox1.AppendText("Subchunk2Size: " + Subchunk2Size.ToString() + "\n");

                reader.Close();

            }
            else richTextBox1.AppendText("Nie wybrano żadnego pliku!\n");
        }

        private void button1_Click(object sender, EventArgs e)  //Wybór pliku
        {
            OpenFileDialog wavFile = new OpenFileDialog();
            wavFile.Filter = "Audio files (.wav)|*.wav";
            if(wavFile.ShowDialog() == DialogResult.OK)
            {
                pathToFile = wavFile.FileName;
                richTextBox1.AppendText("Wybrany plik:\n");
                richTextBox1.AppendText(pathToFile + "\n");
            }




        }
    }
}
