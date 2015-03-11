// Build: 2014-09-25 19:44:03
using System;
using System.IO;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Runtime.Serialization.Formatters.Binary;

namespace WindowsApplication
{
    public partial class P206OpenFileDialog : Form
    {
        public P206OpenFileDialog()
        {
            InitializeComponent();
        }

        private void bntOpen_Click(object sender, EventArgs e)
        {
            openFileDialog1.ShowDialog();   // 打开文件对话框
        }

        private void openFileDialog1_FileOk(object sender, CancelEventArgs e)
        {
            txtFileName.Text = openFileDialog1.FileName;    // 返回选中的文件名
            Stream stream = openFileDialog1.OpenFile();     // 打开选中的文件
            BinaryFormatter bf = new BinaryFormatter();     // 创建序列化对象
            StudentList students = (StudentList)bf.Deserialize(stream); // 把流反向序列化
            int k = 0;
            while (students[k] != null) // 逐个显示学生列表中的数据
            {
                string s_no = students[k].student_no;
                string name = students[k].name;
                string depart = students[k].department;
                string result = String.Format("{0}\t{1}\t{2}", s_no, name, depart);
                lbResult.Items.Add(result);
                k++;
            }
            stream.Close();
        }
    }
}
