using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Xml;

namespace WindowsApplication.我的项目
{
    public partial class _02添加学生信息 : Form
    {
        XmlNode FindOne = null;     // 保存查找到的学生信息
        XmlDocument doc;
        XmlNode root;
        public delegate void updateFun(object sender, EventArgs e);
        updateFun upf;
        public _02添加学生信息(string flag, updateFun f)
        {
            upf = f;
            InitializeComponent();
            if (flag == "Add")
            {
                bntDel.Visible = false;
                bntOk.Text = "增加";
                bntOk.Size = new System.Drawing.Size(75, 140);
            }
            else if (flag == "Search")
            {
                this.Text = "删除 修改 等操作...";
                bntOk.Text = "关闭";
                bntDel.Visible = true;
            }
            else
            {
                MessageBox.Show("初始化 Form: 添加学生信息 时给了错误的参数");
            }
        }
        private void bntOk_Click(object sender, EventArgs e)
        {
            if (((Button)sender).Text == "关闭")
            {
                this.Close();
            }
            else if (((Button)sender).Text == "增加")
            {
                if (txtBoxName.Text == "")
                {
                    MessageBox.Show("添加失败, 学生名字为必填内容");
                    return;
                }
                addXml();
                MessageBox.Show("添加成功!");
                Close();
            }
            else if (((Button)sender).Text == "修改")
            {
                updateXml();
                MessageBox.Show("修改成功!");
                this.Close();
            }
            else
            {
                MessageBox.Show("无效的bntOk.Text");
            }
        }
        private void _02添加学生信息_Load(object sender, EventArgs e)
        {
            comboBox1.SelectedIndex = 0;    // 默认显示 "汉族"
        }
        #region 把内存中的xml树保存到文件中
        private void addXml()
        {
            XmlDocument doc = new XmlDocument();
            string path = System.Environment.CurrentDirectory + "\\02学生数据信息.xml";
            doc.Load(path);
            XmlNode root = doc.SelectSingleNode("学生们");
            XmlElement node学生 = doc.CreateElement("学生");   // 创建一个节点
            XmlElement node学号 = doc.CreateElement("学号");
            node学号.InnerText = (Convert.ToInt32(root.LastChild.FirstChild.InnerText) + 1).ToString();
            XmlElement node姓名 = doc.CreateElement("姓名");
            node姓名.InnerText = txtBoxName.Text;
            XmlElement node性别 = doc.CreateElement("性别");
            node性别.InnerText = rbntMan.Checked ? "男" : "女";
            XmlElement node生日 = doc.CreateElement("生日");
            node生日.InnerText = dateTimePicker1.Text;
            XmlElement node民族 = doc.CreateElement("民族");
            node民族.InnerText = comboBox1.SelectedItem.ToString();
            XmlElement node地址 = doc.CreateElement("地址");
            node地址.InnerText = txtBoxAddress.Text;
            node学生.AppendChild(node学号);
            node学生.AppendChild(node姓名);
            node学生.AppendChild(node性别);
            node学生.AppendChild(node生日);
            node学生.AppendChild(node民族);
            node学生.AppendChild(node地址);           
            root.AppendChild(node学生);

            doc.Save(path);
        }
        #endregion
        #region 修改xml
        private void updateXml()
        {
            if (FindOne == null)
            {
                MessageBox.Show("无法确定要修改的对象是哪个!");
            }
            else
            {
                System.Collections.IEnumerator iterator = FindOne.GetEnumerator();
                iterator.MoveNext();    // 学号
                iterator.MoveNext();    // 姓名
                ((XmlNode)iterator.Current).InnerText = txtBoxName.Text;
                iterator.MoveNext();    // 性别
                ((XmlNode)iterator.Current).InnerText = rbntMan.Checked ? "男" : "女";
                iterator.MoveNext();    // 生日
                ((XmlNode)iterator.Current).InnerText = dateTimePicker1.Text;
                iterator.MoveNext();    // 民族
                ((XmlNode)iterator.Current).InnerText = comboBox1.SelectedItem.ToString();
                iterator.MoveNext();    // 地址
                ((XmlNode)iterator.Current).InnerText = txtBoxAddress.Text;

                string path = System.Environment.CurrentDirectory + "\\02学生数据信息.xml";
                doc.Save(path);
            }
        }
        #endregion
        #region 获取一个学号, 将xml文件中此学号的学生放到窗口中
        public void findAndOperator(int findNum)
        {
            doc = new XmlDocument();
            string path = System.Environment.CurrentDirectory + "\\02学生数据信息.xml";
            doc.Load(path);
            root = doc.SelectSingleNode("学生们");
            
            foreach (XmlNode item in root)
            {
                if (item.FirstChild.InnerText == findNum.ToString())
                {
                    FindOne = item;
                    break;
                }
            }
            if (FindOne != null)
            {
                System.Collections.IEnumerator NodePointer = FindOne.GetEnumerator();
                NodePointer.MoveNext(); // 赋值完毕后指向的不是第一个而是第一个前边的一个位置, 这里MoveNext一下就指向了第一个
                NodePointer.MoveNext(); // 姓名
                txtBoxName.Text = ((XmlNode)NodePointer.Current).InnerText;
                NodePointer.MoveNext();
                if (((XmlNode)NodePointer.Current).InnerText == "男")
                    rbntMan.Checked = true;
                else
                    rbntWoman.Checked = true;
                NodePointer.MoveNext();
                dateTimePicker1.Text = ((XmlNode)NodePointer.Current).InnerText;
                NodePointer.MoveNext();
                int i;
                for (i = 0; i < comboBox1.Items.Count; i++)
                {
                    if (comboBox1.Items[i].ToString() == ((XmlNode)NodePointer.Current).InnerText)
                        break;
                }
                NodePointer.MoveNext();
                txtBoxAddress.Text = ((XmlNode)NodePointer.Current).InnerText;
                Show(); // 这里把combox1中的设置成了汉族 下边的语句可能设置成了其他
                if (i >= 4)
                    MessageBox.Show("((XmlNode)NodePointer.Current).InnerText 在 02添加学生信息.comboBox1.Items 中不存在");
                else
                    comboBox1.SelectedIndex = i;
            }
            else
            {
                FindOne = null;
                MessageBox.Show("查无此人!");
            }
                
        }

        #endregion

        private void txtBoxName_TextChanged(object sender, EventArgs e)
        {
            if (bntOk.Text == "关闭")
                bntOk.Text = "修改";    
        }
        #region 删除xml信息
        private void bntDel_Click(object sender, EventArgs e)
        {
            if (FindOne == null)
            {
                MessageBox.Show("无法确定要删除的对象是哪个!");
            }
            else
            {
                root.RemoveChild(FindOne);

                string path = System.Environment.CurrentDirectory + "\\02学生数据信息.xml";
                doc.Save(path);
            }
            MessageBox.Show("删除成功!");
            this.Close();
        }
        #endregion

        #region 关闭窗口要更新主窗口信息
        private void _02添加学生信息_FormClosed(object sender, FormClosedEventArgs e)
        {
            upf(null, null);
        }
        #endregion
    }
}
