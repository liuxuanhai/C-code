using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Collections;
using System.IO;

namespace WindowsApplication
{
    public partial class HeabPlayer1 : Form
    {
        public HeabPlayer1()
        {
            InitializeComponent();
            //axWindowsMediaPlayer1.uiMode = "mini";
            axWindowsMediaPlayer1.settings.autoStart = false;
        }

                // 创建播放列表

        private void createPlayList(int begin)
        {
            // 把文件们放到新建的播放列表中

            WMPLib.IWMPPlaylist playlist = axWindowsMediaPlayer1.playlistCollection.newPlaylist("HeabPlayList");
            WMPLib.IWMPMedia media;

            for (int i = begin; i < lbSongsList.Items.Count; i++)
            {
                media = axWindowsMediaPlayer1.newMedia(lbSongsList.Items[i].SubItems[1].Text);
                playlist.appendItem(media);

                axWindowsMediaPlayer1.currentPlaylist = playlist;
                //axWindowsMediaPlayer1.Ctlcontrols.play();
            }
        }

        private void bntAdd_Click(object sender, EventArgs e)
        {
                // 将选择的文件名放到ListBox中

            Stream myStream = null;
            if (opendSongsFileDialog.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                try
                {
                    if ((myStream = opendSongsFileDialog.OpenFile()) != null)
                    {
                        string[] fileNameAndPath = opendSongsFileDialog.FileNames;
                        string[] fileName = opendSongsFileDialog.SafeFileNames;
                        for (int i = 0; i < opendSongsFileDialog.SafeFileNames.Count(); i++)
                        {
                            string [] listViewItem = new string[2];
                            listViewItem[0] = fileName[i];
                            listViewItem[1] = fileNameAndPath[i];
                            ListViewItem lv1 = new ListViewItem(listViewItem);
                            lbSongsList.Items.Add(lv1);
                        }
                    }
                }
                catch (Exception)
                {
                    MessageBox.Show("无法打开文件!!!");
                }
                
            }
            createPlayList(0);
        }
        int curPlaying  = -1;
        private void lbSongsList_DoubleClick(object sender, EventArgs e)
        {
            string selectedFile = lbSongsList.FocusedItem.SubItems[1].Text;
            axWindowsMediaPlayer1.URL = @selectedFile;
            createPlayList(lbSongsList.FocusedItem.Index);
            axWindowsMediaPlayer1.Ctlcontrols.play();

            curPlaying = lbSongsList.FocusedItem.Index - 1;
        }

        #region 关于...

        private void 关于ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            P170AboutForm about = new P170AboutForm();
            about.lblMainText = "HeabPlayer1.0";
            about.Show();
        }
        #endregion

        int flag = 0;
        private void axWindowsMediaPlayer1_PlayStateChange(object sender, AxWMPLib._WMPOCXEvents_PlayStateChangeEvent e)
        {
            if (axWindowsMediaPlayer1.playState == WMPLib.WMPPlayState.wmppsPlaying)
            {
                flag = 1;   // 放一个标志位, 确保wmppsTransitioning消息不是添加的时候给的而是播放以后给的
                curPlaying = (++curPlaying) % lbSongsList.Items.Count;
                lbSongsList.Items[curPlaying].BackColor  = Color.LightSteelBlue;    // 改变当前项
            }
            else if (axWindowsMediaPlayer1.playState == WMPLib.WMPPlayState.wmppsMediaEnded
                    || (flag == 1 && axWindowsMediaPlayer1.playState == WMPLib.WMPPlayState.wmppsTransitioning))
            {
                lbSongsList.Items[curPlaying].BackColor = Color.White;             // 恢复上一个    
            }
        }

                // 将歌曲单写入磁盘文件

        private void HeabPlayer1_FormClosing(object sender, FormClosingEventArgs e)
        {
            StreamWriter sw = new StreamWriter(System.AppDomain.CurrentDomain.SetupInformation.ApplicationBase + "HeabPlayList.txt", true);
            // 利用StreamWriter类的构造函数创建流写入器对象, 当文件不存在的时候, 流写入器自动创建一个文件
            // 第二个true表示流写入器将添加内容不会覆盖原来的内容

            for (int i = 0; i < lbSongsList.Items.Count; i++)
            {
                sw.WriteLine(lbSongsList.Items[i].SubItems[1].Text);    
            }

            sw.Close();
        }
                
                // 读取磁盘歌单文件
            
        private void HeabPlayer1_Load(object sender, EventArgs e)
        {
            StreamReader sr = null;
            try
            {
                sr = new StreamReader(System.AppDomain.CurrentDomain.SetupInformation.ApplicationBase + "HeabPlayList.txt", false);
            }
            catch (Exception)
            {

                MessageBox.Show(System.AppDomain.CurrentDomain.SetupInformation.ApplicationBase + "HeabPlayList.txt 文件丢失, 请创建一个!");
            }
            
            string str = null;
            
            try
            {
                while ((str = sr.ReadLine()) != null)
            {
                string[] listViewItem = new string[2];
                listViewItem[0] = str.Substring(str.LastIndexOf("\\") + 1);
                listViewItem[1] = str;
                ListViewItem lv1 = new ListViewItem(listViewItem);
                lbSongsList.Items.Add(lv1);
            }
            }
            catch (Exception)
            {
                MessageBox.Show(System.AppDomain.CurrentDomain.SetupInformation.ApplicationBase + "HeabPlayList.txt 文件被非法修改, 歌单数据可能有损失!");
            }
            
            sr.Close();
        }

        //private void lbSongsList_SelectedIndexChanged(object sender, EventArgs e)
        //{
        // axWindowsMediaPlayer1.URL = paths[lbSongsList.SelectedIndex];
        //}

        //private void axWindowsMediaPlayer1_PlayStateChange(object sender, AxWMPLib._WMPOCXEvents_PlayStateChangeEvent e)
        //{
        //if (axWindowsMediaPlayer1.playState == WMPLib.WMPPlayState.wmppsStopped)
        //{
        //    axWindowsMediaPlayer1.URL = paths[lbSongsList.SelectedIndex];
        //    axWindowsMediaPlayer1.Ctlcontrols.play();
        //    //WMPLib.IWMPMedia3 firstMedia = (WMPLib.IWMPMedia3)axWindowsMediaPlayer1.mediaCollection.getAll().get_Item(1 );
        //    //axWindowsMediaPlayer1.currentMedia = firstMedia;

        //    //MessageBox.Show(axWindowsMediaPlayer1.currentPlaylist.name);
        //    //axWindowsMediaPlayer1.Ctlcontrols.play();
        //}
        //}
    }
}
