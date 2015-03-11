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
    public partial class _02学生管理系统 : Form
    {
        public _02学生管理系统()
        {
            InitializeComponent();
        }

        private void 关于ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            AboutForm about = new AboutForm();
            about.lblMainText = "HeabStudentManagementSystem3.0";
            about.lbl1Text = "作者: 软件2班 何士雄";
            about.lbl2Text = "学号: 2012484119";
            about.lbl3Text = "指导老师: 王涛";
            about.Show();
        }

        private void 增加ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            _02添加学生信息 addForm = new _02添加学生信息("Add", 更新ToolStripMenuItem_Click);
            addForm.ShowDialog();
        }

        private int findNum;
        _02获取要查找的学号 findForm;
        private void 查找并操作ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            findForm = new _02获取要查找的学号(getNum);
            findForm.ShowDialog();
            addForm.Focus();
        }

        _02添加学生信息 addForm;
        private void getNum()
        {
            findNum = findForm.getNum();
            addForm = new _02添加学生信息("Search", 更新ToolStripMenuItem_Click);
            addForm.findAndOperator(findNum);
        }

        private void _02学生管理系统_Load(object sender, EventArgs e)
        {
            更新ToolStripMenuItem_Click(null, null);
        }

        public void 更新ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            DataSet dataSet1 = new DataSet();
            string path = System.Environment.CurrentDirectory + "\\02学生数据信息.xml";
            dataSet1.ReadXml(path);
            dataGridView1.DataSource = dataSet1.Tables[0];
        }
    }
}
