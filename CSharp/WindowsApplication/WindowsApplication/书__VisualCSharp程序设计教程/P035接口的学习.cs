// Build: 2014-09-18 12:54:31
// 结构和类的区别: 
//      1. 结构是值类型   所以结构变量可以不使用new来初始化  C#的结构之间不能继承
//      2. 类是引用类型   必须使用new运算符来进行初始化
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
    public partial class P035接口的学习 : Form
    {
        public P035接口的学习()
        {
            InitializeComponent();
        }

        private void P035接口的学习_Load(object sender, EventArgs e)
        {
            this.Text = "P035接口的学习";
        }

        // 声明接口         接口声明中不能包含任何实现语句
        interface IStudent
        {
            string Answer();
        }

        // 声明类实现接口
        class Student : IStudent
        {
            public int no;
            public string name;
            public string Answer()
            {
                string result = "该学生的信息如下: ";
                result += "\n学号: " + no;
                result += "\n姓名: " + name;
                return result;
            }
        }

        private void okBnt_Click(object sender, EventArgs e)
        {
            Student a = new Student();
            a.no = Convert.ToInt32(numTxtBox.Text);
            a.name = nameTxtBox.Text;
            showLbl.Text = a.Answer();
        }
    }
}
