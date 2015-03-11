// Build: 2014-10-20 13:14:50
// TextBoxBase => TextBox, RichTextBox, MaskedTextBox
// TextBoxBase:
//      1.  MultiLine   是否允许多行, 每一行都是字符串的 !一部分!
//      2.  Lines       每行字符串数组 Type: public string []
//      3.  Text        整个文本框内容
//      4.  TextLength  文本字符串总长度
//      5.  MaxLength   限制文本框字符串长度
//      6.  SelectedText, SelectionLength, SelectionStart处理当前选中的文本
// TextBox:
//      7.  AcceptsReturn = true; 按回车键会在文本框中新建一行 AcceptsReturn = false; 按回车键激活窗体上的默认按钮;
//      8.  CharactorCasing确定文本框中文本的大小写 Lower, 使所有输入小写, Upper把所有转换为大写. Normal把文本显示为输入时的形式
//      9.  PasswordChar
// RichTextBox: 一个文本编辑控件
//      10. Selection属性:    SelectionFont, SelectionColor, SelectionBullet可以修改格式, SelectionIndent, SelectionRightIndent, SelectionHangingIndent可以修改段落格式
//                            所有Selection属性的工作方式都相同, 如果有一段突出显示的文本, 对Selection属性的修改就影响选中的文本, 否则这些修改对当前插入点后边的文本起作用
//      11. Text返回控件的文本 Rtf属性返回带格式的文本
//      12. LoadFile()方法用两种不同的方式从文件中加载文本  
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

namespace WindowsApplication.书__CSharp高级编程
{
    public partial class P1190TextBox控件 : Form
    {
        public P1190TextBox控件()
        {
            InitializeComponent();
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void P1190_TextBox控件_Load(object sender, EventArgs e)
        {   
            txtBoxMulti1.Text = "我是TextBox, 属性是MultiLine为true, 每行都是一个字符串数组";    // MultiLine = true;
                // 说明直接给Text赋值并不会在分行的地方分txtbox.lines    

            textBox1.Text = "我是TextBox, 属性是MultiLine为true, 每行都是一个字符串数组";
            textBox2.Text = txtBoxMulti1.Lines[0] + "";

            string[] tempLines = { "我是第一行", "我是第二行" };
            txtBoxMulti2.Lines = tempLines;
            textBox3.Text = txtBoxMulti2.Lines[0];
            textBox4.Text = txtBoxMulti2.Text;  // 说明TextBox.Text是所有lines组成的一个字符串

            // RichTextBox:
            DirectoryInfo path = new DirectoryInfo(Environment.CurrentDirectory);
            string s = path.Parent.Parent.FullName + "\\书  CSharp高级编程\\P1190测试LoadFile.txt";
            richTextBox1.LoadFile(s, RichTextBoxStreamType.PlainText);
                // s可以是路径 + 文件名或者流对象
                // RichTextBoxStreamType: PlainText 没有格式信息 RichNoOleObjs Rich文本格式, 但是不包含OLE对象已经包含的空格 RichText 格式化的RTF, 且包含OLE对象 TextTextOleObjs 纯文本, 用文本替换OLE对象 UnicodePlainText 与PlainText相同, 但是编码为Unicode
        }

        private void textBox2_TextChanged(object sender, EventArgs e)
        {

        }

        private void label1_Click(object sender, EventArgs e)
        {

        }
    }
}
