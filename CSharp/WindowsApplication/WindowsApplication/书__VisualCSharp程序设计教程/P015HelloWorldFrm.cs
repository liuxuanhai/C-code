using System;   // 使用using关键字(在C++中是指令)把.net Framework中的类库相对应的命名空间应用过来
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
    public partial class P015HelloWorldFrm : Form
    {
        public P015HelloWorldFrm()
        {
            InitializeComponent();
        }

        private void HelloWorldFrm_Load(object sender, EventArgs e)
        {
            this.Text = "P015 具有输入功能的HelloWorld";                    // this主窗口部件, this.Text就是窗口部件的标题

            Label lblShow = new Label();

            lblShow.Location = new Point(50, 30);   // 设置部件的位置
            lblShow.AutoSize = true;                // 自动大小确保把所有文字都显示出来
            lblShow.Text = "Hello, C# World!";

            this.Controls.Add(lblShow);             // 将部件添加到窗体中
        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void okBtn_Click(object sender, EventArgs e)
        {
            string result = nameTxtBox.Text + "先生, 你好!";
            showLabel.Text = result;
        }
    }
}
