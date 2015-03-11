using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsApplication
{
    public partial class Player : Form
    {
        public Player()
        {
            InitializeComponent();
            //mediaPlayer.uiMode = "none";      // 不显示控制按钮
            //mediaPlayer.uiMode = "mini";      // 跟没写一样
            //mediaPlayer.uiMode = "invisible"; // 一个白底的东西
            //mediaPlayer.uiMode = "full";      // 默认的

            //mediaPlayer.settings.rate = 3;    // 快进
        }

        private void bntPickFile_Click(object sender, EventArgs e)
        {
            using (OpenFileDialog dlgOpenFile = new OpenFileDialog())
            {
                dlgOpenFile.Filter = "All Files|*.*";
                if (dlgOpenFile.ShowDialog() == System.Windows.Forms.DialogResult.OK)
                {
                    try
                    {
                        mediaPlayer.URL = dlgOpenFile.FileName;
                        lblPath.Text = dlgOpenFile.FileName;
                    }
                    catch (Exception ex)
                    {
                        MessageBox.Show("Unable to load file\n\n" + ex.Message);    
                    }
                }
            }
        }

        private void bntStop_Click(object sender, EventArgs e)
        {
            mediaPlayer.Ctlcontrols.pause();
        }

        private void bntStart_Click(object sender, EventArgs e)
        {
            mediaPlayer.Ctlcontrols.play();
        }

        private void bntFullScreen_Click(object sender, EventArgs e)
        {
            if (mediaPlayer.URL.Length > 0)
            {
                mediaPlayer.fullScreen = true;
            }
        }

        private void mediaPlayer_PlayStateChange(object sender, AxWMPLib._WMPOCXEvents_PlayStateChangeEvent e)
        {
            if (mediaPlayer.playState == WMPLib.WMPPlayState.wmppsStopped)
            {
                mediaPlayer.Ctlcontrols.play();
            }
        }
    }
}
