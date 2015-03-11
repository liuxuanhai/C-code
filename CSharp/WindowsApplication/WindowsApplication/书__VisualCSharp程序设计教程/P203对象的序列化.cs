// Build: 2014-9-25 18:07:13
// 对象的序列化: 把对象转换为可保存或传输的格式的过程
using System.Collections;
using System.Windows.Forms;
using System;
using System.IO;
using System.Runtime.Serialization.Formatters.Binary;

namespace WindowsApplication
{
    public partial class P203对象的序列化 : Form
    {
        public P203对象的序列化()
        {
            InitializeComponent();
        }

        private StudentList list = new StudentList();   // 声明一个学生列表
        private int i = 0;  // i用来标记即将加入列表中的学生的个数, 也代表学生的个数



        private void P203对象的序列化_Load(object sender, EventArgs e)
        {

        }

        // 添加: 把学生的数据信息添加到数据列表中(内存)
        private void btnAdd_Click(object sender, EventArgs e)
        {
            Student student = new Student(txtNum.Text, txtName.Text, txtDepartment.Text);
            list[i] = student;  // 把学生添加到列表中
            i++;
        }
        // 保存: 把学生列表序列化在写入磁盘文件
        private void bntSave_Click(object sender, EventArgs e)
        {
            string file = @"d:\C#程序设计\student.dat";
            Stream stream = new FileStream(file, FileMode.OpenOrCreate, // FileMode.Open, FileMode.Append
                FileAccess.Write);
            BinaryFormatter bf = new BinaryFormatter(); // 创建序列化对象
            bf.Serialize(stream, list); // 把学生列表序列化并写入流中
            stream.Close();
        }
        // 显示: 先读取磁盘文件, 在反序列化得到学生列表, 最后逐个显示学生
        private void bntShow_Click(object sender, EventArgs e)
        {
            string file = @"d:\C#程序设计\student.dat";
            Stream stream = new FileStream(file, FileMode.Open, FileAccess.Read);
            BinaryFormatter bf = new BinaryFormatter(); // 创建序列化对象
            StudentList students = (StudentList)bf.Deserialize(stream);    // 把流反序列化
            int k = 0;
            while (students[k] != null) // 逐个显示学生数据
            {
                string s_no = students[k].student_no;
                string name = students[k].name;
                string depart = students[k].department;
                string result = String.Format("{0}\t{1}\t{2}", s_no, name, depart);
                lbResult.Items.Add(result);
                k++;
            }
            stream.Close();
        }
    }

    // 学生类
    [Serializable]
    public class Student
    {
        public string student_no;
        public string name;
        public string department;

        public Student(string s_no, string name, string depart)
        {
            this.student_no = s_no;
            this.name = name;
            this.department = depart;
        }    
    }
    // 学生列表类
    [Serializable]
    public class StudentList
    {
        private Student[] list = new Student[100];
        public Student this[int index] // 索引器
        {
            get 
            {
                if (index < 0 || index >= 100)
                    return list[0];
                else
                    return list[index];
            }
            set
            {
                if (!(index < 0 || index >= 100))
                    list[index] = value;
            }
        }
    }
    
}
