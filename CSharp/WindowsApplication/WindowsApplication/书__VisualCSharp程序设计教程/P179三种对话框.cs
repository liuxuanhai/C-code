// Build: 2014-09-21 15:21:36
// 三种对话框: 模态对话框使用frm.ShowDialog显示, 非模态对话框用frm.Show显示
//      1.  模态对话框:  弹出的时候鼠标不能单击对话框之外的区域
//      2.  非模态对话框:比如查找对话框
//      3.  通用对话框:  从用户获取信息, 如文件名
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
    public partial class P179三种对话框 : Form
    {
        public P179三种对话框()
        {
            InitializeComponent();
        }

        private void lbl1_Click(object sender, EventArgs e)
        {
            P179三种对话框_对话框窗体 frm = new P179三种对话框_对话框窗体();
            frm.message = "这是一个模态对话框!";
            frm.ShowDialog();
        }

        private void P179三种对话框_Load(object sender, EventArgs e)
        {

        }

        private void lbl2_Click(object sender, EventArgs e)
        {
            P179三种对话框_对话框窗体 frm = new P179三种对话框_对话框窗体();
            frm.message = "这是一个非模态对话框!";
            frm.Show();
        }
    }
}
