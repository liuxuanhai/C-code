// Build: 2014-10-20 13:14:50
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
    public partial class 显示模块测试 : Form
    {
        public 显示模块测试()
        {
            InitializeComponent();
        }

        private void AppendLineBnt_Click(object sender, EventArgs e)
        {
            string [] temp = new string[textBox1.Lines.Length + 1]; // 多分配一一行
            for (int i = 0; i < textBox1.Lines.Length; i++ )        // 克隆原来的值
                temp[i] = textBox1.Lines[i];
            temp[textBox1.Lines.Length] = "1";          // 给新行赋值
            textBox1.Lines = temp;                      // 更新显示
            textBox1.Select(textBox1.TextLength, 0);    // 光标定位到文本最后
            textBox1.ScrollToCaret();                   // 滚动到光标处
        }

        private void HeabCalculator1_Load(object sender, EventArgs e)
        {
            string[] t = { "11", "2"};
            textBox1.Lines = t;
        }

        private void PushCharBnt_Click(object sender, EventArgs e)
        {
            string[] temp = new string[textBox1.Lines.Length];         // 分配一样大
            for (int i = 0; i < textBox1.Lines.Length - 1; i++)        // 克隆原来的值
                temp[i] = textBox1.Lines[i];
            temp[textBox1.Lines.Length - 1] = "+" + textBox1.Lines[textBox1.Lines.Length - 1];
            textBox1.Lines = temp;                      // 更新显示
            textBox1.Select(textBox1.TextLength, 0);    // 光标定位到文本最后
            textBox1.ScrollToCaret();                   // 滚动到光标处
        }

        private void PopCharBnt_Click(object sender, EventArgs e)
        {
            string[] temp = new string[textBox1.Lines.Length];         // 分配一样大
            for (int i = 0; i < textBox1.Lines.Length - 1; i++)        // 克隆原来的值
                temp[i] = textBox1.Lines[i];
            try
            {
                temp[textBox1.Lines.Length - 1] = textBox1.Lines[textBox1.Lines.Length - 1].Remove(0, 1);
            }
            catch (System.ArgumentOutOfRangeException)
            {
                MessageBox.Show("你还想删除什么呢, 都叫你删干净了");
            }
            textBox1.Lines = temp;                      // 更新显示
            textBox1.Select(textBox1.TextLength, 0);    // 光标定位到文本最后
            textBox1.ScrollToCaret();                   // 滚动到光标处
        }
    }
}
