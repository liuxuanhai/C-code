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
    public partial class P146windows窗体与事件驱动 : Form
    {
        public P146windows窗体与事件驱动()
        {
            InitializeComponent();
        }

        // 自动把该事件方法与控件的TextChanged事件绑定起来
        private void txtSource_TextChanged(object sender, EventArgs e)
        {
            lblTarget.Text = "正在输入: " + txtSource.Text;
        }

        private void P146windows窗体与事件驱动_Load(object sender, EventArgs e)
        {

        }
    }
}
