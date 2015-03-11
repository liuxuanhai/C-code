// Build: 2014-09-22 13:01:15

using System;
using System.Windows.Forms;
using System.IO;

namespace WindowsApplication
{
    public partial class P202读写二进制文件 : Form
    {
        public P202读写二进制文件()
        {
            InitializeComponent();
        }

        private void lblSave_Click(object sender, EventArgs e)
        {
            FileStream fs = new FileStream(@"d:\C#程序设计\student.dat", FileMode.Append, FileAccess.Write);
                // 创建一个文件流对象
                // 文件模式:    FileMode.Append打开现有文件并查找文件尾(如果文件不存在则创建新文件)
                // 文件操作方式:FileAccess.Write表示写文件      

            BinaryWriter bw = new BinaryWriter(fs);
                // 通过文件流对象创建BinaryWriter写入器对象

            // 把文本框中的数据写入文件流
            bw.Write(textBox1.Text);
            bw.Write(textBox2.Text);
            bw.Write(textBox3.Text);

            fs.Close();
            bw.Close();
        }

        private void btnShow_Click(object sender, EventArgs e)
        {
            FileStream fs = new FileStream(@"d:\C#程序设计\student.dat", FileMode.Open, FileAccess.Read);
            BinaryReader br = new BinaryReader(fs);
            fs.Position = 0;
            while (fs.Position != fs.Length)
            {
                string s_no = br.ReadString();
                string name = br.ReadString();
                string depart = br.ReadString();
                string result = string.Format("{0}\t{1}\t{2}", s_no, name, depart);
                lbResult.Items.Add(result);
            }
            br.Close();
            fs.Close();
        }
    }
}
