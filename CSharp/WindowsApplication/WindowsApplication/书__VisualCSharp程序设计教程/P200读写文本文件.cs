// Build: 2014-09-22 12:19:28
using System;
using System.IO;
using System.Windows.Forms;

namespace WindowsApplication
{
    public partial class P200读写文本文件 : Form
    {
        public P200读写文本文件()
        {
            InitializeComponent();
        }

        private void bntAdd_Click(object sender, EventArgs e)
        {
            StreamWriter sw = new StreamWriter(@"d:\C#程序设计\abc.txt", true);
                // 利用StreamWriter类的构造函数创建流写入器对象, 当文件不存在的时候, 流写入器自动创建一个文件
                // 第二个true表示流写入器将添加内容不会覆盖原来的内容

            sw.WriteLine(txtContent.Text);
            sw.Close();
        }

        private void bntShow_Click(object sender, EventArgs e)
        {
            StreamReader sr = new StreamReader(@"d:\C#程序设计\abc.txt");
            txtResult.Text = sr.ReadToEnd();
            sr.Close();
        }

        private void P200读写文本文件_Load(object sender, EventArgs e)
        {

        }
    }
}
