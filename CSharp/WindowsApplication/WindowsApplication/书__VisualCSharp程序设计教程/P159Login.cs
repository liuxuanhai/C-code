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
    public partial class P159Login : Form
    {
        public P159Login()
        {
            InitializeComponent();
        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void btnYes_Click(object sender, EventArgs e)
        {
            string username = txtName.Text;
            string password = txtPwd.Text;
            if (username == "admin" && password == "admin")
            {
                MessageBox.Show("欢迎进入成绩管理系统!", "登录成功",
                    MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
            else
            {
                MessageBox.Show("您输入的用户名或者密码错误!", "登录失败",
                    MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
            }
        }

        private void btnCancel_Click(object sender, EventArgs e)
        {
            // 清除输入的信息, 将光标放在txtName上
            txtName.Text = "";
            txtPwd.Text = "";
            txtName.Focus();
        }

        private void P159Login_Load(object sender, EventArgs e)
        {
            txtName.Focus();
        }
    }
}
