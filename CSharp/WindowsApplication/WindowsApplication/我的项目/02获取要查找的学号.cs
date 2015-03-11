using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsApplication.我的项目
{
    public partial class _02获取要查找的学号 : Form
    {
        public delegate void MyDelegate();
        MyDelegate delegageFunGetNum;
        public _02获取要查找的学号(MyDelegate fun)
        {
            InitializeComponent();
            delegageFunGetNum = fun;
        }

        private void bntSearch_Click(object sender, EventArgs e)
        {
            if (textBox1.Text != "")
            {
                delegageFunGetNum();
            }
            Close();
        }

        public int getNum()
        {
            return Convert.ToInt32(textBox1.Text);
        }

        private void _02获取要查找的学号_Load(object sender, EventArgs e)
        {
            textBox1.Text = "0";
        }
    }
}
