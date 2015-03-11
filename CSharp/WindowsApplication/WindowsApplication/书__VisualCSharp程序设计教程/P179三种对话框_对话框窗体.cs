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
    public partial class P179三种对话框_对话框窗体 : Form
    {
        public string message;
        public P179三种对话框_对话框窗体()
        {
            InitializeComponent();
        }

        private void P179三种对话框_对话框窗体_Load(object sender, EventArgs e)
        {
            label1.Text = message;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        
    }
}
