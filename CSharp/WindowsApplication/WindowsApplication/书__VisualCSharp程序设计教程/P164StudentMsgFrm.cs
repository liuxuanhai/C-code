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
    public partial class P164StudentMsgFrm : Form
    {
        public P164StudentMsgFrm()
        {
            InitializeComponent();
        }

        private void StudentMsgFrm_Load(object sender, EventArgs e)
        {
            rdoMale.Checked = true;     // 默认选择性别为男
            cboDept.SelectedIndex = 0;  // 初始选择组合框中的第一项"计算机系"
        }

        private void cboDept_SelectedIndexChanged(object sender, EventArgs e)
        {
            switch (cboDept.SelectedItem.ToString())
            {
                case "计算机系":
                    lstSpec.Items.Clear();  // 清除列表框中的所有选项
                    lstSpec.Items.Add("计算机科学与技术");
                    lstSpec.Items.Add("信息与计算科学");
                    break;
                case "微电子技术系":
                    lstSpec.Items.Clear();  // 清除列表框中的所有选项
                    lstSpec.Items.Add("集成电路与集成系统");
                    lstSpec.Items.Add("集成电路设计与继承系统");
                    break;
                case "电子信息工程系":
                    lstSpec.Items.Clear();  // 清除列表框中的所有选项
                    lstSpec.Items.Add("通信工程");
                    lstSpec.Items.Add("电子信息工程");
                    lstSpec.Items.Add("电磁场与无线技术");
                    lstSpec.Items.Add("机械设计制造及其自动化");
                    break;
                case "经济与管理工程系":
                    lstSpec.Items.Clear();  // 清除列表框中的所有选项
                    lstSpec.Items.Add("国际经济与贸易");
                    lstSpec.Items.Add("电子商务");
                    lstSpec.Items.Add("信息管理与信息系统");
                    lstSpec.Items.Add("财务管理");
                    break;
                case "图形艺术系":
                    lstSpec.Items.Clear();  // 清除列表框中的所有选项
                    lstSpec.Items.Add("数字动画");
                    lstSpec.Items.Add("影视动画");
                    lstSpec.Items.Add("商用插画");
                    break;
                default:
                    lstSpec.Items.Clear();
                    lstSpec.Items.Add("暂无");
                    break;
            }
            lstSpec.SelectedIndex = 0;
        }

        private void btnYes_Click(object sender, EventArgs e)
        {
            string sex = "";
            if (rdoMale.Checked)
                sex = rdoMale.Text;
            else
                sex = rdoFemale.Text;
            string dept = cboDept.SelectedItem.ToString();
            string spect = lstSpec.SelectedItem.ToString();
            string hobby = "";
            if (checkBox1.Checked)
                hobby += checkBox1.Text;
            if (checkBox2.Checked)
                hobby += ", " + checkBox2.Text;
            if (checkBox3.Checked)
                hobby += ", " + checkBox3.Text;
            if (checkBox4.Checked)
                hobby += ", " + checkBox4.Text;
            if (checkBox5.Checked)
                hobby += ", " + checkBox5.Text;
            if (checkBox6.Checked)
                hobby += ", " + checkBox6.Text;
            string studentMessage = "您的姓名是: " + 
                txtName.Text + "\n性别为: " + sex +
                "\n您是" + dept + "系" + spect + 
                "专业的学生\n您的兴趣是: " + hobby;
            MessageBox.Show(studentMessage, "学生信息", MessageBoxButtons.OK,
                MessageBoxIcon.Information);
        }

        private void btnClose_Click(object sender, EventArgs e)
        {
            this.Close();
        }
    }
}
