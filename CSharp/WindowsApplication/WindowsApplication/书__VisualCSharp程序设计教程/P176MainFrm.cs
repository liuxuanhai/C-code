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
    public partial class P176MainFrm : Form
    {
        public P176MainFrm()
        {
            InitializeComponent();
        }

        private void P176MainFrm_Load(object sender, EventArgs e)
        {
             
        }

        private void tsmExit_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void tsmNewStudent_Click(object sender, EventArgs e)
        {
            P164StudentMsgFrm studentMsgFrm = new P164StudentMsgFrm();  // 创建子窗体对象
            studentMsgFrm.MdiParent = this;     // 指定当前窗体为MDI父窗体
            studentMsgFrm.Show();               // 打开子窗体
            tssMsg.Text = studentMsgFrm.Text;   // 在状态栏中显示操作内容 
        }

        private void tsmAbout_Click(object sender, EventArgs e)
        {
            P170AboutForm aboutForm = new P170AboutForm();
            string temp = tssMsg.Text;
            tssMsg.Text = aboutForm.Text; // 在模态窗体生成之前在状态栏显示
            aboutForm.ShowDialog();             // 打开窗体, 该窗体是一个模态窗体
            tssMsg.Text = temp;                 // 恢复
        }

        private void tsmNewCourse_Click(object sender, EventArgs e)
        {
            P167CourseMsgFrm courseMsgFrm = new P167CourseMsgFrm();
            courseMsgFrm.MdiParent = this;
            courseMsgFrm.Show();
            tssMsg.Text = courseMsgFrm.Text;
        }
    }
}
