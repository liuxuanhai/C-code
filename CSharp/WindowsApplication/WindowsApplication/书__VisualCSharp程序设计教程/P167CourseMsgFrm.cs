using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

// Build: 2014-09-21 10:19:33
namespace WindowsApplication
{
    public partial class P167CourseMsgFrm : Form
    {
        string courseName;
        string courseClass;
        string required;
        int credit;
        int prelectionCredit;
        int experimentCredit;

        public P167CourseMsgFrm()
        {
            InitializeComponent();
        }

        private void btnNext_Click(object sender, EventArgs e)
        {
            // 如果课程名为空或者课程类别未选择, 则弹出对话框告知用户
            if (txtName.Text == "" || cboClass.SelectedIndex < 0 ||
                (rdoRequired.Checked == false && rdoElective.Checked == false))
                MessageBox.Show("输入信息不完整!", "信息不完整", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
            else
                tabControl1.SelectedTab = tabPage2; // 显示"确认信息"选项卡
        }

        private void tabControl1_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (tabControl1.SelectedIndex == 1)
            {
                if (txtName.Text == "" || cboClass.SelectedIndex < 0 ||
                    (rdoRequired.Checked == false && rdoElective.Checked == false))
                {
                    MessageBox.Show("输入信息不完整!", "信息不完整", 
                        MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                    tabControl1.SelectedTab = tabPage1;
                }
                else 
                {
                    courseName = txtName.Text;
                    courseClass = cboClass.SelectedItem.ToString();
                    required = rdoRequired.Checked ? "必修" : "选修";
                    credit = (int)nudCredit.Value;
                    prelectionCredit = (int)nudPrelection.Value;
                    experimentCredit = (int)nudExpt.Value;
                    string message = String.Format("课程名: {0}\n课程类别: {1}\n课程性质: {2}\n学分: {3}\n理论学时: {4}\n实验学时: {5}", courseName, courseClass, required, credit, prelectionCredit, experimentCredit);
                    richTextBox1.Text = message;
                }
            }
        }

        private void tabPage1_Click(object sender, EventArgs e)
        {
            
        }

        private void P167CourseMsgFrm_Load(object sender, EventArgs e)
        {
            cboClass.SelectedIndex = 0;
        }
    }
}
