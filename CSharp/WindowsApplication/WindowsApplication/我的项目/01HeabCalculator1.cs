using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;

namespace WindowsApplication.我的项目
{
    public partial class _01HeabCalculator1 : Form
    {
        // 输入输出控制器
        private _01HeabCalculatorIO HCIO;
        // 构造函数
        public _01HeabCalculator1()
        {
            InitializeComponent();
            // 将计算器的屏幕交给输入输出控制器控制
            HCIO = new _01HeabCalculatorIO(ref txtBoxShow);
        }
        // 加载主窗体事件
        private void _01HeabCalculator1_Load(object sender, EventArgs e)
        {
            
        }
        // 按下About
        private void bntAbout_Click(object sender, EventArgs e)
        {
            AboutForm about = new AboutForm();
            about.lblMainText = "HeabCalculator1";
            about.Show();
        }
        // 按下数字键
        private void bntNum_Click(object sender, EventArgs e)
        {
            Console.Beep();
            HCIO.addFactor(sender);
        }
        // 按下运算符
        private void bntOperator_Click(object sender, EventArgs e)
        {
            Console.Beep();
            HCIO.addOpe(sender);
        }
        // 按下退格符
        private void bntDel_Click(object sender, EventArgs e)
        {
            Console.Beep();
            HCIO.delOneChar();
        }
        // 按下等于键
        private void bntEqaul_Click(object sender, EventArgs e)
        {
            Console.Beep();
            HCIO.endOne(sender);
        }

        private void bntX_Click(object sender, EventArgs e)
        {
            HCIO.changeFuHao();
        }
    }

}
